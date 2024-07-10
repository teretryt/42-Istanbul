#pragma once
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <vector>
#define MAX_CHANNEL_IN 10

class Client
{
private:
	int					_socket;
	bool				verify;
	bool				invisible;
	std::string			nickName;
	std::string			userName;
	std::string			realName;
	std::string			hostName;
	std::vector<char>	modes;
public:
	//CONSTURCTERS
	Client();
	Client(const Client& copy);

	//SETTER FUNCTIONS
	void		setSocket(const int _socket);
	void		setVerify(const std::string& cli_pass, const std::string& pass);
	void		setInvisible(const bool& invisible);
	void		setNickName(const std::string& nickname);
	void		setUserName(const std::string& username);
	void		setRealName(const std::string& realname);
	void		setHostName(const std::string& hostname);
	void		addMode(const char mode);
	void		removeMode(const char mode);
	//GETTER FUNCTIONS
	const int&			getSocket();
	const bool&			getVerify();
	const bool&			getInvisible();
	const std::string&	getNickName();
	const std::string&	getUserName() const;
	const std::string&	getRealName();
	const std::string&	getHostName() const;
	std::string			getMods();
	bool				getIsHaveMode(const char mode);
	//OPERATOR OVRL
	bool			operator==(Client const& client);

	Client &operator=(const Client& right);
	~Client();
};

std::ostream &operator<<(std::ostream& os, const Client& client);
