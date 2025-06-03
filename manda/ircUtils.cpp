/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircUtils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:15:47 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:32:40 by noacharbogn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"

int Irc::getServerSocket() const {return _serverSocket;}

std::map<int, Client *>& Irc::getClientBook() {return _clientBook;}

std::map<std::string, Channel *>& Irc::getChannels() {return _channels;}

std::vector<pollfd>& Irc::getPollFds() {return _pollfds;}

void Irc::setServerRunning(bool b) {_serverRunning = b;}

bool Irc::valueExist(std::string value){
	for (std::map<int, Client*>::const_iterator it = _clientBook.begin(); it != _clientBook.end(); ++it) {
		if (it->second && it->second->getNickname() == value)
			return true;
	}
	return false;
}