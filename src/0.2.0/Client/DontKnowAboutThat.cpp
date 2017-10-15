#include "Client.h"

int __cdecl main() {

	Client myClient("127.0.0.1",2222); //Creates a connection to my laptop on the local network
	if (!myClient.connectToServer()) {//if the connection fails
		cout << "Failed to connect to server" << endl;
		system("pause");
		return 1;
	}

	// sending until disconected
	string userInput; //string buffer to send
	while (true) {
		cout <<">" ;
		std::getline(std::cin, userInput);//gets the console line when the user presses enter
		if (!myClient.sendString(userInput)) {//sends the string userInput, if it fails to send, we will break.
			break; // if we failed to send a string, leaves loop because connection to server was lost.qw
		}
		Sleep(10);
	}

	// cleanup
	WSACleanup();

	system("pause");
	return 0;
}


/////Orignial command prompt start
//int main() {
//	Card::buildCards(); // Builds the playing cards
//
//	Dealer dealer;
//
//	DKATGame game(dealer.introduction());
//
//	system("pause");
//	return 0;
//}
