#ifndef SRC_CARD_H_
#define SRC_CARD_H_
#include <iostream>
#include <sstream>
using namespace std;

enum SUITS {
	CLUB, DIAMOND, HEART, SPADE,NONE
};

class Card {
public:
	Card();
	Card(int number);
	int ID;
	SUITS suit;
	int value;
	string name;

	static Card ALLCARDS[52];

	int findCardValue(string cardName);

	int findCardID(string cardName);

	static void buildCards();



};



#endif /* SRC_CARD_H_ */
