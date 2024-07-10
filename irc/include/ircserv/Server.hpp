#pragma once
#include <iostream>
#include <sys/socket.h>
	#include <netdb.h>
	#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <ctime>
#include <map>
#include <iomanip>
#include <algorithm>
#include "Client.hpp"
#include "Channel.hpp"
#include "Config.hpp"

#define PORT_MAX 65535


class Server{
	public:
		int							serv_sock;
		int							cli_sock;
		int							port;
		int							newSocket;
		std::vector<struct pollfd>	fds;
		std::string					password;
		std::string					hostname;
		sockaddr_in					serv_addr;
		sockaddr_in					cli_addr;
		Config						cfg;
		Server(int ac, char **av);
		Server(const Server &copy);
		Server& operator=(const Server& right);
		~Server();
		const std::string&	getHostname() const;
		class PortMaxException : public std::exception
		{
		public:
			virtual const char *what() const throw();
		};

		class PortMinException : public std::exception
		{
		public:
			virtual const char *what() const throw();
		};
};
