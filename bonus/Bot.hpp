/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:08:10 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/21 11:11:46 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "botUtils.hpp"

# include <iostream>
# include <string>
# include <cstring>
# include <cstdlib>
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

	public:
		Bot(std::string IPaddress, std::string password);
		~Bot();

		void dealer();
		void setStop(bool b) {_stop = b;}
		int getFd() const {return _socketFd;}
		bool getStop() const {return _stop;}

		std::string getSender() const {return _sender;}
};

extern Bot* g_bot;