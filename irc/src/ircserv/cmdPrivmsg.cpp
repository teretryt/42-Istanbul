#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdPrivmsg(){
	if (splitted.size() < 2)
		send_client(users[uindex].getSocket() ,create_code_msg("411", uindex, " :No recipient given PRIVMSG"));
	else if (splitted.size() < 3)
		send_client(users[uindex].getSocket() ,create_code_msg("412", uindex, " :No text to send"));
	else
		comMsg(parsed[this->index], uindex);
}

void	CommandRunner::comMsg(std::string line, int uindex){
	std::stringstream			ss;
	std::string					word;
	std::vector<std::string>	words;
	ss << line;
	while (std::getline(ss, word, ' '))
		words.push_back(word);
	words[2].erase(0, 1);
	int i = findUser(words[1]);
	if (i == -1){
		size_t idx = Channel::isChannel(vChannel, words[1]);
		if (idx != std::string::npos && !(vChannel[idx].isHaveMode('m') && !vChannel[idx].isOperator(users[uindex]) && !users[uindex].getIsHaveMode('o'))){
			if (words[2] == "!bot" && (vChannel[idx].isOperator(users[uindex]) || users[uindex].getIsHaveMode('o'))
				&& findUserWithNick("bot") != std::string::npos && !vChannel[idx].isUsrOnChnl(users[findUserWithNick("bot")]))
			{
				int tmp = this->uindex;
				this->uindex = findUserWithNick("bot");
				joinChannel(vChannel[idx].getName());
				vChannel[idx].sendMessageToChannel(this->users[this->uindex], ":" + users[this->uindex].getNickName() + "!" +
					this->users[this->uindex].getUserName() + "@" + this->users[uindex].getHostName() + " PRIVMSG " + vChannel[idx].getName() +
						" :Bot added to channel by " + users[tmp].getNickName()  + "\r\n");
				this->uindex = tmp;
			}else
				vChannel[idx].sendMessageToChannel(this->users[uindex], ":" + users[uindex].getNickName() + "!" + this->users[uindex].getUserName() + "@" + this->users[uindex].getHostName() + " " + line + "\r\n");
		}
		if (idx == std::string::npos){
			send_client(users[uindex].getSocket() ,create_code_msg("401", uindex, words[1] + " :No such nick/channel"));
			return ;
		}
		if (vChannel[idx].isHaveMode('m') && !vChannel[idx].isOperator(users[uindex]) && !users[uindex].getIsHaveMode('o')){
			send_client(users[uindex].getSocket() ,create_code_msg("404", uindex, words[1] + " :You are not an operator, you cannot send messages!"));
			return ;
		}
		return ;
	}
	ss.clear();
	ss << line;
	std::getline(ss, word, ' ');
	std::getline(ss, word, ' ');
	std::getline(ss, word, '\0');
	word.erase(0, 1);
	send_client(users[i].getSocket(), create_msg("PRIVMSG " + words[1] + " :" + word));
}
