/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:04:39 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/21 13:00:56 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Bot.hpp"
# include "gamble.hpp"

Bot* g_bot = NULL;

Bot::Bot(std::string port, std::string password): _port(port), _password(password), _stop(false){

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

void handle_sigint(int sig){
	(void)sig;
	g_bot->setStop(true);
	sendMessage(g_bot->getFd(), "KICK #GambleRoom " + g_bot->getSender() + "\r\n");
	sendMessage(g_bot->getFd(), "QUIT\r\n");
	close(g_bot->getFd());
}

void Bot::dealer(){
	g_bot = this;
	std::string input;
	std::signal(SIGINT, handle_sigint);

	sendMessage(_socketFd, "JOIN #GambleRoom\r\n");
	while (1){
		input = recvMessage(_socketFd);
		if (input.find("JOIN #GambleRoom") != std::string::npos &&
		input.find("GambleDealer") != std::string::npos)
		break;
	}
	sendMessage(_socketFd, "MODE #GambleRoom +il 2\r\n");
	while (_stop == false)
	{
		input = recvMessage(_socketFd);
		if (!input.empty()){
			std::cout << input << std::endl;
			_sender = input.substr(1, input.find(" ") - 1);
			if (_sender.find("!") != std::string::npos)
				_sender = _sender.substr(0, _sender.find("!"));
			std::string message = input.substr(input.find(":", 1) + 1);
			if (message == "GAMBLE\r\n")
			{
				sendMessage(_socketFd, "INVITE " + _sender + " #GambleRoom\r\n");
				sendChannelMessage(_socketFd, "NEW GAMBLE GAME");
			}
			if (input.find("JOIN #GambleRoom") != std::string::npos &&
				input.find(_sender) != std::string::npos) {
				std::cout << "ready to play" << std::endl;
				Gamble gamble(100);
				if (gamble.playGamble(_socketFd))
					sendMessage(_socketFd, "KICK #GambleRoom " + _sender + "\r\n");
			}
		}
	}
	sendMessage(_socketFd, "QUIT\r\n");
	close(_socketFd);
}