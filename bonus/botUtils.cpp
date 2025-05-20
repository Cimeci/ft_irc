/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botUtils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:45:46 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 18:29:30 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "botUtils.hpp"
# include "Bot.hpp"

void sendMessage(int fd, std::string msg){
	send(fd, msg.c_str(), msg.length(), 0);
}

void sendChannelMessage(int fd, std::string msg){
    std::string full_msg = "PRIVMSG #GambleRoom :" + msg + "\r\n";
    send(fd, full_msg.c_str(), full_msg.length(), 0);
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

std::vector<std::string> ft_split(std::string str, const std::string& c) {
	std::vector<std::string> split;
	size_t end = 0;
	size_t new_end;

	while ((new_end = str.find(c, end)) != std::string::npos) {
		std::string part = str.substr(end, new_end - end);
		if (!part.empty())
			split.push_back(part);
		end = new_end + c.size();
	}
	if (end < str.size()) {
		std::string part = str.substr(end);
		if (!part.empty())
			split.push_back(part);
	}
	return split;
}