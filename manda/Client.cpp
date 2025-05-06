/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:14 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/06 17:47:46 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client(){}

Client::~Client(){}

void Client::setNickname(const std::string nick){_nickname = nick;}

void Client::setUsername(const std::string user){_username = user;}