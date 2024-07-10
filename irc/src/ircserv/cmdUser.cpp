#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdUser(){
	if (splitted.size() < 5)
	{
		send_client(users[uindex].getSocket(), create_code_msg("461", uindex, "USER :Not enough parameters"));
		return ;
	}
	if (users[uindex].getUserName().length() > 0 || findUserWithUsername(splitted[1]) != std::string::npos)
	{
		send_client(users[uindex].getSocket(), create_code_msg("462", uindex, ":You may not reregister"));
		return ;
	}
	//USER user_tcelik 0 127.0.0.1 :Taha Çelik
	//USER user_tcelik 0 127.0.0.1 :KVIrc 5.0.0 Aria http://kvirc.net/
	users.at(uindex).setUserName(splitted[1]);
	std::vector<std::string>::iterator it = splitted.begin();
	std::advance(it, 4);
	std::string tmp = mergeMsg(it, std::distance(it, splitted.end()));
	users.at(uindex).setRealName(tmp);
	std::cout << "USERNAME ATAMA:" << users.at(uindex).getUserName() << "|" <<  std::endl;
	if (users[uindex].getNickName().length() > 0)
		this->first_login = true;
	if (irc.cfg.isHaveOperator(splitted[1]))
		users[uindex].addMode('o');
}
