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
 * ----Also may be moved to the Dealer Object
 * CURRENT GOAL, - Best BIG-O implementation for restricting the max amount of cards a player can have.
 * - Brandon
 */
void DKATGame::dealCards() {
	int numberOfCardsPerPlayer = 52 / playerNumber;
	int remainingCards = 52 % playerNumber;
	int remainingCardsPulled[remainingCards];
	int remainingCardsPulledCurrentLength = 0;
	srand(time(NULL)); //Randomizes the number each run through of the application

	//Chooses cards to remove until the remaining cards match the projected remainder.
	for (int i = 0; i < remainingCards; i++) {
		while (true) {
			int cardPulled = rand() % 52 + 1; //Picks a random card to pull]

			bool cardAlreadyPulled = false;
			for (int j = 0; j < remainingCardsPulledCurrentLength; j++) { //checks to see if card was already pulled
				if (remainingCardsPulled[j] == cardPulled) { //Marks the check if the card was already pulled
					cardAlreadyPulled = true;
				}
			}
			if(!cardAlreadyPulled){
				cout << "The " << cardPulled << " was pulled" << endl;
				remainingCardsPulled[remainingCardsPulledCurrentLength++] = cardPulled;
				break;
			}

		}
	}

	////////////////
	for (int i = 1; i <= 52; i++) {  	////actually deals the cards

		// CHECKS TO SEE IF CARD HAS BEEN REMOVED FROM ARRAY
		bool cardHasBeenRemoved = false;
		for(int j=0;j<remainingCards;j++){
			if(remainingCardsPulled[j]==i){
				cardHasBeenRemoved = true;
				cout << i << " has been removed *****" << endl;
			}
		}
		if(cardHasBeenRemoved){
			continue;
		}
		//// Check card removed claus end.

		int randomedPlayer = rand() % playerNumber;
		//Checks to see if player has max card count
		while (true) {
			if (players[randomedPlayer].cardCount != numberOfCardsPerPlayer) {
				players[randomedPlayer].cards[players[randomedPlayer].cardCount++] =
						i;
				cout << i << " goes to player " << randomedPlayer << endl;
				break;
			} else {
				//This else statement will pass the card to the person who goes after the current player.
				randomedPlayer++;
				if (randomedPlayer >= playerNumber) {
					// If the card is passed to a player above the threshold, it gets passed to the first player.
					randomedPlayer = 0;
				}
			}
		}

	}
	for (int i = 0; i < playerNumber; i++) {
		cout << "Player " << i << " has " << players[i].cardCount
				<< " many cards." << endl;
	}

	cout<<"This is how many cards that have been removed: "<<remainingCardsPulledCurrentLength;
}
