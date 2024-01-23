#include "Libs.hpp"
#include "Commands/ACommand.hpp"

// ACommand::ACommand()
// {
	
// }

ACommand::ACommand(Server & server, User * sender, string msg): _server(server), _sender(sender), _msg(msg)
{
	
}

ACommand::~ACommand()
{
	
}

void ACommand::_connectUser()
{
	string msg001 = ":127.0.0.1 001 " + _sender->getNick() + " :Welcome to the Internet Relay Network\r\n";
	string msg002 = ":127.0.0.1 002 " + _sender->getNick() + " :Your host is ft_irc, running version 0.1\r\n";
	string msg003 = ":127.0.0.1 003 " + _sender->getNick() + " :This server was created NOW\r\n";
	string msg004 = ":127.0.0.1 004 " + _sender->getNick() + " 127.0.0.1 ft_irc0.1 * itkol\r\n";

	send(_sender->getFd(), msg001.c_str(), msg001.length(), 0);
	send(_sender->getFd(), msg002.c_str(), msg002.length(), 0);
	send(_sender->getFd(), msg003.c_str(), msg003.length(), 0);
	send(_sender->getFd(), msg004.c_str(), msg004.length(), 0);
	_sender->setConnected(true);
}

