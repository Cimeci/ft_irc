/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamble.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:41:07 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 18:28:44 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gamble.hpp"
# include <algorithm>
# include <iostream>
# include <ctime>

GAMBLEEXCEPTION::GAMBLEEXCEPTION(const std::string& msg) : _msg(msg) {}

const char* GAMBLEEXCEPTION::what() const throw() {
	return _msg.c_str();
}

GAMBLEEXCEPTION::~GAMBLEEXCEPTION() throw() {}


Gamble::Gamble(size_t bank): bank(bank){setCardsPack();}
Gamble::~Gamble(){}

size_t Gamble::getBank() const {return bank;}
void Gamble::setBank(size_t newAmount){bank = newAmount;}

std::vector<std::string> Gamble::getCardPack() const{return cardsPack;}
std::string Gamble::getCard(const size_t index) const{return cardsPack[index];}

bool Gamble::isDoublonCard(std::string card){
	for (size_t i = 0; i < cardsPack.size(); i++)
	{
		if (card == cardsPack[i])
			return true;
	}
	return false;
}

void Gamble::setCardsPack(){
	std::string card;
	int i = 0;
	while (1)
	{
		card = generateCard();
		if (!isDoublonCard(card)){
			cardsPack.push_back(card);
			i++;
		}
		if (i > 3)
			break;
	}
}

void Gamble::clearCardPack() {cardsPack.clear();}

std::string Gamble::generateCard(){
	std::string card;
	int color = std::rand() % 2;
	int type = std::rand() % 2;
	// std::cout << "color : " << color << " | type : " << type << std::endl;
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
	int number = std::rand() % 12 + 1;
	// std::cout << number << std::endl;
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
				card += "Q";break;
			case 13:
				card += "K";break;
		}
	}
	return card;
}

std::string Gamble::getEmojiFromCardCode(std::string code) {
    // std::cout << std::endl << "CARD : " << code << std::endl;
    std::string emojis[] = {
        "🂡","🂢","🂣","🂤","🂥","🂦","🂧","🂨","🂩","🂪","🂫","🂭","🂮",
        "🂱","🂲","🂳","🂴","🂵","🂶","🂷","🂸","🂹","🂺","🂻","🂽","🂾",
        "🃁","🃂","🃃","🃄","🃅","🃆","🃇","🃈","🃉","🃊","🃋","🃍","🃎",
        "🃑","🃒","🃓","🃔","🃕","🃖","🃗","🃘","🃙","🃚","🃛","🃝","🃞"
    };

    std::string values = "123456789XVQK";
    std::string color = code.substr(0, 1);
    std::string suit = code.substr(1, 1);
    char valueChar = code[2];

    size_t valueIndex = values.find(valueChar);
    if (valueIndex == std::string::npos)
        return "❌";

    int offset = 0;
    if (suit == "S" && color == "B") offset = 0;
    else if (suit == "H" && color == "R") offset = 13;
    else if (suit == "D" && color == "R") offset = 26;
    else if (suit == "C" && color == "B") offset = 39;
    else return "❌";

    return emojis[offset + valueIndex];
}

int Gamble::gambleAtoi(char nb){

	if (isdigit(nb))
		return (nb - '0');
	char more[5] = {'X', 'V', 'Q', 'K'};
	size_t i = 0;
	for (; nb != more[i]; i++);
	if(i > 3)
		return (-1);
	return (10 + i);
}

bool isStringDigit(std::string &str){
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

std::string getCommand(std::string input){
	input = input.substr(input.find(":", 1) + 1);
	input = input.substr(0, input.find("\r\n"));
	return input;
}

int Gamble::playGamble(int fd)
{
	std::srand(std::time(0));
	Gamble gamble(100);
	size_t bet = 0;
	size_t multiple = 1;
	std::string line = "0";
	std::string input = "10000000000000";
	std::string name;
	std::string handlePlay1[2] = {"RED", "BLACK"};
	std::string handlePlay2[2] = {"LOWER", "UPPER"};
	std::string handlePlay3[2] = {"INSIDE", "OUTSIDE"};
	std::string handlePlay4[4] = {"CLUB", "HEART", "SPADE", "DIAMOND"};
	
	std::cout << "PRESENTATION" << std::endl;
	sendChannelMessage(fd, "--------------------------- command ---------------------------");
	sendChannelMessage(fd, "'PLAY' : for play camble");
	sendChannelMessage(fd, "'EXIT' : for exit");
	sendChannelMessage(fd, "--------------------------- command ---------------------------");
	while (line != "EXIT"){
		if (gamble.getBank() == 0){
			sendChannelMessage (fd, "[you're broke, goodbye]"); return(1);
		}
		gamble.clearCardPack();
		gamble.setCardsPack();
		line = getCommand(recvMessage(fd));
		// std::cout << "'" << line << "'" << std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (line == "PLAY")
		{
			bet = 0;
			multiple = 1;
			try {

				sendChannelMessage(fd, "Your have " + size_t_to_string(gamble.getBank()) + " in your bank account");
				while (!isStringDigit(input) || atoi(input.c_str()) > (int)gamble.getBank()){
					sendChannelMessage(fd, "Enter the amount to bet : ");
					input = getCommand(recvMessage(fd));
				}
				bet = atoi(input.c_str());
				sendChannelMessage(fd, "Let's Play");
					
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				sendChannelMessage(fd, "For a x2, Bet the card is 'RED' or 'BLACK' ?");
				while (1)
				{
					input = getCommand(recvMessage(fd));
					if (input == "OUT") {throw std::bad_exception();}
					gamble.setBank(gamble.getBank() - bet);
					if (input == "RED")
					{
						if (gamble.getCard(0)[0] == 'R'){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(0)) + "");
							multiple = 2;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card isn't red " + gamble.getEmojiFromCardCode(gamble.getCard(0)) + "");}
					}
					else if (input == "BLACK")
					{
						if (gamble.getCard(0)[0] == 'B'){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(0)) + "");
							multiple = 2;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card isn't black " + gamble.getEmojiFromCardCode(gamble.getCard(0)) + "");}
					}
				}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


				sendChannelMessage(fd, "For a x3, Bet the card is 'LOWER' or 'UPPER' than the actual card : " + gamble.getEmojiFromCardCode(gamble.getCard(0)) + " ?");
				while (1)
				{
					input = getCommand(recvMessage(fd));
					if (input == "OUT") {gamble.setBank(gamble.getBank() + bet * multiple);throw std::bad_exception();}
					if (input == "LOWER")
					{
						if (gamble.gambleAtoi(gamble.getCard(1)[2]) <= gamble.gambleAtoi(gamble.getCard(0)[2])){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(1)) + "");
							multiple = 3;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card isn't lower " + gamble.getEmojiFromCardCode(gamble.getCard(1)) + "");}
					}
					else if (input == "UPPER")
					{
						if (gamble.gambleAtoi(gamble.getCard(1)[2]) >= gamble.gambleAtoi(gamble.getCard(0)[2])){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(1)) + "");
							multiple = 3;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card isn't upper " + gamble.getEmojiFromCardCode(gamble.getCard(1)) + "");}
					}
				}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				sendChannelMessage(fd, "For a x5, Bet the card is 'INSIDE' or 'OUTSIDE' than actuals cards are: " + gamble.getEmojiFromCardCode(gamble.getCard(0)) + " and " + gamble.getEmojiFromCardCode(gamble.getCard(1)) + " ?");
				while (1)
				{
					input = getCommand(recvMessage(fd));
					if (input == "OUT") {gamble.setBank(gamble.getBank() + bet * multiple);throw std::bad_exception();}
					int max = gamble.gambleAtoi(gamble.getCard(0)[2]) > gamble.gambleAtoi(gamble.getCard(1)[2]) ? gamble.gambleAtoi(gamble.getCard(0)[2]) : gamble.gambleAtoi(gamble.getCard(1)[2]);
					int min = gamble.gambleAtoi(gamble.getCard(0)[2]) < gamble.gambleAtoi(gamble.getCard(1)[2]) ? gamble.gambleAtoi(gamble.getCard(0)[2]) : gamble.gambleAtoi(gamble.getCard(1)[2]);
					if (input == "INSIDE")
					{
						if (gamble.gambleAtoi(gamble.getCard(2)[2]) <= max && gamble.gambleAtoi(gamble.getCard(2)[2]) >= min){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(2)) + "");
							multiple = 5;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card " + gamble.getEmojiFromCardCode(gamble.getCard(2)) + " isn't inside "+ gamble.getEmojiFromCardCode(gamble.getCard(0)) + " and " + gamble.getEmojiFromCardCode(gamble.getCard(1)) + "");}
					}
					else if (input == "OUTSIDE")
					{
						if (!(gamble.gambleAtoi(gamble.getCard(2)[2]) <= max && gamble.gambleAtoi(gamble.getCard(2)[2]) >= min)){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(2)) + "");
							multiple = 5;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card " + gamble.getEmojiFromCardCode(gamble.getCard(2)) + " isn't outside "+ gamble.getEmojiFromCardCode(gamble.getCard(0)) + " and " + gamble.getEmojiFromCardCode(gamble.getCard(1)) + "");}
					}
				}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				sendChannelMessage(fd, "For a x10, Bet the card is a 'CLUB', 'HEART', 'SPADE' or 'DIAMOND' ?");
				while (1)
				{
					input = getCommand(recvMessage(fd));
					if (input == "OUT") {gamble.setBank(gamble.getBank() + bet * multiple);throw std::bad_exception();}
					if (input == "CLUB")
					{
						if (gamble.getCard(3)[1] == 'C'){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(3)) + "");
							multiple = 10;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card " + gamble.getEmojiFromCardCode(gamble.getCard(3)) + " isn't a club");}
					}
					else if (input == "HEART")
					{
						if (gamble.getCard(3)[1] == 'H'){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(3)) + "");
							multiple = 10;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card " + gamble.getEmojiFromCardCode(gamble.getCard(3)) + " isn't a heart");}
					}
					else if (input == "SPADE")
					{
						if (gamble.getCard(3)[1] == 'S'){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(3)) + "");
							multiple = 10;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card " + gamble.getEmojiFromCardCode(gamble.getCard(3)) + " isn't a spade");}
					}
					else if (input == "DIAMOND")
					{
						if (gamble.getCard(3)[1] == 'D'){
							sendChannelMessage(fd, "SUCCESS : card is " + gamble.getEmojiFromCardCode(gamble.getCard(3)) + "");
							multiple = 10;
							break;
						}
						else {throw GAMBLEEXCEPTION("[FAILED] : card " + gamble.getEmojiFromCardCode(gamble.getCard(3)) + " isn't a diamond");}
					}
				}
				sendChannelMessage(fd, "GG you win the max bet");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				gamble.setBank(gamble.getBank() + bet * multiple);
			}
			catch (GAMBLEEXCEPTION &e){sendChannelMessage(fd, e.what());}
			catch (std::bad_exception &e){}
		}
	}
	return (0);
}