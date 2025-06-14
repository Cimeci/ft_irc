/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:28:52 by inowak--          #+#    #+#             */
/*   Updated: 2025/06/04 11:28:59 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"

void Irc::handlePassword(int client_socket, std::string input) {
	std::string defaultNick = "*";
	std::string command = input.substr(0, input.find(" "));

	if (command != "PASS") {
		if (command == "USER" || command == "NICK")
			return ;
		else
			sendMessage(client_socket, _serverName + ERR_UNKNOWNCOMMAND(defaultNick, input));
	}
	else if (input.length() < 6)
		sendMessage(client_socket, _serverName + ERR_NEEDMOREPARAMS(defaultNick));
	else if (!strcmp(input.substr(0, 5).c_str(), "PASS ")
		&& !strcmp(_password.c_str(), input.substr(5, input.size() - 5).c_str())) {
		_clientBook[client_socket]->setState(Client::AUTHENTICATED);
	}
	else if (!strcmp(input.substr(0, 5).c_str(), "PASS "))
		sendMessage(client_socket, _serverName + ERR_PASSWDMISMATCH(defaultNick));
}

bool Irc::checkNickname(const std::string &input) {
	if (input.length() > 15)
		return false;
	for(int i = 0; i < input[i]; i++) {
		if (!isalnum(input[i]) && !std::strchr("[]{}\'|", input[i]))
			return false;
	}
	return true;
}

void Irc::handleNickname(int client_socket, std::string input) {
	std::string defaultNick = "*";
	std::string command = input.substr(0, input.find(" "));
	
	if (command != "NICK") {
		if (command == "PASS")
			sendMessage(client_socket, ERR_ALREADYREGISTERED(_clientBook[client_socket]->getNickname()));
		else if (command == "USER")
			return ; 
		else
			sendMessage(client_socket, ERR_UNKNOWNCOMMAND(defaultNick, input));
		return ;
	}
	if (input.length() < 6) {
		sendMessage(client_socket, _serverName + ERR_NONICKNAMEGIVEN(defaultNick));
		return ;
	}
	std::string newNick = input.substr(5, input.length() - 5);
	if (valueExist(newNick))
		sendMessage(client_socket, _serverName + ERR_NICKNAMEINUSE(defaultNick, newNick));
	else if (!checkNickname(newNick))
		sendMessage(client_socket, ERR_ERRONEUSNICKNAME(defaultNick, newNick));
	else if (!strcmp(input.substr(0, 5).c_str(), "NICK ") && input.length() > 5) {
		if (_clientBook[client_socket]->getState() == Client::USER)
			sendMessage(client_socket, NICK(_clientBook[client_socket]->getNickname(), _clientBook[client_socket]->getUsername(), newNick));
		else
			_clientBook[client_socket]->setState(Client::REGISTERED);
		_clientBook[client_socket]->setNickname(newNick);
		_nicknameToFd[newNick] = client_socket;
	}
}

void Irc::successfulRegistration(int client_socket) {
	std::string nick = _clientBook[client_socket]->getNickname();
	std::string user = _clientBook[client_socket]->getUsername();

	sendMessage(client_socket, _serverName + RPL_WELCOME(nick, user, user));
	sendMessage(client_socket, _serverName + RPL_YOURHOST(user, _serverName));
	sendMessage(client_socket, _serverName + RPL_CREATED(user, getTime()));
	sendMessage(client_socket, _serverName + RPL_MYINFO(user, _serverName));
	sendMessage(client_socket, _serverName + RPL_ISUPPORT(nick));
}

void Irc::handleUsername(int client_socket, std::string input) {
	std::string user;
	std::string command = input.substr(0, input.find(" "));

	if (command != "USER") {
		if (command == "PASS")
			sendMessage(client_socket, ERR_ALREADYREGISTERED(_clientBook[client_socket]->getNickname()));
		else if (command == "NICK")
			handleNickname(client_socket, input);
		else
			sendMessage(client_socket, _serverName + ERR_UNKNOWNCOMMAND(_clientBook[client_socket]->getNickname(), input));
	}
	else if (input.length() < 6)
		sendMessage(client_socket, _serverName + ERR_NEEDMOREPARAMS(_clientBook[client_socket]->getNickname()));
	else if (!strcmp(input.substr(0, 5).c_str(), "USER ") && input.size() > 5) {
		user = input.substr(input.find(" ") + 1, input.size());
		user = user.substr(0, user.find(" "));
		_clientBook[client_socket]->setUsername(user);
		_clientBook[client_socket]->setState(Client::USER);
		successfulRegistration(client_socket);
		std::cout << ORANGE << _clientBook[client_socket]->getUsername() << " has connected to Irc server" << RESET << std::endl;
	}
}
