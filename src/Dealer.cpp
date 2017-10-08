/*
 * Dealer.cpp
 *
 *  Created on: Oct 7, 2017
 *      Author: Brandon Rosales
 */

#include "Dealer.h"
#include <iostream>
using namespace std;

/**
 * Method retrieves and returns the ammount of players for the game.
 */
int Dealer::introduction() {
	cout << "Welcome to my table!" << endl
			<< "How many players would you like to play BullCrap with?" << endl;
	int numberOfPlayers;

	cin>>numberOfPlayers;

	return numberOfPlayers;

}

