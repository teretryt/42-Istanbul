#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdPass(){
	if (splitted.size() < 2)
	{
		send_client(users[uindex].getSocket(), create_code_msg("461", uindex, "PASS :Not enough parameters"));
		return ;
	}
	if (users[uindex].getVerify() == 1)
	{
		send_client(users[uindex].getSocket(), create_code_msg("462", uindex, ":You may not reregister"));
		return ;
	}
	std::string tmp = splitted[1].erase(0, 1);
	users[uindex].setVerify(tmp, irc.password);
}
