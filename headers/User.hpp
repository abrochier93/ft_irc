#ifndef __USER_H__
#define __USER_H__


#include "Libs.hpp"

class User
{
	private:
		string					_nick; 
		string					_username;
		string					_realname;
		string					_ip;
		string					_port;
		bool					_pass_ok;	// !! Initialise a true si pas de server pass
		bool					_connected;
		int						_fd;
		struct sockaddr_storage	*_sock;
		string					_buffer;

	public:
		User();
		User(int fd, struct sockaddr *cl);
		~User();

		bool	operator==(User const & rhs) const;
		void clean_buffer(size_t *trail);

		//get
		const string&			getNick() const;
		const string&			getUsername() const;
		const string&			getName() const;
		const string&			getIp()	const;
		const string&			getPort() const;
		const string			getID() const;
		int						getFd() const;
		struct sockaddr_storage	*getSock();
		string					getBuffer() const;
		bool					isFirstMsg() const;
		bool					isConnected() const;
		bool					isPassAccepted() const;
		
		//set
		void		setNick(string const & nick);
		void		setUsername(string const & username);
		void		setName(string const & name);
		void		setIp();
		void		setFd(int fd);
		void		msgReceived();
		void		setConnected(bool is_connected);
		void		setBuffer(char *buf);
		void		setSock(struct sockaddr_storage *s);
		void		passwordAccepted();
	};



#endif // __USER_H__