/*
 * DKATGame.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Brandon Rosales
 */

#ifndef DKATGAME_H_
#define DKATGAME_H_
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "Player.h"

using namespace std;

class DKATGame	 {
public:
	int playerNumber;
	Player players[8];
	int cardPile[52];
	int cardPileCount = 0;

	DKATGame(int numberOfPlayers);
	string cardsInPileToString();
	void dealCards();
	void playGame();
	void displayPlayerOptions(Player &player);
};

#endif /* DKATGAME_H_ */
