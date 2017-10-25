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

string Player::cardNamesToStringNoName() {
	stringstream ss;
	for (int i = 0; i < cardCount; i++) {
		ss << cards[i].name;
		if ((i+1)<cardCount) {
			ss << " ";
		}
	}
	return ss.str();
}

void Player::addCard(Card cardToAdd,bool sort) {
	cards[cardCount++]=cardToAdd;
	if (sort) {
		sortByValue();

	}
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

void Player::sortByID() {
	for (int i = 0; i < cardCount - 1; i++) {
		if (cards[i].ID>(cards[i + 1]).ID) {
			Card tempCard = cards[i];
			cards[i] = cards[i + 1];
			cards[i + 1] = tempCard;
			i = -1;
		}
	}
}

void Player::sortByValue() {
	for (int i = 0; i < cardCount - 1; i++) {
		if (cards[i].value>(cards[i + 1]).value) {
			Card tempCard = cards[i];
			cards[i] = cards[i + 1];
			cards[i + 1] = tempCard;
			i = -1;
		}
	}
}

int Player::findCardIndexInHand(string cardName) {
	for (int i = 0; i < cardCount; i++) {
		if (cardName == cards[i].name) {
			return i;
		}
	}
	return -1;
}

int Player::findAmountOfValueInHand(int value) {
	int amountOfCardsWithValue = 0;
	for (int i = 0; i < cardCount; i++) {
		if (cards[i].value==value) {
			amountOfCardsWithValue++;
		}
	}
	return amountOfCardsWithValue;
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