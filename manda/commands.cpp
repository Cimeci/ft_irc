/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:52:16 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/15 15:28:01 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

void Irc::handleJoin(int fd, const std::string& channelName, const std::string& passChannel) {
    Client *client = clientBook[fd];

	std::vector<std::string> channelGroup = ft_split(channelName, ",");
	std::vector<std::string> passChanGroup = ft_split(passChannel, ",");
	size_t j = 0;
	for (size_t i = 0; i < channelGroup.size(); i++)
	{
		std::cout << BLUE << "[DEBUG] " << RESET << "channelName='" << channelName << "'" << std::endl;
		if (channelGroup[i].empty()) {
			sendMessage(fd, ERR_BADCHANMASK(channelGroup[i]));
			continue;
		}
		if (channelGroup[i][0] != '&' && channelGroup[i][0] != '#') {
			sendMessage(fd, ERR_BADCHANMASK(channelGroup[i]));
			continue;
		}
		// if (!passChanGroup[j].empty())
		// 	std::cout << BLUE << "[DEBUG] " << RESET << " if password" << passChanGroup[j] << " | " << _channels[channelGroup[i]]->getPassword() << std::endl;
		if (_channels.find(channelGroup[i]) == _channels.end()) {
			std::cout << BLUE << "[DEBUG] " << RESET << "here owner of the channel" << std::endl;
			_channels[channelGroup[i]] = new Channel(channelGroup[i]);
			_channels[channelGroup[i]]->addClient(fd, *client);
			client->_clientChannels[_channels[channelGroup[i]]] = Client::OPERATOR;
			if (!passChanGroup.empty() && !passChanGroup[j].empty())
				j++;
		}
		else if (!passChanGroup.empty() && j < passChanGroup.size() && !passChanGroup[j].empty() && passChanGroup[j] == _channels[channelGroup[i]]->getPassword()){
			std::cout << BLUE << "[DEBUG] " << RESET << "go here for password" << std::endl;
			_channels[channelGroup[i]]->addClient(fd, *client);
			client->_clientChannels[_channels[channelGroup[i]]] = Client::MEMBER;
			j++;
		}
		else if (!_channels[channelGroup[i]]->getPassword().empty()){
			sendMessage(fd, ERR_BADCHANNELKEY(client->getNickname(), channelGroup[i])); continue ;
		}
		else if (_channels[channelGroup[i]]->getInvitation() == true){
			sendMessage(fd, ERR_INVITEONLYCHAN(client->getNickname(), channelGroup[i])); continue ;
		}
		else {
			_channels[channelGroup[i]]->addClient(fd, *client);
			client->_clientChannels[_channels[channelGroup[i]]] = Client::MEMBER;
		}

		//* send confirmation //
		sendMessage(fd, ":" + client->getNickname() + "!" + client->getUsername() + "@host" + " JOIN " + channelGroup[i] + "\r\n");

		// * send MODE //
		handleMode(fd, channelGroup[i], "");


		//* send actual topic //
		std::string topic = _channels[channelGroup[i]]->getTopic();
		if (topic.empty())
			sendMessage(fd, RPL_NOTOPIC(client->getNickname(), channelGroup[i])); // 331
		else
			sendMessage(fd, RPL_TOPIC(client->getNickname(), channelGroup[i], topic)); // 332

		handleWho(fd, channelGroup[i]);
	}
}

void Irc::handleWho(int fd, const std::string& channelName){
	//* send actual member list //
	const std::map<int, Client *>& members = _channels[channelName]->getClients();
	std::string names;

	for (std::map<int, Client *>::const_iterator it = members.begin(); it != members.end(); ++it) {
		char prefix = it->second->getPrefix(it->second->_clientChannels[_channels[channelName]]);
		if (prefix != '\0')
			names += prefix + it->second->getNickname() + " ";
		else
			names += it->second->getNickname() + " ";
	}

	sendMessage(fd, RPL_NAMEREPLY(clientBook[fd]->getNickname(), _channels[channelName]->getSymbol(), channelName));
	sendMessage(fd, RPL_ENDOFNAMES(clientBook[fd]->getNickname(), channelName));
}

void Irc::handlePrivMsg(int fd, const std::string& target, const std::string& message) {
	Client* sender = clientBook[fd];
	std::string formatted_msg;


	std::vector<std::string> targetGroup = ft_split(target, ",");

	for (size_t i = 0; i < targetGroup.size(); i++)
	{
		//* error empty //
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
				sendMessage(fd, ERR_NOSUCHNICK(sender->getNickname(), target));
		}
		else {
			bool isSend = false;
			for (std::map<int, Client*>::iterator it = clientBook.begin(); it != clientBook.end(); ++it) {
				if (it->second->getNickname() == targetGroup[i]) {
					sendMessage(it->first, ":" + sender->getNickname() + " PRIVMSG " + targetGroup[i] + " :" + message + "\r\n");
					isSend = true;
				}
			}
			if (isSend == false)
				sendMessage(fd, ERR_NOSUCHNICK(sender->getNickname(), target));
		}
	}
}

void Irc::handlePart(int fd, const std::string& channelName) {
	Client* client = clientBook[fd];
	Channel *channel =_channels.find(channelName)->second;

	if (channelName.empty()) {
		std::string response = serverName + ERR_NEEDMOREPARAMS(client->getNickname());
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (_channels.find(channelName) != _channels.end() && channel->isClientInChannel(fd)) {
		_channels[channelName]->removeClient(fd);
		client->_clientChannels.erase(_channels[channelName]);
		std::string response = PART(client->getNickname(), client->getUsername(), channelName);
		std::cout << response << std::endl;
		send(fd, response.c_str(), response.length(), 0);
	}
	else if (_channels.find(channelName) != _channels.end() && !channel->isClientInChannel(fd)) {
		std::string response = serverName + ERR_NOTONCHANNEL(client->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
	}
	else {
		std::string response = serverName + ERR_NOSUCHCHANNEL(client->getNickname(), channelName);
		send(fd, response.c_str(), response.length(), 0);
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

void Irc::handleQuit(int fd) {
	Client *client = clientBook[fd];

	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		Channel *channel = it->second;
		for (std::map<int, Client *>::iterator cit = channel->getClients().begin(); cit != channel->getClients().end(); ){
			if (cit->second->getNickname() == client->getNickname())
				channel->getClients().erase(cit++);
			else
				++cit;
		}
	}
	client->markForClose();
	client->setBuffer("Quit :Leaving\r\n");
	for (size_t i = 0; i < _pollfds.size(); ++i) {
		if (_pollfds[i].fd == fd) {
			_pollfds[i].events |= POLLOUT;
			break;
		}
	}
}

size_t getOption(const char &opt){
	std::string modeoption = "itlok";
	size_t j;
	for(j = 0; j < modeoption.size() && opt != modeoption[j]; j++);
	return (j);
}

void Irc::handleMode(int fd, const std::string &channelName, const std::string &mode){
	if (_channels.find(channelName) == _channels.end()) {
		sendMessage(fd, ERR_NOSUCHCHANNEL(clientBook[fd]->getNickname(), channelName)); return ;
	}
	if (channelName[0] != '#' && channelName[0] != '&') {
		sendMessage(fd, ERR_NOSUCHNICK(clientBook[fd]->getNickname(), channelName)); return ;
	}
	if (mode.empty()){
		sendMessage(fd, RPL_CHANNELMODEIS(clientBook[fd]->getNickname(), channelName, _channels[channelName]->getModeInString()));
		return ;
	}
	
	std::vector<std::string> modeGroup = ft_split(mode, " ");
	std::cout << BLUE << "[DEBUG] " << RESET << modeGroup[0] << std::endl;
	if (clientBook[fd]->_clientChannels[_channels[channelName]] != Client::OPERATOR){
			sendMessage(fd, ERR_CHANOPRIVSNEEDED(clientBook[fd]->getNickname(), channelName));
	}
	size_t OptionMode = 1;
	if (modeGroup[0][0] == '+')
	{
		for (size_t i = 1; i < modeGroup[0].size(); i++) {
			
			switch (getOption(modeGroup[0][i])) {
				case 0 : // i
					_channels[channelName]->setInvitaion(true); break;
				case 1 : // t
					_channels[channelName]->setIsOpTopic(true); break;
				case 2 : // l
					if (atoi(modeGroup[OptionMode].c_str()) > 0 && atoi(modeGroup[OptionMode].c_str()) < 10000){
						_channels[channelName]->setLimitClients(atoi(modeGroup[OptionMode].c_str()));
						OptionMode++;
					}
					break;
				case 3 : // o
					if (nicknameToFd.find(modeGroup[OptionMode]) != nicknameToFd.end()){
						clientBook[nicknameToFd[modeGroup[OptionMode]]]->_clientChannels[_channels[channelName]] = Client::OPERATOR;
						OptionMode++;
					}
					else {
						sendMessage(fd, ERR_NOSUCHNICK(clientBook[fd]->getNickname(), channelName));
					}
					break;
				case 4 : // k
					_channels[channelName]->setPassword(modeGroup[OptionMode]); OptionMode++; break;
				default :
					sendMessage(fd, ERR_UMODEUNKNOWNFLAG(clientBook[fd]->getNickname()));
			}
		}
	}
	else if (modeGroup[0][0] == '-')
	{
		for (size_t i = 1; i < modeGroup[0].size(); i++) {
			
			switch (getOption(modeGroup[0][i])) {
				case 0 : // i
					_channels[channelName]->setInvitaion(false); break;
				case 1 : // t
					_channels[channelName]->setIsOpTopic(false); break;
				case 2 : // l
					_channels[channelName]->setLimitClients(10000); break;
				case 3 : // o
					if (nicknameToFd.find(modeGroup[OptionMode]) != nicknameToFd.end()){
						clientBook[nicknameToFd[modeGroup[OptionMode]]]->_clientChannels[_channels[channelName]] = Client::MEMBER;
						OptionMode++;
					}
					else {
						sendMessage(fd, ERR_NOSUCHNICK(clientBook[fd]->getNickname(), channelName));
					}
					break;
				case 4 : // k
					_channels[channelName]->setPassword(""); break;

				default :
					sendMessage(fd, ERR_UMODEUNKNOWNFLAG(clientBook[fd]->getNickname()));
			}
		}
	}
	else
		sendMessage(fd, ERR_UMODEUNKNOWNFLAG(clientBook[fd]->getNickname()));
}
