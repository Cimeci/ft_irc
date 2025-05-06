/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:53:41 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/06 17:47:32 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

class Client{
	private:
		int client_socket;
		std::string _username;
		std::string _nickname;

	public:
		Client();
		~Client();

		void setNickname(const std::string nick);
		void setUsername(const std::string user);
};