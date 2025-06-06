/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleWho.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:56:27 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:32:59 by noacharbogn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handleWho(int fd, std::string channelName){
	//* send actual member list //
	std::string names;
	Client *client = _clientBook[fd];
	
	if (channelName.empty()) {
		sendMessage(fd, RPL_ENDOFWHO(client->getNickname(), "*"));
	}
	else if (_channels.find(channelName) == _channels.end()){
		sendMessage(fd, ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
	}
	else {
		channelName = _channels.find(channelName)->first;
		const std::map<int, Client *>& members = _channels[channelName]->getClients();
		for (std::map<int, Client *>::const_iterator it = members.begin(); it != members.end(); ++it) {
			char prefix = it->second->getPrefix(it->second->_clientChannels[_channels[channelName]]);
			if (prefix != '\0')
				names += prefix + it->second->getNickname() + " ";
			else
				names += it->second->getNickname() + " ";
		}
		sendMessage(fd, RPL_NAMEREPLY(client->getNickname(), _channels[channelName]->getSymbol(), channelName));
		sendMessage(fd, RPL_ENDOFWHO(client->getNickname(), channelName));
	}
}
