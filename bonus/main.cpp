/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:20:19 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 10:49:39 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/colors.hpp"
# include "Bot.hpp"

int main(int argc, char **argv){
	
	if (argc != 3 || !argv[1] || !argv[2]){
		std::cout << RED << "[ERROR] " << RESET << "Invalid format : ./gamble serverPort serverPassword" << std::endl;
		return (1);
	}
	for (size_t i = 0; argv[1][i]; i++){
		if (!isdigit(argv[1][i])){
			std::cout << RED << "[ERROR] " << RESET << "Invalid format : serverPort must be numbers only" << std::endl;
			return (1);
		}
	}

	Bot bot = Bot(argv[1], argv[2]);
	bot.dealer();
}