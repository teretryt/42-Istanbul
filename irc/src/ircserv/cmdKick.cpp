#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdKick(){
	if (splitted.size() < 3){
		send_client(this->users[uindex].getSocket(), create_code_msg("461", uindex, splitted[0] + " :Not enough parameters"));
		return ;
	}
	size_t idx = Channel::isChannel(vChannel, splitted[1]);
	if (idx == std::string::npos)
		send_client(users[uindex].getSocket(), create_code_msg("403", uindex, splitted[1] + " :No such channel"));
	else if (!(users[uindex].getIsHaveMode('o') || vChannel[idx].isOperator(users[uindex])))
		send_client(users[uindex].getSocket(), create_code_msg("482", uindex, splitted[1] + " :You're not channel operator"));
	else if (!(CommandRunner::findUser(splitted[2]) != -1 && vChannel[idx].isUsrOnChnl(users[CommandRunner::findUser(splitted[2])])))
		send_client(users[uindex].getSocket(), create_code_msg("441", uindex, splitted[2] + " " + splitted[1] + " :They aren't on that channel"));
	else if (vChannel[idx].isUsrOnChnl(users[uindex]) == false)
		send_client(users[uindex].getSocket(), create_code_msg("442", uindex, splitted[2] + " :You're not on that channel"));
	else{
		std::string comment = " :";
		int i = CommandRunner::findUser(splitted[2]);
		if (splitted.size() > 3){
			std::vector<std::string>::iterator it = splitted.begin();
			std::advance(it, 3);
			comment += mergeMsg(it, std::distance(it, splitted.end()));
		}else
			comment += "NOTHING";
		std::string msg = create_msg("KICK " + splitted[1] + " " + splitted[2] + comment);
		vChannel[idx].delUserChnl(users[i]);
		send_client(users[i].getSocket(), msg);
		vChannel[idx].send_channel_message(users[i], msg);
		updateChannel(idx);
	}
}
