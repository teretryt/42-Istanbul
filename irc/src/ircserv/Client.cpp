#include "../../include/ircserv/Client.hpp"

Client::Client(){
	_socket = -1;
	verify = false;
	invisible = false;
	nickName = "";
	userName = "";
	realName = "";
}

Client::Client(const Client& copy){
	this->_socket = copy._socket;
	this->verify = copy.verify;
	this->invisible = copy.invisible;
	this->nickName = copy.nickName;
	this->userName = copy.userName;
	this->realName = copy.realName;
	this->hostName = copy.hostName;
	this->modes = copy.modes;
}

Client& Client::operator=(const Client& right){
	this->_socket = right._socket;
	this->verify = right.verify;
	this->nickName = right.nickName;
	this->userName = right.userName;
	this->realName = right.realName;
	this->hostName = right.hostName;
	return (*this);
}

Client::~Client(){

}

void	Client::setSocket(const int _socket){
	this->_socket = _socket;
}

void	Client::setVerify(const std::string& cli_pass, const std::string& pass){
	if (cli_pass == pass)
	{
		this->verify = true;
		std::cout << "Password is correct welcome " << std::endl;
	}
	else
	{
		this->verify = false;
		std::cout << "The tried password is incorrect: " << cli_pass << std::endl;
	}
}

void	Client::setInvisible(const bool& invisible){
	this->invisible = invisible;
}

void	Client::setNickName(const std::string& nickname){
	this->nickName = nickname;
}

void	Client::setUserName(const std::string& username){
	this->userName = username;
}

void	Client::setRealName(const std::string& realname){
	this->realName = realname;
}

void	Client::setHostName(const std::string& hostname){
	this->hostName = hostname;
}

void	Client::addMode(const char mode){
	if (getIsHaveMode(mode))
		return ;
	this->modes.push_back(mode);
}

void	Client::removeMode(const char mode){
	if (getIsHaveMode(mode) == false)
		return ;
	std::vector<char>::iterator it = this->modes.begin();
	for (size_t i = 0; i < this->modes.size(); i++)
		if (modes[i] == mode)
			it += i;
	this->modes.erase(it);
}


const int&			Client::getSocket() {return this->_socket;}
const bool&			Client::getVerify() {return this->verify;}
const bool&			Client::getInvisible() {return this->invisible;}
const std::string&	Client::getNickName() {return this->nickName;}
const std::string&	Client::getUserName() const {return this->userName;}
const std::string&	Client::getRealName() {return this->realName;}
const std::string&	Client::getHostName() const {return this->hostName;}
bool				Client::getIsHaveMode(const char mode){
	for (size_t i = 0; i < this->modes.size(); i++)
		if (mode == modes[i])
			return (true);
	return (false);
}

std::string	Client::getMods() {
	std::string res = "";
	if (this->modes.size() > 0)
		res += "+";
	for (size_t i = 0; i < this->modes.size(); i++){
		res = res + this->modes[i];
	}
	return (res);
}


bool	Client::operator==(Client const& client) {
	return (this->userName == client.userName);
}

