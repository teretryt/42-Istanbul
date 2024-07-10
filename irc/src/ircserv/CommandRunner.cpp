#include "../../include/ircserv/CommandRunner.hpp"

CommandRunner::CommandRunner(std::vector<Client>& users, Server&	irc, std::vector<Channel>&	_vChannel, int senderIndx): users(users), irc(irc), vChannel(_vChannel){
	this->senderIdx = senderIndx;
	for (size_t i = 0; i < users.size(); i++)
		std::cout << "Socket no:" << users[i].getSocket() << std::endl;
	funcMap["PASS"] = &CommandRunner::cmdPass;
	funcMap["NICK"] = &CommandRunner::cmdNick;
	funcMap["USER"] = &CommandRunner::cmdUser;
	funcMap["JOIN"] = &CommandRunner::cmdJoin;
	funcMap["PART"] = &CommandRunner::cmdPart;
	funcMap["QUIT"] = &CommandRunner::cmdQuit;
	funcMap["TOPIC"] = &CommandRunner::cmdTopic;
	funcMap["PRIVMSG"] = &CommandRunner::cmdPrivmsg;
	funcMap["PING"] = &CommandRunner::cmdPong;
	funcMap["MODE"] = &CommandRunner::cmdMode;
	funcMap["LIST"] = &CommandRunner::cmdList;
	funcMap["NAMES"] = &CommandRunner::cmdNames;
	funcMap["INVITE"] = &CommandRunner::cmdInvite;
	funcMap["WHO"] = &CommandRunner::cmdWho;
	funcMap["KICK"] = &CommandRunner::cmdKick;
}

CommandRunner::~CommandRunner() {}

std::vector<std::string> CommandRunner::split(std::string str, char delimeter)
{
	std::vector<std::string> 	r;
	std::stringstream			ss(str);
	std::string					word;

	while (std::getline(ss, word, delimeter))
	{
		r.push_back(word);
	}
	return (r);
}


void	CommandRunner::send_client(int fd, std::string msg){
	std::cout << "fd: " << fd << "->" + msg << std::endl;
	if (send(fd, msg.c_str(), msg.length(), 0) == -1)
		std::cerr << "Client socket is close!" << std::endl;
};

int	CommandRunner::findUser(std::string nickName) {
	for (size_t i = 0; i < users.size() ; i++)
	{
		if (users.at(i).getNickName() == nickName)
			return (i);
	}
	return (-1);
}

std::string	CommandRunner::createMsg(std::vector<std::string> splitted, int uindex){
	std::vector<std::string>::iterator it = splitted.begin();
	std::advance(it, 2);
	std::string merge = mergeMsg(it, std::distance(it, splitted.end()));
	std::string msg = ":" + users[uindex].getNickName() + "!" + this->users[uindex].getUserName() + "@" + this->users[uindex].getHostName() + " " + splitted[0] + " " + splitted[1] + " :" + merge + "\r\n";
	std::cout << "Create Msg Func:" + msg;
	return (merge);
}

std::string	CommandRunner::create_code_msg(std::string code, size_t uindex, std::string msg)
{
	std::string tmp = ":" + users[uindex].getHostName() + " " + code + " " + users[uindex].getNickName() + " " + msg + "\r\n";
	return (tmp);
}

std::string CommandRunner::create_msg(std::string _msg){
	//    Usage -> : nick_name!user_name@hostname [SPACE] [COMMAND] [SPACE] receiver_nick_name [SPACE] : [message]\r\n
	std::string msg = ":" + users[uindex].getNickName() + "!" + users[uindex].getUserName() + "@" + users[uindex].getHostName() + " " + _msg + "\r\n";
	return msg;
}

void	CommandRunner::selectAndRunCom(std::vector<std::string> parsed, int uindex)
{
	this->parsed = parsed;
	this->first_login = false;
	this->uindex = uindex;
	for (size_t i = 0; i < parsed.size(); i++)
	{
		this->index = i;
		splitted = split(parsed[i], ' ');
		std::map<std::string, void (CommandRunner::*)()>::iterator it = this->funcMap.find(splitted[0]);
		if (it != this->funcMap.end()) {
			if (users[uindex].getVerify() == 1 || splitted[0] == "PASS" || splitted[0] == "QUIT"){
				(this->*(it->second))();
			}else{
				std::cout << "a:" << parsed[i] <<std::endl;
				std::cerr << "Please firstly verify password!" << std::endl;
			}
		}
		else{
			std::cout << "Key not found." << std::endl;
		}
		if (first_login == true && users[uindex].getVerify() && users[uindex].getNickName().length() > 0 && users[uindex].getUserName().length() > 0)
		{
			time_t rawtime;
			struct tm *timeinfo;
			char buffer[80];
			std::time(&rawtime);
			timeinfo = localtime(&rawtime);
			strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);

			const std::string&	nick = users[uindex].getNickName();
			const std::string&	username = users[uindex].getUserName();

			send_client(users[uindex].getSocket(), create_code_msg("001", uindex, ":Welcome to the Internet Relay Network " + nick + "!" + username + "@" + users[uindex].getHostName()));
			send_client(users[uindex].getSocket(), create_code_msg("002", uindex, ":Your host is " + users[uindex].getHostName() +", running version v1.0"));
			send_client(users[uindex].getSocket(), create_code_msg("003", uindex, ":This server was created " + std::string(buffer)));
			send_client(users[uindex].getSocket(), create_code_msg("004", uindex, users[uindex].getHostName() + " 1.0 swoi beliIkmsto beliIko"));
			send_client(users[uindex].getSocket(), create_code_msg("251", uindex, ":There are " + std::to_string(users.size()) + " users and 0 services on 1 server"));
		}
	}
}

std::string	CommandRunner::mergeMsg(std::vector<std::string>::iterator splitted, size_t size)
{
	std::string merge = "";
	for (size_t i = 0; i < size; i++){
		merge += *splitted;
		if (i == 0)
			merge.erase(0, 1);
		if (i != size - 1)
			merge += " ";
		std::advance(splitted, 1);
	}
	return (merge);
}

bool CommandRunner::channelExist(std::string name)
{
	for (size_t i = 0; i < this->vChannel.size(); i++)
	{
		if (vChannel[i].getName() == name)
			return true;
	}
	return false;
}

size_t	CommandRunner::returnChannelIndex(const std::string& channelName)
{
	for (size_t i = 0; i < this->vChannel.size(); i++)
	{
		if (this->vChannel[i].getName() == channelName)
			return (i);
	}
	return (std::string::npos);
}

int	CommandRunner::countOfChannelIn(const Client& client)
{
	int	counter = 0;
	for (size_t i = 0; i < vChannel.size(); i++)
	{
		if (vChannel[i].isUsrOnChnl(client))
			counter++;
	}
	return (counter);
}

void	CommandRunner::addChannel(const std::string& channelName){
	Channel tmp(channelName, users[uindex]);
	this->vChannel.push_back(tmp);
	// :nick!user@host JOIN #channelname * :Real Name
	std::string msg = ":" + users[uindex].getNickName() + "!" + this->users[uindex].getUserName() + "@" + this->users[uindex].getHostName() + " " + splitted[0] + " " + channelName + "\r\n";
	std::cout << "JOIN MSG: " + msg;
	send_client(this->users[uindex].getSocket(), msg);
	updateChannel(this->vChannel.size() - 1);
}

void	CommandRunner::updateChannel(size_t chnIdx){
	std::vector<std::string> tmp = splitted;
	size_t tmpU = uindex;
	splitted.clear();
	splitted.push_back("NAMES");
	splitted.push_back(vChannel[chnIdx].getName());
	for(size_t idx = 0; idx < users.size(); idx++)
	{
		uindex = idx;
		if (vChannel[chnIdx].isUsrOnChnl(users[idx]))
			cmdNames();
	}
	uindex = tmpU;
	splitted = tmp;
}

size_t		CommandRunner::findUserWithUsername(const std::string& userName){
	size_t i;
	for (i = 0; i < users.size(); i++)
		if (users[i].getUserName() == userName)
			return (i);
	return (std::string::npos);
}

size_t	CommandRunner::findUserWithNick(const std::string& nickName){
	size_t i;
	for (i = 0; i < users.size(); i++)
		if (users[i].getNickName() == nickName)
			return (i);
	return (std::string::npos);
}

void	CommandRunner::checkCloseChannels(void){
	for (std::vector<Channel>::iterator it = vChannel.begin(); it < vChannel.end(); it++)
		if ((*it).getNbUsers() == 0)
			vChannel.erase(it);
}
