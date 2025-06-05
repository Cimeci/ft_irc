/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:48 by inowak--          #+#    #+#             */
/*   Updated: 2025/06/04 11:23:19 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../../includes/colors.hpp"
# include "IRCMacros.hpp"

# ifndef BONUS
	# include "../../bonus/gamble.hpp"
# endif

# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <poll.h>
# include <iostream>
# include <iomanip>
# include <cstring>
# include <vector>
# include <cstdlib>
# include <map>
# include <string>
# include <algorithm>
# include <sstream>
# include <ctime>
# include <csignal>
# include <cctype>

class Client;
class Channel;

# include "../Client/Client.hpp"
# include "../Channel/Channel.hpp"

# define BUFFER_SIZE 1024
# define MAX_PORT 65535
# define MAX_CLIENTS 1000
# define HEXCHAT_OPT "CAP LS 302"

struct CaseInsensitiveCompare
{
	bool operator()(const std::string& lhs, const std::string& rhs) const
	{
		std::string::const_iterator it1 = lhs.begin();
		std::string::const_iterator it2 = rhs.begin();

		while (it1 != lhs.end() && it2 != rhs.end()) {
			char c1 = std::tolower(static_cast<unsigned char>(*it1));
			char c2 = std::tolower(static_cast<unsigned char>(*it2));
			if (c1 < c2)
				return true;
			else if (c1 > c2)
				return false;
			++it1;
			++it2;
		}
		return lhs.length() < rhs.length();
	}
};

class Irc{
	private:
		const std::string _serverName;
		int _serverSocket;
		int _port;
		std::string _password;
		bool _serverRunning;

		std::vector<pollfd> _pollfds;

		std::map<int, Client *> _clientBook;
		std::map<std::string, Channel *, CaseInsensitiveCompare> _channels;
		std::map<std::string, int, CaseInsensitiveCompare> _nicknameToFd;

	public:
		Irc(): _serverName(":irc.climbers.ni"), _serverRunning(true) {}
		bool setParameters(const int port, const std::string &password);

		int server();

		int getServerSocket() const;
		std::map<int, Client *>& getClientBook();
		std::map<std::string, Channel *, CaseInsensitiveCompare>& getChannels();
		std::vector<pollfd>& getPollFds();


		void handleNewConnection();
		void handleClientData(int fd);

		void handlePassword(int client_socket, std::string input);
		void handleNickname(int client_socket, std::string input);
		void handleUsername(int client_socket, std::string input);

		bool checkNickname(const std::string &input);

		void handleCommand(int client_socket, std::string input);

		void handleJoin(int fd, const std::string& channelName, const std::string& passChannel);
		void handlePart(int fd, const std::string &channelName, const std::string& reason);
		void handleTopic(int fd, std::string channelName, const std::string& topic);
		void handleQuit(int fd, std::string reason);
		void handleWho(int fd, std::string channelName);
		void handlePrivMsg(int fd, const std::string& target, const std::string& message);
		void handleMode(int fd, std::string channelName, const std::string &mode);
		void handleInvite(int fd, const std::string &client, std::string channelName);
		void handleKick(int fd, std::string channel, std::string after);

		bool valueExist(const std::string &value);
		void successfulRegistration(int client_socket);
		void setServerRunning(bool b);
		bool compareEquality(const std::string &s1, const std::string &s2);
};

void sendMessage(int fd, std::string msg);
std::vector<std::string> ft_split(std::string str, const std::string &c);
std::string getTime(void);
std::string toUpper(std::string &str);
