/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:48 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 14:35:43 by inowak--         ###   ########.fr       */
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
# include <cstring>
# include <vector>
# include <cstdlib>
# include <map>
# include <string>
# include <algorithm>
# include <sstream>
# include <ctime>
# include <csignal>

class Client;
class Channel;

# include "../Client/Client.hpp"
# include "../Channel/Channel.hpp"

# define PORT 6667
# define BUFFER_SIZE 1024
# define MAX_PORT 65535
# define MAX_CLIENTS 1000
# define HEXCHAT_OPT "CAP LS 302"

class Irc{
	private:
		const std::string _serverName;
		int _server_socket;
		int _port;
		std::string _password;
		bool _serverRunning;

		std::vector<pollfd> _pollfds;

		std::map<int, Client *> _clientBook;
		std::map<std::string, Channel *> _channels;
		std::map<std::string, int> _nicknameToFd;

	public:
		Irc(): _serverName(":irc.climbers.ni"), _serverRunning(true) {}
		bool setParameters(const int port, const std::string password);

		int server();

		int getServerSocket() const;
		std::map<int, Client *>& getClientBook();
		std::map<std::string, Channel *>& getChannels();
		std::vector<pollfd>& getPollFds();
		

		void handleNewConnection();
		void handleClientData(int fd);

		void handlePassword(int client_socket, std::string input);
		void handleNickname(int client_socket, std::string input);
		void handleUsername(int client_socket, std::string input);

		void handleClient(int client_socket, std::string input);

		void handleJoin(int fd, const std::string& channelName, const std::string& passChannel);
		void handlePart(int fd, const std::string& channelName, const std::string& reason);
		void handleTopic(int fd, const std::string& channelName, const std::string& topic);
		void handleQuit(int fd, std::string reason);
		void handleWho(int fd, const std::string& channelName);
		void handlePrivMsg(int fd, const std::string& target, const std::string& message);
		void handleMode(int fd, const std::string &channelName, const std::string &mode);
		void handleInvite(int fd, const std::string &channelName, const std::string &client);
		void handleKick(int fd, std::string channel, std::string after);
		
		void sendMessage(int fd, std::string msg);

		bool valueExist(std::string value);
		void successfulRegistration(int client_socket);
		void setServerRunning(bool b);
};

std::vector<std::string> ft_split(std::string str, const std::string &c);
std::string getTime(void);
