/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleKick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:37:05 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:07:34 by noacharbogn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

static void parseKick(std::string &input, std::string &after, std::string &comment, std::string &channelName, std::vector<std::string> &target) {
	size_t space = after.find(" ");
	
	channelName = input;
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
}

void	Irc::handleKick(int fd, std::string input, std::string after) {
	int targetFd = -1;
	std::string channelName;
	std::vector<std::string> target;
	std::string comment;
	std::string response;
	
	if (_clientBook.find(fd) == _clientBook.end())
		return;
	#ifdef BONUS
	if (_clientBook[fd]->getNickname() == "GambleDealer")
	_clientBook[fd]->_clientChannels[_channels["#GambleRoom"]] = Client::OPERATOR;
	#endif
	parseKick(input, after, comment, channelName, target);

	if (channelName.empty() || target.empty())
		sendMessage(fd, _serverName + ERR_NEEDMOREPARAMS(_clientBook[fd]->getNickname()));
	else if (_channels.find(channelName) == _channels.end())
		sendMessage(fd, _serverName + ERR_NOSUCHCHANNEL(_clientBook[fd]->getNickname(), channelName));
	else {
		Channel* channel = _channels.find(channelName)->second;
		if (channel->getClients().find(fd) == channel->getClients().end()) {
			sendMessage(fd, _serverName + ERR_NOTONCHANNEL(_clientBook[fd]->getNickname(), channelName));
			return ;
		}
		channelName = _channels.find(channelName)->first;
		for (std::vector<std::string>::iterator it = target.begin(); it != target.end(); ++it) {
			for (std::map<int, Client *>::iterator cit = _clientBook.begin(); cit != _clientBook.end(); ++cit) {
				if (compareEquality(cit->second->getNickname(), *it) == true)
					targetFd = cit->first;
			}
			if (targetFd == -1 || channel->getClients().find(targetFd) == channel->getClients().end()) {
				sendMessage(fd, ERR_NOSUCHNICK(_clientBook[fd]->getNickname(), *it));
				continue ;
			}
			int gradeSource = _clientBook[fd]->_clientChannels[_channels[channelName]];
			int gradeTarget = _clientBook[targetFd]->_clientChannels[_channels[channelName]];
			if (gradeSource > gradeTarget || (gradeSource == 1 && gradeTarget == 1)) {
				if (comment.empty())
					response = KICK(_clientBook[fd]->getNickname(), _clientBook[fd]->getUsername(), channelName, _clientBook[targetFd]->getNickname(), _clientBook[fd]->getNickname());
				else
					response = KICK(_clientBook[fd]->getNickname(), _clientBook[fd]->getUsername(), channelName, _clientBook[targetFd]->getNickname(), comment);
				_channels[channelName]->broadcast(response, fd);
				sendMessage(fd, response);
				_channels[channelName]->removeClient(targetFd);
				_clientBook[targetFd]->_clientChannels.erase(channel);
				if (_channels[channelName]->getNbClients() < 1) {
					delete _channels[channelName];
					_channels.erase(channelName);
				}
			}
			else
				sendMessage(fd, _serverName + ERR_CHANOPRIVSNEEDED(_clientBook[fd]->getNickname(), channelName));
		}
	}
}