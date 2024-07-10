#pragma once

#include "Server.hpp"

enum CMD{
	PRIVMSG =1,
	USER,
	NICK,
	PASS
};
class CommandRunner;

//typedef  void (CommandRunner::*MemberFunctionPtr)();

class CommandRunner{
	private:
		std::vector<Client>&		users;
		Server&						irc;
		std::vector<Channel>&		vChannel;
		int							senderIdx;
		bool						first_login;
		std::map<std::string,void(CommandRunner::*)()>	funcMap;
		std::vector<std::string>	splitted;
		std::vector<std::string>	parsed;
		int 						uindex;
		int							index;

		std::string				createMsg(std::vector<std::string> splitted, int uindex);

		// COMMANDS
		void					cmdPass();
		void					cmdNick();
		void					cmdUser();
		void					cmdJoin();
		void					cmdPart();
		void					cmdQuit();
		void					cmdTopic();
		void					cmdPrivmsg();
		void					cmdPong();
		void					cmdMode();
		void					cmdList();
		void					cmdNames();
		void					cmdInvite();
		void					cmdWho();
		void					cmdKick();
		void 					execBanMode(const std::string& param, const char& type);
		void 					execExceptMode(const std::string& param, const char& type);
		void 					execLimitMode(const std::string& param, const char& type);
		void 					execKeyMode(const std::string& param, const char& type);
		void					execOpMode(const std::string& param, const char& type);

		// COMMANDS UTILS
		void					userMode();
		void					channelMode();
		void					updateChannel(size_t chnIdx);
		std::string 			getNotHaveModes(std::string modes, const std::string& inpModes);
		std::string				setModeClient(const std::string& modes);
		std::string				setModeChannel(const std::string& modes, const std::string& params, int index);

	public:

		CommandRunner(std::vector<Client>& users, Server&	irc, std::vector<Channel>&	vChannel, int senderIndx);
		~CommandRunner();
		void		send_client(int fd, std::string msg);
		std::string	getFirstWord(std::string str);
		int			findUser(std::string nickName);
		std::string	create_msg(std::string _msg);
		void		comMsg(std::string line, int uindex);
		void		selectAndRunCom(std::vector<std::string> parsed, int uindex);
		bool		nickAlreadyTaken(std::string nick);
		bool		channelExist(std::string name);
		bool		nickRulesCheck(std::string nick);
		std::string	create_code_msg(std::string code, size_t uindex, std::string msg);
		void		addChannel(const std::string& channelName);
		std::string	mergeMsg(std::vector<std::string>::iterator splitted, size_t size);
		size_t		returnChannelIndex(const std::string& channelName);
		int			countOfChannelIn(const Client& client);
		void		joinChannel(const std::string& channelName);
		size_t		findUserWithNick(const std::string& nickName);
		size_t		findUserWithUsername(const std::string& userName);
		void		listModes(size_t idx, std::vector<Client> user, char type);
		void		findAndChangeNick(std::string oldNick, std::string newNick);
		void		checkCloseChannels(void);
		std::vector<std::string>	split(std::string str, char delimeter);
};

