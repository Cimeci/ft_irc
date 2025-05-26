/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleQuit.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:35:54 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 14:39:20 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

void Irc::handleQuit(int fd, std::string reason) {
	Client *client = _clientBook[fd];
	std::map<std::string, Channel *>::iterator tmp;

	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); )
	{
		Channel *channel = it->second;
		for (std::map<int, Client *>::iterator cit = channel->getClients().begin(); cit != channel->getClients().end(); ){
			if (cit->second->getNickname() == client->getNickname())
				channel->getClients().erase(cit++);
			else
				++cit;
		}
		if (channel->getNbClients() < 1) {
			delete it->second;
			tmp = it;
    		++it;
        	_channels.erase(tmp);	
		}
		else
			++it;
	}
	client->markForClose();
	if (reason.find(" ") == std::string::npos)
		client->setBuffer("Quit :Leaving\r\n");
	else
		client->setBuffer("Quit " + reason.substr(reason.find(" ") + 1, reason.length()) + "\r\n");
	for (size_t i = 0; i < _pollfds.size(); ++i) {
		if (_pollfds[i].fd == fd) {
			_pollfds[i].events |= POLLOUT;
			break;
		}
	}
}