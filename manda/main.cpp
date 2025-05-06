/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:40:45 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/06 15:29:39 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

int main(int argc, char **argv)
{
	if (argc != 3) { std::cerr << "./ircserv <port> <password>"; return 1; }

	Irc irc;

	if (!irc.setParameters(atoi(argv[1]), argv[2])) { return 1; }

	// irc.parsing();
	irc.server();
}