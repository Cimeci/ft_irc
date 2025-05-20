/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:33:56 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 11:02:10 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# define RPL_WELCOME(client, nick, user)			(" 001 " + client + " :Welcome to the IRC Network, " + nick + " [!" + user + "@host]\r\n")
# define RPL_YOURHOST(client, server) 				(" 002 " + client + " :Your host is " + server + ", running version 1\r\n")
# define RPL_CREATED(client, date) 					(" 003 " + client + " :This server was created " + date + "\r\n")
# define RPL_MYINFO(client, server) 				(" 004 " + client + " " + server + "<available user modes> <available channel modes> [<channel modes with a parameter>]\r\n")

# define RPL_NOTOPIC(client, channel)				(serverName + " 331 " + client + " " + channel + " :No topic is set\r\n")
# define RPL_TOPIC(client, channel, topic)			(serverName + " 332 " + client + " " + channel + " :" + topic + "\r\n")
# define RPL_TOPICWHOTIME(client, channel, user, t)	(" 333 " + client + " " + channel + " " + client + "!~" + user + "@localhost " + t + "\r\n")
# define RPL_CHANNELMODEIS(nick, channel, modes) 	(serverName + " 324 " + nick + " " + channel + " " + modes + "\r\n")
# define RPL_INVITING(client, nick, channel) 		(serverName + " 341 " + client + " " + nick + " " + channel + "\r\n")
# define RPL_NAMEREPLY(nick, symbol, channel)		(serverName + " 353 " + nick + " " + symbol + " " + channel + " :" + names + "\r\n")
# define RPL_ENDOFNAMES(nick, channel) 				(serverName + " 366 " + nick + " " + channel + " :End of /NAMES list.\r\n")

# define ERR_NOSUCHNICK(client, channel)			(serverName + " 401 " + client + " " + channel + " :" + "No such nick/channel" + "\r\n")
# define ERR_NOSUCHCHANNEL(client, channel)			(serverName + " 403 " + client + " " + channel + " :No such channel\r\n")
# define ERR_NORECIPIENT(client)					(serverName + " 411 " + client + " :No recipient given (PRIVMSG)\r\n")
# define ERR_NOTEXTTOSEND(client)					(serverName + " 412 " + client + " :No text to send\r\n")
# define ERR_UNKNOWNCOMMAND(client, cmd) 			(" 421 " + client + " " + cmd + " :Unknown command\r\n")
# define ERR_NONICKNAMEGIVEN(client) 				(" 431 " + client + " :No nickname given\r\n")
# define ERR_NICKNAMEINUSE(client, nick) 			(" 433 " + client + " " + nick + " :Nickname is already in use\r\n")
# define ERR_USERNOTINCHANNEL(client, nick, channel)(" 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n")
# define ERR_NOTONCHANNEL(client, channel)			(" 442 " + client + " " + channel + " :You're not on that channel\r\n")
# define ERR_USERONCHANNEL(client, nick, channel)	(" 443 " + client + " " + nick + " " + channel + " :is already on channel\r\n")

# define ERR_NEEDMOREPARAMS(client) 				(" 461 " + client + " :Not enough parameters\r\n")
# define ERR_PASSWDMISMATCH(client) 				(" 464 " + client + " :Password incorrect\r\n")

// ilan //

# define ERR_CHANNELISFULL(nick, channel)			(serverName + " 471 " + nick + " " + channel + " :Cannot join channel (+l)\r\n")
# define ERR_INVITEONLYCHAN(nick, channel)			(serverName + " 473 " + nick + " " + channel + " :Cannot join channel (+i)\r\n")
# define ERR_BADCHANNELKEY(client, channel)			(serverName + " 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
# define ERR_BADCHANMASK(channel) 					(serverName + " 476 " + channel + " :Bad Channel Mask\r\n")
# define ERR_CHANOPRIVSNEEDED(nick, channel)		(serverName + " 482 " + nick + " " + channel + " :You're not channel operator\r\n")
# define ERR_UMODEUNKNOWNFLAG(client)				(serverName + " 501 " + client + " :Unknown MODE flag\r\n")

# define ERR_INVALIDMODEPARAM(client, channel, mode, param, reason)(serverName + " 696 " + client + " " + channel + " " + mode + " " + param + " :" + reason + "\r\n")

# define MODE(nick, user, channel, mode, param)		(":" + nick + "!~" + user + "@localhost MODE " + channel + " " + mode + " " + param + "\r\n")
# define PART(nick, user, channel, reason)			(":" + nick + "!~" + user + "@localhost PART " + channel + " :" + reason + "\r\n")
# define KICK(nick, user, channel, target, comment)	(":" + nick + "!~" + user + "@localhost KICK " + channel + " " + target + " :" + comment + "\r\n")
# define TOPIC(nick, user, channel, topic)			(":" + nick + "!~" + user + "@localhost TOPIC " + channel + " :" + topic + "\r\n")
# define JOIN(nick, user, channel)					(":" + nick + "!~" + user + "@localhost JOIN " + channel + "\r\n")
# define INVITE(nick, user, target, channel)		(":" + nick + "!~" + user + "@localhost INVITE " + target + " :" + channel + "\r\n")