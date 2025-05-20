/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:04:39 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 14:29:17 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Bot.hpp"

Bot::Bot(std::string port, std::string password): _port(port), _password(password){

	_socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketFd < 0) {
    	std::cerr << "[ERROR] socket" << std::endl;
    	exit(1);
	}

	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(_port.c_str()));
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    	std::cerr << "Invalid address" << std::endl;
    	exit(1);
	}

	if (connect(_socketFd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cerr << "[ERROR] connect" << std::endl;
		exit(1);
	}

	std::string msg;
	sendMessage(_socketFd, "PASS " + _password + "\r\n");
	sendMessage(_socketFd, "NICK GambleDealer\r\n");
	sendMessage(_socketFd, "USER Gamble\r\n");
}

Bot::~Bot(){}

void Bot::dealer(){
	while (1)
	{
		std::string input = recvMessage(_socketFd);
		if (!input.empty())
			return ;
		std::string sender = input.substr(1, input.find(" "));
		std::string message = input.substr(input.find(":", 1));
		if (message == "GAMBLE")
		{
			sendMessage(_socketFd, "JOIN #GambleRoom\r\n");
			sendMessage(_socketFd, "MODE +il 2\r\n");
			sendMessage(_socketFd, "INVITE " + sender + " #GambleRoom\r\n");
			Gamble gamble = Gamble(100);
			if (gamble.playGamble(_socketFd))
				sendMessage(_socketFd, "KICK #GambleRoom " + sender + "\r\n");
		}
	}
}