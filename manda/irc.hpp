/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:48 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/07 15:12:16 by inowak--         ###   ########.fr       */
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

# include "Client.hpp"
# include "Channel.hpp"

#define PORT 6667
#define BUFFER_SIZE 1024
#define MAX_PORT 65535

class Irc{
	private:
		
		int server_socket;
		int _port;
		std::string _password;
		
		std::vector<pollfd> _pollfds;
		
		std::map<int, Client *> clientBook;
		std::map<std::string, Channel*> _channels;
	
	public:
		bool setParameters(const int port, const std::string password);
		
		int server();
		
		void handleNewConnection();
		void handleClientData(int fd);
		
		void handlePassword(int client_socket);
		void handleNickname(int client_socket);
		void handleUsername(int client_socket);

		void handleClient(int client_socket);

		void handleJoin(int fd, const std::string& channelName);
		void handlePrivMsg(int fd, const std::string& target, const std::string& message);
		void handlePart(int fd, const std::string& channelName);
		void handleTopic(int fd, const std::string& channelName, const std::string& topic);

};
