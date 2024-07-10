#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdNick(){
	if (splitted.size() < 2){
		send_client(users[uindex].getSocket(), create_code_msg("431", uindex, ":No nickname given"));
		return ;
	}
	if (!nickRulesCheck(splitted[1])){
		send_client(users[uindex].getSocket(), create_code_msg("432", uindex, splitted[1] + " :Erroneus nickname"));
		return ;
	}
	if (nickAlreadyTaken(splitted[1])){
		send_client(users[uindex].getSocket(), create_code_msg("433", uindex, splitted[1] + " :Nickname is already in use"));
		return ;
	}
	std::string oldNick = users.at(uindex).getNickName();
	users.at(uindex).setNickName(splitted[1]);
	findAndChangeNick(oldNick, splitted[1]);
	for (size_t i = 0; i < vChannel.size(); i++)
		if (vChannel[i].isUsrOnChnl(users[uindex]))
			vChannel[i].send_channel_message(users[uindex], ":" + oldNick +"!"+users[uindex].getUserName()+"@"+users[uindex].getHostName()+" NICK " + splitted[1] + "\r\n");
	send_client(users[uindex].getSocket(), ":" + oldNick +"!"+users[uindex].getUserName()+"@"+users[uindex].getHostName()+" NICK "+splitted[1]+"\r\n");
	if (users[uindex].getUserName().length() > 0)
		this->first_login = true;
}

bool	CommandRunner::nickRulesCheck(std::string nick)
{
	std::string specials = "[]{}\\|^`-_";
	if (nick.length() > 9)
		return (0);
	for (size_t i = 0; i < nick.length(); i++)
	{
		if (i == 0 && !std::isalpha(nick[i]) && specials.find(nick[i]) == std::string::npos)
			return (0);
		if (i != 0 && !std::isalnum(nick[i]) && specials.find(nick[i]) == std::string::npos && nick[i] != '-')
			return (0);
	}
	return (1);
}

bool	CommandRunner::nickAlreadyTaken(std::string nick)
{
	for (size_t i = 0; i < users.size(); i++){
		if (this->users[i].getNickName() == nick)
			return true;
	}
	return false;
}

void		CommandRunner::findAndChangeNick(std::string oldNick, std::string newNick){
	for (size_t i = 0; i < vChannel.size(); i++)
		vChannel[i].findAndChangeNick(oldNick, newNick);
}
