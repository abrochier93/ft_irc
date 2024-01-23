#ifndef __SERVER_H__
#define __SERVER_H__


#include "Libs.hpp"

class Channel;
class User;

class Server
{
	private:
		vector<struct pollfd>	_fds;
		list<User>				_users;
		vector<Channel>			_channels;
		string					_password;
		addrinfo				*_servinfo;

		bool check_password(char *buf);
		void disconnect_userList(User * user);
		void disconnect_fdList(User * user);

	public:
		Server();
		Server(string password);
		~Server();

		void init();
		void listenForEvents();

		void new_client();
		void new_channel(string channelName, User * sender, string password);
		void new_server(int fd);
		void handle_event(int fd);

		void disconnect_user(User * user);
		void removeChannel(Channel & c);
		void partUserFromChannel(User * u, Channel * c);

		bool isNickTaken(string const & nick);
		bool isChannelExist(string const &channel); //AJOUT ALEX
		const string &getPassword() const;
		User *getUser(int fd);
		User *getUser(string nick);
		Channel *getChannel(string channel_name);
		vector<Channel *> getUserChannels(User * user);
		void joinExistingChannel(User * u, Channel &chan);

		// void handle_client(int new_fd);

		// void leaveChannel(User &u, string msg);
		// void joinExistingChannel(User &u, Channel &chan);
		// void joinChannel(User &u, pair<string, string> chan);
		// void connectClient(User *u);
		// void sendMessage(User &u , string message);
		// void changeMode(User &u , string message);

		// void new_client();
		// void new_client(int fd);
		// void disconnect_user(int client_i);
		// void parse_UserCommandinfo(int client_i, string parseUserInfo);

		// //utils
		// void createChannelMsg(User &u, string chan) const;
		// void getAndJoinChannels(User &u, string channels);

		// User	*getUser(int fd);
		// User	*getUser(string nick);

		// void 		setPassword(string newPassword);
		// const char	*getPassword()	const;
		// int			getSocket()		const;

		// 	//AJOUT DE ALEX // 
		// void kickChannels(User &u, string str);
		// void skipWhitespace(string &str);
		// bool isUser(string UserCommandto_kick, string channel_name);
		// bool userExist(string UserCommandto_invite);
		// bool channelExist(string channel_name);
		// void inviteChannels(User &u, string str);
};


#endif // __SERVER_H__