/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:28:52 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/07 13:55:42 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void Irc::handlePassword(int client_socket) {
    char buffer[BUFFER_SIZE];
    std::string input;
    std::string response;
    
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received <= 0) {
        return;
    }
    
    input = std::string(buffer);
    if (!strcmp(input.substr(0, 5).c_str(), "PASS ") && !strcmp(_password.c_str(), input.substr(5, input.size() - 6).c_str())) {
        std::cout << "Password correct\n";
        clientBook[client_socket]->setState(Client::AUTHENTICATED);
        response = "Password accepted\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
	else if (!strcmp(input.substr(0, 5).c_str(), "PASS ")){
        response = "error :irc.climbers 464 * :Password incorrect\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
        std::cout << "error password : input : " << input.substr(5, input.size() - 6) << std::endl;
    }
	else {
		response = "error :irc.climbers * :Keyword incorrect\r\n";
		send(client_socket, response.c_str(), response.length(), 0);
        std::cout << "error keyword : input : " << input.substr(0, 5) << std::endl;
	}
}

void Irc::handleNickname(int client_socket) {
    char buffer[BUFFER_SIZE];
    std::string input;
    std::string response;

    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received <= 0) {
        return;
    }
    
    input = std::string(buffer);
    if (!strcmp(input.substr(0, 5).c_str(), "NICK ")) {
        std::cout << "Nick input : " << input.substr(5, input.size() - 6) << std::endl;
        clientBook[client_socket]->setNickname(input.substr(5, input.size() - 6));
        clientBook[client_socket]->setState(Client::REGISTERED);
        response = "Nickname accepted\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
	else {
        response = "error :irc.climbers * :Keyword incorrect\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
        std::cout << "error nickname : input : " << input.substr(0, 5) << std::endl;
    }
}

void Irc::handleUsername(int client_socket) {
    char buffer[BUFFER_SIZE];
    std::string input;
    std::string response;

    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    
    if (bytes_received <= 0) {
        return;
    }
    
    input = std::string(buffer);
    if (!strcmp(input.substr(0, 5).c_str(), "USER ")) {
        std::cout << "User input : " << input.substr(5, input.size() - 6) << std::endl;
        clientBook[client_socket]->setUsername(input.substr(5, input.size() - 6));
        clientBook[client_socket]->setState(Client::USER);
        response = "Username accepted\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
    }
	else {
        response = "error :irc.climbers * :Keyword incorrect\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
        std::cout << "error username : input : " << input.substr(0, 5) << std::endl;
    }
}