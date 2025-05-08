/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:44:10 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/08 10:14:58 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <map>

class Channel{
	private:
		std::string _name;
		std::string _topic;
		std::map<int, bool> _clients;

	public:
		Channel(const std::string& name);
	
    	void addClient(int client_fd);
    	void removeClient(int client_fd);
    	void broadcast(const std::string& message, int sender_fd);
	
		std::string getName() const;
		void setTopic(const std::string& topic);
		std::string getTopic() const;
	
};