/*
 * Player.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: Brandon Rosales
 */

#include "Player.h"

Player::Player():name("No Name"){
}

string Player::cardNumbersToString() {
	stringstream ss;
	ss << name << "'s card numbers: ";
	for (int i = 0; i < cardCount; i++) {
		ss << cards[i].ID << " ";
	}
	return ss.str();
}

string Player::cardNamesToString() {
	stringstream ss;
	ss << name << "'s hand: ";
	for (int i = 0; i < cardCount; i++) {
		ss << cards[i].name << " ";
	}
	return ss.str();
}


bool Player::removeCard(string cardName) {
	for (int i = 0; i < cardCount;i++) {
		if (cardName==cards[i].name) {
			for (int j = i; j <cardCount-1 ;j++) {
				cards[j] = cards[j + 1];
			}
			cardCount--;
			//cout << "Card at index " << i << " was removed from " << name <<"'s hand."<< endl;
			return true;
		}
	}
	return false;
}

int Player::findCardIndexInHand(string cardName) {
	for (int i = 0; i < cardCount; i++) {
		if (cardName == cards[i].name) {
			return i;
		}
	}
	return -1;
}

//bool Player::removeCard(int cardNumber) {
//	for (int i = 0; i < cardCount;i++) {
//		if (cardNumber==cards[i].ID) {
//			for (int j = i; j <cardCount-1 ;j++) {
//				cards[j] = cards[j + 1];
//			}
//			cardCount--;
//			cout << "Card at index " << i << " was removed from " << name <<"'s hand."<< endl;
//			return true;
//		}
//	}
//	return false;
//}