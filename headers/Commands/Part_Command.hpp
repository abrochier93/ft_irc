#ifndef __Part_Command_H__
#define __Part_Command_H__

#include "Libs.hpp"

class Part_Command : public ACommand
{
	private:
		vector<Channel *>		_channelsToPart;
		string					_partMessage;

	public:
		Part_Command(string msg, Server &server, User *sender);
		~Part_Command();

		void fillChannels(string channelStringList);

		bool parse();
		void execute();
};

#endif //__Part_Command_H__
