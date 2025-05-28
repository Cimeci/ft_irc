/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:14 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:27:00 by noacharbogn      ###   ########.fr       */
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

void Client::setState(State state){_state = state;}

void Client::setBuffer(std::string buffer) {_buffer = buffer;}


std::string Client::getNickname() const{return _nickname;}

std::string Client::getUsername() const{return _username;}

std::string Client::getHostname() const{return _hostname;}

std::string Client::getServername() const{return _servername;}

std::string Client::getRealname() const{return _realname;}

Client::State Client::getState() const{return _state;}

void Client::markForClose() {_shouldClose = true;}

bool Client::getShouldClose() const {return _shouldClose;}

char Client::getPrefix(Grade g){
	switch (g){
        case OPERATOR:		return '@';
        default:			return '\0'; 
	}
}

std::string Client::getBuffer() {return _buffer;}

bool Client::hasDataToSend() {return !_buffer.empty();}