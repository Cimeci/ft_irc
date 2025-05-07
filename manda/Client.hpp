/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/07 14:43:19 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <string>
# include <vector>

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
	    State _state;

		std::vector<std::string> _channels;
		bool _isOperator;
	
	public:
	    Client();
	    ~Client();
	
	    void setNickname(const std::string nick);
	    void setUsername(const std::string user);
	
	    std::string getNickname() const;
	    std::string getUsername() const;
	    State getState() const;
	    void setState(State state);
};
