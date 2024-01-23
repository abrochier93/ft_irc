// https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.3

#include "Commands/User_Command.hpp"

User_Command::User_Command(string msg, Server &server, User * sender): ACommand(server, sender, msg), _username(""), _realname("")
{
	std::cout << "User command created" << std::endl;
}

User_Command::~User_Command()
{
	
}

bool User_Command::parse()
{
	stringstream ss(_msg);
	string username;

	ss >> _username;
	if (!_username.empty() && _username.at(0) == ':')
		return ERROR;  
	ss >> _realname >> _realname >> _realname;
	if (_realname.at(0) == ':')
	{
		string temp;
		while (ss >> temp)	
			_realname += " " + temp;
	}
	return SUCCESS;
}

void User_Command::execute()
{
	string msg;

	// if (!_sender->) check pass
	// 	return ; // ERR OR DISCONNECT
	if (parse() == ERROR)
	{
		msg = errorMessage(461, "USER", "0", "0"); //AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); //AJOUT ALEX
		return ; // ERR 
	}
	_sender->setUsername(_username);
	_sender->setName(_realname);
	if (_sender->isConnected())//AJOUT ALEX
	{
		msg = errorMessage(462, "0", "0", "0"); //AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); //AJOUT ALEX
		return ; //AJOUT ALEX
	}
	if (!_sender->isConnected() && !_sender->getUsername().empty() && !_sender->getName().empty())
		_connectUser();
}
