/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/09 11:18:47 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <string>
# include <map>

class Channel;

class Client {
	public:
	    enum State {
	        CONNECTED,
	        AUTHENTICATED,
	        REGISTERED,
			USER
	    };
	
	private:
		std::string _username;
		std::string _nickname;
		std::string _hostname;
		std::string _servername;
		std::string _realname;
	    State _state;

		
	public:
		Client();
		~Client();
		
		void setNickname(const std::string nickname);
		void setUsername(const std::string username);
		void setHostname(const std::string hostname);
		void setServername(const std::string servername);
		void setRealname(const std::string realname);
		
		std::string getNickname() const;
		std::string getUsername() const;
		State getState() const;
		void setState(State state);
		
		std::map<Channel *, bool> _channels;
	
};
