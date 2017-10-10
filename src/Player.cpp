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
