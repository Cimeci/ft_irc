/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleInvite.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:36:39 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:22:14 by noacharbogn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handleInvite(int fd, const std::string &client, std::string channelName){
	Channel* channel = _channels.find(channelName)->second;
	if (client.empty() || channelName.empty()){
		sendMessage(fd, _serverName + ERR_NEEDMOREPARAMS(_clientBook[fd]->getNickname()));
		return ;
	}
	else if (_nicknameToFd.find(client) == _nicknameToFd.end()) {
		sendMessage(fd, ERR_NOSUCHNICK(_clientBook[fd]->getNickname(), client));
		return ;
	}
	if (_channels.find(channelName) == _channels.end()) {
		sendMessage(fd, ERR_NOSUCHCHANNEL(_clientBook[fd]->getNickname(), channelName));
	}
	else {
		channelName = _channels.find(channelName)->first;
		if (_clientBook[fd]->_clientChannels.find(_channels[channelName]) == _clientBook[fd]->_clientChannels.end()){
			sendMessage(fd, ERR_NOTONCHANNEL(_clientBook[fd]->getNickname(), channelName));
		}
		else if (_channels[channelName]-> getInvitation() == true && _clientBook[fd]->_clientChannels[_channels[channelName]] != Client::OPERATOR) {
			sendMessage(fd, ERR_CHANOPRIVSNEEDED(_clientBook[fd]->getNickname(), channelName));
		}
		else if (_clientBook[_nicknameToFd[client]]->_clientChannels.find(_channels[channelName]) != _clientBook[_nicknameToFd[client]]->_clientChannels.end()){
			sendMessage(fd, ERR_USERONCHANNEL(_clientBook[fd]->getNickname(), client, channelName)); return ;
		}
		else if (_clientBook[fd]->_clientChannels[channel] != Client::OPERATOR) {
			sendMessage(fd, _serverName + ERR_CHANOPRIVSNEEDED(_clientBook[fd]->getNickname(), channelName));
		}
		else {
			_channels[channelName]->broadcast(INVITE(_clientBook[fd]->getNickname(), _clientBook[fd]->getUsername(), client, channelName), fd);
			sendMessage(_nicknameToFd[client], INVITE(_clientBook[fd]->getNickname(), _clientBook[fd]->getUsername(), client, channelName));
			sendMessage(fd, INVITE(_clientBook[fd]->getNickname(), _clientBook[fd]->getUsername(), client, channelName));
			std::cout << _clientBook[fd]->getNickname() + " has invited " + client + " to the channel " + channelName << std::endl;
			_clientBook[_nicknameToFd[client]]->_invitationChannels[_channels[channelName]] = true;
		}
	}
}