/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:36:37 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/06 16:33:26 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "irc.hpp"

int Irc::server() {
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		std::cerr << "Erreur socket()\n";
		return 1;
	}
	
	int opt = 1;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Erreur bind()\n";
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, 10) < 0) {
        std::cerr << "Erreur listen()\n";
        close(server_socket);
        return 1;
    }

    std::cout << "Serveur en écoute sur le port " << _port << "...\n";

	if (clients())
		return 1;
	
    close(server_socket);
    return 0;
}

int Irc::clients(){
	
	sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
	
    client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_len);
    if (client_socket < 0) {
        std::cerr << "Erreur accept()\n";
        close(server_socket);
        return 1;
    }

    std::cout << "Connexion acceptée depuis " << inet_ntoa(client_addr.sin_addr) << "\n";
	
	connection();
}