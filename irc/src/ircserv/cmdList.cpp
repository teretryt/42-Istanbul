#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdList(){
	if (splitted.size() < 2)
	{
		if (vChannel.size())
			send_client(users[uindex].getSocket(), create_code_msg("321", uindex, "<Channel Name> - <Client Count> - <Topic>"));
		for (size_t i = 0; i < vChannel.size(); i++)
		{
			if (!vChannel[i].getSecret())
				send_client(users[uindex].getSocket(), create_code_msg("322", uindex, vChannel[i].getName() + " "
				+ std::to_string(vChannel[i].getNbUsers()) + " :" + vChannel[i].getTopic()));
		}
		if (vChannel.size())
			send_client(users[uindex].getSocket(), create_code_msg("323", uindex, ":End of /LIST"));

	}else if (splitted.size() < 3){
		std::vector<std::string> list = split(splitted[1], ',');
		if (list.size())
			send_client(users[uindex].getSocket(), create_code_msg("321", uindex, "<Channel Name> - <Client Count> - <Topic>"));
		for (size_t i = 0; i < list.size(); i++)
		{
			if (Channel::isChannel(vChannel, list[i]) == std::string::npos)
				continue ;
			std::string name = vChannel[Channel::isChannel(vChannel, list[i])].getName();
			std::string nbUser = std::to_string(vChannel[Channel::isChannel(vChannel, list[i])].getNbUsers());
			std::string topic = vChannel[Channel::isChannel(vChannel, list[i])].getTopic();
			send_client(users[uindex].getSocket(), create_code_msg("322", uindex, name + " " + nbUser + " :" + topic));
		}
		if (list.size())
			send_client(users[uindex].getSocket(), create_code_msg("323", uindex, ":END OF LIST"));
	}
}
