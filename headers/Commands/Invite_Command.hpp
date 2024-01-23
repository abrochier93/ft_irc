#ifndef __INVITE_COMMAND_H__
#define __INVITE_COMMAND_H__

#include "Libs.hpp"

class Server;
class User;
class Invite_Command : public ACommand
{
	private:
		User	*_userToInvite;
		Channel	*_channel;

	public:
		Invite_Command();
		Invite_Command(string msg, Server &server, User *sender);
		~Invite_Command();

		bool parse();
		void execute();
};

#endif // __INVITE_COMMAND_H__
