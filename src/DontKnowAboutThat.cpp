#include <iostream>
#include "Dealer.h"
#include "DKATGame.h"
using namespace std;

int main() {
	Dealer dealer;

	DKATGame game(dealer.introduction());

	return 0;
}