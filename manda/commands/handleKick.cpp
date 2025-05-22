/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleKick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:37:05 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/22 16:15:40 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void	Irc::handleKick(int fd, std::string input, std::string after) {

	if (clientBook.find(fd) == clientBook.end())
		return;

	int targetFd = -1;
	std::string channelName;
	std::string target;
	std::string comment;
	std::string response;
	size_t space;

	#ifdef BONUS
		if (clientBook[fd]->getNickname() == "GambleDealer")
			clientBook[fd]->_clientChannels[_channels["#GambleRoom"]] = Client::OPERATOR;
	#endif
	channelName = input;
	space = after.find(" ");
	target = after.substr(0, space);
	if (channelName == "IRC"){
		channelName = target;
		if (after[space + 1] == ':') space++;
		target = after.substr(space + 1, after.find(" ", space + 1) - space - 1);
		space = after.find(" ", space + 1);
	}
	if (after[space + 1] == ':') space++;
	comment = after.substr(space + 1);

	std::cout << "[DEBUG] " << channelName + " | " + target + " | " + comment << std::endl;

	if (channelName.empty() || target.empty()) {
		response = serverName + ERR_NEEDMOREPARAMS(clientBook[fd]->getNickname());
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (_channels.find(channelName) == _channels.end()) {
		response = serverName + ERR_NOSUCHCHANNEL(clientBook[fd]->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else {
		Channel* channel = _channels.find(channelName)->second;
		for (std::map<int, Client *>::iterator it = clientBook.begin(); it != clientBook.end(); ++it) {
			if (it->second->getNickname() == target)
			targetFd = it->first;
		}
		if (channel->getClients().find(fd) == channel->getClients().end()) {
			response = serverName + ERR_NOTONCHANNEL(clientBook[fd]->getNickname(), channelName);
			send(fd, response.c_str(), response.length(), 0);
			return ;
		}
		if (targetFd == -1 || channel->getClients().find(targetFd) == channel->getClients().end()) {
			response = serverName + ERR_NOSUCHNICK(clientBook[fd]->getNickname(), target);
			send(fd, response.c_str(), response.length(), 0);
			return ;
		}
		int gradeSource = clientBook[fd]->_clientChannels[_channels[channelName]];
		int gradeTarget = clientBook[targetFd]->_clientChannels[_channels[channelName]];
		if (gradeSource > gradeTarget || (gradeSource == 1 && gradeTarget == 1)) {
			if (comment.empty())
				response = KICK(clientBook[fd]->getNickname(), clientBook[fd]->getUsername(), channelName, target, clientBook[fd]->getNickname());
			else
				response = KICK(clientBook[fd]->getNickname(), clientBook[fd]->getUsername(), channelName, target, comment);
			_channels[channelName]->broadcast(response, fd);
			send(fd, response.c_str(), response.length(), 0);
			_channels[channelName]->removeClient(targetFd);
			clientBook[targetFd]->_clientChannels.erase(channel);
			if (_channels[channelName]->getNbClients() < 1) {
				delete _channels[channelName];
				_channels.erase(channelName);
			}
		}
		else {
			response = serverName + ERR_CHANOPRIVSNEEDED(clientBook[fd]->getNickname(), channelName);
			send(fd, response.c_str(), response.length(), 0);
		}
	}
}