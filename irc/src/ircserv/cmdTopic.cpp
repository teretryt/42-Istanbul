#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdTopic(){
	if (splitted.size() < 2){
		send_client(this->users[uindex].getSocket(), create_code_msg("461", uindex, splitted[0] + " :Not enough parameters"));
		return ;
	}
 	size_t i = returnChannelIndex(splitted[1]);
	if (i == std::string::npos){
		send_client(this->users[uindex].getSocket(), create_code_msg("403", uindex, splitted[1] + " :No such channel"));
		return ;
	}
	if (vChannel[i].isUsrOnChnl(this->users[this->uindex]) == false){
		send_client(this->users[uindex].getSocket(), create_code_msg("442", uindex, splitted[1] + " :You're not on that channel"));
		return ;
	}
	if (splitted.size() == 2){
		if (vChannel[i].getTopic().length() == 0)
			send_client(this->users[uindex].getSocket(), create_code_msg("331", uindex, splitted[1] + " :No topic is set"));
		else
			send_client(this->users[uindex].getSocket(), create_code_msg("332", uindex, splitted[1] + " :" + vChannel[i].getTopic()));
		return ;
	}
	if (!(users[uindex].getIsHaveMode('o') || vChannel[i].isOperator(users[uindex])) && vChannel[i].isHaveMode('t')){
		send_client(this->users[uindex].getSocket(), create_code_msg("482", uindex, splitted[1] + " :You're not channel operator"));
		return ;
	}
	if (splitted.size() >= 3){
		std::vector<std::string>::iterator it = splitted.begin();
		std::advance(it, 2);
		std::string merge  = mergeMsg(it, std::distance(it, splitted.end()));
		std::string msg = ":" + users[uindex].getNickName() + "!" + this->users[uindex].getUserName() + "@" + this->users[uindex].getHostName() + " " + splitted[0] + " " + splitted[1] + " :" + merge + "\r\n";
		send_client(this->users.at(uindex).getSocket(), msg);
		vChannel[i].sendMessageToChannel(this->users[uindex], msg);
		vChannel[i].setTopic(merge);
	}

}
