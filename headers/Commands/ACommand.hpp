#ifndef __ACOMMAND_H__
#define __ACOMMAND_H__

# include "Libs.hpp"

class Server;
class User;
class ACommand
{
	protected:
		Server	& _server;
		User	* _sender;
		string	_msg;

		void	_connectUser();

	public:
		// ACommand();
		ACommand(Server & server, User * sender, string msg);
		virtual ~ACommand();

		virtual void	execute() = 0;
};

#endif // __ACOMMAND_H__
