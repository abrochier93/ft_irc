#ifndef __CHANNEL_H__
#define __CHANNEL_H__


#include "Libs.hpp"


class Channel
{
private:
	string 				_name;
	string 				_topic;
	string 				_password;			// mode +k

	vector<User *>			_channelUsers;
	vector<User *>			_operators;			// mode +o

	//mode
	bool						_isInviteOnly;		// mode +i
	vector<User *>			_inviteList;
	bool						_topicRestriction;	// mode +t
	int							_userLimit;			// mode +l

public:
	Channel();
	Channel(string name, User * creator, string pass);
	Channel(string name, User * creator);
	~Channel();

	// **** OPERATORS ****

	bool		operator==(Channel const & rhs) const;

	// **** METHODS ****
	void				addUser(User * u);
	void				addOperator(User * u);

	void				removeUser(User * u);
	void				removeOperator(User * op);

	void				sendToChannel(string message);
	void 				sendToChannelExcept(string message, User * except);
	void				addToWhiteList(User * newUser);
	void				RemoveFromWhiteList(User * newUser);

	// **** GETTERS ****

	const string &	getName() const;
	const string &	getTopic() const;
	const string &	getPassword() const;
	bool			isOperator(User * u) const;
	bool			isInviteOnly() const;
	bool			isTopicRestricted() const;
	bool			isInvited(User * u) const;
	bool			isInChannel(User * u) const;
	int				countUsers() const;
	int				getUserLimit() const;
	bool 			isWhitelisted(User * u);
	const string	getUserList();

	// **** SETTERS ****

	void	setTopic(const string & new_topic);
	void	setPassword(const string & new_pass); // mode +k 123
	void	setUserLimit(int userLimit);
	void 	setInviteOnlyOn();
	void 	setInviteOnlyOff();
	void 	setTopicRestriction(bool state);
};

#endif // __CHANNEL_H__