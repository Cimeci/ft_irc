/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:28:52 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 14:29:58 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"

void Irc::handlePassword(int client_socket, std::string input) {
	std::string response;
	std::string defaultNick = "*";

	if (!strcmp(input.substr(0, 5).c_str(), "PASS ") && !strcmp(_password.c_str(), input.substr(5, input.size() - 5).c_str())) {
		_clientBook[client_socket]->setState(Client::AUTHENTICATED);
	}
	else if (input.length() < 6) {
		response = _serverName + ERR_NEEDMOREPARAMS(defaultNick);
		send(client_socket, response.c_str(), response.length(), 0);
		std::cout << "error password: no password" << std::endl;
	}
	else if (!strcmp(input.substr(0, 5).c_str(), "PASS ")) {
		response = _serverName + ERR_PASSWDMISMATCH(defaultNick);
		send(client_socket, response.c_str(), response.length(), 0);
		std::cout << "error password : input : " << input.substr(5, input.size() - 5) << std::endl;
	}
	else {
		response = _serverName + ERR_UNKNOWNCOMMAND(defaultNick, input);
		send(client_socket, response.c_str(), response.length(), 0);
		std::cout << "error keyword : input : " << input.substr(0, input.size()) << std::endl;
	}
}

void Irc::handleNickname(int client_socket, std::string input) {
	std::string response;
	std::string defaultNick = "*";

	if (input.length() <= 5) {
		response = _serverName + ERR_NONICKNAMEGIVEN(defaultNick);
		send(client_socket, response.c_str(), response.length(), 0);
	}
	else if (valueExist(input.substr(5, input.length() - 5))) {
		response = _serverName + ERR_NICKNAMEINUSE(defaultNick, input.substr(5, input.size() - 5));
		send(client_socket, response.c_str(), response.length(), 0);
	}
	else if (!strcmp(input.substr(0, 5).c_str(), "NICK ") && input.length() > 5) {
		_clientBook[client_socket]->setNickname(input.substr(5, input.length() - 5));
		_nicknameToFd[input.substr(5, input.length() - 5)] = client_socket; 
		_clientBook[client_socket]->setState(Client::REGISTERED);
	}
	else {
		response = _serverName + ERR_UNKNOWNCOMMAND(defaultNick, input);
		send(client_socket, response.c_str(), response.length(), 0);
		std::cout << "error nickname : input : " << input.substr(0, 5) << std::endl;
	}
}

void Irc::successfulRegistration(int client_socket) {
	std::string nick = _clientBook[client_socket]->getNickname();
	std::string user = _clientBook[client_socket]->getUsername();

	std::string response = _serverName + RPL_WELCOME(nick, user, user);
	send(client_socket, response.c_str(), response.length(), 0);
	response = _serverName + RPL_YOURHOST(user, _serverName);
	send(client_socket, response.c_str(), response.length(), 0);
	response = _serverName + RPL_CREATED(user, getTime());
	send(client_socket, response.c_str(), response.length(), 0);
	response = _serverName + RPL_MYINFO(user, _serverName);
	send(client_socket, response.c_str(), response.length(), 0);
}

void Irc::handleUsername(int client_socket, std::string input) {
	std::string response;
	std::string user;

	if (input.length() <= 5){
		response = _serverName + ERR_NEEDMOREPARAMS(_clientBook[client_socket]->getNickname());
		send(client_socket, response.c_str(), response.length(), 0);
		std::cout << "error username : input : " << input.substr(0, 5) << std::endl;
	}
	else if (!strcmp(input.substr(0, 5).c_str(), "USER ") && input.size() > 5) {
		user = input.substr(input.find(" ") + 1, input.size());
		user = user.substr(0, user.find(" "));
		_clientBook[client_socket]->setUsername(user);
		_clientBook[client_socket]->setState(Client::USER);
		successfulRegistration(client_socket);
		std::cout << ORANGE << _clientBook[client_socket]->getUsername() << " has been connected on Irc server" << RESET << std::endl;
	}
	else {
		response = _serverName + ERR_UNKNOWNCOMMAND(_clientBook[client_socket]->getNickname(), input);
		send(client_socket, response.c_str(), response.length(), 0);
		std::cout << "error username : input : " << input.substr(0, 5) << std::endl;
	}
}
