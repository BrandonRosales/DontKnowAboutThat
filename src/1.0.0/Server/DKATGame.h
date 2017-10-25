/*
 * DKATGame.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Brandon Rosales
 */
#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "Card.h"
#include "CardPile.h"
#include "Player.h"
#include "Server.h"

using namespace std;

class DKATGame	 {
public:
	static int numberOfPlayersWithNames; // NEW
	static string activeCardValue; // new


	bool onePlayerRun;
	int playerOneRunPlayerNumber;

	int playerNumber;
	static Player players[8]; //static is new
	static CardPile cardPile;
	string lastCardsSubmitted[4];
	int lastNumberOfCardsSubmitted;

	DKATGame(int numberOfPlayers,Server &server);
	void dealCards();
	void playGame();
	void displayActiveNumberAndPlayer(int activeCardNumber, int activePlayer);
	void playerSubmitsCards(int activeCard, int activePlayer);
	bool processingSubmitCards(int numberActivated, Player &playerr,int playerID, string cardsToSubmit);
	void playerResponses(int activeCard, int activePlayer);
	bool shouldTheBotChallenge(int activeCardNumber, int activePlayer, int botNumber);
	bool challengePlayer(int activeCard, int activePlayer, int challengingPlayer);

	bool activatePlayersTurn(int activePlayer,string &cardsToSubmit);
private:
	Server server;
};