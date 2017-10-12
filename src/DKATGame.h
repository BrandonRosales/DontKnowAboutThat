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
#include "Card.h"
#include "CardPile.h"
#include "Player.h"



using namespace std;

class DKATGame	 {
public:
	int playerNumber;
	Player players[8];
	CardPile cardPile;
	string lastCardsSubmitted[4];
	int lastNumberOfCardsSubmitted;

	DKATGame(int numberOfPlayers);
	void dealCards();
	void playGame();
	void playerSubmitsCards(int activeCard, int activePlayer);
	void playerResponses(int activeCard, int activePlayer);
	bool challengePlayer(int activeCard, int activePlayer, int challengingPlayer);
	bool submitCards(int numberActivated, Player &playerr, string cardsToSubmit);
};

#endif /* DKATGAME_H_ */
