/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClient.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:52:16 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/15 15:51:34 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"
# include "Channel.hpp"
# include "Client.hpp"

void Irc::sendMessage(int fd, std::string msg)
{
	std::cout << ORANGE << "[SEND] " << RESET << msg;
	send(fd, msg.c_str(), msg.length(), 0);
}

void Irc::handleClient(int client_socket, std::string input) {

	size_t end = input.find("\n");
	if (end != std::string::npos)
		input = input.substr(0, end);

	size_t space1 = input.find(' ');
	size_t space2 = input.find(' ', space1 + 1);
	size_t space3; for(space3 = space2; space3 < input.size() && input[space3] == ' '; space3++);

	std::cout << BLUE << "[DEBUG] " << RESET << "space1: " << space1 << " | space2: " << space2 << " | space3: " << space3 << std::endl;

	std::string command = input.substr(0, space1);

	std::string target;
	if (space1 != std::string::npos && input.substr(space1 + 1, space2 - space1 - 1)[0] != ':')
		target = input.substr(space1 + 1, space2 - space1 - 1);

	std::string message;
	if (space3 != std::string::npos){
		if (input[space3] == ':') space3++;
		message = input.substr(space3);
	}
	std::cout << BLUE << "[DEBUG] " << RESET << "command: " << command << " | target: " << target << " | message: " << message << std::endl;

    if (command == "JOIN") {
        handleJoin(client_socket, target, message);
    }
    else if (command == "PART") {
        handlePart(client_socket, target);
    }
    else if (command == "TOPIC") {
        handleTopic(client_socket, target, message);
    }
	else if (command == "WHO") {
        handleWho(client_socket, target);
    }
	else if (command == "PRIVMSG") {
		std::cout << YELLOW << "<server>" << RESET << " PRIVMSG " << target << " " << message << std::endl;
        handlePrivMsg(client_socket, target, message);
    }
	else if (command == "MODE") {
		handleMode(client_socket, target, message);
	}
	else if (command == "QUIT") {
		handleQuit(client_socket);
	}
	else if (command == "KICK") {
		handleKick(client_socket, input.substr(space1 + 1, input.length()));
	}
}