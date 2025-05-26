/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleInvite.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:36:39 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/22 16:15:30 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handleInvite(int fd, const std::string &client, const std::string &channelName){
	Channel* channel = _channels.find(channelName)->second;
	if (client.empty() || channelName.empty()){
		sendMessage(fd, ERR_NEEDMOREPARAMS(clientBook[fd]->getNickname()));
	}
	else if (nicknameToFd.find(client) == nicknameToFd.end()) {
		sendMessage(fd, ERR_NOSUCHNICK(clientBook[fd]->getNickname(), client));
	}
	else if (_channels.find(channelName) == _channels.end()) {
		sendMessage(fd, ERR_NOSUCHCHANNEL(clientBook[fd]->getNickname(), channelName));
	}
	else if (clientBook[fd]->_clientChannels.find(_channels[channelName]) == clientBook[fd]->_clientChannels.end()){
		sendMessage(fd, ERR_NOTONCHANNEL(clientBook[fd]->getNickname(), channelName));
	}
	else if (_channels[channelName]-> getInvitation() == true && clientBook[fd]->_clientChannels[_channels[channelName]] != Client::OPERATOR) {
		sendMessage(fd, ERR_CHANOPRIVSNEEDED(clientBook[fd]->getNickname(), channelName));
	}
	else if (clientBook[nicknameToFd[client]]->_clientChannels.find(_channels[channelName]) != clientBook[nicknameToFd[client]]->_clientChannels.end()){
		sendMessage(fd, ERR_USERONCHANNEL(clientBook[fd]->getNickname(), client, channelName)); return ;
	}
	else if (clientBook[fd]->_clientChannels[channel] != Client::OPERATOR) {
		std::string response = serverName + ERR_CHANOPRIVSNEEDED(clientBook[fd]->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else {
		_channels[channelName]->broadcast(INVITE(clientBook[fd]->getNickname(), clientBook[fd]->getUsername(), client, channelName), fd);
		sendMessage(nicknameToFd[client], INVITE(clientBook[fd]->getNickname(), clientBook[fd]->getUsername(), client, channelName));
		sendMessage(fd, INVITE(clientBook[fd]->getNickname(), clientBook[fd]->getUsername(), client, channelName));
		std::cout << clientBook[fd]->getNickname() + " has invited " + client + " to the channel " + channelName << std::endl;
		clientBook[nicknameToFd[client]]->_invitationChannels[_channels[channelName]] = true;
	}
}