/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleTopic.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:35:29 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 12:17:29 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handleTopic(int fd, const std::string& channelName, const std::string& topic) {
	Channel* channel = _channels.find(channelName)->second;
	Client* client = clientBook[fd];
	std::string response;

	if (channelName.empty() || channelName == "IRC") {
		if (channelName == "IRC")
			response = serverName + ERR_NOSUCHCHANNEL(clientBook[fd]->getNickname(), " ");
		else
			response = serverName + ERR_NEEDMOREPARAMS(clientBook[fd]->getNickname());
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (_channels.find(channelName) == _channels.end()) {
		std::string response = serverName + ERR_NOSUCHCHANNEL(client->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (channel->getClients().find(fd) == channel->getClients().end()) {
		std::string response = serverName + ERR_NOTONCHANNEL(clientBook[fd]->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (topic.empty()) {
		if (_channels[channelName]->getTopic().empty())
		response = serverName + RPL_NOTOPIC(client->getNickname(), channelName);
		else {
			response = serverName + RPL_TOPIC(client->getNickname(), channelName, channel->getTopic());
			send(fd, response.c_str(), response.length(), 0);
			time_t tm = time(0);
			std::ostringstream oss;
			oss << tm;
			std::string t = oss.str();
			response = serverName + RPL_TOPICWHOTIME(client->getNickname(), channelName, client->getUsername(), t);
		}
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (channel->getIsOpTopic() == true && client->_clientChannels[_channels[channelName]] != Client::OPERATOR) {
		std::string response = serverName + ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else {
		_channels[channelName]->setTopic(topic);
		response = TOPIC(client->getNickname(), client->getUsername(), channelName, topic);
		_channels[channelName]->broadcast(response, fd);
		send(fd, response.c_str(), response.length(), 0);
	}
}