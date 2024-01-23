// https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.2

#include "Commands/Nick_Command.hpp"

Nick_Command::Nick_Command(string msg, Server &server, User * sender): ACommand(server, sender, msg)
{
	std::cout << "Nick command created" << std::endl;
}

Nick_Command::~Nick_Command()
{
	
}

bool Nick_Command::parse()
{
	if (_msg.empty())
		return ERROR;
	else if (_msg.at(0) == ':')
		return ERROR;
	_new_nick = _msg;
	return SUCCESS;
}

void Nick_Command::execute()
{
	std::string msg; //AJOUT ALEX

	if (!_sender->isPassAccepted())
	{
		std::cout << "User has not entered password yet." << std::endl;
		return ; // ERR OR DISCONNECT
	}
	if (parse() == ERROR)
	{
		msg = errorMessage(431, "0", "0", "0"); //AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); //AJOUT ALEX
		return ; // ERR MSG
	}
	if (_server.isNickTaken(_new_nick))
	{
		msg = errorMessage(433, _new_nick, "0", "0"); //AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); //AJOUT ALEX
		return ; // !!! ERR NICK TAKEN
	}


	//REMARQUE ALEX 
	// ERREUR 484
	// Sent by the server to a user upon connection to indicate
    //the restricted nature of the connection (user mode "+r").


	// Broadcast aux channels du user: "old_nick is now known as new_nick" et resend la list des users
	vector<Channel *> channels = _server.getUserChannels(_sender);
	vector<Channel *>::iterator it;
	for (it = channels.begin(); it != channels.end(); it++)
	{
		string msg = _sender->getID() + " NICK " + _new_nick + "\r\n";
		(*it)->sendToChannel(msg);
	}
	_sender->setNick(_new_nick);

	// Connect user s'il n'est pas connecte
	if (!_sender->isConnected() && !_sender->getUsername().empty() && !_sender->getName().empty())
		_connectUser();
}