/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/21 13:48:59 by inowak--         ###   ########.fr       */
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
		enum Grade {
			MEMBER = 0,
			OPERATOR,
		};

	private:
		std::string _username;
		std::string _nickname;
		std::string _hostname;
		std::string _servername;
		std::string _realname;
		std::string _buffer;
		bool _shouldClose;
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
		std::string getHostname() const;
		std::string getServername() const;
		std::string getRealname() const;


		State getState() const;
		void setState(State state);

		char getPrefix(Grade g);

		void markForClose() {_shouldClose = true;}

		bool getShouldClose() const {return _shouldClose;}

		void setBuffer(std::string buffer) {_buffer = buffer;}
		std::string getBuffer() {return _buffer;}
		bool hasDataToSend() {return !_buffer.empty();}

		std::map<Channel *, Grade> _clientChannels;
		std::map<Channel *, bool> _invitationChannels;

};
