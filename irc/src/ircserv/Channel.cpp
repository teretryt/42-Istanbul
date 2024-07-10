#include "../../include/ircserv/Channel.hpp"

Channel::Channel(std::string channelName, Client const& usr)
{
	this->secret = false;
	this->topic = "";
	this->channelPass = "";
	this->channelName = channelName;
	this->users.push_back(usr);
	this->operators.push_back(usr);
	this->createrUser = usr.getUserName();
	this->clientLimit = std::string::npos;
}

Channel::~Channel(){
}

//PRIVATE FUNCS
std::vector<Client>::iterator Channel::usrFind(Client const& usr){
	std::vector<Client>::iterator it;
	it = std::find(this->users.begin(), this->users.end(), usr);
	return (it);
}

std::vector<Client>::iterator Channel::usrFind(Client const& usr, std::vector<Client>& vUsr){
	std::vector<Client>::iterator it;
	it = std::find(vUsr.begin(), vUsr.end(), usr);
	return (it);
}

//SET FUNCS
void	Channel::delUserChnl(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr);
	if (*it.base() == usr){
		this->users.erase(it);
	}else{
		std::cerr << "usr Parametre not member in " + channelName + "channel" << std::endl;
	}
}

void    Channel::delUserChnl(Client const& usr, std::vector<Channel>& vChnl){
	std::vector<Client>::iterator it;
	for (size_t i = 0; i < vChnl.size(); i++)
	{
		it = usrFind(usr, vChnl.at(i).users);
		if (*it.base() == usr){
			vChnl.at(i).users.erase(it);
		}
	}
}

void	Channel::addUserToChnl(Client const& usr){
	this->users.push_back(usr);
}

void	Channel::setTopic(std::string const& topic){
	this->topic = topic;
}

void	Channel::setChannelPass(std::string const& pass){
	this->channelPass = pass;
}

void	Channel::setCrtUser(const std::string& user){
	this->createrUser = user;
}

void	Channel::setChannelLimit(const size_t& limit){
	this->clientLimit = limit;
}

void	Channel::banTheUsr(Client const& usr){
	std::vector<Client>::iterator itU = usrFind(usr);
	std::vector<Client>::iterator itBanned = usrFind(usr, this->bannedUsers);
	if (itU != this->users.end())
		this->users.erase(itU);
	if (itBanned == this->bannedUsers.end())
		this->bannedUsers.push_back(usr);
}

void	Channel::banRemoveUsr(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->bannedUsers);
	if (it != this->bannedUsers.end())
		this->bannedUsers.erase(it);
}

void	Channel::addUserToException(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->exceptionList);
	if (it == this->exceptionList.end())
		this->exceptionList.push_back(usr);
}

void	Channel::removeUserToException(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->exceptionList);
	if (it != this->exceptionList.end())
		this->exceptionList.erase(it);
}

void	Channel::addUserToInvite(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->inviteList);
	if (it == this->inviteList.end())
		this->inviteList.push_back(usr);
}

void	Channel::removeUserToInvite(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->inviteList);
	if (it != this->inviteList.end())
		this->inviteList.erase(it);
}

void	Channel::addUserToInviteException(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->inviteExceptionList);
	if (it == this->inviteExceptionList.end())
		this->inviteExceptionList.push_back(usr);
}

void	Channel::removeUserToInviteException(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->inviteExceptionList);
	if (it != this->inviteExceptionList.end())
		this->inviteExceptionList.erase(it);
}

void	Channel::addUserToOperators(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->operators);
	if (it == this->operators.end())
		this->operators.push_back(usr);
}

void	Channel::removeUserToOperators(Client const& usr){
	std::vector<Client>::iterator it = usrFind(usr, this->operators);
	if (it != this->operators.end())
		this->operators.erase(it);
}

void	Channel::sendMessageToChannel(Client& client, const std::string& msg)
{
	for (size_t i = 0; i < this->getNbUsers(); i++)
		if (this->users[i].getUserName() != client.getUserName())
			send(this->users[i].getSocket(), msg.c_str(), msg.length(), 0);
}

void	Channel::addMode(const char mode){
	if (isHaveMode(mode))
		return ;
	this->modes.push_back(mode);
}

void	Channel::removeMode(const char mode){
	if (isHaveMode(mode) == false)
		return ;
	std::vector<char>::iterator it = this->modes.begin();
	for (size_t i = 0; i < this->modes.size(); i++)
		if (modes[i] == mode)
			it += i;
	this->modes.erase(it);
}

void	Channel::setSecret(bool secret){
	this->secret = secret;
}

//BOOL FUNCS
bool	Channel::operator==(std::string const& channelName) {return this->channelName == channelName;}
bool	Channel::operator==(Channel const& other) {return this->channelName == other.channelName;}

bool	Channel::isBanned(Client const& usr) {
	std::vector<Client>::iterator cl = usrFind(usr, this->bannedUsers);
	if (cl == this->bannedUsers.end())
		return false;
	return *usrFind(usr, this->bannedUsers).base() == usr;
}

bool	Channel::isExceptional(Client const& usr) {
	std::vector<Client>::iterator cl = usrFind(usr, this->exceptionList);
	if (cl == this->exceptionList.end())
		return false;
	return *usrFind(usr, this->exceptionList).base() == usr;
}

bool	Channel::isInvited(Client const& usr) {
	std::vector<Client>::iterator cl = usrFind(usr, this->inviteList);
	if (cl == this->inviteList.end())
		return false;
	return *usrFind(usr, this->inviteList).base() == usr;
}

bool	Channel::isOperator(const Client& usr){
	std::vector<Client>::iterator cl = usrFind(usr, this->operators);
	if (cl == operators.end())
		return (false);
	return (*cl.base() == usr);
}

bool	Channel::isUsrOnChnl(Client const& usr) {
	std::vector<Client>::iterator cl = usrFind(usr);
	if (cl == this->users.end())
		return false;
	return (*cl.base() == usr);
}

bool	Channel::isHaveMode(const char mode){
	for (size_t i = 0; i < this->modes.size(); i++)
		if (mode == modes[i])
			return (true);
	return (false);
}

//GET FUNCS
size_t		Channel::getNbUsers() { return this->users.size(); }
std::string	Channel::getName() { return this->channelName; }
std::string	Channel::getTopic() { return this->topic; }
std::string	Channel::getChannelPass() { return this->channelPass; }
std::string	Channel::getCrtUser() { return this->createrUser; }
bool		Channel::getSecret() { return this->secret; }

std::string	Channel::getChnlModNames(){
	std::string res = "";
	if (this->modes.size() > 0)
		res += "+";
	for (size_t i = 0; i < this->modes.size(); i++){
		res += this->modes[i];
	}
	return (res);
}

std::string Channel::getChnlLimit(){
	if (this->isHaveMode('l') == false)
		return ("");
	return (std::to_string(this->clientLimit));
}

size_t Channel::getChannelLimit(){
	return (this->clientLimit);
}

size_t Channel::isChannel(std::vector<Channel>vChnl, std::string chnlName) {
	for (size_t i = 0; i < vChnl.size(); i++)
		if (vChnl[i].getName() == chnlName)
			return (i);
	return (std::string::npos);
}

void Channel::send_channel_message(Client sender, std::string message) const
{
	for (size_t idx = 0; idx < users.size(); ++idx) {
		if (((Client)(users[idx])).getSocket() != sender.getSocket()) {
			std::cout << "fd: " <<  ((Client)(users[idx])).getSocket() << "->" << message << std::endl;
			send(((Client)(users[idx])).getSocket(), message.c_str(), message.length(), 0);
		}
	}
}

void Channel::findAndChangeNick(std::string oldNick, std::string newNick)
{
	size_t i;
	for (i = 0; i < this->users.size(); i++){
		if (users[i].getNickName() == oldNick){
			users[i].setNickName(newNick);
			break;
		}
	}

	if (i == users.size())
		return ;

	if (createrUser == oldNick)
		createrUser = newNick;

	for (size_t j = 0; j < operators.size(); j++)
		if (operators[j].getNickName() == oldNick)
			operators[j].setNickName(newNick);

	for (size_t j = 0; j < bannedUsers.size(); j++)
		if (bannedUsers[j].getNickName() == oldNick)
			bannedUsers[j].setNickName(newNick);

	for (size_t j = 0; j < inviteExceptionList.size(); j++)
		if (inviteExceptionList[j].getNickName() == oldNick)
			inviteExceptionList[j].setNickName(newNick);

	for (size_t j = 0; j < inviteList.size(); j++)
		if (inviteList[j].getNickName() == oldNick)
			inviteList[j].setNickName(newNick);

	for (size_t j = 0; j < exceptionList.size(); j++)
		if (exceptionList[j].getNickName() == oldNick)
			exceptionList[j].setNickName(newNick);
}
