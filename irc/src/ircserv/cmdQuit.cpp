#include "../../include/ircserv/CommandRunner.hpp"

void	CommandRunner::cmdQuit(){
	for (size_t i = 0; i < vChannel.size(); i++)
		if (vChannel[i].isUsrOnChnl(users[uindex])){
			std::vector<std::string> tmp = splitted;
			splitted.clear();
			splitted.push_back("PART");
			splitted.push_back(vChannel[i].getName());
			cmdPart();
			splitted.clear();
			splitted = tmp;
			tmp.clear();
			updateChannel(i);
		}
	users.erase(users.begin() + uindex);
	close(irc.fds[uindex + 1].fd);
	irc.fds.erase(irc.fds.begin() + uindex + 1);
}
