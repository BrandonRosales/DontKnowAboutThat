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
#include "Player.h"

using namespace std;

class DKATGame {
	int playerNumber;
public:
	Player players[8];
	int activeCardNumber = 1;
	DKATGame(int numberOfPlayers);
	void dealCards();
};

#endif /* DKATGAME_H_ */
