/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:28:52 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/06 17:36:44 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void Irc::connection(){
	
	char buffer[BUFFER_SIZE];
	std::string input;
	std::string response;
	
	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		input = "0";
		int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
		input = std::string(buffer);
    	if (bytes_received > 0 && !strcmp(input.substr(0, 5).c_str(), "PASS ") && !strcmp(_password.c_str(), input.substr(5, input.size() - 6).c_str())) {
    	    std::cout << "Password input : " << input;
			break;
    	}
		else {
			response = ":irc.climbers 464 * :Password incorrect\r\n";
			send(client_socket, response.c_str(), response.length(), 0);
		}
	}

	Client usr;
	clientBook[client_socket] = &usr;

	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		input = "0";
		int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
		input = std::string(buffer);
    	if (bytes_received > 0 && !strcmp(input.substr(0, 5).c_str(), "NICK ")) {
    	    std::cout << "Nick input : " << input;
			clientBook[client_socket].set
			break;
    	}
		else {
			response = ":irc.climbers 464 * :Password incorrect\r\n";
			send(client_socket, response.c_str(), response.length(), 0);
		}
	}
}