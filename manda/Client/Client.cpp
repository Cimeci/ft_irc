/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:14 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/21 13:48:46 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client() : _username(""), _nickname(""), _hostname("0"), _servername("*"), _realname("realname"), _buffer(""), _shouldClose(false),  _state(CONNECTED) {}

Client::~Client() {}

void Client::setNickname(const std::string nickname){_nickname = nickname;}

void Client::setUsername(const std::string username){_username = username;}

void Client::setHostname(const std::string hostname){_hostname = hostname;}

void Client::setServername(const std::string servername){_servername = servername;}

void Client::setRealname(const std::string realname){_realname = realname;}


std::string Client::getNickname() const{return _nickname;}

std::string Client::getUsername() const{return _username;}

std::string Client::getHostname() const{return _hostname;}

std::string Client::getServername() const{return _servername;}

std::string Client::getRealname() const{return _realname;}


Client::State Client::getState() const{return _state;}

void Client::setState(State state){_state = state;}

char Client::getPrefix(Grade g){
	switch (g){
        case OPERATOR:		return '@';
        default:			return '\0'; 
	}
}