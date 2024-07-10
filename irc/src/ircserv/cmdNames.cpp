#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdNames(){
	if (splitted.size() < 2)
		send_client(users[uindex].getSocket(), create_code_msg("461", uindex, "NAMES :Not enough parameters"));
	else
	{
		std::string msg = "";
		std::vector<std::string> list = split(splitted[1], ',');
		for (size_t i = 0; i < list.size(); i++)
		{
			size_t chnIdx = Channel::isChannel(vChannel, list[i]);
			if (chnIdx != std::string::npos && !vChannel[chnIdx].getSecret() && vChannel[chnIdx].isUsrOnChnl(users[uindex])){
				msg += "= " + vChannel[chnIdx].getName() + " :";
				for (size_t j = 0; j < users.size(); j++){
					std::string prefix = "";
					if (vChannel[chnIdx].isUsrOnChnl(users[j]) == false || users[j].getInvisible())
						continue ;
					if (users[j].getIsHaveMode('o'))
						prefix = "@";
					else if (vChannel[chnIdx].isOperator(users[j]))
						prefix = "@";
					msg +=  prefix + users[j].getNickName() + " ";
				}
				msg.resize(msg.size() - 1);
				send_client(users[uindex].getSocket(), create_code_msg("353", uindex, msg));
			}
		}
		send_client(users[uindex].getSocket(), create_code_msg("366", uindex, splitted[1] + " :End of NAMES list"));
	}
}
