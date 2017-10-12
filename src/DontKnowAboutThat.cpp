#include <iostream>
#include "Dealer.h"
#include "DKATGame.h"
using namespace std;

int main() {
	Card::buildCards(); // Builds the playing cards

	Dealer dealer;

	DKATGame game(dealer.introduction());

	system("pause");
	return 0;
}
