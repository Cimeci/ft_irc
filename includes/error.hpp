/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:33:56 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/14 12:11:08 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

// noa //

# define RPL_WELCOME(client, nick, user)			(std::string(" 001 ") + client + std::string(" :Welcome to the IRC Network, ") + nick + std::string(" [!") + user + std::string("@host]\r\n"))
# define RPL_YOURHOST(client, server) 				(std::string(" 002 ") + client + std::string(" :Your host is ") + server + std::string(", running version 1\r\n"))
# define RPL_CREATED(client, date) 					(std::string(" 003 ") + client + std::string(" :This server was created ") + date + std::string("\r\n"))
# define RPL_MYINFO(client, server) 				(std::string(" 004 ") + client + std::string(" ") + server + std::string("<available user modes> <available channel modes> [<channel modes with a parameter>]\r\n"))
# define ERR_UNKNOWNCOMMAND(client, cmd) 			(std::string(" 421 ") + client + std::string(" ") + cmd + std::string(" :Unknown command\r\n"))
# define ERR_NONICKNAMEGIVEN(client) 				(std::string(" 431 ") + client + std::string(" :No nickname given\r\n"))
# define ERR_NICKNAMEINUSE(client, nick) 			(std::string(" 433 ") + client + std::string(" ") + nick + std::string(" :Nickname is already in use\r\n"))
# define ERR_NEEDMOREPARAMS(client) 				(std::string(" 461 ") + client + std::string(" PASS :Not enough parameters\r\n"))
# define ERR_PASSWDMISMATCH(client) 				(std::string(" 464 ") + client + std::string(" :Password incorrect\r\n"))

// ilan //

# define ERR_NOSUCHNICK(client, channel)			(serverName + " 401 " + client + " " + channel + " :" + "No such nick/channel" + "\r\n")
# define ERR_NORECIPIENT(client)					(serverName + " 411 " + client + " :No recipient given (PRIVMSG)\r\n")
# define ERR_NOTEXTTOSEND(client)					(serverName + " 412 " + client + " :No text to send\r\n")

# define ERR_BANNEDFROMCHAN(client, channel)		(serverName + " 474 " + client + " " + channel + " :Cannot join channel (+b)\r\n")
# define ERR_BADCHANNELKEY(client, channel)			(serverName + " 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
# define ERR_NOSUCHCHANNEL(client, channel)			(serverName + " 403 " + client + " " + channel + " :No such channel\r\n")
# define ERR_BADCHANMASK(channel) 					(serverName + " 476 " + channel + " :Bad Channel Mask\r\n")
# define RPL_CHANNELMODEIS(nick, channel, modes) 	(serverName + " 324 " + nick + " " + channel + " " + modes + "\r\n")
# define RPL_NOTOPIC(client, channel)				(serverName + " 331 " + client + " " + channel + " :No topic is set\r\n")
# define RPL_TOPIC(client, channel, topic)			(serverName + " 332 " + client + " " + channel + " :" + topic + "\r\n")
# define RPL_NAMEREPLY(nick, symbol, channel)		(serverName + " 353 " + nick + " " + symbol + " " + channel + " :" + names + "\r\n")
# define RPL_ENDOFNAMES(nick, channel) 				(serverName + " 366 " + nick + " " + channel + " :End of /NAMES list.\r\n")