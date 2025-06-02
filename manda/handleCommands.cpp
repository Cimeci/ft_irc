/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:52:16 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 14:29:29 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"
# include "Channel/Channel.hpp"
# include "Client/Client.hpp"

void Irc::handleClient(int client_socket, std::string input) {

	size_t end = input.find("\n");
	if (end != std::string::npos)
		input = input.substr(0, end);

	size_t space1 = input.find(' ');
	size_t space2 = input.find(' ', space1 + 1);
	size_t space3; for(space3 = space2; space3 < input.size() && input[space3] == ' '; space3++);

	std::string command = input.substr(0, space1);

	std::string target;
	if (space1 != std::string::npos && input.substr(space1 + 1, space2 - space1 - 1)[0] != ':')
		target = input.substr(space1 + 1, space2 - space1 - 1);

	std::string message;
	if (space3 != std::string::npos){
		if (input[space3] == ':') space3++;
		message = input.substr(space3);
	}
    if (command == "JOIN") {
        handleJoin(client_socket, target, message);
    }
    else if (command == "PART") {
        handlePart(client_socket, target, message);
    }
    else if (command == "TOPIC") {
        handleTopic(client_socket, target, message);
    }
	else if (command == "WHO") {
        handleWho(client_socket, target);
    }
	else if (command == "PRIVMSG") {
        handlePrivMsg(client_socket, target, message);
    }
	else if (command == "MODE") {
		handleMode(client_socket, target, message);
	}
	else if (command == "INVITE") {
		handleInvite(client_socket, target, message);
	}
	else if (command == "QUIT") {
		handleQuit(client_socket, input);
	}
	else if (command == "KICK") {
		handleKick(client_socket, target, message);
	}
	else {
		sendMessage(client_socket, ERR_UNKNOWNCOMMAND(_clientBook[client_socket]->getNickname(), command));
	}
}