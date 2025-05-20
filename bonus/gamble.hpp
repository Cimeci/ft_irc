/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamble.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:55:04 by inowak--          #+#    #+#             */
/*   Updated: 2025/05/20 17:18:11 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../includes/colors.hpp"
# include "botUtils.hpp"

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
		bool isDoublonCard(std::string card);

		int gambleAtoi(char nb);

		int playGamble(int fd);

};