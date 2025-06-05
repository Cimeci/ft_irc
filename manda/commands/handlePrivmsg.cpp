/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePrivmsg.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:32:55 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 14:41:08 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handlePrivMsg(int fd, const std::string& target, const std::string& message) {
	Client* sender = _clientBook[fd];
	std::string formatted_msg;

	std::vector<std::string> targetGroup = ft_split(target, ",");
	if (targetGroup.size() < 1)
			sendMessage(fd, ERR_NORECIPIENT(sender->getNickname()));

	for (size_t i = 0; i < targetGroup.size(); i++)
	{
		std::map<std::string, Channel*, CaseInsensitiveCompare>::iterator it = _channels.find(targetGroup[i]);
		if (message.empty())
			sendMessage(fd, ERR_NOTEXTTOSEND(sender->getNickname()));
		if ((targetGroup[i][0] == '#' || targetGroup[i][0] == '&')) {
			if (it != _channels.end()) {
				if (sender->_clientChannels.find(it->second) != sender->_clientChannels.end()) {
					std::string formatted_msg = ":" + sender->getNickname() + " PRIVMSG " + it->first + " :" + message + "\r\n";
					_channels[targetGroup[i]]->broadcast(formatted_msg, fd);
				}
				else
					sendMessage(fd, ERR_CANNOTSENDTOCHAN(sender->getNickname(), target));
			}
			else
				sendMessage(fd, ERR_NOSUCHCHANNEL(sender->getNickname(), target));
		}
		else {
			std::map<std::string, int>::iterator it = _nicknameToFd.find(targetGroup[i]);
			if (_clientBook.find(it->second) != _clientBook.end())
				sendMessage(it->second, ":" + sender->getNickname() + " PRIVMSG " + it->first + " :" + message + "\r\n");
			else
				sendMessage(fd, ERR_NOSUCHNICK(sender->getNickname(), target));
		}
	}
}
