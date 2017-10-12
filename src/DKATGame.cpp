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
DKATGame::DKATGame(int numberOfPlayers) : playerNumber(numberOfPlayers) {
	if (numberOfPlayers >= 3) {
		cout << this->playerNumber << " Players are in the game" << endl;

		for (int i = 0; i < numberOfPlayers; i++) {
			/////////place holder for potential future initilization - creates new players for game
			players[i] = Player();
		}

		dealCards();
		playGame();
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
			int cardPulled = rand() % 52; //Picks a random card to pull]

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
				cardPile.cards[cardPile.cardCount++] = Card::ALLCARDS[cardPulled];
				cout << cardPulled << " was added to the card pile" << endl;
				break;
			}

		}
	}

	////////////////
	for (int i = 0; i < 52; i++) {  	////actually deals the cards

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
				players[randomedPlayer].cards[players[randomedPlayer].cardCount++] = Card::ALLCARDS[i];
				cout << i << " goes to player " << randomedPlayer << endl;
				break;
			}
			else {
				randomedPlayer = rand() % playerNumber;
			}
		}

	}
	for (int i = 0; i < playerNumber; i++) {
		cout << "Player " << i << " has " << players[i].cardCount
			<< " many cards." << endl;
	}

	/////// for demonstration purposes only
	for (int i = 0; i < playerNumber; i++) {
		cout << i << " : " << players[i].cardNamesToString() << endl;
	}

	cout << cardPile.cardsNamesToString() << endl;

	cout << "This is how many cards that have been removed: " << remainingCardsPulledCurrentLength << endl;

	/////// for demonstration purposes only

	//potentially move to deconstructor.
	delete premainingCardsPulled;
}

bool DKATGame::submitCards(int numberActivated, Player &player, string cardsToSubmit) {
	cout << "Submiting card: " << cardsToSubmit << endl;
	string cardsSubmitted[4] = { "" };
	int numberOfCardsSubmitted = 0;

	//reads string input and puts it into cardsSubmitted array as integers;
	size_t pos = 0;  //LEARN MORE ABOUT SIZE_T
	string token;
	stringstream ss;

	//SPLITS STRING and stores it in cardsSubmitted[]
	while ((pos = cardsToSubmit.find(",")) != std::string::npos) { //Stops so it doesn't go pass EOF 
		if (numberOfCardsSubmitted == 3) { //or if there have been 3 tokens submitted already.
			cout << "You can not submit more than 4 cards!" << endl;
			return false;
		}

		token = cardsToSubmit.substr(0, pos);
		ss << token;
		ss >> cardsSubmitted[numberOfCardsSubmitted++];
		ss.clear();
		ss.str(string()); // empties string stream buffer
		cardsToSubmit.erase(0, pos + 1); //Moves the buffer to the start of the next number
	}
	ss << cardsToSubmit;
	ss >> cardsSubmitted[numberOfCardsSubmitted++];
	/*
	*Compares each card in the array to each card in the players hand
	*/
	for (int j = 0; j < numberOfCardsSubmitted; j++) {
		bool doesThisCardPass = false;
		for (int i = 0; i < player.cardCount; i++) {
			if (player.cards[i].name == cardsSubmitted[j]) {
				doesThisCardPass = true;
				break;
			}
		}
		if (doesThisCardPass == false) {
			return false;
		}
	}

	//Removes Cards
	for (int i = 0; i < numberOfCardsSubmitted; i++) {
		cardPile.cards[cardPile.cardCount++] = Card::ALLCARDS[Card::ALLCARDS->findCardID(cardsSubmitted[i])];
		player.removeCard(cardsSubmitted[i]);
		//cout << cardsSubmitted[i] << " was added to the card pile" << endl;
	}

	//Saves cards for checking purposes
	lastCardsSubmitted[0] = cardsSubmitted[0];
	lastCardsSubmitted[1] = cardsSubmitted[1];
	lastCardsSubmitted[2] = cardsSubmitted[2];
	lastCardsSubmitted[3] = cardsSubmitted[3];
	lastNumberOfCardsSubmitted = numberOfCardsSubmitted;
	return true;
}

void DKATGame::playGame() {
	bool haveAWinner = false;
	int playersTurn = 0;

	do { // set to run once
		for (int i = 1; i <= 13; i++) {

			playerSubmitsCards(i, playersTurn);
			//wait a couple seconds for a response.
			playerResponses(i, playersTurn);


			playersTurn++;
			if (playersTurn == playerNumber) {
				playersTurn = 0;
			}
			//winner if statement here + break
		}
	} while (haveAWinner);

}

void DKATGame::playerSubmitsCards(int activeCardNumber, int activePlayer) {
	cout << "\n" << endl;
	cout << cardPile.cardsNamesToString() << endl;
	cout << "It is player " << activePlayer << " turn!" << endl;
	cout << "the active card to play is : ";
	switch (activeCardNumber) {
	case 1:
		cout << "Ace" << endl;
		break;
	case 11:
		cout << "Jack" << endl;
		break;
	case 12:
		cout << "Queen" << endl;
		break;
	case 13:
		cout << "King" << endl;
		break;
	default:
		cout << activeCardNumber << endl;
		break;
	}

	cout << players[activePlayer].cardNamesToString() << endl;
	cout << players[activePlayer].name << ", which cards would you like to submit? (seperate with ',')" << endl;
	string cardsToSubmit;
	cin >> cardsToSubmit; // need to run a check for this (assume all is okay for now)

	while (!submitCards(activeCardNumber, players[activePlayer], cardsToSubmit))
	{
		cout << "Your input was not accepted, try again." << endl;
		cin >> cardsToSubmit;
	}
}

void DKATGame::playerResponses(int activeCardNumber, int activePlayer) {
	bool aPlayerChallenged = false;
	for (int i = 0; i < playerNumber && (!aPlayerChallenged); i++) {
		if (activePlayer != i) { // only the other players to respond
			while (true) {
				cout << "---Player " << i << " do you think they are bluffing? ('y' or 'n')" << endl;
				string response;
				cin >> response;
				if (response == "y") {
					challengePlayer(activeCardNumber, activePlayer, i);
					aPlayerChallenged = true;
					break;
				}
				else if (response == "n") {
					//passes
					break;
				}
				else {
					cout << "Invalid command" << endl;
				}
			}
		}
	}
}

bool DKATGame::challengePlayer(int activeCardNumber, int activePlayer, int challengingPlayer) {
	for (int i = 0; i < lastNumberOfCardsSubmitted; i++) {
		cout << "Comparing active card number : " << activeCardNumber << " to previous card accepted: " << Card::ALLCARDS->findCardValue(lastCardsSubmitted[i]) << endl;
		if (Card::ALLCARDS->findCardValue(lastCardsSubmitted[i]) != activeCardNumber) {
			cout << "---===A card failed to match!===---" << endl;
			return true;
		}
	}
	//If it gets here then the active player played ALL acceptable cards
	cout << "---===ALL CARDS MATCHED!===---" << endl;
	return false;
}