/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamble.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:55:04 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/05 16:02:27 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "colors.hpp"

# include <iostream>
# include <vector>

class GAMBLEEXCEPTION : public std::exception {
	private:
		std::string _msg;
	public:
		GAMBLEEXCEPTION(const std::string& msg);
		virtual const char* what() const throw();
		virtual ~GAMBLEEXCEPTION() throw();
};

class Gamble{

	private:
		size_t bank;
		std::vector<std::string> cardsPack;
		std::string _name;
	
	public:
		Gamble(size_t bank);
		~Gamble();

		size_t getBank() const;
		void setBank(size_t newAmount);
		
		std::vector<std::string> getCardPack() const;
		void setCardsPack();
		void clearCardPack();
		std::string getCard(const size_t index) const;

		std::string getEmojiFromCardCode(std::string code);

		std::string generateCard();

		int gambleAtoi(char nb);

		std::string getName() const;
		void setName(std::string name);

};