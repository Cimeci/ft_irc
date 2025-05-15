/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:04:17 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/15 13:43:34 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

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

bool Irc::valueExist(std::string value){
	for (std::map<int, Client*>::const_iterator it = clientBook.begin(); it != clientBook.end(); ++it) {
		if (it->second && it->second->getNickname() == value)
			return true;
	}
	return false;
}

std::string getTime(void) {
	std::time_t t = std::time(0);
	std::tm *now = std::localtime(&t);

	std::stringstream ss;
	ss << (now->tm_year + 1900) << "-"
		<< (now->tm_mon + 1) << "-"
		<< now->tm_mday << "_"
		<< now->tm_hour << ":"
		<< now->tm_min;
	return ss.str();
}
