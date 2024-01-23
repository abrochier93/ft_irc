#ifndef __Pass_Command_H__
#define __Pass_Command_H__

#include "Libs.hpp"

class Server;
class User;
class Pass_Command : public ACommand
{
	private:
		string _password;

	public:
		Pass_Command( string msg, Server &server, User *sender);
		~Pass_Command();

		bool	parse();
		void	execute();
};

#endif // __Pass_Command_H__
