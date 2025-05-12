/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:15:06 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/12 17:12:55 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"
# include "irc.hpp"

Channel::Channel(const std::string& name) : _name(name), _topic(""), _symbol("=") {}

void Channel::addClient(int client_fd, Client &client) {
	if (!isClientInChannel(client_fd))
		_clients[client_fd] = &client;
}

void Channel::removeClient(int client_fd) {
	_clients.erase(client_fd);
}

bool Channel::isClientInChannel(int client_fd) const {
	return _clients.find(client_fd) != _clients.end();
}



void Channel::broadcast(const std::string& message, int sender_fd) {
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->first != sender_fd && it->second->getBanState() < 2)
			send(it->first, message.c_str(), message.length(), 0);
	}
}


std::string Channel::getName() const { return _name; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

std::string Channel::getTopic() const { return _topic; }

void Channel::setSymbol(const std::string& symbol) { _symbol = symbol; }

std::string Channel::getSymbol() const { return _symbol; }

const std::map<int, Client *>& Channel::getClients() const {
    return _clients;
}
