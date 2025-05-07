/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:14 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/07 11:36:51 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client() : _username(""), _nickname(""), _state(CONNECTED) {}

Client::~Client() {}

void Client::setNickname(const std::string nick){_nickname = nick;}

void Client::setUsername(const std::string user){_username = user;}

std::string Client::getNickname() const{return _nickname;}

std::string Client::getUsername() const{return _username;}

Client::State Client::getState() const{return _state;}

void Client::setState(State state){_state = state;}