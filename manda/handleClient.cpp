/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClient.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:52:16 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/08 18:13:22 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"
# include "Channel.hpp"
# include "Client.hpp"

void Irc::handleClient(int client_socket) {
    char buffer[BUFFER_SIZE];
    std::string input;
    
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received <= 0) {
        return;
    }
    
    input = std::string(buffer, bytes_received);
    
    size_t end = input.find("\n");
    if (end != std::string::npos) {
        input = input.substr(0, end);
    }
    
    size_t space1 = input.find(' ');
    std::string command = input.substr(0, space1);
    
    if (command == "JOIN") {
        std::string channel = input.substr(space1 + 1);
        handleJoin(client_socket, channel);
    }
    else if (command == "PRIVMSG") {
        size_t space2 = input.find(' ', space1 + 1);
        std::string target = input.substr(space1 + 1, space2 - space1 - 1);
        std::string message = input.substr(space2 + 1);
		std::cout << YELLOW << "<server>" << RESET << " PRIVMSG " << target << " " << message << std::endl;
        handlePrivMsg(client_socket, target, message);
    }
    else if (command == "PART") {
        std::string channel = input.substr(space1 + 1);
        handlePart(client_socket, channel);
    }
    else if (command == "TOPIC") {
        size_t space2 = input.find(' ', space1 + 1);
        std::string channel = input.substr(space1 + 1, space2 - space1 - 1);
        std::string topic = input.substr(space2 + 1);
        handleTopic(client_socket, channel, topic);
    }
	else if (command == "QUIT") {
		close(client_socket);
	}
}