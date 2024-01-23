#ifndef __PRIVMSG_COMMAND_H__
#define __PRIVMSG_COMMAND_H__

#include "Libs.hpp"

class Privmsg_Command : public ACommand
{
	private:
		Channel 	*_channel;
		User	 	*_user;
		string	_message;

		bool channel_is_ok(string name);
		bool user_is_ok(string name);

	public:
		Privmsg_Command( string msg, Server &server, User *sender );
		~Privmsg_Command();
		
		bool parse();
		void execute();
};

#endif // __PRIVMSG_COMMAND_H__
