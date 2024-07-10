#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdInvite(){
	if (splitted.size() != 3)
	{
		send_client(users[uindex].getSocket(), create_code_msg("461", uindex, "INVITE :Not enough parameters"));
		return ;
	}
	size_t idx = Channel::isChannel(vChannel, splitted[2]);
	if (idx == std::string::npos)
		send_client(users[uindex].getSocket(), create_code_msg("403", uindex, splitted[2] + " :No such channel"));
	else if (vChannel[idx].isUsrOnChnl(users[uindex]) == false)
		send_client(users[uindex].getSocket(), create_code_msg("442", uindex, splitted[2] + " :You're not on that channel"));
	else if (!(users[uindex].getIsHaveMode('o') || vChannel[idx].isOperator(users[uindex])))
		send_client(users[uindex].getSocket(), create_code_msg("442", uindex, splitted[2] + " :You're not channel operator"));
	else if (CommandRunner::findUserWithNick(splitted[1]) != std::string::npos && vChannel[idx].isUsrOnChnl(users[CommandRunner::findUserWithNick(splitted[1])]))
		send_client(users[uindex].getSocket(), create_code_msg("443", uindex, splitted[2] + " :is already on channel"));
	else if (findUser(splitted[1]) != -1)
	{
		send_client(users[uindex].getSocket(), create_code_msg("341", uindex, splitted[1] + " " + splitted[2]));
		send_client(users[findUser(splitted[1])].getSocket(), create_msg(splitted[0] + " " + splitted[1] + " " + splitted[2]));
		vChannel[idx].addUserToInvite(users[findUser(splitted[1])]);
	}
}
