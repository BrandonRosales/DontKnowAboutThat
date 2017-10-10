/*
 * DKATGame.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: Brandon Rosales
 */

#include "DKATGame.h"

 /*
  * Checks the amount of players in a game
  */
DKATGame::DKATGame(int numberOfPlayers) : playerNumber(numberOfPlayers), cardPile{0} {
	if (numberOfPlayers >= 3) {
		cout << this->playerNumber << " Players are in the game" << endl;

		for (int i = 0; i < numberOfPlayers; i++) {
			/////////place holder for potential future initilization - creates new players for game
			players[i] = Player();
		}

		dealCards();
	}
	else {
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
	int *premainingCardsPulled = new int[remainingCards];
	//int remainingCardsPulled[remainingCards]; //
	int remainingCardsPulledCurrentLength = 0;
	srand(time(NULL)); //Randomizes the number each run through of the application

	//Chooses cards to remove until the remaining cards match the projected remainder.
	for (int i = 0; i < remainingCards; i++) {
		while (true) {
			int cardPulled = rand() % 52 + 1; //Picks a random card to pull]

			bool cardAlreadyPulled = false;
			for (int j = 0; j < remainingCardsPulledCurrentLength; j++) { //checks to see if card was already pulled
				if (premainingCardsPulled[j] == cardPulled) { //Marks the check if the card was already pulled
					cardAlreadyPulled = true;
				}
			}
			if (!cardAlreadyPulled) {
				cout << "The " << cardPulled << " was pulled" << endl;
				premainingCardsPulled[remainingCardsPulledCurrentLength++] = cardPulled;
				//
				cardPile[cardPileCount++] = cardPulled;
				cout << cardPulled << " was added to the card pile"<<endl;
				break;
			}

		}
	}

	////////////////
	for (int i = 1; i <= 52; i++) {  	////actually deals the cards

		// CHECKS TO SEE IF CARD HAS BEEN REMOVED FROM ARRAY
		bool cardHasBeenRemoved = false;
		for (int j = 0; j < remainingCards; j++) {
			if (premainingCardsPulled[j] == i) {
				cardHasBeenRemoved = true;
				cout << i << " has been removed *****" << endl;
			}
		}
		if (cardHasBeenRemoved) {
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
			}
			else {
				randomedPlayer = rand() % playerNumber;

				//				//This else statement will pass the card to the person who goes after the current player.
				//				randomedPlayer++;
				//				if (randomedPlayer >= playerNumber) {
				//					// If the card is passed to a player above the threshold, it gets passed to the first player.
				//					randomedPlayer = 0;
				//				}
			}
		}

	}
	for (int i = 0; i < playerNumber; i++) {
		cout << "Player " << i << " has " << players[i].cardCount
			<< " many cards." << endl;
	}

	/////// for demonstration purposes only
	for (int i = 0; i < playerNumber;i++) {
		cout <<i<<" : "<< players[i].cardsToString()<<endl;
	}

	cout << cardsInPileToString() << endl;

	cout << "This is how many cards that have been removed: " << remainingCardsPulledCurrentLength << endl;
	
	/////// for demonstration purposes only
	playGame();

	//potentially move to deconstructor.
	delete premainingCardsPulled;
}

/**
* Returns the cards currently in the pile in a string
*/
string DKATGame::cardsInPileToString() {
	stringstream ss;
	ss << "Card Pile: ";
	for (int i = 0; i < cardPileCount; i++) {
		ss << cardPile[i] << " ";
	}
	return ss.str();
}

void DKATGame::displayPlayerOptions(Player &player) {
	cout << "\n\n"<<player.cardsToString()<<endl;
	cout << player.name << "'s options:" << endl;
	cout << endl;
}

void DKATGame::playGame() {
	bool haveAWinner = false;
	int playersTurn = 0;

	do { // set to run once
		for (int i = 1; i <= 13; i++) {
			cout << "It is player " << playersTurn << " turn!"<<endl;
			cout << "the active card to play is : " << i << endl;
			displayPlayerOptions(players[playersTurn]);
			playersTurn++;
			if (playersTurn==playerNumber) {
				playersTurn = 0;
			}
			//winner if statement here + break
		}
	} while (haveAWinner);

}