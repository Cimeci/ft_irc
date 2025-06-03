/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:04:17 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:32:32 by noacharbogn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/Irc.hpp"

bool Irc::setParameters(const int port, const std::string &password){
	if (!(port >= 0 && port <= MAX_PORT)) {
		std::cerr << "Invalid port" << std::endl;
    	return false;
	}
	_port = port;
	if (password.empty()) {
		std::cerr << "Invalid password" << std::endl;
		return false;
	}
	_password = password;
	return true;
}

void Irc::sendMessage(int fd, std::string msg)
{
	std::cout << ORANGE << "[SEND] " << RESET << msg;
	if (send(fd, msg.c_str(), msg.length(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
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

std::string getTime(void) {
	std::time_t t = std::time(0);
	std::tm *now = std::localtime(&t);

	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << (now->tm_year + 1900) << "-"
		<< std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << "-"
		<< std::setw(2) << std::setfill('0') << now->tm_mday << "_"
		<< std::setw(2) << std::setfill('0') << now->tm_hour << ":"
		<< std::setw(2) << std::setfill('0') << now->tm_min;
	return ss.str();
}

std::string toUpper(std::string &str)
{
	std::string input;
	for (int i = 0; str[i]; i++)
		input += toupper(str[i]);
	return input;
}