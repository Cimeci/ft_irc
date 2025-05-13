/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:48 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/13 10:59:28 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../includes/colors.hpp"

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

# define RPL_WELCOME(client, nick, user) (std::string(" 001 ") + client + std::string(" :Welcome to the IRC Network, ") + nick + std::string(" [!") + user + std::string("@host]\r\n"))
# define RPL_YOURHOST(client, server) (std::string(" 002 ") + client + std::string(" :Your host is ") + server + std::string(", running version 1\r\n"))
# define RPL_CREATED(client, date) (std::string(" 003 ") + client + std::string(" :This server was created ") + date + std::string("\r\n"))
# define RPL_MYINFO(client, server) (std::string(" 004 ") + client + std::string(" ") + server + std::string("<available user modes> <available channel modes> [<channel modes with a parameter>]"))
# define ERR_UNKNOWNCOMMAND(client, cmd) (std::string(" 421 ") + client + std::string(" ") + cmd + std::string(" :Unknown command\r\n"))
# define ERR_NONICKNAMEGIVEN(client) (std::string(" 431 ") + client + std::string(" :No nickname given\r\n"))
# define ERR_NICKNAMEINUSE(client, nick) (std::string(" 433 ") + client + std::string(" ") + nick + std::string(" :Nickname is already in use\r\n"))
# define ERR_NEEDMOREPARAMS(client) (std::string(" 461 ") + client + std::string(" PASS :Not enough parameters\r\n"))
# define ERR_PASSWDMISMATCH(client) (std::string(" 464 ") + client + std::string(" :Password incorrect\r\n"))

class Irc{
	private:
		const std::string server_name;
		int server_socket;
		int _port;
		std::string _password;

		std::vector<pollfd> _pollfds;

		std::map<int, Client *> clientBook;
		std::map<std::string, Channel *> _channels;

	public:
		Irc(): server_name(":irc.climbers.ni") {}
		bool setParameters(const int port, const std::string password);

		int server();

		void handleNewConnection();
		void handleClientData(int fd);

		void handlePassword(int client_socket, std::string input);
		void handleNickname(int client_socket, std::string input);
		void handleUsername(int client_socket, std::string input);

		void handleClient(int client_socket, std::string input);

		void handleJoin(int fd, const std::string& channelName);
		void handlePrivMsg(int fd, const std::string& target, const std::string& message);
		void handlePart(int fd, const std::string& channelName);
		void handleTopic(int fd, const std::string& channelName, const std::string& topic);

		bool valueExist(std::string value);
		void successfulRegistration(int client_socket);
};

std::vector<std::string> ft_split(std::string str, const std::string c);
std::string getTime(void);
