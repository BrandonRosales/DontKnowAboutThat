#include "Server.h"
#include "DKATGame.h"

int __cdecl main(void)
{
	Card::buildCards(); // Builds the playing cards
	
	Server myServer(2222, true);

	myServer.startFetchingConnections();

	//Master Commander here.
	string command;
	while (true) {
		cout << "Type 'start' to stop players from joining and begin the game." << endl;
		cin >> command;

		if (command == "start") {
			myServer.gameStart = true;
			cout << "We are no longer searching for connections." << endl;


			DKATGame game(myServer.totalConnections,myServer);

			break;
		}

	}


	WSACleanup;
	system("pause");
	return 0;
}