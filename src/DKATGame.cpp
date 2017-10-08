/*
 * DKATGame.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: Brandon Rosales
 */

#include "DKATGame.h"

/*
 * Checks the ammount of players in a game
 */
DKATGame::DKATGame(int numberOfPlayers) :
		playerNumber(numberOfPlayers) {
	if (numberOfPlayers >= 3) {
		cout << this->playerNumber << " Players are in the game" << endl;

		for (int i = 0; i < numberOfPlayers; i++) {
			/////////place holder for potential future initilization - creates new players for game
			players[i] = Player();
		}

		dealCards();
	} else {
		cout << "There needs to be at least 3 people to play this game!"
				<< endl;
	}
}
/**
 * Deals cards out amongst players in game
 * CURRENT GOAL, - Best BIG-O implementation for restricting the max amount of cards a player can have.
 * - Brandon
 */
void DKATGame::dealCards() {
	int numberOfCardsPerPlayer = 52 / playerNumber;
	int remainingCards = 52 % playerNumber;
	srand(time(NULL)); //Randomizes the number each run through of the application

	for (int i = 1; i <= 52; i++) {
		int randomedPlayer = rand() % playerNumber;
		players[randomedPlayer].cards[players[randomedPlayer].cardCoubt++] = i;
		cout << i << " goes to player " << randomedPlayer << endl;

	}
	for (int i = 0; i < playerNumber; i++) {
		cout << "Player " << i << " has " << players[i].cardCoubt
				<< " many cards." << endl;
	}
}
