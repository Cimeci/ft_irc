/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:04:39 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 18:34:43 by inowak--         ###   ########.fr       */
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
		if (!input.empty()){
			std::cout << input << std::endl;
			std::string sender = input.substr(1, input.find(" ") - 1);
			std::string message = input.substr(input.find(":", 1) + 1);
			if (message == "GAMBLE\r\n")
			{
				sendMessage(_socketFd, "JOIN #GambleRoom\r\n");
			
				while (1){
					input = recvMessage(_socketFd);
					if (input.find("JOIN #GambleRoom") != std::string::npos &&
						input.find("GambleDealer") != std::string::npos)
						break;
				}
			
				sendMessage(_socketFd, "MODE #GambleRoom +il 2\r\n");
				sendMessage(_socketFd, "INVITE " + sender + " #GambleRoom\r\n");
				sendChannelMessage(_socketFd, "NEW GAMBLE GAME");
			
				while (1){
					input = recvMessage(_socketFd);
					if (input.find("JOIN #GambleRoom") != std::string::npos &&
						input.find(sender) != std::string::npos)
						break;
				}
			
				std::cout << "ready to play" << std::endl;
				Gamble gamble(100);
				if (gamble.playGamble(_socketFd))
				{
					std::cout << "have to kick the player" << std::endl;
					sendMessage(_socketFd, "KICK #GambleRoom " + sender + "\r\n");
				}
			}
		}
	}
}