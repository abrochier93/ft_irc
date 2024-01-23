#include "Commands/Mode_Command.hpp"
// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.3

Mode_Command::Mode_Command(string msg, Server &server, User * sender) : ACommand(server, sender, msg)
{
	_action = NONE;
	_availableModes = "itkol";
	_channel = NULL;
}

Mode_Command::~Mode_Command()
{
}

// Remplace ou ajoute un mode dans la liste
// Faire check de validite avant!
void Mode_Command::_addMode(char mode, t_operation op)
{
	std::vector<t_mode>::iterator	it;

	// Cherche si le mode est deja present et le met a jour
	for (it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->mode == mode)
		{
			it->operation = op;
			return ;
		}
	}
	// S'il le trouve pas, ajoute
	t_mode m;

	m.mode = mode;
	m.operation = op;
	_modes.push_back(m);
}


void Mode_Command::changeMode_i(t_operation op)
{
	(op == OP_ADD) ? _channel->setInviteOnlyOn() : _channel->setInviteOnlyOff();
	// MODE MSG
}

void Mode_Command::changeMode_t(t_operation op)
{
	(op == OP_ADD) ? _channel->setTopicRestriction(true) : _channel->setTopicRestriction(false);
	// MODE MSG
}

void Mode_Command::changeMode_k(t_operation op, string arg)
{
	(op == OP_ADD) ? _channel->setPassword(arg) : _channel->setPassword("");
	// MODE MSG
}

void Mode_Command::changeMode_o(t_operation op, string arg)
{
	User * target = _server.getUser(arg);

	if (!_channel->isInChannel(target)) // sais pas si c'est safe si NULL
	{
		// !!! ERR NOT IN CHANNEL
		return ;
	}

	if (op == OP_ADD && _channel->isOperator(target)) // deja op, rien faire
		return ;

	(op == OP_ADD) ? _channel->addOperator(target) : _channel->removeOperator(target);
	// MODE MSG
}

void Mode_Command::changeMode_l(t_operation op, string arg)
{
	std::istringstream iss(arg);
	int newLimit = -1;

	iss >> newLimit;
	if (op == OP_ADD)
	{
		if (newLimit >= 1 && newLimit <= 100) // Limite user?
		{
			_channel->setUserLimit(newLimit);
			// MODE MSG avec arg
		}
	}
	else
	{
		_channel->setUserLimit(NO_LIMIT);
		// MODE MSG sans arg
	}
}

bool Mode_Command::_fillModeVector(string modes)
{
	t_operation op = OP_ADD;	// si aucun signe, ajoute par defaut

	for (size_t i = 0; i < modes.length(); i++)
	{
		if (modes[i] == '+')
			op = OP_ADD;
		else if (modes[i] == '-')
			op = OP_REMOVE;
		else if (std::find(_availableModes.begin(), _availableModes.end(), modes[i]) != _availableModes.end()) // cherche le mode dans la list de modes permis
			_addMode(modes[i], op);
		else
		{
			std::cout << "ERROR " << modes[i] << " not available!!" << std::endl;
			/// !!! ERR 472 (MODE x is unavailable)
			return ERROR; // ne pas continuer
		}
	}
	return SUCCESS;
}

// montre seulement les modes actifs
void Mode_Command::_showModes()
{
	string modes = "+";

	if (_channel->isInviteOnly())
		modes += "i";
	if (_channel->isTopicRestricted())
		modes += "t";
	if (_channel->getPassword() != "")
		modes += "k";
	if (_channel->getUserLimit() > NO_LIMIT)
		modes += "l";

	if (modes != "+")
	{
		std::cout << modes << std::endl;
		// SHOW MODES MSG !!!
	}
}

bool Mode_Command::parse()
{
	std::istringstream	iss(_msg);
	string				channel;
	string				mode_str;

	if (!(iss >> channel))
	{
		// !!! ERR NO ENOUGH PARAMS
		return ERROR;
	}

	_channel = _server.getChannel(channel);
	if (!_channel)
	{
		// !!! NO SUCH CHANNER
		return ERROR;
	}
	else if (!_channel->isInChannel(_sender))
	{
		// !!! NOT IN CHANNEL
		return ERROR;
	}

	if (!(iss >> mode_str) || mode_str == ":")
	{
		_action = SHOW;
		return SUCCESS;
	}
	else
		_action = CHANGE;

	if (_fillModeVector(mode_str) == ERROR)
		return ERROR;

	string temp;
	iss >> _args;
	while (iss >> temp)
		_args += " " + temp;

	return SUCCESS;
}

void Mode_Command::execute()
{
	if (parse() == ERROR)
		return ;
	
	if (_action == SHOW)
	{
		std::cout << "Action: SHOW | Channel: " << _channel->getName() << std::endl;
		_showModes();
	}
	else if (_action == CHANGE && _channel->isOperator(_sender))
	{
		std::istringstream iss(_args);
		// itere la liste de modes pour call les fonctions
		for (vector<t_mode>::iterator it = _modes.begin(); it != _modes.end(); it++)
		{
			string arg;
			switch (it->mode)
			{
			case 'i':
				changeMode_i(it->operation);
				break;
			case 't':
				changeMode_t(it->operation);
				break;
			case 'k':
				iss >> arg;	// erreur si pas d'args, meme si c'est pour enlever le mdp (-k * pour enlever)
				changeMode_k(it->operation, arg);
				break;
			case 'o':
				iss >> arg;
				changeMode_o(it->operation, arg);
				break;
			case 'l':
				iss >> arg;
				changeMode_l(it->operation, arg);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		// ERR NOT OP !!!
	}
}