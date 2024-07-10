#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdPart(){
	if (splitted.size() < 2){
		send_client(users[uindex].getSocket(), create_code_msg("461", uindex, "PART :Not enough parameters"));
		return ;
	}
	std::vector<std::string> chNames = split(splitted[1], ',');
	for (size_t i = 0; i < chNames.size(); i++)
	{
		size_t k = Channel::isChannel(vChannel, chNames[i]);
		if (k == std::string::npos){
			send_client(users[uindex].getSocket(), create_code_msg("403", uindex, chNames[i] + " :No such channel"));
			continue;
		}
		if (!vChannel[k].isUsrOnChnl(users[uindex])){
			send_client(users[uindex].getSocket(), create_code_msg("442", uindex, chNames[i] + " :You're not on that channel"));
			continue;
		}
		vChannel[k].delUserChnl(users.at(uindex));
		std::string msg = ":" + users[uindex].getNickName() + "!" + this->users[uindex].getUserName() + "@"+this->users[uindex].getHostName()+ " PART " + chNames[i] + "\r\n";
		send_client(this->users[uindex].getSocket(), msg);
		vChannel[k].send_channel_message(this->users[uindex], msg);
		updateChannel(k);
	}
}
