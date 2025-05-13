/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:52:16 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/13 11:19:00 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void Irc::handleJoin(int fd, const std::string& channelName) {
    Client *client = clientBook[fd];
	std::cout << BLUE << "[DEBUG] " << channelName << RESET << std::endl;
	

	std::vector<std::string> channelGroup = ft_split(channelName, ",");
	for (size_t i = 0; i < channelGroup.size(); i++)
	{
		//* if the channel currently exist //
			//* create it, add Client and grade him OWNER  //
		//* else //
			//* add Client and grade him MEMBER  //
		if (_channels.find(channelGroup[i]) == _channels.end()) {
			_channels[channelGroup[i]] = new Channel(channelGroup[i]);
			_channels[channelGroup[i]]->addClient(fd, *client);
			client->_clientChannels[_channels[channelGroup[i]]] = Client::OWNER;
			
		}
		else {
			_channels[channelGroup[i]]->addClient(fd, *client);
			client->_clientChannels[_channels[channelGroup[i]]] = Client::MEMBER;
		}
		
		//* send confirmation //
		sendMessage(fd, ":" + client->getNickname() + " JOIN " + channelGroup[i] + "\r\n");
		
		//* send actual topic //
		std::string topic = _channels[channelGroup[i]]->getTopic();
		if (!topic.empty())
			sendMessage(fd, client->getNickname() + " " + channelGroup[i] + " :" + topic + "\r\n");
	}
}

void Irc::handleWho(int fd, const std::string& channelName){
	//* send actual member list //
	const std::map<int, Client *>& members = _channels[channelName]->getClients();
	std::string names;
	
	for (std::map<int, Client *>::const_iterator it = members.begin(); it != members.end(); ++it) {
		names += it->second->getPrefix(it->second->_clientChannels[_channels[channelName]]) + it->second->getNickname() + " ";
		// names += "@~" + it->second->getNickname() + " ";
	}
	
	sendMessage(fd, RPL_NAMEREPLY(clientBook[fd]->getNickname(), _channels[channelName]->getSymbol(), channelName, names));
	sendMessage(fd, RPL_ENDOFNAMES(clientBook[fd]->getNickname(), channelName));

}

void Irc::handlePrivMsg(int fd, const std::string& target, const std::string& message) {
    Client* sender = clientBook[fd];
    std::string formatted_msg;

	std::cout << BLUE << "[DEBUG] " << target << " | " << message << RESET << std::endl;

	std::vector<std::string> targetGroup = ft_split(target, ",");
	
	for (size_t i = 0; i < targetGroup.size(); i++)
	{
		//* error empty //
		if (targetGroup[i].empty())
			sendMessage(fd, ERR_NORECIPIENT);
		else if (message.empty())
			sendMessage(fd, ERR_NOTEXTTOSEND);
	
		//* channel //
    	else if (targetGroup[i][0] == '#' || targetGroup[i][0] == '&') {
    	    if (_channels.find(targetGroup[i]) != _channels.end()) {
    	        std::string formatted_msg = ":" + sender->getNickname() + " PRIVMSG " + targetGroup[i] + " :" + message + "\r\n";
    	        _channels[targetGroup[i]]->broadcast(formatted_msg, fd);
    	    }
			else
				sendMessage(fd, ERR_NOSUCHNICK);
    	}
		//* user //
		else {
			bool isSend = false;
			for (std::map<int, Client*>::iterator it = clientBook.begin(); it != clientBook.end(); ++it) {
    	        if (it->second->getNickname() == targetGroup[i]) {
					sendMessage(it->first, ":" + sender->getNickname() + " PRIVMSG " + targetGroup[i] + " :" + message + "\r\n");
					isSend = true;
    	        }
    	    }
			if (isSend == false)
				sendMessage(fd, ERR_NOSUCHNICK);
    	}
	}
}

void Irc::handlePart(int fd, const std::string& channelName) {
    Client* client = clientBook[fd];

    if (_channels.find(channelName) != _channels.end()) {
        _channels[channelName]->removeClient(fd);
        client->_clientChannels.erase(_channels[channelName]);
    
		sendMessage(fd, ":" + client->getNickname() + " PART " + channelName + "\r\n");
    }
}

void Irc::handleTopic(int fd, const std::string& channelName, const std::string& topic) {
    if (_channels.find(channelName) != _channels.end()) {
        _channels[channelName]->setTopic(topic);

        Client* client = clientBook[fd];
        std::string response = ":" + client->getNickname() + " TOPIC " + channelName + " :" + topic + "\r\n";
        _channels[channelName]->broadcast(response, fd);
    }
}