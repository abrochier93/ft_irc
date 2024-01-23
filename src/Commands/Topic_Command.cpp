// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.4

#include "Commands/Topic_Command.hpp"

Topic_Command::Topic_Command(string msg, Server &server, User * sender) : ACommand(server, sender, msg), _new_topic("")
{
}

Topic_Command::~Topic_Command()
{
}

bool Topic_Command::parse()
{
	stringstream	ss(_msg);
	string			arg;
	string 			msg; 

	//ss >> arg;
	if (_msg.empty() || !(ss >> arg) || arg == ":")
	{
		msg = errorMessage(461, "TOPIC", "0", "0"); // AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  //AJOUT ALEX
		return ERROR; // ERR need more args
	}
	_channel = _server.getChannel(arg);
	if (!_channel)
	{
		msg = errorMessage(403, arg, "0", "0"); // AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); // AJOUT ALEX
		return ERROR; // ERR CHANNEL NOT FOUND
	}
	if (_channel->isInChannel(_sender) == false)
	{
		msg = errorMessage(442, arg, "0", "0"); // AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); // AJOUT ALEX
		return ERROR; // ERR NOT ON CHANNEL
	}

	ss >> _new_topic;
	if (_new_topic.empty())
		_action = SHOW;
	else if (_new_topic == ":")
		_action = CLEAR;
	else
	{
		_action = CHANGE;
		if (_new_topic.at(0) == ':')
		{
			string temp;
			while (ss >> temp)
				_new_topic += " " + temp;
			_new_topic = _new_topic.substr(1);
		}
	}
	return SUCCESS;
}

void Topic_Command::execute()
{
	string msg;

	if (parse() == ERROR)
		return ;
	switch (_action)
	{
	case SHOW:
		std::cout << "TOPIC :" << _channel->getTopic() << std::endl; // !!! RPL_TOPIC au user
		break;
	case CLEAR:
		// Check mode +t
		// Check isOperator si restriction
		if (_channel->isTopicRestricted() && _channel->isOperator(_sender) == false)
		{
			msg = errorMessage(482, _channel->getName(), "0", "0");
			send(_sender->getFd(), msg.c_str(), msg.length(), 0);
			break;
		}
		_new_topic = "";
	case CHANGE:
		if (_channel->isTopicRestricted() && _channel->isOperator(_sender) == false)
		{
			msg = errorMessage(482, _channel->getName(), "0", "0");
			send(_sender->getFd(), msg.c_str(), msg.length(), 0);
			break;
		}
		std::cout << "TOPIC set to :" << _new_topic << std::endl;
		_channel->setTopic(_new_topic);
		break;
	
	default:
		break;
	}
}
