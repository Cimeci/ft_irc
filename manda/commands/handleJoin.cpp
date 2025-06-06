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
	if (channelGroup.size() < 1) {
		sendMessage(fd, _serverName + ERR_NEEDMOREPARAMS(client->getNickname()));
		return ;
	}
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
		std::map<std::string, Channel *, CaseInsensitiveCompare>::iterator it = _channels.find(channelGroup[i]);
		if (it == _channels.end()) {
			#ifdef BONUS
				if (channelName == "#GambleRoom" && client->getNickname() != "GambleDealer"){
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

		else if (_channels[it->first]->getLimitClients() <= _channels[it->first]->getNbClients()){
			sendMessage(fd, ERR_CHANNELISFULL(client->getNickname(), it->first)); continue;
		}
		
		//* Error invitation for join the channel (+i) *//

		else if (_channels[it->first]->getInvitation() == true && client->_invitationChannels[_channels[it->first]] == false){
			sendMessage(fd, ERR_INVITEONLYCHAN(client->getNickname(), it->first)); continue ;
		}

		//* Join the channel if the channel request a password *//
		
		else if (!passChanGroup.empty() && j < passChanGroup.size() && !passChanGroup[j].empty() && passChanGroup[j] == _channels[it->first]->getPassword()){
			_channels[it->first]->addClient(fd, *client);
			client->_clientChannels[_channels[it->first]] = Client::MEMBER;
			j++;
		}

		//* Error password incorrect for join the channel (+k) *//

		else if (!_channels[it->first]->getPassword().empty()){
			sendMessage(fd, ERR_BADCHANNELKEY(client->getNickname(), it->first)); continue ;
		}
		
		//* Join the channel *//
		
		else {
			_channels[it->first]->addClient(fd, *client);
			client->_clientChannels[_channels[it->first]] = Client::MEMBER;
		}
		if (it != _channels.end())
			channelGroup[i] = it->first;
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