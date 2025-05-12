/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:04:17 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/12 14:28:00 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

std::vector<std::string> ft_split(std::string str, const std::string c){
	std::vector<std::string> split;
	size_t end = 0;
	size_t new_end;

	while ((new_end = str.find(c, end)) != std::string::npos) {
		split.push_back(str.substr(end, new_end - end));
		end = new_end + c.size();
	}
	if (end < str.size())
		split.push_back(str.substr(end));
	return split;
}

bool Irc::valueExist(std::string value, int mode){
	for (std::map<int, Client*>::const_iterator it = clientBook.begin(); it != clientBook.end(); ++it) {
		if (it->second && it->second->getNickname() == value && mode == 1)
			return true;
	}
	if (mode == 1)
		return false;
	for (std::map<int, Client*>::const_iterator it = clientBook.begin(); it != clientBook.end(); ++it) {
		if (it->second && it->second->getUsername() == value && mode == 2)
			return true;
	}
	if (mode == 2)
		return false;
}