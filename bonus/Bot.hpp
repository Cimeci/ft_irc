/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:08:10 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 14:17:55 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "gamble.hpp"
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

	public:
		Bot(std::string IPaddress, std::string password);
		~Bot();

		void dealer();
};