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
	bool onePlayerRun;
	int playerOneRunPlayerNumber;

	int playerNumber;
	Player players[8];
	CardPile cardPile;
	string lastCardsSubmitted[4];
	int lastNumberOfCardsSubmitted;

	DKATGame(int numberOfPlayers);
	void dealCards();
	void playGame();
	void displayActiveNumberAndPlayer(int activeCardNumber, int activePlayer);
	void playerSubmitsCards(int activeCard, int activePlayer);
	bool processingSubmitCards(int numberActivated, Player &playerr, string cardsToSubmit);
	void playerResponses(int activeCard, int activePlayer);
	bool shouldTheBotChallenge(int activeCardNumber, int activePlayer, int botNumber);
	bool challengePlayer(int activeCard, int activePlayer, int challengingPlayer);
};

#endif /* DKATGAME_H_ */
