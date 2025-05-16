/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:15:06 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/16 16:24:25 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"
# include "irc.hpp"

Channel::Channel(const std::string& name) : _name(name), _topic(""), _symbol("="), _invitation(false), _isOpTopic(true), _limitClients(10000), _password("") {}

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
		if (it->first != sender_fd) {
			send(it->first, message.c_str(), message.length(), 0);
		}
	}
}


std::string Channel::getName() const { return _name; }


void Channel::setTopic(const std::string& topic) { _topic = topic; }

std::string Channel::getTopic() const { return _topic; }


void Channel::setSymbol(const std::string& symbol) { _symbol = symbol; }

std::string Channel::getSymbol() const { return _symbol; }


void Channel::setPassword(const std::string& password) { _password = password; }

std::string Channel::getPassword() const { return _password; }


void Channel::setInvitaion(const bool info) { _invitation = info; }

bool Channel::getInvitation() const { return _invitation; }


void Channel::setIsOpTopic(const bool info) { _isOpTopic = info; }

bool Channel::getIsOpTopic() const { return _isOpTopic; }


void Channel::setLimitClients(const size_t limit) { _limitClients = limit; }

size_t Channel::getLimitClients() const { return _limitClients; }


std::string Channel::getModeInString() const{
	std::string mode;

	if (_invitation)
		mode += "i";
	if (_isOpTopic)
		mode += "t";
	if (_limitClients < 10000)
		mode += "l";
	if (!_password.empty())
		mode += "k";
	if (!mode.empty())
		mode = "+" + mode;
	return mode;
}

size_t Channel::getNbClients() const{ return _clients.size(); }


const std::map<int, Client *>& Channel::getClients() const {
    return _clients;
}
