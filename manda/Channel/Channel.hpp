/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:44:10 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:29:19 by noacharbogn      ###   ########.fr       */
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

		bool _invitation;
		bool _isOpTopic;
		size_t _limitClients;
		std::string _password;
		

	public:
		Channel(const std::string& name);

    	void addClient(int client_fd, Client &Client);
		bool isClientInChannel(int client_fd) const;
    	void removeClient(int client_fd);

		void broadcast(const std::string& message, int sender_fd);
		
		void setTopic(const std::string& topic);
		void setSymbol(const std::string& symbol);
		void setPassword(const std::string& password);
		void setInvitation(const bool info);
		void setIsOpTopic(const bool info);
		void setLimitClients(const size_t info);
		
		std::string getTopic() const;
		std::string getSymbol() const;
		std::string getPassword() const;
		bool getInvitation() const;
		bool getIsOpTopic() const;
		size_t getLimitClients() const;
		std::string getModeInString() const;
		size_t getNbClients() const;
		std::map<int, Client *> &getClients();
		std::string getName() const;
};