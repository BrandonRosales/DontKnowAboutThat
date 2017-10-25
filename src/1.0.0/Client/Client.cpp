#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include "Client.h"

#include "DontKnowAboutThat.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

SOCKET Client::connection = INVALID_SOCKET; // moved from client.h
SOCKADDR_IN Client::addr;
int Client::sizeOFAddr = sizeof(addr); // moved from client.h
bool Client::myTurn = false;
bool Client::isConnected = false;
MyMessageBox Client::messageBox;
Client::Client(string IP, int port) {

	// Initialize Winsock

	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) {// Also check compatibility
		MessageBoxA(NULL, "Winsocket startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	InetPtonA(AF_INET, IP.c_str(), &addr.sin_addr.s_addr); // this uses the non depricated version to conver the string to IPV4 valu

	addr.sin_port = htons(port); // puts in the port number entered from the constructor
	addr.sin_family = AF_INET;//This is the IP family so, ONLY ACCEPTS IPv4
}

bool Client::connectToServer() {
	// Attempt to connect to an address until one succeeds

		// Create a SOCKET for connecting to server
	connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connection, (SOCKADDR*)&addr, sizeOFAddr) != 0) {
		MessageBoxA(NULL, "Failed to connect to server!", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//////////////////////////// CONNECTED//////////////////////
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientThread, NULL, NULL, NULL); // Creates thread to receive input from every client.

	return true;
}

bool Client::processPacket(Packet packetType) {
	switch (packetType) {
	case P_ChatMessage:
	{
		string message;
		if (!getString(message)) { //gets the chat message and stores on message
			return false; // fails if message wasn't received
		}
		
		messageBox.add(message); // pushes this to the queue!
		cout << message << endl;
		InvalidateRect(hWnd, 0, true); // refreshes screen
		break;
	}
	case P_NameRequest: // ran once, to submit your name
	{
		DialogBox(hInst, MAKEINTRESOURCE(IDD_UserName), hWnd, userNameDialog);
		break;
	}
	case P_SendCards: // ran multiple times, to get cards in your hand
	{
		string cards;
		if (!getString(cards)) { //gets the card list and stores it locally
			return false; // fails if message wasn't received
		}
		processCardsReceived(cards); // process and renders the cards into the screen
		break;
	}
	case P_SendNames: //ran once, to receive names
	{
		int _numberOfPlayers;
		getInt(_numberOfPlayers);
		string *_playerNames = new string[_numberOfPlayers];
		for (int i = 0; i < _numberOfPlayers; i++) {
			string playerName;
			if (!getString(playerName)) { //gets the card list and stores it locally
				return false; // fails if message wasn't received
			}
			_playerNames[i] = playerName;
		}
		setNames(_playerNames, _numberOfPlayers); // sends names to the window and saves the names as well as the amount of player
		delete[]_playerNames; //deallocate space.
		break;
	}
	case P_SendCardAmounts: //ran multiple times, to receive number of cards each player has
	{
		for (int i = 0; i < getTotalAmountOfPlayers(); i++) {
			int _cardAmount;
			if (!getInt(_cardAmount)) { //gets the card list and stores it locally
				return false; // fails if message wasn't received
			}
			setNumberOfCardsAPlayerHas(i, _cardAmount);
		}
		break;
	}
	case P_SendPileCount: //ran multiple times, to receive number of cards in the pile
	{
		int _cardPileAmount;
		if (!getInt(_cardPileAmount)) { //gets the card list and stores it locally
			return false; // fails if message wasn't received
		}
		setCardPileCount(_cardPileAmount);
		break;
	}
	case P_SendActiveCardValue:
	{
		string _activeCardValue;
		if (!getString(_activeCardValue)) { //gets the card list and stores it locally
			return false; // fails if message wasn't received
		}
		setActiveCardValue(_activeCardValue);
		break;
	}
	case P_SendActivatePlayer:
	{
		Beep(523, 100);
		myTurn = true;
		InvalidateRect(hWnd, 0, true); // refreshes screen
		break;
	}
	case P_YesNoResponse:
	{
		Beep(523, 100);
		int _activePlayerID;
		int _numberOfCardsSubmitted;
		if (!getInt(_activePlayerID)) { //gets the card list and stores it locally
			return false; // fails if message wasn't received
		}
		if (!getInt(_numberOfCardsSubmitted)) { //gets the card list and stores it locally
			return false; // fails if message wasn't received
		}


		stringstream ss;
		ss << "Do you think " << getName(_activePlayerID) << " put in " << _numberOfCardsSubmitted << " " << getActiveCardValue() << "(s)?";
		const int result = MessageBoxA(NULL, ss.str().c_str(), "What do you think?", MB_YESNO);
		switch (result) {
		case IDYES:
		{
			string yes = "n";
			sendYesNoResponse(yes);
		}
		break;
		case IDNO:
		case IDCANCEL:
		{
			string no = "y";
			sendYesNoResponse(no);
		}

		break;
		}






		break;
	}
	default:
		stringstream ss;
		ss << "Unrecognized Packet: " << packetType;
		MessageBoxA(NULL, ss.str().c_str(), "Error", MB_OK | MB_ICONERROR);
		break;
	}
	return true;
}

bool Client::closeConnection() {
	if (closesocket(connection) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAENOTSOCK) { //If is already closed
			return true; // since socket was already closed
		}
		string errorMessage = "Failed to closed the socket.  Winsock Error: " + to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void Client::clientThread() {

	Packet packetType;

	while (true) {
		if (!getPacketType(packetType)) {
			break;
		}
		if (!processPacket(packetType)) { //If packet is not properly processed
			break; //break out of receiving loop
		}
	}
	MessageBoxA(NULL, "Lost connection to the server", "Error", MB_OK | MB_ICONERROR);

	if (closeConnection()) {
		//		MessageBoxA(NULL, "Socket to the server was closed successfully", "Error", MB_OK | MB_ICONERROR); //not necessary
	}
	else {
		MessageBoxA(NULL, "Socket was not able to be closed", "Error", MB_OK | MB_ICONERROR);
	}

	exit(0);
}