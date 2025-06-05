/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircUtils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:15:47 by inowak--          #+#    #+#             */
/*   Updated: 2025/06/04 11:26:06 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"

int Irc::getServerSocket() const {return _serverSocket;}

std::map<int, Client *>& Irc::getClientBook() {return _clientBook;}

std::map<std::string, Channel *, CaseInsensitiveCompare>& Irc::getChannels() {return _channels;}

std::vector<pollfd>& Irc::getPollFds() {return _pollfds;}

void Irc::setServerRunning(bool b) {_serverRunning = b;}

bool Irc::compareEquality(const std::string &s1, const std::string &s2) {
	if (s1.length() != s2.length())
		return false;
	for (size_t i = 0; i < s1.length(); i++) {
		if (tolower(s1[i]) != tolower(s2[i]))
			return false;
	}
	return true;
}

bool Irc::valueExist(const std::string &value){
	for (std::map<int, Client*>::const_iterator it = _clientBook.begin(); it != _clientBook.end(); ++it) {
		if (it->second && compareEquality(it->second->getNickname(), value))
			return true;
	}
	return false;
}