/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:52:16 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/08 18:22:13 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void Irc::handleJoin(int fd, const std::string& channelName) {
    Client* client = clientBook[fd];
    
//* check if the channel currently exist // 
    if (_channels.find(channelName) == _channels.end()) {
        _channels[channelName] = new Channel(channelName);
    }
    
//* add client to channel //
    _channels[channelName]->addClient(fd);
    client->_channels[_channels[channelName]] = true;
    
//* send confirmation //
    std::string response = ":" + client->getNickname() + " JOIN " + channelName + "\r\n";
    send(fd, response.c_str(), response.length(), 0);
    
//* send actual topic //
    std::string topic = _channels[channelName]->getTopic();
    if (!topic.empty()) {
        response = ":irc.climbers 332 " + client->getNickname() + " " + channelName + " :" + topic + "\r\n";
        send(fd, response.c_str(), response.length(), 0);
    }
}

void Irc::handlePrivMsg(int fd, const std::string& target, const std::string& message) {
    Client* sender = clientBook[fd];
    
//* channel //
    if (target[0] == '#' || target[0] == '&') {
        if (_channels.find(target) != _channels.end()) {
            std::string formatted_msg = ":" + sender->getNickname() + " PRIVMSG " + target + " :" + message + "\r\n";
            _channels[target]->broadcast(formatted_msg, fd);
        }
    }
//* user //
	else {
        for (std::map<int, Client*>::iterator it = clientBook.begin(); it != clientBook.end(); ++it) {
            if (it->second->getNickname() == target) {
                std::string formatted_msg = ":" + sender->getNickname() + " PRIVMSG " + target + " :" + message + "\r\n";
                send(it->first, formatted_msg.c_str(), formatted_msg.length(), 0);
                break;
            }
        }
    }
}

void Irc::handlePart(int fd, const std::string& channelName) {
    Client* client = clientBook[fd];
    
    if (_channels.find(channelName) != _channels.end()) {
        _channels[channelName]->removeClient(fd);
        client->_channels.erase(_channels[channelName]);
        
        std::string response = ":" + client->getNickname() + " PART " + channelName + "\r\n";
        send(fd, response.c_str(), response.length(), 0);
    }
}

void Irc::handleTopic(int fd, const std::string& channelName, const std::string& topic) {
    if (_channels.find(channelName) != _channels.end()) {
        _channels[channelName]->setTopic(topic);
        
        Client* client = clientBook[fd];
        std::string response = ":" + client->getNickname() + " TOPIC " + channelName + " :" + topic + "\r\n";
        _channels[channelName]->broadcast(response, fd);
    }
}