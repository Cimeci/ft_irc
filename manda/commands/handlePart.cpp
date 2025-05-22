/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePart.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:34:47 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/22 16:15:47 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handlePart(int fd, const std::string& channelName, const std::string& reason) {
	Client* client = clientBook[fd];
	std::vector<std::string> channels;
	std::string response;

	if (channelName.empty()) {
		response = serverName + ERR_NEEDMOREPARAMS(client->getNickname());
		send(fd, response.c_str(), response.length(), 0);
		return ;
	}
	if (channelName.find(",") != std::string::npos)
		channels = ft_split(channelName, ",");
	else
		channels.push_back(channelName);
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it) {
		if (_channels.find(*it) != _channels.end()) {
			Channel *channel = _channels.find(*it)->second;
			if (channel->isClientInChannel(fd)) {
				_channels[*it]->removeClient(fd);
				client->_clientChannels.erase(_channels[*it]);
				if (reason.empty())
					response = PART(client->getNickname(), client->getUsername(), *it, "Leaving");
				else
					response = PART(client->getNickname(), client->getUsername(), *it, reason);
				_channels[*it]->broadcast(response, fd);
				if (_channels[channelName]->getNbClients() < 1) {
					delete _channels[channelName];
					_channels.erase(channelName);
				}
			}
			else
				response = serverName + ERR_NOTONCHANNEL(client->getNickname(), *it);
		}
		else
			response = ERR_NOSUCHCHANNEL(client->getNickname(), *it);
		send(fd, response.c_str(), response.length(), 0);
	}
}