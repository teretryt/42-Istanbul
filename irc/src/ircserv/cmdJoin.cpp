#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdJoin(){
	if (splitted.size() < 2)
	{
		send_client(users[uindex].getSocket(), create_code_msg("461", uindex, "JOIN :Not enough parameters"));
		return ;
	}
	std::vector<std::string> channelNames = split(splitted[1], ',');
	std::vector<std::string> channelPasses;
	if (splitted.size() == 3)
	{
		channelPasses = split(splitted[2], ',');
		for (size_t l = channelPasses.size(); l < channelNames.size(); l++)
			channelPasses.push_back("");
	}
	for (size_t j = 0; j < channelNames.size(); j++)
	{
		size_t k = Channel::isChannel(vChannel, channelNames[j]);
		if (k == std::string::npos && !users[uindex].getIsHaveMode('o')){
			send_client(users[uindex].getSocket(), create_code_msg("403", uindex, channelNames[j] + " :No such channel"));
			continue ;
		}
		if (countOfChannelIn(users[uindex]) >= MAX_CHANNEL_IN){
			send_client(users[uindex].getSocket(), create_code_msg("405", uindex, channelNames[j] + " :You have joined too many channels"));
			continue ;
		}
		if (k == std::string::npos){
			CommandRunner::addChannel(channelNames[j]);
			continue ;
		}
		if (vChannel[k].isHaveMode('k') && (splitted.size() != 3 || channelPasses[j] != vChannel[k].getChannelPass())){
			send_client(users[uindex].getSocket(), create_code_msg("475", uindex, channelNames[j] + " :Cannot join channel (+k)"));
			continue ;
		}
		if (vChannel[k].isBanned(users[uindex]) && !vChannel[k].isExceptional(users[uindex])){
			send_client(users[uindex].getSocket(), create_code_msg("474", uindex, channelNames[j] + " :Cannot join channel (+b)"));
			continue ;
		}
		if (vChannel[k].isHaveMode('I') && !vChannel[k].isInvited(users[uindex]) && !vChannel[k].isExceptional(users[uindex])
			&& !vChannel[k].isOperator(users[uindex]) && !users[uindex].getIsHaveMode('o')){
			send_client(users[uindex].getSocket(), create_code_msg("473", uindex, channelNames[j] + " :Cannot join channel (+I)"));
			continue ;
		}
		if (vChannel[k].isHaveMode('i') && !vChannel[k].isInvited(users[uindex])
			&& !vChannel[k].isOperator(users[uindex]) && !users[uindex].getIsHaveMode('o')){
			send_client(users[uindex].getSocket(), create_code_msg("473", uindex, channelNames[j] + " :Cannot join channel (+i)"));
			continue ;
		}
		if (vChannel[k].isHaveMode('l') && vChannel[k].getNbUsers() >= vChannel[k].getChannelLimit()){
			send_client(users[uindex].getSocket(), create_code_msg("471", uindex, channelNames[j] + " :Cannot join channel (+l)"));
			continue ;
		}
		CommandRunner::joinChannel(channelNames[j]);

	}
}

void	CommandRunner::joinChannel(const std::string& channelName){
	size_t i = Channel::isChannel(vChannel, channelName);
	if (this->vChannel[i].isUsrOnChnl(this->users[uindex]))
		return ;
	this->vChannel.at(i).addUserToChnl(this->users[uindex]);
	std::string msg = ":" + users[uindex].getNickName() + "!" + this->users[uindex].getUserName() + "@" + this->users[uindex].getHostName() + " JOIN " + channelName + "\r\n";
	std::cout << "JOIN MSG: " + msg;
	send_client(this->users[uindex].getSocket(), msg);
	updateChannel(i);
	if (this->vChannel[i].isInvited(this->users[uindex]))
		this->vChannel[i].removeUserToInvite(this->users[uindex]);
}
