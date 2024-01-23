#ifndef __JOIN_COMMAND_H__
#define __JOIN_COMMAND_H__

#include "Libs.hpp"


class Server;
class User;
class Join_Command : public ACommand
{
private:
	vector< pair<string, string> > _channelNamePass;
	Channel	*_channel;
	string 	_channelName;
	string 	_password;

public:
	Join_Command(string msg, Server &server, User *sender);
	~Join_Command();
	void joinChannel(pair<string, string> *channel_name_pass);
	bool passIsOk(Channel *channel, string password);

	bool parse();
	void execute();
};

#endif // __JOIN_COMMAND_H__
