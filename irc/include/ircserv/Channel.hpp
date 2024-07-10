#pragma once
#include <vector>
#include "Server.hpp"
#include "Client.hpp"
#define RPL_WELCOME

class Channel
{
	private:
		std::string						channelName;
		std::string						channelPass;
		std::string						topic;
		std::string						createrUser;
		std::vector<char>				modes;
		std::vector<Client>				users;
		std::vector<Client>				operators;
		bool							secret;
		size_t							clientLimit;

	public:
		std::vector<Client>				bannedUsers;
		std::vector<Client>				exceptionList;
		std::vector<Client>				inviteList;
		std::vector<Client>				inviteExceptionList;
		Channel(std::string channelName, Client const& user);
		~Channel();

		//FUNCS
		std::vector<Client>::iterator	usrFind(Client const& usr);
		std::vector<Client>::iterator	usrFind(Client const& usr, std::vector<Client>& vUsers);
		//SET FUNCS
		void	delUserChnl(Client const& usr);
		void	delUserChnl(Client const& usr, std::vector<Channel>& vChnl); //bu kullanımdan bulunamadı
		void	addUserToChnl(Client const& usr);
		void	banTheUsr(Client const& usr);
		void	banRemoveUsr(Client const& usr);
		void	addUserToException(Client const& usr);
		void	removeUserToException(Client const& usr);
		void	addUserToInvite(Client const& usr);
		void	removeUserToInvite(Client const& usr);
		void	addUserToInviteException(Client const& usr);
		void	removeUserToInviteException(Client const& usr);
		void	addUserToOperators(Client const& usr);
		void	removeUserToOperators(Client const& usr);
		void	setTopic(std::string const& topic);
		void	setChannelPass(std::string const& pass);
		void	sendMessageToChannel(Client& client, const std::string& msg);
		void	addMode(const char mode);
		void	removeMode(const char mode);
		void	setCrtUser(const std::string& user);
		void	setChannelLimit(const size_t& limit);
		void	setSecret(bool secret);
		void	findAndChangeNick(std::string oldNick, std::string newNick);

		// GET FUNCS
		size_t		getNbUsers();
		std::string getCrtUser();
		std::string	getName();
		std::string	getTopic();
		std::string	getChannelPass();
		std::string	getChnlModNames();
		std::string getChnlLimit();
		size_t 		getChannelLimit();
		bool		getSecret();

		//BOOL FUNCS
		bool		isOperator(const Client& usr);
		bool		isHaveMode(const char mode);
		bool		isUsrOnChnl(Client const& usr);
		bool		isBanned(Client const& usr);
		bool		isExceptional(Client const& usr);
		bool		isInvited(Client const& usr);
		bool		operator==(std::string const& channelName);
		bool		operator==(Channel const& other);


		static size_t	isChannel(std::vector<Channel>vChnl, std::string chnName);
		void		send_channel_message(Client sender, std::string message) const;
};

