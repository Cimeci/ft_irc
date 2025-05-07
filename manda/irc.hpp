/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:48 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/07 13:48:46 by inowak--         ###   ########.fr       */
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

#define PORT 6667
#define BUFFER_SIZE 1024
#define MAX_PORT 65535

class Irc{
	private:
		
		int server_socket;
		int _port;
		std::string _password;
		std::map<int, Client *> clientBook;
		std::vector<pollfd> _pollfds;
	
	public:
		bool setParameters(const int port, const std::string password);
		bool parsing();
		
		int server();
		int clients();
		
		void handleNewConnection();
		void handleClientData(int fd);
		
		void handlePassword(int client_socket);
		void handleNickname(int client_socket);
		void handleUsername(int client_socket);

		void handleClient(int client_socket);

};
