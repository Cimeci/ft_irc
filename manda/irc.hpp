/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:30:48 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/06 17:28:57 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <cstring>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <cstdlib>
# include <map>

# include "Client.hpp"

#define PORT 6667
#define BUFFER_SIZE 1024
#define MAX_PORT 65535

class Irc{
	private:
		
		int client_socket;
		int server_socket;
		int _port;
		std::string _password;
		std::map<int, Client *> clientBook;
	
	public:
		bool setParameters(const int port, const std::string password);
		bool parsing();
		
		int server();
		int clients();
		
		void connection();
		


};
