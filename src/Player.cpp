/*
 * Player.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: Brandon Rosales
 */

#include "Player.h"

Player::Player():name("No Name"){
}

string Player::cardsToString() {
	stringstream ss;
	ss << name << "'s hand: ";
	for (int i = 0; i < cardCount;i++) {
		ss << cards[i]<<" ";
	}
	return ss.str();
}

bool Player::removeCard(int cardNumber) {
	for (int i = 0; i < cardCount;i++) {
		if (cardNumber==cards[i]) {
			for (int j = i; j <cardCount-1 ;j++) {
				cards[j] = cards[j + 1];
			}
			cardCount--;
			cout << "Card at index " << i << " was removed from " << name <<"'s hand."<< endl;
			return true;
		}
	}
	return false;
}