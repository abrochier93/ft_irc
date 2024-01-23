#ifndef __COMMANDFACTORY_H__
#define __COMMANDFACTORY_H__

#include "Libs.hpp"

class ACommand;
class CommandFactory
{
	private:
		ACommand *NickFactory(string, Server&, User*);
		ACommand *UserFactory(string, Server&, User*);
		ACommand *JoinFactory(string, Server&, User*);
		ACommand *PassFactory(string, Server&, User*);
		ACommand *TopicFactory(string, Server&, User*);
		ACommand *PrivmsgFactory(string, Server&, User*);
		ACommand *PartFactory(string, Server &, User *);
		ACommand *InviteFactory(string, Server &, User *);
		ACommand *KickFactory(string, Server &, User *);
		ACommand *ModeFactory(string, Server &, User *);
		ACommand *QuitFactory(string, Server &, User *);

	public:
		CommandFactory();
		~CommandFactory();

		ACommand *getCommand(string msg, Server &serv, User * u);
};

#endif // __COMMANDFACTORY_H__
