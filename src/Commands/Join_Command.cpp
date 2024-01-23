// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.1

#include "Commands/Join_Command.hpp"

Join_Command::Join_Command(string msg, Server &server, User * sender) : ACommand(server, sender, msg)
{
	
}

Join_Command::~Join_Command()
{
	
}

bool Join_Command::parse()
{
	pair<string, string> pair;
	string channels;
	string passwords;
	string channel_token;
	string password_token;

	channels = _msg.substr(0, _msg.find(' '));
	if (_msg.find(' ') != string::npos)
		passwords = _msg.substr(_msg.find(' '));

	stringstream channel_stream(channels);
	stringstream password_stream(passwords);

	while (std::getline(channel_stream, channel_token, ','))
	{
		if (!std::getline(password_stream, password_token, ','))
			password_token = "";

		pair.first = channel_token;
		pair.second = password_token;
		_channelNamePass.push_back(pair);
	}
	return SUCCESS;//error case???
}

// void joinChannel()
// {

// }

bool Join_Command::passIsOk(Channel *channel, string password)
{
	if (password == channel->getPassword())
		return SUCCESS;
	return ERROR;
}

void Join_Command::joinChannel(pair<string, string> *channel_name_pass)
{
	string msg;

	_channel = _server.getChannel(channel_name_pass->first);
	_channelName = channel_name_pass->first;
	_password = channel_name_pass->second;

	if (_channel == NULL)//si le _channel n'existe pas
	{
		// createChannel()
		_server.new_channel(_channelName, _sender, _password);
		_server.joinExistingChannel(_sender, *_server.getChannel(_channelName));
		//send client _channel created message !!!
	}
	else if (_channel->isInviteOnly() && !_channel->isWhitelisted(_sender)) //bouncer
	{
		// is not whitelisted message !!!
	}
	else if (!passIsOk(_channel, _password))
	{
		// wrong _channel password message !!!
	}
	else // join
	{
		_channel->addUser(_sender);
		_server.joinExistingChannel(_sender, *_channel);
		_channel->RemoveFromWhiteList(_sender);
	}
}

void Join_Command::execute()
{
	// vector< pair<string, string> >::iterator it  = _channelNamePass.begin();
	if (parse() == ERROR)
		return ;
	if (!_sender->isConnected())
	{
		std::cout << "Cannot join, user not connected" << std::endl;
		return ;
	}
	for (vector< pair<string, string> >::iterator it  = _channelNamePass.begin(); it != _channelNamePass.end(); it++)
	{
		joinChannel(&(*it));
	}
}