/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:48 by inowak--          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/13 15:10:43 by ncharbog         ###   ########.fr       */
=======
/*   Updated: 2025/05/14 11:08:08 by inowak--         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../includes/colors.hpp"
# include "../includes/error.hpp"

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

class Client;
class Channel;

# include "Client.hpp"
# include "Channel.hpp"

# define PORT 6667
# define BUFFER_SIZE 1024
# define MAX_PORT 65535
# define MAX_CLIENTS 1000
# define HEXCHAT_OPT "CAP LS 302"

class Irc{
	private:
		const std::string serverName;
		int server_socket;
		int _port;
		std::string _password;

		std::vector<pollfd> _pollfds;

		std::map<int, Client *> clientBook;
		std::map<std::string, Channel *> _channels;

	public:
		Irc(): serverName(":irc.climbers.ni") {}
		bool setParameters(const int port, const std::string password);

		int server();

		void handleNewConnection();
		void handleClientData(int fd);

		void handlePassword(int client_socket, std::string input);
		void handleNickname(int client_socket, std::string input);
		void handleUsername(int client_socket, std::string input);

		void handleClient(int client_socket, std::string input);

		void handleJoin(int fd, const std::string& channelName, const std::string& passChannel);
		void handlePart(int fd, const std::string& channelName);
		void handleTopic(int fd, const std::string& channelName, const std::string& topic);
		void handleQuit(int fd);
		void handleWho(int fd, const std::string& channelName);
		void handlePrivMsg(int fd, const std::string& target, const std::string& message);
		void handleMode(int fd, const std::string &target);


		void sendMessage(int fd, std::string msg);

		bool valueExist(std::string value);
		void successfulRegistration(int client_socket);
};

std::vector<std::string> ft_split(std::string str, const std::string c);
std::string getTime(void);
