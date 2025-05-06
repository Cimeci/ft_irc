/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:35:48 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/06 15:29:47 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

bool Irc::setParameters(const int port, const std::string password){
	if (!(port >= 0 && port <= MAX_PORT))
    	return false;
	_port = port;
	_password = password;
	return true;
}