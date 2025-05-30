/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:08:10 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/26 12:12:43 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "botUtils.hpp"

# include <iostream>
# include <string>
# include <cstring>
# include <cstdlib>
# include <map>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>

class Bot{
	private:
		int _socketFd;
		std::string _port;
		std::string _password;
		bool _stop;
		std::string _sender;
		std::map<std::string, size_t> _players;

	public:
		Bot(std::string IPaddress, std::string password);
		~Bot();

		void dealer();

		void setStop(bool b) {_stop = b;}

		int getFd() const {return _socketFd;}
		bool getStop() const {return _stop;}
		std::map<std::string, size_t> getPlayers() {return _players;}
		std::string getSender() const {return _sender;}

};

extern Bot* g_bot;