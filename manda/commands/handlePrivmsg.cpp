/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlePrivmsg.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:32:55 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/22 16:15:49 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handlePrivMsg(int fd, const std::string& target, const std::string& message) {
	Client* sender = clientBook[fd];
	std::string formatted_msg;

	std::vector<std::string> targetGroup = ft_split(target, ",");

	for (size_t i = 0; i < targetGroup.size(); i++)
	{
		if (targetGroup[i].empty())
			sendMessage(fd, ERR_NORECIPIENT(sender->getNickname()));
		else if (message.empty())
			sendMessage(fd, ERR_NOTEXTTOSEND(sender->getNickname()));
		else if (targetGroup[i][0] == '#' || targetGroup[i][0] == '&') {
			if (sender->_clientChannels.find(_channels[targetGroup[i]]) != sender->_clientChannels.end()) {
				std::string formatted_msg = ":" + sender->getNickname() + " PRIVMSG " + targetGroup[i] + " :" + message + "\r\n";
				_channels[targetGroup[i]]->broadcast(formatted_msg, fd);
			}
			else
				sendMessage(fd, ERR_NOSUCHCHANNEL(sender->getNickname(), target));
		}
		else {
			if (clientBook.find(nicknameToFd[targetGroup[i]]) != clientBook.end()) {
				sendMessage(nicknameToFd[targetGroup[i]], ":" + sender->getNickname() + " PRIVMSG " + targetGroup[i] + " :" + message + "\r\n");
			}
			else {
				sendMessage(fd, ERR_NOSUCHNICK(sender->getNickname(), target));
			}
		}
	}
}