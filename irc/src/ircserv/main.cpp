#include "../../include/ircserv/Server.hpp"
#include "../../include/ircserv/CommandRunner.hpp"

std::vector<std::string> parser(std::string& buffer);

int main(int ac, char**av)
{
	char buffer[4096];
	Server	irc(ac, av);
	socklen_t addrLen = sizeof(irc.cli_addr);
	std::vector<Client>users;
	std::vector<Channel>channel;
	CommandRunner cmdRunner(users, irc, channel, 0);
	while (1) {
		int result = poll(&(irc.fds[0]), irc.fds.size(), -1);
		if (result == -1) {
			std::cerr << "Poll failed" << std::endl;
			exit(EXIT_FAILURE);
		}
		if (irc.fds[0].revents & POLLIN) {
			irc.newSocket = accept(irc.serv_sock, (struct sockaddr*)&(irc.cli_addr), &addrLen);
			std::cout << "newsocket:" << irc.newSocket << std::endl;
			if (irc.newSocket == -1) {
				std::cerr << "Accept failed" << std::endl;
			}else{
				Client tmp;
				tmp.setSocket(irc.newSocket);
				std::string ipAddr = inet_ntoa(irc.cli_addr.sin_addr);
				std::cout << "Connecting client IP address: " << ipAddr << std::endl;
				tmp.setHostName(ipAddr);
				users.push_back(tmp);
				std::cout << "SOCKET NUM: " << users.end()->getSocket() << std::endl;
				struct pollfd tmp2;
				irc.fds.push_back(tmp2);
				irc.fds.at(irc.fds.size() - 1).fd = irc.newSocket;
				irc.fds.at(irc.fds.size() - 1).events = POLLIN;
				std::cout << "New connection established." << std::endl;
			}
		}
		for (size_t i = 1; i < irc.fds.size(); i++)
		{
			if (irc.fds[i].fd != -1 && irc.fds[i].revents & POLLIN) {
				ssize_t bytesRead = recv(irc.fds[i].fd, buffer, sizeof(buffer), 0);
				if (bytesRead <= 0) {
					std::vector<std::string> parsed;
					parsed.push_back("QUIT");
					cmdRunner.selectAndRunCom(parsed, i - 1);
					std::cout << "Connection closed." << std::endl;
				}
				else {
					buffer[bytesRead] = '\0';
					std::cout << "Received from client " << i << ":" << buffer << std::endl;
					std::string s = buffer;
					std::vector<std::string> parsed = parser(s);
					cmdRunner.selectAndRunCom(parsed, i - 1);
				}
				cmdRunner.checkCloseChannels();
			}
		}
	}
	// Close sockets
	close(irc.serv_sock);
	return 0;
}
