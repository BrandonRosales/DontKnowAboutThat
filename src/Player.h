/*
 * Player.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Brandon Rosales
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include <iostream>

using namespace std;

class Player {
public:
	Player();
	string name;
	int cards[52] = {0};
	int cardCoubt = 0;
};

#endif /* SRC_PLAYER_H_ */
