/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botUtils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:16:06 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/21 11:00:23 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <vector>
# include <sstream>
# include <cstring>
# include <csignal>

std::vector<std::string> ft_split(std::string str, const std::string& c);
std::string recvMessage(int fd);
void sendMessage(int fd, std::string msg);
void sendChannelMessage(int fd, std::string msg);
std::string size_t_to_string(size_t value);