#include "../../include/ircserv/Server.hpp"

Server::Server(int ac, char **av){
	char host[256];
	if (ac != 3)
	{
		std::cerr << "Error: Usage ./ircserv <port> <password>" << std::endl;
		exit(EXIT_FAILURE);
	}
	try
	{
		this->port = std::stoi(av[1]);
		this->password  = av[2];
		if (this->port > PORT_MAX)
		{
			throw Server::PortMaxException();
		}
		else if (this->port < 0)
		{
			throw Server::PortMinException();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	gethostname(host, 256);
	this->hostname = std::string(host);
	if ((this->serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
		std::cerr << "Failed to create socket!" << std::endl;
		exit(EXIT_FAILURE);
	}else{
		std::cout << "Socket created successfully. Socket number is: " << this->serv_sock << std::endl;
	}
	//int optval = 1;
	//setsockopt(this->serv_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	memset(&(this->serv_addr), 0, sizeof(this->serv_addr));
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_addr.s_addr = INADDR_ANY;
	this->serv_addr.sin_port = htons(this->port); // Port number
	if (bind(this->serv_sock, (struct sockaddr*)&(this->serv_addr), sizeof(this->serv_addr)) == -1){
		std::cerr << "Socket not connected!" << std::endl;
		close(this->serv_sock);
		exit(EXIT_FAILURE);
	}else{
		std::cout << "Socket connected successful!" << std::endl;
	}

	if (listen(this->serv_sock, 5) == -1){
		std::cerr << "Listening failed!" << std::endl;
		close(this->serv_sock);
		exit(EXIT_FAILURE);
	}
	else{
		std::cout << "Listening successful!" << std::endl;
	}
	struct pollfd tmp;
	this->fds.push_back(tmp);
	this->fds[0].fd = this->serv_sock;
	this->fds[0].events = POLLIN;
}

Server::Server(const Server& copy){
	*this = copy;
}

Server& Server::operator=(const Server& right){
	this->serv_sock = right.serv_sock;
	return *this;
}

const char *Server::PortMaxException::what(void) const throw()
{
	return ("Error: Port max number is 65535");
};

const char *Server::PortMinException::what(void) const throw()
{
	return ("Error: Port min number is 0");
};

const std::string& Server::getHostname() const{
	return (this->hostname);
}

Server::~Server(){}
