#include "CardPile.h"

CardPile::CardPile() :cards{ 0 } {

}

/**
* Returns the cards currently in the pile in a string
*/
string CardPile::cardsNumbersToString() {
	stringstream ss;
	ss << "Card Pile: ";
	for (int i = 0; i < cardCount; i++) {
		ss << cards[i].ID << " ";
	}
	return ss.str();
}

string CardPile::cardsNamesToString() {
	stringstream ss;
	ss << "Card Pile: ";
	for (int i = 0; i < cardCount; i++) {
		ss << cards[i].name<< " ";
	}
	return ss.str();
}