/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamble.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:41:07 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/30 16:44:38 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gamble.hpp"
# include <algorithm>
# include <iostream>
# include <ctime>

Gamble::Gamble(size_t bank): bank(bank){}
Gamble::~Gamble(){}

size_t Gamble::getBank() const {return bank;}
void Gamble::setBank(size_t newAmount){bank = newAmount;}

std::string Gamble::generateCard(){
	std::string card;
	int color = std::rand() % 2;
	int type = std::rand() % 2;
	std::cout << "color : " << color << " | type : " << type << std::endl;
	switch (color)
	{
		case 0:
			card = "R";
			if (type == 0){card += "H";}
			else {card += "D";}
			break;

		case 1:
			card = "B";
			if (type == 0){card += "C";}
			else {card += "S";}
			break;
	}
	int number = std::rand() % 13;
	std::cout << number << std::endl;
	if (number < 10)
		card += number + '0';
	else
	{
		switch (number){
			case 10:
				card += "X";break;
			case 11:
				card += "V";break;
			case 12:
				card += "D";break;
			case 13:
				card += "R";break;
		}
	}
	return card;
}

int main(void)
{
	std::srand(std::time(0));
	Gamble gamble(100);
	std::string card = gamble.generateCard();
	std::cout << "CARD : " << card << std::endl;
	std::cout << gamble.getBank() << std::endl;
	// std::string line = "0";
	// std::string input = "0";
	// std::string handlePlay1[2] = {"RED", "BLACK"};
	// std::string handlePlay2[2] = {"LOWER", "UPPER"};
	// std::string handlePlay3[2] = {"INSIDE", "OUTSIDE"};
	// std::string handlePlay4[4] = {"CLUB", "HEART", "SPADE", "DIAMOND"};
	
	// while (line != "EXIT"){
	// 	std::getline(std::cin, line);
	// 	std::cout << "IF YOU WANT TO PLAY SAY 'PLAY'" << std::endl;
	// 	if (line == "PLAY")
	// 	{
	// 		std::cout << "Say 'OUT' if you want to leave" << std::endl;
	// 		while (input != "OUT")
	// 		{
	// 			while (atoi(input.c_str()) > gamble.getBank()){
	// 				std::cout << "Your have " << gamble.getBank() << " in your bank account" << std::endl;
	// 				std::cout << "Enter the amount to bet : ";
	// 				std::getline(std::cin, input);
	// 			}
	// 			std::cout << "Let's Play" << std::endl << std::endl;
	// 			std::cout << "Bet the card is red or black ?" << std::endl;
	// 			std::getline(std::cin, input);
	// 			if (input != )
				
				
	// 		}
	// 	}
		
		
	// }

}