#include "../../include/ircserv/CommandRunner.hpp"

static size_t	paramCounter(const std::string& params){
	size_t counter = 0;
	std::string modes = "belko";
	for (size_t i = 0; i < params.size(); i++)
		if (modes.find(params[i]) != std::string::npos)
			counter++;
	return (counter);
}

static std::vector<std::string> parseModes(const std::string& modes) {
	std::vector<std::string> ret;
	std::string tmp = "";
	for (std::string::const_iterator it = modes.begin(); it != modes.end(); ++it) {
		char chr = *it;
		if (chr == '+' || chr == '-') {
			if (!tmp.empty()) {
				if (tmp.length() != 1)
					ret.push_back(tmp);
				tmp.clear();
			}
			tmp.push_back(chr);
		}
		else
			tmp.push_back(chr);
	}
	if (!tmp.empty() && tmp.length() != 1)
		ret.push_back(tmp);
	return (ret);
}

void	CommandRunner::cmdMode(){
	if (splitted.size() < 2){
		send_client(users[uindex].getSocket(), create_code_msg("461", uindex, "MODE :Not enough parameters"));
		return ;
	}
	if (splitted[1][0] == '#'){
		channelMode();
	}else{
		userMode();
	}
}

void	CommandRunner::channelMode(){
	size_t index = Channel::isChannel(vChannel, splitted[1]);
	if (index == std::string::npos){
		send_client(users[uindex].getSocket(), create_code_msg("403", uindex, splitted[1] + " :No such channel"));
	}else if (vChannel[index].isUsrOnChnl(users[uindex]) == false){
		send_client(users[uindex].getSocket(), create_code_msg("442", uindex, splitted[1] + " :You're not on that channel"));
	}else if (splitted.size() == 2){
		send_client(users[uindex].getSocket(), create_code_msg("324", uindex, vChannel[index].getName() + " " + vChannel[index].getChnlModNames() + " " + vChannel[index].getChnlLimit()));
	}else if (splitted.size() == 3 && splitted[2].length() == 1 && (splitted[2].find('b') != std::string::npos || splitted[2].find('e') != std::string::npos || splitted[2].find('I') != std::string::npos)){
		if (splitted[2][0] == 'b')
			listModes(index, vChannel[index].bannedUsers, 'b');
		else if (splitted[2][0] == 'e')
			listModes(index, vChannel[index].exceptionList, 'e');
		else if (splitted[2][0] == 'I')
			listModes(index, vChannel[index].inviteList, 'I');
	}else if (!(users[uindex].getIsHaveMode('o') || vChannel[index].isOperator(users[uindex]))){
		send_client(users[uindex].getSocket(), create_code_msg("482", uindex, splitted[1] + " :You're not channel operator"));
	}else if (splitted.size() >= 3){
		std::string notMods = getNotHaveModes("+-beliIkmsto", splitted[2]);
		if (!notMods.empty())
			return ;
		if (splitted.size() >= 4)
			CommandRunner::setModeChannel(splitted[2], splitted[3], index);
		else
			CommandRunner::setModeChannel(splitted[2], "", index);
		updateChannel(index);
	}
}

void	CommandRunner::userMode(){
	size_t	index = findUserWithNick(splitted[1]);
	if (index == std::string::npos){
		send_client(users[uindex].getSocket(), create_code_msg("401", uindex, splitted[1] + " :No such nick"));
	}else if (index != (size_t)uindex){
		send_client(users[uindex].getSocket(), create_code_msg("502", uindex, ":Cant change mode for other users"));
	}else if (splitted.size() == 2){
		send_client(users[uindex].getSocket(), create_code_msg("221", uindex, users[uindex].getMods()));
	}else{
		std::string changedModes = setModeClient(splitted[2]);
		std::cout << "chn:" << changedModes << std::endl;
		if (!changedModes.empty()){
			send_client(users[uindex].getSocket(), create_code_msg("221", uindex, users[uindex].getMods()));
		}else{
			send_client(users[uindex].getSocket(), create_code_msg("221", uindex, ":already exists flag(s)"));
		}
		if (!getNotHaveModes("+-iwso", splitted[2]).empty()){
			send_client(users[uindex].getSocket(), create_code_msg("472", uindex, getNotHaveModes("+-iwso", splitted[2]) + " :is unknown mode char to me"));
		}
	}
}

void CommandRunner::listModes(size_t idx, std::vector<Client> user, char type){
	for (size_t i = 0; i < user.size(); i++){
		switch (type)
		{
			case 'b':
				send_client(users[uindex].getSocket(), create_code_msg("367", uindex, vChannel[idx].getName() + " " + user[i].getNickName()));
				break;
			case 'e':
				send_client(users[uindex].getSocket(), create_code_msg("348", uindex, vChannel[idx].getName() + " " + user[i].getNickName()));
				break;
			case 'I':
				send_client(users[uindex].getSocket(), create_code_msg("346", uindex, vChannel[idx].getName() + " " + user[i].getNickName()));
				break;
			default:
				break;
		}
	}
	switch (type)
	{
		case 'b':
			send_client(users[uindex].getSocket(), create_code_msg("368", uindex, vChannel[idx].getName() + " :End of channel ban list" ));
			break;
		case 'e':
			send_client(users[uindex].getSocket(), create_code_msg("349", uindex, vChannel[idx].getName() + " :End of channel exception list" ));
			break;
		case 'I':
			send_client(users[uindex].getSocket(), create_code_msg("347", uindex, vChannel[idx].getName() + " :End of Channel Invite Exception List"));
			break;
		default:
			break;
	}
}

std::string CommandRunner::getNotHaveModes(std::string modes, const std::string& inpModes){
	std::string res = "";
	for (size_t i = 1; i < inpModes.size(); i++)
		if (modes.find(inpModes[i]) == std::string::npos)
			res += inpModes[i];
	return (res);
}

std::string	CommandRunner::setModeChannel(const std::string& modes, const std::string& params, int index){
	size_t	pIdx = 0;
	std::string sysModes = "beliIkmsto";
	std::string listModes = "beiI";
	std::string changed = "";
	std::vector<std::string> pModes;
	std::vector<std::string> paramList = split(params, ',');
	for (size_t k = paramList.size(); k < paramCounter(modes); k++)
		paramList.push_back("");
	if (modes[0] != '+' && modes[0] != '-')
		pModes = parseModes("+" + modes);
	else
		pModes = parseModes(modes);
	for (size_t j = 0; j < pModes.size(); j++)
	{
		for (size_t i = 0; i < pModes[j].size(); i++){
			if (sysModes.find(pModes[j][i]) == std::string::npos)
				continue ;
			if (std::string("lko").find(pModes[j][i]) != std::string::npos && paramList[pIdx].length() == 0)
				continue ;
			if (!vChannel[index].isHaveMode(pModes[j][i]) && pModes[j][0] != '-'){
				changed += pModes[j][i];
				vChannel[index].addMode(pModes[j][i]);
			}else if (vChannel[index].isHaveMode(pModes[j][i]) && pModes[j][0] == '-' && !(listModes.find(pModes[j][i]) != std::string::npos && params != "")){
				changed += pModes[j][i];
				vChannel[index].removeMode(pModes[j][i]);
			}
			switch (pModes[j][i])
			{
				case 'b':
					execBanMode(paramList[pIdx], pModes[j][0]);
					pIdx++;
					break ;
				case 'e':
					execExceptMode(paramList[pIdx], pModes[j][0]);
					pIdx++;
					break ;
				case 'l':
					execLimitMode(paramList[pIdx], pModes[j][0]);
					pIdx++;
					break ;
				case 'k':
					execKeyMode(paramList[pIdx], pModes[j][0]);
					pIdx++;
					break ;
				case 'o':
					execOpMode(paramList[pIdx], pModes[j][0]);
					pIdx++;
					break ;
				case 's':
					vChannel[index].setSecret(pModes[j][0] == '+');
					break;
				default:
					break ;
			}
		}
	}
	return (changed);
}

std::string	CommandRunner::setModeClient(const std::string& modes){
	std::string sysModes = "swoi";
	std::string changed = "";
	size_t i = 0;
	if (modes[0] == '+' || modes[0] == '-')
		i++;
	for (; i < modes.size(); i++){
		if (sysModes.find(modes[i]) == std::string::npos)
			continue ;
		if (!users[uindex].getIsHaveMode(modes[i]) && modes[0] != '-'){
			if (modes[i] == 'o')
				continue ;
			changed += modes[i];
			users[uindex].addMode(modes[i]);
		}
		else if (users[uindex].getIsHaveMode(modes[i]) && modes[0] == '-'){
			changed += modes[i];
			users[uindex].removeMode(modes[i]);
		}
		if (modes[i] == 'i')
			users[uindex].setInvisible(modes[0] != '-');
	}
	return (changed);
}

void CommandRunner::execBanMode(const std::string& param, const char& type){
	size_t index = Channel::isChannel(vChannel, splitted[1]);
	if (type == '+')
	{
		int idx = findUser(param);
		if (param.length() == 0){
			std::string list = "";
			for (size_t i = 0; i < vChannel[index].bannedUsers.size(); i++)
				list += " " + vChannel[index].bannedUsers[i].getNickName();
			if (vChannel[index].bannedUsers.size())
				send_client(users[idx].getSocket(), create_code_msg("367", uindex, vChannel[index].getName() + list));
			send_client(users[idx].getSocket(), create_code_msg("368", uindex, vChannel[index].getName() + " :End of channel ban list"));
		}else if (idx != -1){
			vChannel[index].banTheUsr(users[idx]);
			std::string msg = ":" + users[idx].getNickName() + "!" + this->users[idx].getUserName() + "@" + this->users[idx].getHostName() + " PART " + vChannel[index].getName() + "\r\n";
			send_client(this->users[idx].getSocket(), msg);
			vChannel[index].send_channel_message(this->users[idx], msg);
			send_client(users[idx].getSocket(), create_code_msg("474", uindex, vChannel[index].getName() + " :You banned from " + vChannel[index].getName()));
		}
	}
	else if (type == '-')
	{
		int idx = findUser(param);
		if (idx != -1){
			vChannel[index].banRemoveUsr(users[idx]);
			if (vChannel[index].bannedUsers.size() == 0)
				vChannel[index].removeMode('b');
		}
	}
}

void CommandRunner::execExceptMode(const std::string& param, const char& type){
	size_t index = Channel::isChannel(vChannel, splitted[1]);
	if (type == '+')
	{
		int idx = findUser(param);
		if (param.length() == 0){
			std::string list = "";
			for (size_t i = 0; i < vChannel[index].exceptionList.size(); i++)
				list += " " + vChannel[index].exceptionList[i].getNickName();
			if (vChannel[index].exceptionList.size())
				send_client(users[idx].getSocket(), create_code_msg("348", uindex, vChannel[index].getName() + list));
			send_client(users[idx].getSocket(), create_code_msg("349", uindex, vChannel[index].getName() + " :End of channel exception list"));
		}else if (idx != -1)
			vChannel[index].addUserToException(users[idx]);
	}
	else if (type == '-')
	{
		int idx = findUser(param);
		if (idx != -1){
			vChannel[index].removeUserToException(users[idx]);
			if (vChannel[index].exceptionList.size() == 0)
				vChannel[index].removeMode('e');
		}
	}
}

void CommandRunner::execLimitMode(const std::string& param, const char& type){
	size_t index = Channel::isChannel(vChannel, splitted[1]);
	if (type == '+')
	{
		try{
			size_t limit = std::stoul(param);
			vChannel[index].setChannelLimit(limit);
			std::cout << "channelLimit :" << vChannel[index].getChannelLimit() << std::endl;
		}catch(std::exception& e)
		{
			vChannel[index].setChannelLimit(std::string::npos);
		}
	}
	else if (type == '-')
		vChannel[index].setChannelLimit(std::string::npos);
}

void CommandRunner::execKeyMode(const std::string& param, const char& type){
	size_t index = Channel::isChannel(vChannel, splitted[1]);
	if (type == '+')
		vChannel[index].setChannelPass(param);
	else if (type == '-')
		vChannel[index].setChannelPass("");
}

void	CommandRunner::execOpMode(const std::string& param, const char& type){
	size_t index = Channel::isChannel(vChannel, splitted[1]);
	if (type == '+')
	{
		int idx = findUser(param);
		if (idx != -1)
			vChannel[index].addUserToOperators(users[idx]);
	}
	else if (type == '-')
	{
		int idx = findUser(param);
		if (idx != -1)
			vChannel[index].removeUserToOperators(users[idx]);
	}
}
