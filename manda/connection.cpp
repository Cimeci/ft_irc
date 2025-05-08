/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:28:52 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/08 14:40:08 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void Irc::handlePassword(int client_socket, std::string input) {
    std::string response;
	
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

void Irc::handleNickname(int client_socket, std::string input) {
    std::string response;
	
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

void Irc::handleUsername(int client_socket, std::string input) {
    std::string response;
	
    if (!strcmp(input.substr(0, 5).c_str(), "USER ")) {
        std::cout << "User input : " << input.substr(5, input.size() - 6) << std::endl;
        clientBook[client_socket]->setUsername(input.substr(5, input.size() - 6));
        clientBook[client_socket]->setState(Client::USER);
        response = "Username accepted\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
		std::string welcome = "\n\033[38;5;214mWelcome to the IRC server from the Climbers team's.\033[0m\r\n\n";
		send(client_socket, welcome.c_str(), welcome.length(), 0);
    }
	else {
        response = "error :irc.climbers * :Keyword incorrect\r\n";
        send(client_socket, response.c_str(), response.length(), 0);
        std::cout << "error username : input : " << input.substr(0, 5) << std::endl;
    }
}