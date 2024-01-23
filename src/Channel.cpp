#include "Libs.hpp"
#include "Channel.hpp"

Channel::Channel()
{
}

Channel::Channel(string name, User * creator, string pass) :
_name(name),
_topic(""),
_password(pass),
_isInviteOnly(false),
_topicRestriction(false),
_userLimit(NO_LIMIT)
{
	this->_channelUsers.push_back(creator);
	this->_operators.push_back(creator);
}

Channel::Channel(string name, User * creator) :
_name(name),
_topic(""),
_password(""),
_isInviteOnly(false),
_topicRestriction(false),
_userLimit(NO_LIMIT)
{
	this->_channelUsers.push_back(creator);
	this->_operators.push_back(creator);
}

Channel::~Channel()
{
}

/********************
	OPERATORS
*********************/
bool	Channel::operator==(Channel const & rhs) const
{
	return this->getName() == rhs.getName();
}

/********************
	METHODS
*********************/

void	Channel::addUser(User * u)		{ _channelUsers.push_back(u); }
void	Channel::addOperator(User * u)	{ _operators.push_back(u); }

void	Channel::removeUser(User * u)
{
	vector<User *>::const_iterator it = std::find(_channelUsers.begin(), _channelUsers.end(), u);
	if (it != _channelUsers.end())
		_channelUsers.erase(it);
}

void	Channel::removeOperator(User * op)
{
	vector<User *>::const_iterator it = std::find(_operators.begin(), _operators.end(), op);
	if (it != _operators.end())
		_operators.erase(it);
}

void Channel::sendToChannel(string message)
{
	for (vector<User *>::iterator it = _channelUsers.begin(); it != _channelUsers.end(); it++)
    {
    	send((*it)->getFd(), message.c_str(), message.length(), 0);
    }
}

void Channel::sendToChannelExcept(string message, User * except)
{
	for (vector<User *>::iterator it = _channelUsers.begin(); it != _channelUsers.end(); it++)
    {
		if ((*it)->getNick() != except->getNick())
		{
    		send((*it)->getFd(), message.c_str(), message.length(), 0);
		}	
    }
}

bool Channel::isWhitelisted(User * u)
{
	for (vector<User *>::iterator it = _inviteList.begin(); it != _inviteList.end(); it++)
	{
		if (u->getNick() == (*it)->getNick())
			return true;
	}
	return false;
}

void	Channel::addToWhiteList(User * newUser)
{
	_inviteList.push_back(newUser);
}

void	Channel::RemoveFromWhiteList(User * user)
{
	vector<User *>::iterator it = _inviteList.begin();
	for (; it != _inviteList.end() ; it++)
	{
		if (user == *it)
			_inviteList.erase(it); return ;
	}
}

void Channel::setInviteOnlyOn()
{
	_isInviteOnly = true;
}

void Channel::setInviteOnlyOff()
{
	_inviteList.clear();
	_isInviteOnly = false;
}

void Channel::setTopicRestriction(bool state)
{
	_topicRestriction = state;
}


/********************
	GETTERS
*********************/

const string &	Channel::getName() const		{ return _name; }
const string & Channel::getTopic() const		{ return _topic; }
const string &	Channel::getPassword() const	{ return _password; }
bool Channel::isInviteOnly() const				{ return _isInviteOnly; }
bool Channel::isTopicRestricted() const			{ return _topicRestriction; }
int Channel::countUsers() const					{ return _channelUsers.size(); }
int	Channel::getUserLimit() const				{ return _userLimit; };

bool	Channel::isOperator(User * u) const
{
	vector<User *>::const_iterator it = std::find(_operators.begin(), _operators.end(), u);
	return (it != _operators.end());
}

bool	Channel::isInvited(User * u) const
{
	vector<User *>::const_iterator it = std::find(_inviteList.begin(), _inviteList.end(), u);
	return (it != _inviteList.end());
}

bool	Channel::isInChannel(User * u) const
{
	vector<User *>::const_iterator it = std::find(_channelUsers.begin(), _channelUsers.end(), u);
	return (it != _channelUsers.end());
}

// TODO: mettre les ops en 1er dans la liste (ou pas)
const string Channel::getUserList()
{
	vector<User *>::iterator it = _channelUsers.begin();
	string	userList = "";

	for (; it != _channelUsers.end(); it++)
	{
		string user = "";
		if (isOperator(*it))
			user += "@";
		user += (*it)->getNick();
		if (std::next(it) != _channelUsers.end())
			user += " ";
		userList += user;
	}
	return userList;
}

/********************
	SETTERS
*********************/
void	Channel::setTopic(const string & new_topic)		{ _topic = new_topic; }
void	Channel::setPassword(const string & new_pass)	{ _password = new_pass; }
void	Channel::setUserLimit(int userLimit)			{ _userLimit = userLimit; }