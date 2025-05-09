/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:15:06 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/09 16:52:56 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"
# include "irc.hpp"

Channel::Channel(const std::string& name) : _name(name), _topic("") {}

void Channel::addClient(int client_fd) { _clients[client_fd] = false; }

void Channel::removeClient(int client_fd) { _clients.erase(client_fd); }

void Channel::broadcast(const std::string& message, int sender_fd) {
	sender_fd = 0;
    for (std::map<int, bool>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        // if (it->first != sender_fd) {}
        send(it->first, message.c_str(), message.length(), 0);
        // }
    }
}

std::string Channel::getName() const { return _name; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

std::string Channel::getTopic() const { return _topic; }