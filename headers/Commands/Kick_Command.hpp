#ifndef __KICK_COMMAND_H__
#define __KICK_COMMAND_H__

#include "Libs.hpp"

class Kick_Command : public ACommand
{
	private:
		vector<Channel *>	_channels;
		vector<User *>	_users;
		string			_message;

		bool has_operator_rights();
		void parse_message(stringstream &separator_stream);
		bool parse_channels(stringstream &separator_stream);
		bool parse_users(stringstream &separator_stream);
		string formatMessage(Channel *channel, User *user);

	public:
		Kick_Command(string msg, Server &server, User *sender);
		~Kick_Command();

		bool parse();
		void execute();
};

#endif // __KICK_COMMAND_H__
