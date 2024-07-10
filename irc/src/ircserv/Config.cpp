#include "../../include/ircserv/Config.hpp"

Config::Config():fOpList(op_file, std::ios::in){
	std::string	str;
	while (std::getline(fOpList, str))
	{
		if (str.length() > 0)
			this->operators.push_back(str);
	}
	if (fOpList.is_open())		fOpList.close();
}

Config::~Config(){}

//	SET FUNCTIONS
void	Config::addOperator(std::string userName){
	if (isHaveOperator(userName))
		return ;
	operators.push_back(userName);
}

void	Config::removeOperator(std::string userName){
	if (!isHaveOperator(userName))
		return ;
	std::vector<std::string>::iterator it = std::find(operators.begin(), operators.end(), userName);
	operators.erase(it);
}

//	BOOL FUNCTIONS
bool	Config::isHaveOperator(std::string userName){
	std::vector<std::string>::iterator it = std::find(operators.begin(), operators.end(), userName);
	if (it != operators.end())
		return (true);
	return (false);
}

