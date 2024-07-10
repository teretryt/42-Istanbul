#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdWho(){
	if (splitted.size() < 2){
		send_client(this->users[uindex].getSocket(), create_code_msg("461", uindex, splitted[0] + " :Not enough parameters"));
		return ;
	}
	if (splitted[1][0] == '#'){
		size_t idx = Channel::isChannel(vChannel, splitted[1]);
		if (idx == std::string::npos)
			return ;
		for (size_t i = 0; i < users.size(); i++){
			if (!vChannel[idx].isUsrOnChnl(users[i]))
				continue;
			if (users[i].getInvisible() == false){
				std::string msg = vChannel[idx].getName() + " " + users[i].getUserName() + " " + users[i].getHostName() + " ircserv " + users[i].getNickName() + " H" ;
				if (users[i].getIsHaveMode('o') || vChannel[idx].isOperator(users[i]))
					msg += "*";
				msg += " :0 " + users[i].getRealName();
				send_client(users[uindex].getSocket() ,create_code_msg("352", uindex, msg));
			}
		}
	}else{
		int i = findUser(splitted[1]);
		if (i != -1 && !users[i].getInvisible()){
			std::string chnList = "";
			for (size_t j = 0; j < vChannel.size(); j++){
				if (vChannel[j].isUsrOnChnl(users[i]))
					chnList += vChannel[j].getName() + ",";
			}
			if (chnList.size() > 0)
				chnList.erase(chnList.length() - 1, 1);
			else
				chnList = "*";
			std::string msg = chnList + " " + users[i].getUserName() + " " + users[i].getHostName() + " ircserv " + users[i].getNickName() + " H" ;
			if (users[i].getIsHaveMode('o'))
				msg += "*";
			msg += " :0 " + users[i].getRealName();
			send_client(users[uindex].getSocket() ,create_code_msg("352", uindex, msg));
		}
	}
	send_client(users[uindex].getSocket() ,create_code_msg("315", uindex, users[uindex].getHostName() + " :End of WHO list"));
}
