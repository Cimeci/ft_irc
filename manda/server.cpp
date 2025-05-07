/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:36:37 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/07 13:48:25 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

int Irc::server() {
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		std::cerr << "Error socket()\n";
		return 1;
	}
	
	int opt = 1;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error bind()\n";
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, 10) < 0) {
        std::cerr << "Error listen()\n";
        close(server_socket);
        return 1;
    }
	
	// Initialize poll structure for server socket
	pollfd server_pollfd;
	server_pollfd.fd = server_socket;
	server_pollfd.events = POLLIN;
	_pollfds.push_back(server_pollfd);
	
	std::cout << "Server listening on port " << _port << "...\n";
	
	while (true) {
		int poll_count = poll(_pollfds.data(), _pollfds.size(), -1);
		if (poll_count < 0) {
			std::cerr << "Error poll()\n";
			break;
		}
	
		// Check all file descriptors
		for (size_t i = 0; i < _pollfds.size(); i++) {
			if (_pollfds[i].revents & POLLIN) {
				if (_pollfds[i].fd == server_socket) {
					// New connection
					handleNewConnection();
				} else {
					// Client data
					handleClientData(_pollfds[i].fd);
				}
			}
		}
	}
	
	close(server_socket);
	return 0;
}

void Irc::handleNewConnection() {
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    int new_client = accept(server_socket, (sockaddr*)&client_addr, &client_len);
    if (new_client < 0) {
        std::cerr << "Error accept()\n";
        return;
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    
    std::cout << "New connection from " << client_ip << ":" 
              << ntohs(client_addr.sin_port) << "\n";

    // Add new client to poll structure
    pollfd new_pollfd;
    new_pollfd.fd = new_client;
    new_pollfd.events = POLLIN;
    _pollfds.push_back(new_pollfd);

    // Create and store new client object
    Client *new_client_obj = new Client();
    clientBook[new_client] = new_client_obj;

	std::string welcome = "\033[38;5;214mWelcome to the IRC server from the Climbers team's.\033[0m\n\nPlease enter PASS / NICK / USER to connect\r\n";
	send(new_client, welcome.c_str(), welcome.length(), 0);
}

void Irc::handleClientData(int fd) {
    Client *client = clientBook[fd];
	// std::string response;

    switch(client->getState()) {
        case Client::CONNECTED:
            handlePassword(fd);
            break;
        case Client::AUTHENTICATED:
            handleNickname(fd);
            break;
        case Client::REGISTERED:
            handleUsername(fd);
            break;
		case Client::USER:
			handleClient(fd);
			break;
        default:
            close(fd);
            break;
    }
}