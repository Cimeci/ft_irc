/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:36:37 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 14:56:33 by inowak--         ###   ########.fr       */
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
		for (size_t i = 0; i < _pollfds.size(); i++) {
			if (_pollfds[i].revents & POLLOUT) {
				Client* client = clientBook[_pollfds[i].fd];
				if (!client) continue;
				if (client->hasDataToSend()){
					send(_pollfds[i].fd, client->getBuffer().c_str(), client->getBuffer().length(), 0);
					_pollfds[i].events &= ~POLLOUT;
				}
				if (client->getShouldClose()) {
					std::cout << client->getBuffer() << std::endl;
					delete clientBook[_pollfds[i].fd];
					clientBook.erase(_pollfds[i].fd);
					close(_pollfds[i].fd);
					_pollfds.erase(_pollfds.begin() + i);
					--i;
				}
			}
			if (_pollfds[i].revents & POLLIN) {
				if (_pollfds[i].fd == server_socket) {
					handleNewConnection();
				} else {
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

	if (_pollfds.size() > MAX_CLIENTS) {
		std::cerr << "Too many clients\n";
		close(new_client);
		return;
	}


    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);

    std::cout << "New connection from " << client_ip << ":"
              << ntohs(client_addr.sin_port) << "\n";


	std::cout << "Currently : " << _pollfds.size() - 1 << " clients has connected" << std::endl;

	// Add new client to poll structure
    pollfd new_pollfd;
    new_pollfd.fd = new_client;
    new_pollfd.events = POLLIN;
    _pollfds.push_back(new_pollfd);

    // Create and store new client object
    Client *new_client_obj = new Client();
    clientBook[new_client] = new_client_obj;

	std::string openInput = "Please enter PASS / NICK / USER to connect\r\n";
	send(new_client, openInput.c_str(), openInput.length(), 0);
}

void Irc::handleClientData(int fd) {
    Client *client = clientBook[fd];
    char buffer[BUFFER_SIZE];
    std::string input;

    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(fd, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_received <= 0) {
		std::cout << "Client disconnected: fd " << fd << std::endl;
		close(fd);
		delete clientBook[fd];
		clientBook.erase(fd);
		for (std::vector<pollfd>::iterator it = _pollfds.begin(); it != _pollfds.end(); ++it) {
			if (it->fd == fd) {
				_pollfds.erase(it);
				break;
			}
		}
		return;
	}

	input = std::string(buffer);
	std::vector<std::string> split;
	if (input.find("\r\n") != std::string::npos)
		split = ft_split(input, "\r\n");
	else
		split = ft_split(input, "\n");
	std::cout << "------ split input -----" << std::endl;
	for (size_t i = 0; i < split.size(); i++)
		std::cout << "split : " << split[i] << std::endl;
	std::cout << "------------------------" << std::endl;
	for (size_t i = 0; i < split.size(); i++)
	{
		if (split[i] == HEXCHAT_OPT);
		else {
			switch(client->getState()) {
				case Client::CONNECTED:
					handlePassword(fd, split[i]);
					break;
				case Client::AUTHENTICATED:
					handleNickname(fd, split[i]);
					break;
				case Client::REGISTERED:
					handleUsername(fd, split[i]);
					break;
				case Client::USER:
				{
					std::string::size_type pos = split[i].find(' ');
					if (pos != std::string::npos)
						std::transform(split[i].begin(), split[i].begin() + pos, split[i].begin(), ::toupper);
					handleClient(fd, split[i]);
					break;
				}
				default:
					close(fd);
					break;
			}
		}
	}
}