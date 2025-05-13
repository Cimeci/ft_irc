/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:44:10 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/13 14:36:48 by ncharbog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <map>

class Client;

class Channel{
	private:
		std::string _name;
		std::string _topic;
		std::string _symbol;
		std::map<int, Client *> _clients;

	public:
		Channel(const std::string& name);

    	void addClient(int client_fd, Client &Client);
		bool isClientInChannel(int client_fd) const;
    	void removeClient(int client_fd);

		void broadcast(const std::string& message, int sender_fd);

		std::string getName() const;

		std::map<int, Client*>& getClients() { return _clients; }

		void setTopic(const std::string& topic);
		std::string getTopic() const;

		void setSymbol(const std::string& symbol);
		std::string getSymbol() const;

		const std::map<int, Client *> &getClients() const;


};