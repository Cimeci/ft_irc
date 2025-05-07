/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClient.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:52:16 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/07 14:05:56 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void Irc::handleClient(int client_socket){
	char buffer[BUFFER_SIZE];
    std::string input;
    std::string response;

    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received <= 0) {
        return;
    }
    
    input = std::string(buffer);
    if (!strcmp(input.c_str(), "MSG\n")) {
        response = "hello world\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
	if (!strcmp(input.c_str(), "GETNICK\n")) {
        response = "Your Nickanme: " + clientBook[client_socket]->getNickname() + "\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
	if (!strcmp(input.c_str(), "GETUSER\n")) {
        response = "Your Username: " + clientBook[client_socket]->getUsername() + "\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
}