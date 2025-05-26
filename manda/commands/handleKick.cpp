/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleKick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:37:05 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 12:51:55 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void	Irc::handleKick(int fd, std::string input, std::string after) {

	if (clientBook.find(fd) == clientBook.end())
		return;

	int targetFd = -1;
	std::string channelName;
	std::vector<std::string> target;
	std::string comment;
	std::string response;
	size_t space;

	#ifdef BONUS
	if (clientBook[fd]->getNickname() == "GambleDealer")
	clientBook[fd]->_clientChannels[_channels["#GambleRoom"]] = Client::OPERATOR;
	#endif
	channelName = input;
	space = after.find(" ");
	target.push_back(after.substr(0, space));
	if (channelName == "IRC"){
		channelName = target[0];
		if (after[space + 1] == ':') space++;
		if (after.substr(space + 1, after.find(" ", space + 1) - space - 1).find(",") != std::string::npos)
			target = ft_split(after.substr(space + 1, after.find(" ", space + 1) - space - 1), ",");
		else
			target[0] = after.substr(space + 1, after.find(" ", space + 1) - space - 1);
		space = after.find(" ", space + 1);
	}
	if (after[space + 1] == ':') space++;
	comment = after.substr(space + 1);
	if (target[0].find(",") != std::string::npos)
		target = ft_split(target[0], ",");

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
		if (channel->getClients().find(fd) == channel->getClients().end()) {
			response = serverName + ERR_NOTONCHANNEL(clientBook[fd]->getNickname(), channelName);
			send(fd, response.c_str(), response.length(), 0);
			return ;
		}
		for (std::vector<std::string>::iterator it = target.begin(); it != target.end(); ++it) {
			for (std::map<int, Client *>::iterator cit = clientBook.begin(); cit != clientBook.end(); ++cit) {
				if (cit->second->getNickname() == *it)
					targetFd = cit->first;
			}
			if (targetFd == -1 || channel->getClients().find(targetFd) == channel->getClients().end()) {
				response = serverName + ERR_NOSUCHNICK(clientBook[fd]->getNickname(), *it);
				send(fd, response.c_str(), response.length(), 0);
				continue ;
			}
			int gradeSource = clientBook[fd]->_clientChannels[_channels[channelName]];
			int gradeTarget = clientBook[targetFd]->_clientChannels[_channels[channelName]];
			if (gradeSource > gradeTarget || (gradeSource == 1 && gradeTarget == 1)) {
				if (comment.empty())
					response = KICK(clientBook[fd]->getNickname(), clientBook[fd]->getUsername(), channelName, *it, clientBook[fd]->getNickname());
				else
					response = KICK(clientBook[fd]->getNickname(), clientBook[fd]->getUsername(), channelName, *it, comment);
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
}