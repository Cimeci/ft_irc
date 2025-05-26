/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleJoin.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:31:40 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 14:36:43 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handleJoin(int fd, const std::string& channelName, const std::string& passChannel) {
	Client *client = _clientBook[fd];

	std::vector<std::string> channelGroup = ft_split(channelName, ",");
	std::vector<std::string> passChanGroup = ft_split(passChannel, ",");
	size_t j = 0;
	for (size_t i = 0; i < channelGroup.size(); i++)
	{

		//* check for base *//
		
		if (channelGroup[i].empty()) {
			sendMessage(fd, ERR_BADCHANMASK(channelGroup[i]));
			continue;
		}
		
		if (channelGroup[i][0] != '&' && channelGroup[i][0] != '#') {
			sendMessage(fd, ERR_BADCHANMASK(channelGroup[i]));
			continue;
		}
		
		//* First join channel = new channel *//

		if (_channels.find(channelGroup[i]) == _channels.end()) {
			#ifdef BONUS
				if (channelName == "#GambleRoom" && client->getNickname() != "GambleDealer") {
					sendMessage(fd, ERR_INVITEONLYCHAN(client->getNickname(), channelGroup[i])); continue ;
				}
			#endif
			_channels[channelGroup[i]] = new Channel(channelGroup[i]);
			_channels[channelGroup[i]]->addClient(fd, *client);
			client->_clientChannels[_channels[channelGroup[i]]] = Client::OPERATOR;
			if (!passChanGroup.empty() && !passChanGroup[j].empty())
				j++;
		}

		//* Error limit client (+l) *//

		else if (_channels[channelGroup[i]]->getLimitClients() <= _channels[channelGroup[i]]->getNbClients()){
			sendMessage(fd, ERR_CHANNELISFULL(client->getNickname(), channelGroup[i])); continue;
		}
		
		//* Error invitation for join the channel (+i) *//

		else if (_channels[channelGroup[i]]->getInvitation() == true && client->_invitationChannels[_channels[channelGroup[i]]] == false){
			sendMessage(fd, ERR_INVITEONLYCHAN(client->getNickname(), channelGroup[i])); continue ;
		}

		//* Join the channel if the channel request a password *//
		
		else if (!passChanGroup.empty() && j < passChanGroup.size() && !passChanGroup[j].empty() && passChanGroup[j] == _channels[channelGroup[i]]->getPassword()){
			_channels[channelGroup[i]]->addClient(fd, *client);
			client->_clientChannels[_channels[channelGroup[i]]] = Client::MEMBER;
			j++;
		}

		//* Error password incorrect for join the channel (+k) *//

		else if (!_channels[channelGroup[i]]->getPassword().empty()){
			sendMessage(fd, ERR_BADCHANNELKEY(client->getNickname(), channelGroup[i])); continue ;
		}
		
		//* Join the channel *//
		
		else {
			_channels[channelGroup[i]]->addClient(fd, *client);
			client->_clientChannels[_channels[channelGroup[i]]] = Client::MEMBER;
		}
		
		//* reset invitation *//
		client->_invitationChannels[_channels[channelGroup[i]]] = false;
		
		//* send confirmation //
		sendMessage(fd, JOIN(client->getNickname(), client->getUsername(), channelGroup[i]));
		_channels[channelGroup[i]]->broadcast(JOIN(client->getNickname(), client->getUsername(), channelGroup[i]), fd);
		
		// * send MODE //
		handleMode(fd, channelGroup[i], "");

		//* send actual topic //
		handleTopic(fd, channelGroup[i], "");

		//* send actual who //
		handleWho(fd, channelGroup[i]);
	}
}