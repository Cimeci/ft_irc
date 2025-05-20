/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botUtils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:45:46 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 14:25:43 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "botUtils.hpp"
# include "Bot.hpp"

void sendMessage(int fd, std::string msg){
	send(fd, msg.c_str(), msg.length(), 0);
}

void sendChannelMessage(int fd, std::string msg){
	msg = "PRIVMSG #GambleRoom" + msg;
	send(fd, msg.c_str(), msg.length(), 0);
}

std::string recvMessage(int fd) {
    char buffer[1024] = {0};
    ssize_t bytes_received = recv(fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        return std::string(buffer);
    }
    return "";
}

std::string size_t_to_string(size_t value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}