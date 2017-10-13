#ifndef SRC_CARDPILE_H_
#define SRC_CARDPILE_H_
#include <iostream>
#include <sstream>
#include "Card.h"
#include "Player.h"
using namespace std;

class CardPile {
public:
	CardPile();
	Card cards[52];
	int cardCount = 0;
	void givePileToPlayer(Player &player);
	void empty();
	string CardPile::cardsNumbersToString();
	string CardPile::cardsNamesToString();

};

#endif /* SRC_CARDPILE_H_ */