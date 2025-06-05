/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:38:57 by inowak--          #+#    #+#             */
/*   Updated: 2025/06/04 11:26:46 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Irc.hpp"

size_t getOption(const char &opt){
	std::string modeoption = "itlok";
	size_t j;
	for(j = 0; j < modeoption.size() && opt != modeoption[j]; j++);
	return (j);
}

void Irc::handleMode(int fd, std::string channelName, const std::string &mode){
	Client *client = _clientBook[fd];

	//* ERROR *//

	if (_channels.find(channelName) == _channels.end()) {
		sendMessage(fd, ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
		return ;
	}
	if (channelName[0] != '#' && channelName[0] != '&') {
		sendMessage(fd, ERR_NOSUCHNICK(client->getNickname(), channelName));
		return ;
	}
	channelName = _channels.find(channelName)->first;
	//* DISPLAY ACTUAL MODE *//

	if (mode.empty()){
		sendMessage(fd, RPL_CHANNELMODEIS(client->getNickname(), channelName, _channels[channelName]->getModeInString()));
		return ;
	}

	std::vector<std::string> modeGroup = ft_split(mode, " ");
	if (client->_clientChannels[_channels[channelName]] != Client::OPERATOR){
			sendMessage(fd, ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName));
			return ;
	}
	size_t OptionMode = 1;
	int Sign = 0;
	for (size_t i = 0; i < modeGroup[0].size(); i++){

		//* FIND THE SIGN *//
		if (modeGroup[0][i] == '+') { Sign = 1; }
		else if (modeGroup[0][i] == '-') { Sign = -1; }
		else if (Sign == 0) { sendMessage(fd, ERR_UMODEUNKNOWNFLAG(client->getNickname())); continue; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////
								//* HANDLE ADD OPTION MODE *//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Sign == 1 && modeGroup[0][i] != '+'){
			switch (getOption(modeGroup[0][i])) {
				case 0 : // !i
					if (_channels[channelName]->getInvitation() == false){
						_channels[channelName]->setInvitation(true);
						_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "+i", ""), fd);
						sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "+i", ""));
					}
					break;
				case 1 : // !t
					if (_channels[channelName]->getIsOpTopic() == false){
						_channels[channelName]->setIsOpTopic(true);
						_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "+t", ""), fd);
						sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "+t", ""));
					}
					break;
				case 2 : // !l
					if(modeGroup.size() == OptionMode || modeGroup[OptionMode].empty()){
						sendMessage(fd, ERR_NEEDMOREPARAMS(client->getNickname()));
					}
					else if (atoi(modeGroup[OptionMode].c_str()) > 0 && atoi(modeGroup[OptionMode].c_str()) < 10000){
						_channels[channelName]->setLimitClients(atoi(modeGroup[OptionMode].c_str()));
						_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "+l", modeGroup[OptionMode]), fd);
						sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "+l", modeGroup[OptionMode]));
						OptionMode++;
					}
					else {
						sendMessage(fd, ERR_INVALIDMODEPARAM(client->getNickname(),channelName, "+l", modeGroup[OptionMode], "Not a valid digit (1 - 9999)"));
					}
					break;
				case 3 : // !o
					if (modeGroup.size() == OptionMode || modeGroup[OptionMode].empty()){
						sendMessage(fd, (_serverName + ERR_NEEDMOREPARAMS(client->getNickname())));
					}
					else {
						std::vector<std::string> GroupClient = ft_split(modeGroup[OptionMode], ",");
						if (GroupClient.empty())
							sendMessage(fd, ERR_INVALIDMODEPARAM(client->getNickname(),channelName, "+o", modeGroup[OptionMode], "Not a valid nickname"));
						else {
							for (size_t k = 0; k < GroupClient.size(); k++){
								if (_nicknameToFd.find(GroupClient[k]) != _nicknameToFd.end() && _clientBook[_nicknameToFd[GroupClient[k]]]->_clientChannels.find(_channels[channelName]) != _clientBook[_nicknameToFd[GroupClient[k]]]->_clientChannels.end())
								{
									if (_clientBook[_nicknameToFd[GroupClient[k]]]->_clientChannels[_channels[channelName]] == Client::MEMBER) {
										_clientBook[_nicknameToFd[GroupClient[k]]]->_clientChannels[_channels[channelName]] = Client::OPERATOR;
										_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "+o", GroupClient[k]), fd);
										sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "+o", GroupClient[k]));
									}
								}
								else {
									sendMessage(fd, ERR_NOSUCHNICK(client->getNickname(), GroupClient[k]));
								}
							}
						}
						OptionMode++;
					}
					break;
				case 4 : // !k
					if (modeGroup.size() != OptionMode && !modeGroup[OptionMode].empty()){
						if (_channels[channelName]->getPassword() != modeGroup[OptionMode]) {
							_channels[channelName]->setPassword(modeGroup[OptionMode]);
							_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "+k", modeGroup[OptionMode]), fd);
							sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "+k", modeGroup[OptionMode]));
						}
						OptionMode++;
					}
					else{
						sendMessage(fd, ERR_NEEDMOREPARAMS(client->getNickname()));
					}
					break;
				default :
					sendMessage(fd, ERR_UMODEUNKNOWNFLAG(client->getNickname()));
			}
		}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
								//* HANDLE REMOVE OPTION MODE *//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (Sign == -1 && modeGroup[0][i] != '-'){
			switch (getOption(modeGroup[0][i])) {
				case 0 : // !i
					if (_channels[channelName]->getInvitation() == true){
						_channels[channelName]->setInvitation(false);
						_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "-i", ""), fd);
						sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "-i", ""));
					}
					break;
				case 1 : // !t
					if (_channels[channelName]->getIsOpTopic() == true){
						_channels[channelName]->setIsOpTopic(false);
						_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "-t", ""), fd);
						sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "-t", ""));
					}
					break;
				case 2 : // !l
					if (_channels[channelName]->getLimitClients() < 10000){
						_channels[channelName]->setLimitClients(10000);
						_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "-l", ""), fd);
						sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "-l", ""));
					}
					break;
				case 3 : // !o
					if (modeGroup.size() == OptionMode || modeGroup[OptionMode].empty()){
						sendMessage(fd, ERR_NEEDMOREPARAMS(client->getNickname()));
					}
					else {
						std::vector<std::string> GroupClient = ft_split(modeGroup[OptionMode], ",");
						if (GroupClient.empty())
							sendMessage(fd, ERR_INVALIDMODEPARAM(client->getNickname(),channelName, "+o", modeGroup[OptionMode], "Not a valid nickname"));
						else {
							for (size_t k = 0; k < GroupClient.size(); k++){
								if (_nicknameToFd.find(GroupClient[k]) != _nicknameToFd.end() && _clientBook[_nicknameToFd[GroupClient[k]]]->_clientChannels.find(_channels[channelName]) != _clientBook[_nicknameToFd[GroupClient[k]]]->_clientChannels.end())
								{
									if (_clientBook[_nicknameToFd[GroupClient[k]]]->_clientChannels[_channels[channelName]] == Client::OPERATOR) {
										_clientBook[_nicknameToFd[GroupClient[k]]]->_clientChannels[_channels[channelName]] = Client::MEMBER;
										_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "-o", GroupClient[k]), fd);
										sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "-o", GroupClient[k]));
									}
								}
								else {
									sendMessage(fd, ERR_NOSUCHNICK(client->getNickname(), channelName));
								}
							}
						}
						OptionMode++;
					}
					break;
				case 4 : // !k
					if (!_channels[channelName]->getPassword().empty()){
						_channels[channelName]->setPassword("");
						_channels[channelName]->broadcast(MODE(client->getNickname(), client->getUsername() ,channelName, "-k", ""), fd);
						sendMessage(fd, MODE(client->getNickname(), client->getUsername() ,channelName, "-k", ""));
					}
					break;
				default :
					sendMessage(fd, ERR_UMODEUNKNOWNFLAG(client->getNickname()));
			}
		}
	}
}