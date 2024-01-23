// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.7

#include "Commands/Invite_Command.hpp"

Invite_Command::Invite_Command(string msg, Server &server, User * sender) : ACommand(server, sender, msg)
{
}

Invite_Command::~Invite_Command()
{
}


bool Invite_Command::parse()
{
	string userName;
	string channelName;

	userName = _msg.substr(0, ' ');
	_userToInvite = _server.getUser(userName);
	if (_userToInvite == NULL)
	{
		// User not found message !!!
		return ERROR;
	}

	channelName = _msg.substr(' ');
	_channel = _server.getChannel(channelName);
	if (_channel == NULL)
	{
		// Channel not found message !!!
		return ERROR;
	}

	if (!_channel->isInviteOnly())
	{
		// no need to invite message !!!
		return ERROR;
	}

	if (!_channel->isOperator(_sender))
	{
		// Don't have Operator rights message !!!
		return ERROR;
	}

	if (_channel->isInChannel(_userToInvite))
	{
		// User already in the channel !!!
		return ERROR;
	}

	return SUCCESS;
}

void Invite_Command::execute()
{
	if (parse() == ERROR)
		return ;
	_channel->addToWhiteList(_userToInvite);
	//added to whitelist message !!!
}