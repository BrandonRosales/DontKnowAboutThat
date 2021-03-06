/*
 * Player.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Brandon Rosales
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include <iostream>
#include <sstream>
#include "Card.h"

using namespace std;

class Player {
public:
	Player();
	string name;
	Card cards[52] = {0};
	int cardCount = 0;

	string cardNumbersToString();
	string cardNamesToString();
	string cardNamesToStringNoName();

	int findCardIndexInHand(string cardName);
	int findAmountOfValueInHand(int value);
	void addCard(Card cardToAdd, bool sort);
	bool removeCard(string cardName);
	void sortByID();
	void sortByValue();
	//bool removeCard(int cardNumber);
};

#endif /* SRC_PLAYER_H_ */
