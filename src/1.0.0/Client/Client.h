#pragma once

#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "MyMessageBox.h"

using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


enum Packet {
	P_ChatMessage,  P_NameRequest, P_SendCards, P_SendNames, P_SendCardAmounts, P_SendPileCount, P_SendActiveCardValue, P_SendActivatePlayer, P_CardsSubmition, P_YesNoResponse
};

class Client {
public:
	Client(string IP, int port);
	static bool connectToServer();
	static bool closeConnection();
	bool sendChatString(string &_string);
	bool sendPlayerName(string _string);
	bool sendCardsSubmition(string &_string);
	static MyMessageBox messageBox;

	static bool isConnected;
	static bool myTurn;
private:
	static bool processPacket(Packet _packetType);
	static void clientThread();

	//Send Functions
	static bool sendInt(int _int);
	static bool sendPacketType(Packet _packetType);
	static bool sendYesNoResponse(string &_string);

	//Getting Functions
	static bool getInt(int &_int);
	static bool getPacketType(Packet &_packetType);
	static bool getString(string &_string);

private:
	static SOCKET connection; // the clents connection to the server
	static SOCKADDR_IN addr; // address to be binded to our Connection socket
	static int sizeOFAddr; // needed for connect function
};

