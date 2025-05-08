/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:04:17 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/08 16:01:06 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

std::vector<std::string> ft_split(std::string str, const std::string c){
	std::vector<std::string> split;
	size_t end = 0;
	size_t new_end = str.find(c) + 1;

	std::cout << "[DEBUG]" << "str : " << BLUE << str << RESET << std::endl;
	while (end < str.size()){
		std::cout << "[DEBUG] :" << end << " : to_push : " << str.substr(end, new_end - end) << std::endl;
		split.push_back(str.substr(end, new_end - end));
		std::cout << "[DEBUG] :" << str[end] << " | " << str[new_end] << std::endl;
		end = new_end;
		new_end = str.find(c, end) + 1;
	}
	return split;
} 