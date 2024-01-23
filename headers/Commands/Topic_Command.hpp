#ifndef __TOPIC_COMMAND_H_
#define __TOPIC_COMMAND_H_

#include "Libs.hpp"

class Server;
class User;
class Topic_Command : public ACommand
{
	private:
		typedef enum e_action
		{
			SHOW,	//	/TOPIC #channel
			CHANGE,	//	/TOPIC #channel :Supa channel ou /TOPIC #channel Cool
			CLEAR	//	/TOPIC #channel :
		} t_action;

		string _new_topic;
		Channel *	_channel;
		t_action	_action;

	public:
		Topic_Command(string msg, Server &server, User *sender);
		~Topic_Command();

		bool	parse();
		void	execute();
};

#endif // __TOPIC_COMMAND_H_
