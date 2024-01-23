#include "Commands/CommandFactory.hpp"

CommandFactory::CommandFactory()
{
}

CommandFactory::~CommandFactory()
{
}

ACommand *CommandFactory::getCommand(string msg, Server &serv, User * u)
{
	const string cmds[] = { "NICK", "USER", "JOIN", "PASS", "TOPIC", "PRIVMSG", "PART", "INVITE", "KICK", "MODE", "QUIT", "NULL"};
	ACommand * (CommandFactory::*f[])(string, Server&, User*) = {
		&CommandFactory::NickFactory,
		&CommandFactory::UserFactory,
		&CommandFactory::JoinFactory,
		&CommandFactory::PassFactory,
		&CommandFactory::TopicFactory,
		&CommandFactory::PrivmsgFactory,
		&CommandFactory::PartFactory,
		&CommandFactory::InviteFactory,
		&CommandFactory::KickFactory,
		&CommandFactory::ModeFactory,
		&CommandFactory::QuitFactory

	};
	
	// MODE
	// MODE blablalba
	// MODEdjsajdsaj
	for (int i = 0; cmds[i] != "NULL"; i++)
	{
		size_t cmd_len = cmds[i].length();
		string cmd_check = msg.substr(0, cmd_len);
		if (msg.length() == cmd_len && msg == cmds[i])
			return (this->*(f[i]))(msg, serv, u);
		if ( msg.length() > cmd_len && !isspace( msg.at(cmd_len)))
			continue ;
		if (cmd_check == cmds[i])
			return (this->*(f[i]))(msg.substr(cmd_len + 1), serv, u);
		
	}
	return NULL;
}

ACommand *CommandFactory::NickFactory(string msg, Server &server, User * sender)
{
	return (new Nick_Command(msg, server, sender));
}

ACommand *CommandFactory::UserFactory(string msg, Server &server, User * sender)
{
	return (new User_Command(msg, server, sender));
}

ACommand *CommandFactory::JoinFactory(string msg, Server &server, User * sender)
{
	return (new Join_Command(msg, server, sender));
}

ACommand *CommandFactory::PassFactory(string msg, Server &server, User * sender)
{
	return (new Pass_Command(msg, server, sender));
}

ACommand *CommandFactory::TopicFactory(string msg, Server &server, User * sender)
{
	return (new Topic_Command(msg, server, sender));
}

ACommand *CommandFactory::PrivmsgFactory(string msg, Server &server, User * sender)
{
	return (new Privmsg_Command(msg, server, sender));
}

ACommand *CommandFactory::PartFactory(string msg, Server &server, User * sender)
{
	return (new Part_Command(msg, server, sender));
}

ACommand *CommandFactory::InviteFactory(string msg, Server &server, User * sender)
{
	return (new Invite_Command(msg, server, sender));
}

ACommand *CommandFactory::KickFactory(string msg, Server &server, User * sender)
{
	return (new Kick_Command(msg, server, sender));
}

ACommand *CommandFactory::ModeFactory(string msg, Server &server, User * sender)
{
	return (new Mode_Command(msg, server, sender));
}

ACommand *CommandFactory::QuitFactory(string msg, Server &server, User * sender)
{
	return (new Quit_Command(msg, server, sender));
}
