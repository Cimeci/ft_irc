/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noacharbogne <noacharbogne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/28 16:28:02 by noacharbogn      ###   ########.fr       */
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
		void setState(State state);
		void setBuffer(std::string buffer);
		void markForClose();

		std::string getNickname() const;
		std::string getUsername() const;
		std::string getHostname() const;
		std::string getServername() const;
		std::string getRealname() const;
		State getState() const;
		char getPrefix(Grade g);
		bool getShouldClose() const;
		std::string getBuffer();

		bool hasDataToSend();

		std::map<Channel *, Grade> _clientChannels;
		std::map<Channel *, bool> _invitationChannels;
};
