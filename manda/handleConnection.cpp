/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:28:52 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:20:54 by noacharbogn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"

void Irc::handlePassword(int client_socket, std::string input) {
	std::string response;
	std::string defaultNick = "*";

	if (!strcmp(input.substr(0, 5).c_str(), "PASS ")
		&& !strcmp(_password.c_str(), input.substr(5, input.size() - 5).c_str())) {
		_clientBook[client_socket]->setState(Client::AUTHENTICATED);
	}
	else if (input.length() < 6)
		sendMessage(client_socket, _serverName + ERR_NEEDMOREPARAMS(defaultNick));
	else if (!strcmp(input.substr(0, 5).c_str(), "PASS "))
		sendMessage(client_socket, _serverName + ERR_PASSWDMISMATCH(defaultNick));
	else
		sendMessage(client_socket, _serverName + ERR_UNKNOWNCOMMAND(defaultNick, input));
}

bool Irc::checkNickname(const std::string &input) {
	for(int i = 0; i < input[i]; i++) {
		if (!isalnum(input[i]) && !std::strchr("[]{}\'|", input[i]))
			return false;
	}
	return true;
}

void Irc::handleNickname(int client_socket, std::string input) {
	std::string response;
	std::string defaultNick = "*";

	if (input.length() <= 5)
		sendMessage(client_socket, _serverName + ERR_NONICKNAMEGIVEN(defaultNick));
	else if (valueExist(input.substr(5, input.length() - 5)))
		sendMessage(client_socket, _serverName + ERR_NICKNAMEINUSE(defaultNick, input.substr(5, input.size() - 5)));
	else if (!checkNickname(input))
		sendMessage(client_socket, ERR_ERRONEUSNICKNAME(defaultNick, input.substr(5, input.size() - 5)));
	else if (!strcmp(input.substr(0, 5).c_str(), "NICK ") && input.length() > 5) {
		_clientBook[client_socket]->setNickname(input.substr(5, input.length() - 5));
		_nicknameToFd[input.substr(5, input.length() - 5)] = client_socket; 
		_clientBook[client_socket]->setState(Client::REGISTERED);
	}
	else
		sendMessage(client_socket, _serverName + ERR_UNKNOWNCOMMAND(defaultNick, input));
}

void Irc::successfulRegistration(int client_socket) {
	std::string nick = _clientBook[client_socket]->getNickname();
	std::string user = _clientBook[client_socket]->getUsername();

	sendMessage(client_socket, _serverName + RPL_WELCOME(nick, user, user));
	sendMessage(client_socket, _serverName + RPL_YOURHOST(user, _serverName));
	sendMessage(client_socket, _serverName + RPL_CREATED(user, getTime()));
	sendMessage(client_socket, _serverName + RPL_MYINFO(user, _serverName));
}

void Irc::handleUsername(int client_socket, std::string input) {
	std::string response;
	std::string user;

	if (input.length() <= 5)
		sendMessage(client_socket, _serverName + ERR_NEEDMOREPARAMS(_clientBook[client_socket]->getNickname()));
	else if (!strcmp(input.substr(0, 5).c_str(), "USER ") && input.size() > 5) {
		user = input.substr(input.find(" ") + 1, input.size());
		user = user.substr(0, user.find(" "));
		_clientBook[client_socket]->setUsername(user);
		_clientBook[client_socket]->setState(Client::USER);
		successfulRegistration(client_socket);
		std::cout << ORANGE << _clientBook[client_socket]->getUsername() << " has been connected on Irc server" << RESET << std::endl;
	}
	else
		sendMessage(client_socket, _serverName + ERR_UNKNOWNCOMMAND(_clientBook[client_socket]->getNickname(), input));
}
