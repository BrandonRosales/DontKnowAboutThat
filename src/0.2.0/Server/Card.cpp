#include "card.h"
Card::Card() {


}
Card::Card(int cardNumber):ID(cardNumber),value(0),name(""),suit(SUITS::NONE) {

}

//Necessary for static variables to compile
Card Card::ALLCARDS[52] = { 0 };

int Card::findCardValue(string cardName) {
	for (int i = 0; i < 52; i++) {
		if (cardName==ALLCARDS[i].name) {
			//cout << "Card name: " << cardName << " was found at index "<<i<<" which's card ID is: "<<ALLCARDS[i].ID<<" the value is: "<<ALLCARDS[i].numberValue<< endl;
			return ALLCARDS[i].value;
		}
	}

	return -1;
}

int Card::findCardID(string cardName) {
	for (int i = 0; i < 52; i++) {
		if (cardName == ALLCARDS[i].name) {
			//cout << "Card name: " << cardName << " was found at index " << i << " which's card ID is: " << ALLCARDS[i].ID << " the value is: " << ALLCARDS[i].numberValue << endl;
			return ALLCARDS[i].ID;
		}
	}

	return -1;
}

void Card::buildCards() {	
	
	//Sets Card Number
	for (int i = 0; i < 52; i++) {
		ALLCARDS[i].ID = i;
	}



	 
	//Sets Card Value
	for (int i = 0; i < 52; i++) {
		switch ((i+1) % 13) {//The +1 displaces the 0 index
		case 1:
			ALLCARDS[i].value = 1;
			ALLCARDS[i].name += "A";
			break;
		case 2:
			ALLCARDS[i].value = 2;
			ALLCARDS[i].name += "2";
			break;
		case 3:
			ALLCARDS[i].value = 3;
			ALLCARDS[i].name += "3";
			break;
		case 4:
			ALLCARDS[i].value = 4;
			ALLCARDS[i].name += "4";
			break;
		case 5:
			ALLCARDS[i].value = 5;
			ALLCARDS[i].name += "5";
			break;
		case 6:
			ALLCARDS[i].value = 6;
			ALLCARDS[i].name += "6";
			break;
		case 7:
			ALLCARDS[i].value = 7;
			ALLCARDS[i].name += "7";
			break;
		case 8:
			ALLCARDS[i].value = 8;
			ALLCARDS[i].name += "8";
			break;
		case 9:
			ALLCARDS[i].value = 9;
			ALLCARDS[i].name += "9";
			break;
		case 10:
			ALLCARDS[i].value = 10;
			ALLCARDS[i].name += "10";
			break;
		case 11:
			ALLCARDS[i].value = 11;
			ALLCARDS[i].name += "J";
			break;
		case 12:
			ALLCARDS[i].value = 12;
			ALLCARDS[i].name += "Q";
			break;
		case 0:
			ALLCARDS[i].value = 13;
			ALLCARDS[i].name += "K";
			break;
		}
	}

	// Set Suits 
	for (int i = 0; i < 13; i++) {
		ALLCARDS[i].suit = CLUB;
		ALLCARDS[i].name += "C";
	}
	for (int i = 13; i < 26; i++) {
		ALLCARDS[i].suit = DIAMOND;
		ALLCARDS[i].name += "D";
	}
	for (int i = 26; i < 39; i++) {
		ALLCARDS[i].suit = HEART;
		ALLCARDS[i].name += "H";
	}
	for (int i = 39; i < 52; i++) {
		ALLCARDS[i].suit = SPADE;
		ALLCARDS[i].name += "S";
	}
	
	////Prints information of every card
	//for (int i = 0; i < 52; i++) {
	//	switch (ALLCARDS[i].suit) {
	//	case CLUB:
	//		cout << "i#" << i << " Card " << ALLCARDS[i].cardNumber << " value is : " << ALLCARDS[i].numberValue << " - Suit: CLUB - Name: " << ALLCARDS[i].name << endl;
	//		break;
	//	case DIAMOND:
	//		cout << "i#" << i << " Card " << ALLCARDS[i].cardNumber << " value is : " << ALLCARDS[i].numberValue << " - Suit: DIAMOND - Name: " << ALLCARDS[i].name << endl;
	//		break;
	//	case HEART:
	//		cout << "i#" << i << " Card " << ALLCARDS[i].cardNumber << " value is : " << ALLCARDS[i].numberValue << " - Suit: HEART - Name: " << ALLCARDS[i].name << endl;
	//		break;
	//	case SPADE:
	//		cout << "i#" << i << " Card " << ALLCARDS[i].cardNumber << " value is : " << ALLCARDS[i].numberValue << " - Suit: SPADE - Name: " << ALLCARDS[i].name << endl;
	//		break;
	//	}
	//}

}

