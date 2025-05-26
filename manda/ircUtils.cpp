/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircUtils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:15:47 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 14:17:32 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"

int Irc::getServerSocket() const {return _server_socket;}

std::map<int, Client *>& Irc::getClientBook() {return _clientBook;}

std::map<std::string, Channel *>& Irc::getChannels() {return _channels;}

std::vector<pollfd>& Irc::getPollFds() {return _pollfds;}

void Irc::setServerRunning(bool b) {_serverRunning = b;}