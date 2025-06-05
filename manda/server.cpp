/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:36:37 by inowak--          #+#    #+#             */
/*   Updated: 2025/06/04 11:26:37 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"

static Irc *g_irc = NULL;

void handleSigintServer(int sig){
	if (sig == 2){}
	std::cout << std::endl << std::endl;
	std::cout << RED << "+----------------------------+" << RESET << std::endl;
	std::cout << RED << "| SHUTDOWN OF THE IRC SERVER |" << RESET << std::endl;
	std::cout << RED << "+----------------------------+" << RESET << std::endl;
	std::map<int, Client *>& clientBook = g_irc->getClientBook();
	for (std::map<int, Client *>::iterator it = clientBook.begin(); it != clientBook.end(); it++){
		close(it->first);
		delete(it->second);
	}
	clientBook.clear();
	std::map<std::string, Channel *, CaseInsensitiveCompare>& channels = g_irc->getChannels();
	for (std::map<std::string, Channel *, CaseInsensitiveCompare>::iterator it = channels.begin(); it != channels.end(); it++){
		delete(it->second);
	}
	channels.clear();
	std::vector<pollfd>& pollFds = g_irc->getPollFds();
	pollFds.clear();
	g_irc->setServerRunning(false);
}

int Irc::server() {
	std::cout << GREEN << "+----------------------------+" << RESET << std::endl;
	std::cout << GREEN << "|  LAUNCH OF THE IRC SERVER  |" << RESET << std::endl;
	std::cout << GREEN << "+----------------------------+" << RESET << std::endl;

	//* Initialize Server *//
	g_irc = this;
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket < 0) {
		std::cerr << "Error socket()\n";
		return 1;
	}

	int opt = 1;
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		std::cerr << "Error setsockopt()" << std::endl;
		close(_serverSocket);
		return 1;
	}

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(_serverSocket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error bind()\n";
        close(_serverSocket);
        return 1;
    }

    if (listen(_serverSocket, MAX_CLIENTS) < 0) {
        std::cerr << "Error listen()\n";
        close(_serverSocket);
        return 1;
    }

	//* Initialize poll *//
	struct pollfd server_pollfd;
	std::memset(&server_pollfd, 0, sizeof(server_pollfd));
	server_pollfd.fd = _serverSocket;
	server_pollfd.events = POLLIN;
	_pollfds.push_back(server_pollfd);

	//* Server Listen His Port *//

	std::cout << "Server listening on port " << _port << "...\n";

	std::signal(SIGINT, handleSigintServer);
	while (_serverRunning == true) {
		for (size_t i = 0; i < _pollfds.size(); ++i)
        	_pollfds[i].revents = 0;

		int poll_count = poll(_pollfds.data(), _pollfds.size(), -1);
		if (poll_count < 0) {
			break;
		}

		for (size_t i = 0; i < _pollfds.size(); i++) {
			if (_pollfds[i].revents == 0)
            	continue;
			if (_pollfds[i].revents & POLLOUT) {
				Client* client = _clientBook[_pollfds[i].fd];
				if (!client)
					continue;
				if (client->hasDataToSend()){
					sendMessage(_pollfds[i].fd, client->getBuffer());
					_pollfds[i].events &= ~POLLOUT;
				}
				if (client->getShouldClose()) {
					std::cout << client->getBuffer() << std::endl;
					delete _clientBook[_pollfds[i].fd];
					_clientBook.erase(_pollfds[i].fd);
					close(_pollfds[i].fd);
					_pollfds.erase(_pollfds.begin() + i);
					--i;
					continue;
				}
			}
			if (_pollfds[i].revents & POLLIN) {
				if (_pollfds[i].fd == _serverSocket) {
					handleNewConnection();
				} else {
					handleClientData(_pollfds[i].fd);
				}
			}
		}
	}
	close(_serverSocket);
	return 0;
}

void Irc::handleNewConnection() {
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int new_client = accept(_serverSocket, (sockaddr*)&client_addr, &client_len);
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

    std::cout << "New connection from " << client_ip << ":" << ntohs(client_addr.sin_port) << "\n";

	std::cout << "Currently : " << _pollfds.size() - 1 << " clients has connected" << std::endl;

	//* Add new client to poll structure *//
    pollfd new_pollfd;
    new_pollfd.fd = new_client;
    new_pollfd.events = POLLIN;
	new_pollfd.revents = 0;
    _pollfds.push_back(new_pollfd);

    //* Create and store new client object *//
    Client *new_client_obj = new Client();
    _clientBook[new_client] = new_client_obj;
	std::string openInput = "Please enter PASS / NICK / USER to connect\r\n";
	sendMessage(new_client, openInput);
}

void Irc::handleClientData(int fd) {
	static std::string saveInput = "";
    Client *client = _clientBook[fd];
    char buffer[BUFFER_SIZE];
    std::string input;

    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = recv(fd, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_received <= 0) {
		std::cout << "Client disconnected: fd " << fd << std::endl;
		close(fd);
		delete _clientBook[fd];
		_clientBook.erase(fd);
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
	saveInput += input;
	if (saveInput.find("\r\n") != std::string::npos)
		split = ft_split(saveInput, "\r\n");
	else if (saveInput.find("\n") != std::string::npos)
		split = ft_split(saveInput, "\n");
	else
		return;
	if (!saveInput.empty())
		saveInput = "";
	std::cout << "------ split input -----" << std::endl;
	for (size_t i = 0; i < split.size(); i++)
		std::cout << "split : " << split[i] << std::endl;
	std::cout << "------------------------" << std::endl;

	//* Connexion Path*//

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
					handleCommand(fd, split[i]);
					break;
				}
				default:
					close(fd);
					break;
			}
		}
	}
}