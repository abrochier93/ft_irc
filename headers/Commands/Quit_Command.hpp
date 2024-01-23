#ifndef __QUIT_COMMAND_H__
#define __QUIT_COMMAND_H__

#include "Libs.hpp"

class Quit_Command : public ACommand
{
	private:
		string	_msg;
		vector<Channel *> _channelsToPart;

	public:
		Quit_Command( string msg, Server &server, User *sender );
		~Quit_Command();

		void execute();
};

#endif // __PRIVMSG_COMMAND_H__
