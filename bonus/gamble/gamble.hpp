/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamble.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:55:04 by inowak--          #+#    #+#             */
/*   Updated: 2025/04/30 16:38:08 by inowak--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <vector>

class Gamble{

	private:
		size_t bank;
		// std::vector<std::string> cardsPack;
	
	public:
		Gamble(size_t bank);
		~Gamble();

		size_t getBank() const;
		void setBank(size_t newAmount);
		std::string generateCard();

};