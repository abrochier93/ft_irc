// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.2

#include "Commands/Part_Command.hpp"

Part_Command::Part_Command(string msg, Server &server, User * sender) :
ACommand(server, sender, msg),
_partMessage("")
{

}

Part_Command::~Part_Command()
{
}

// Split une liste de channels en string "#chan1,#chan2" vers une list d'instance Channel
// existants si le user est dans le channel
void Part_Command::fillChannels(string fillChannelsList)
{
	std::istringstream	iss(fillChannelsList);
	string			chanName;
	string			msg;

	while (std::getline(iss, chanName, ','))
	{
		Channel * c;
		c = _server.getChannel(chanName);
		if (!c)
		{
			// !!! ERR_NOSUCHCHANNEL
			msg = errorMessage(403, chanName, "0", "0"); //AJOUT ALEX
			send(_sender->getFd(), msg.c_str(), msg.length(), 0); //AJOUT ALEX
			continue ;
		}
		else if (!c->isInChannel(_sender))
		{
			// !!! ERR_NOTONCHANNEL
			msg = errorMessage(442, chanName, "0", "0"); //AJOUT ALEX
			send(_sender->getFd(), msg.c_str(), msg.length(), 0); //AJOUT ALEX
			continue ;
		}
		else
			_channelsToPart.push_back(c);
	}
}

bool Part_Command::parse()
{
	string msg;

	if (_msg.empty())
	{
		msg = errorMessage(461, "PART", "0", "0"); // AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  //AJOUT ALEX
		return ERROR;
	}

	std::istringstream	iss(_msg);
	string			chanStringList;
	if (!(iss >> chanStringList) || chanStringList == ":")
	{
		msg = errorMessage(461, "PART", "0", "0"); // AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  //AJOUT ALEX 
		return ERROR;
	}

	fillChannels(chanStringList);
	if (_channelsToPart.empty())	// Liste vide, aucun channel a PART
	{
		return ERROR;
	}
	
	// Check si une raison est donnee
	if (iss >> _partMessage)
	{
		// Si le message a le sufixe ':', va chercher les mots apres espaces
		if (_partMessage.at(0) == ':')
		{
			string temp;
			while (iss >> temp)
				_partMessage += " " + temp;
			//_partMessage = _partMessage.substr(1);	// remove prefix ':'
		}
	}

	return SUCCESS;
}

void Part_Command::execute()
{
	if (parse() == ERROR)
		return ;
	
	vector<Channel *>::iterator it;
	for (it = _channelsToPart.begin(); it != _channelsToPart.end(); it++)
	{
		Channel * channel = *it;

		std::cout << "Parted channel: " << channel->getName() << std::endl;
		std::cout << "Reason: " << _partMessage << std::endl;

		string msg = _sender->getID() + " PART " + channel->getName() + " " + _partMessage + "\r\n";
		channel->sendToChannel(msg);

		_server.partUserFromChannel(_sender, channel);
	}
}