/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleTopic.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:35:29 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 14:40:57 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handleTopic(int fd, const std::string& channelName, const std::string& topic) {
	Channel* channel = _channels.find(channelName)->second;
	Client* client = _clientBook[fd];
	std::string response;

	if (channelName.empty() || channelName == "IRC") {
		if (channelName == "IRC")
			response = _serverName + ERR_NOSUCHCHANNEL(_clientBook[fd]->getNickname(), " ");
		else
			response = _serverName + ERR_NEEDMOREPARAMS(_clientBook[fd]->getNickname());
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (_channels.find(channelName) == _channels.end()) {
		std::string response = _serverName + ERR_NOSUCHCHANNEL(client->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (channel->getClients().find(fd) == channel->getClients().end()) {
		std::string response = _serverName + ERR_NOTONCHANNEL(_clientBook[fd]->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (topic.empty()) {
		if (_channels[channelName]->getTopic().empty())
		response = _serverName + RPL_NOTOPIC(client->getNickname(), channelName);
		else {
			response = _serverName + RPL_TOPIC(client->getNickname(), channelName, channel->getTopic());
			send(fd, response.c_str(), response.length(), 0);
			time_t tm = time(0);
			std::ostringstream oss;
			oss << tm;
			std::string t = oss.str();
			response = _serverName + RPL_TOPICWHOTIME(client->getNickname(), channelName, client->getUsername(), t);
		}
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (channel->getIsOpTopic() == true && client->_clientChannels[_channels[channelName]] != Client::OPERATOR) {
		std::string response = _serverName + ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else {
		_channels[channelName]->setTopic(topic);
		response = TOPIC(client->getNickname(), client->getUsername(), channelName, topic);
		_channels[channelName]->broadcast(response, fd);
		send(fd, response.c_str(), response.length(), 0);
	}
}