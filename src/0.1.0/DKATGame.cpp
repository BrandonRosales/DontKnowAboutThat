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
	///////////////////////////////////////////////////////
	onePlayerRun = true; ////// ACTIVATES playing one player mode
	playerOneRunPlayerNumber = 2;
	cout << "\nonePlayerRunTest is " << onePlayerRun << endl << endl;
	///////////////////////////////////////////////////////

	if (numberOfPlayers >= 3) {
		cout << playerNumber << " Players are in the game" << endl;

		for (int i = 0; i < numberOfPlayers; i++) {
			/////////place holder for potential future initilization - creates new players for game
			players[i] = Player();
		}

		//This sets the player's name if onePlayerRun is on
		if (onePlayerRun) {
			players[playerOneRunPlayerNumber].name = "Brandon";
		}

		dealCards();
		playGame();
	}
	else {
		cout << "There needs to be at least 3 people to play this game!"
			<< endl;
	}
}

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
				//cout << "The " << cardPulled << " was pulled" << endl;
				premainingCardsPulled[remainingCardsPulledCurrentLength++] = cardPulled;
				//
				cardPile.cards[cardPile.cardCount++] = Card::ALLCARDS[cardPulled];
				//cout << cardPulled << " was added to the card pile" << endl;
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
				//cout << i << " has been removed *****" << endl;
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
				players[randomedPlayer].addCard(Card::ALLCARDS[i], false); // This is the new addCard method
				//cout << i << " goes to player " << randomedPlayer << endl;
				break;
			}
			else {
				randomedPlayer = rand() % playerNumber;
			}
		}

	}
	for (int i = 0; i < playerNumber; i++) {
		players[i].sortByValue();
		cout << "Player " << i << " has " << players[i].cardCount
			<< " cards." << endl;
	}

	/////// for demonstration purposes only
	for (int i = 0; i < playerNumber; i++) {
		cout <<"-----"<< i << " : " << players[i].cardNamesToString() << endl;
	}

	cout <<"-----"<< cardPile.cardsNamesToString() << endl;

	//cout << "This is how many cards that have been removed: " << remainingCardsPulledCurrentLength << endl;

	/////// for demonstration purposes only

	//potentially move to deconstructor.
	delete premainingCardsPulled;
}

void DKATGame::playGame() {
	bool haveAWinner = false;
	int playersTurn = 0;

	do { // set to run once
		for (int i = 1; i <= 13; i++) {
			displayActiveNumberAndPlayer(i, playersTurn);
			playerSubmitsCards(i, playersTurn);
			//wait a couple seconds for a response.
			playerResponses(i, playersTurn);

			//winner if statement here 			
			if (players[playersTurn].cardCount==0) {
				haveAWinner = true;
			}
			else {
				playersTurn++;
				if (playersTurn == playerNumber) {
					playersTurn = 0;
				}
			}


		}
	} while (!haveAWinner);

	cout << "The winner of the game is player " << playersTurn << " - " << players[playersTurn].name << endl;

}

void DKATGame::displayActiveNumberAndPlayer(int activeCardNumber, int activePlayer) {
	cout << "\n" << endl;
	cout<<"There are "<<cardPile.cardCount<<" cards in the pile."<<endl;
	cout <<"-----"<< cardPile.cardsNamesToString() << endl;
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
	cout << players[activePlayer].name<<" has " << players[activePlayer].cardCount << " cards left." << endl;
	////////////////////////////////////////////// END DISPLAY

}

void DKATGame::playerSubmitsCards(int activeCardNumber, int activePlayer) {
	string cardsToSubmit = "";

	if (onePlayerRun) {
		if (playerOneRunPlayerNumber == activePlayer) {
			cout << players[activePlayer].cardNamesToString() << endl;
			cout << players[activePlayer].name << ", which cards would you like to submit? (seperate with ',')" << endl;
			cin >> cardsToSubmit;
		}
		else {
			cout <<"-----"<< players[activePlayer].cardNamesToString() << endl; // Shows bots hand
			string tokens[4] = { "" };
			int submitTokensCount = 0;
			stringstream ss;

			//randomizes cards to submit
			//1. If I have the cards put them down.
			//2. If I put less than 3 cards down roll to see if I should add more
			//3. If i put no cards down, roll once automatically, then go back to 2.
			for (int i = 0; i < players[activePlayer].cardCount; i++) {
				if (players[activePlayer].cards[i].value == activeCardNumber) {
					tokens[submitTokensCount++] = players[activePlayer].cards[i].name;
				}
			}
			switch (submitTokensCount) {
			case 3:
				break;
			case 2:
				break;
			case 1:
			case 0:
				for (int i = submitTokensCount; i < 4 && i < players[activePlayer].cardCount; i++) {
					const int ROLL_CHANCE_OF_ADDING_EXTRA_CARDS = 15; // out of 100
					if (submitTokensCount == 0 || (rand()%100)<ROLL_CHANCE_OF_ADDING_EXTRA_CARDS) { // This is a roll for putting something in or not.
						int randomCardNumber = rand() % players[activePlayer].cardCount;
						if (players[activePlayer].cards[randomCardNumber].name != tokens[0]) {
							tokens[submitTokensCount++] = players[activePlayer].cards[randomCardNumber].name;
						}
					}
				}
			}
			//pastes the  token to the string stream
			for (int i = 0; i < submitTokensCount; i++) {
				ss << tokens[i];
				if ((i + 1) < submitTokensCount) {
					ss << ",";
				}
			}

			//end randomizations
			cardsToSubmit = ss.str();
			cout << "-----Bot is submitting: '" << cardsToSubmit << "'" << endl;
		}
	}
	else { //UNIVERSAL CONTROL of PLAYERS
		cout << players[activePlayer].cardNamesToString() << endl;
		cout << players[activePlayer].name << ", which cards would you like to submit? (seperate with ',')" << endl;
		cin >> cardsToSubmit;
	}


	while (!processingSubmitCards(activeCardNumber, players[activePlayer], cardsToSubmit)) {
		cout << "Your input was not accepted, try again." << endl;
		cin >> cardsToSubmit;
	}
}

bool DKATGame::processingSubmitCards(int numberActivated, Player &player, string cardsToSubmit) {
	//cout << "Submitting card: " << cardsToSubmit << endl;
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

	cout << player.name << " submitted " << numberOfCardsSubmitted << " card(s)!" << endl;
	return true;
}

void DKATGame::playerResponses(int activeCardNumber, int activePlayer) {
	bool aPlayerChallenged = false;
	for (int i = 0; i < playerNumber && (!aPlayerChallenged); i++) {
		if (activePlayer != i) { // only the other players to respond
			while (!onePlayerRun || (playerOneRunPlayerNumber != activePlayer&&playerOneRunPlayerNumber==i)) { //Will run if one player mode is off, or...
				cout << "--------------------------------------------Player " << i << " do you think they are bluffing? ('y' or 'n')" << endl;
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
			//Here is where bot uses logic to deduce if the player is bluffing or not.
			if (onePlayerRun&&(playerOneRunPlayerNumber==activePlayer||playerOneRunPlayerNumber != i)) {
				
				if (shouldTheBotChallenge(activeCardNumber,activePlayer,i)) {
					cout << i << ". " << players[i].name << " thinks " << players[activePlayer].name << " is bluffing." << endl;
					challengePlayer(activeCardNumber, activePlayer, i);
					aPlayerChallenged = true;
				}
				else {
					cout <<i<<". "<< players[i].name << " doesn't think " << players[activePlayer].name << " is bluffing." << endl;
				}

			}

		}
	}
}

bool DKATGame::shouldTheBotChallenge(int activeCardNumber, int activePlayer,int botNumber ) {
	int numberOfActiveCardsInBotsHand = 0;

	int randomNumber = rand() % 400;

	//cout << "\n\n\n" << players[botNumber].findAmountOfValueInHand(activeCardNumber) + lastNumberOfCardsSubmitted * 25 << ">=" << randomNumber << "\n\n\n\n"; // prints out roll chance

	//The bot will call if they have enough of the card in their hand to know for certain.
	if (players[botNumber].findAmountOfValueInHand(activeCardNumber)+lastNumberOfCardsSubmitted>4) {
		//cout << "player " << botNumber << " is challengeing because he has " << players[botNumber].findAmountOfValueInHand(activeCardNumber) << " " << activeCardNumber << "s" << endl;
		return true;
	}
	else if ((players[botNumber].findAmountOfValueInHand(activeCardNumber) + lastNumberOfCardsSubmitted)*25>=(randomNumber)) {//the larger rand()%aaa is the less likely a pot will call
		return true;
	}

	return false;
}

bool DKATGame::challengePlayer(int activeCardNumber, int activePlayer, int challengingPlayer) {
	for (int i = 0; i < lastNumberOfCardsSubmitted; i++) {
		cout << "Comparing active card number " << activeCardNumber << " to previous card accepted " << Card::ALLCARDS->findCardValue(lastCardsSubmitted[i]) << endl;
		if (Card::ALLCARDS->findCardValue(lastCardsSubmitted[i]) != activeCardNumber) {
			cout << "---===A card failed to match!===---" << endl;
			cout << players[activePlayer].name << " added all " << cardPile.cardCount << " from the pile to their hand!" << endl;
			cardPile.givePileToPlayer(players[activePlayer]);
			return true;
		}
	}
	//If it gets here then the active player played ALL acceptable cards
	cout << "---===ALL CARDS MATCHED!===---" << endl;
	cout << players[challengingPlayer].name << " added all " << cardPile.cardCount << " from the pile to their hand!" << endl;
	cardPile.givePileToPlayer(players[challengingPlayer]);
	return false;
}

