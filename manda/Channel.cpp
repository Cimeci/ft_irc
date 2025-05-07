/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:15:06 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/07 15:22:03 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

Channel::Channel(const std::string& name):_name(name){
	_topic = "channel";
}

void Channel::addClient(int client_fd){
	_clients[client_fd] = false;	
}

void Channel::removeClient(int client_fd){}

void Channel::broadcast(const std::string& message, int sender_fd){}

std::string Channel::getName() const{}

void Channel::setTopic(const std::string& topic){}

std::string Channel::getTopic() const{}