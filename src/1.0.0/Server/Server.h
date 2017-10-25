#pragma once
#define _WINSOCK_DEPRCAED_NO_WARNINGS
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

//#include "DKATGame.h"

using namespace std;

enum Packet {
	P_ChatMessage, P_NameRequest, P_SendCards, P_SendNames, P_SendCardAmounts, P_SendPileCount, P_SendActiveCardValue, P_SendActivatePlayer, P_CardsSubmition, 
	P_YesNoResponse // sends a requests to respond to client, also used to receive a response from client
};

class Server {
public:
	Server(int port, bool broadcastPublicly = false);

	//DKATGame *game;
	//void attachGame(DKATGame &_game);

	static void startFetchingConnections();
	static void fetchConnectionsThread();
	static bool listenForNewConnection();

	static bool sendPacketType(int ID, Packet _packetType);
	static bool sendPacketTypeToAll(Packet _packetType);
	static bool sendChatString(int ID, string &_string);
	static void sendChatStringToAll(string &_string);

	static void updateGame();

	static bool sendCardAmountsToAll();
	static bool sendCardsToAll();
	static bool sendNamesToPlayersAll();

	static bool sendCardPileAmount(int ID);
	static bool sendCardPileAmountToAll();

	static bool sendActiveCardValue(int ID);
	static bool sendActiveCardValueToAll();

	static bool sendActivationAndPush(int ID);
	static bool sendResponseNotification(int ID, int activePlayerID, int numberOfCardsSubmitted);

public:
	static bool sendInt(int ID, int _int);
	static bool getInt(int ID, int &_int);

	static bool getPacketType(int ID, Packet &_packetType);

	static bool getString(int ID, string &_string);

	static bool processPacket(int ID, Packet packetType);
	static void clientHandlerThread(int ID);




public:
	static volatile bool gameStart;
	static const int MAX_CONNECTIONS;
	static int totalConnections;

	static volatile int setListenID;
	static string stringResponse;

	static bool sendCardAmounts(int ID);
	static bool sendCards(int ID);
	static bool sendNamesToPlayer(int ID);


private:
	static SOCKET listenSocket;
	static SOCKET clientSockets[];


	// MULTIPLE
	SOCKADDR_IN addr; // address the listen socket will be binded to.
	int addrLength = sizeof(addr); // length of addr - required for accept call
};