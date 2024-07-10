#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdPong(){
	if (splitted[2] != users[uindex].getHostName())
	{
		send_client(users[uindex].getSocket() ,create_code_msg("402", uindex, users[uindex].getHostName() + " :No such server"));
		return;
	}
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i].getNickName() == splitted[1])
		{
			send_client(users[i].getSocket(), ":" + users[uindex].getHostName() + " PONG " + users[uindex].getHostName() + " :" + splitted[1] + "\r\n");
			return ;
		}
	}
	create_code_msg("409", uindex,":No origin specified");
}
