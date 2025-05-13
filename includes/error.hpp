/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:33:56 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/13 10:53:28 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# define ERR_NOSUCHNICK serverName + " 401 " + sender->getNickname() + " " + target + " :" + "No such nick/channel" + "\r\n"
# define ERR_NORECIPIENT serverName + " 411 " + sender->getNickname() + " :No recipient given (PRIVMSG)\r\n"
# define ERR_NOTEXTTOSEND serverName + " 412 " + sender->getNickname() + " :No text to send\r\n"

#define RPL_NAMEREPLY(nick, symbol, channel, names) (serverName + " 353 " + nick + " " + symbol + " " + channel + " :" + names + "\r\n")
#define RPL_ENDOFNAMES(nick, channel) (serverName + " 366 " + nick + " " + channel + " :End of /NAMES list.\r\n")