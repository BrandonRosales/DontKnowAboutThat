#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Dealer.h"
#include "DKATGame.h"


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


enum Packet {
	P_ChatMessage, P_IDKATGame
};

class Client {
public:
	Client(string IP, int port);
	static bool connectToServer();
	static bool closeConnection();
	bool sendString(string &_string);
private:
	static bool processPacket(Packet _packetType);
	static void clientThread();

	//Send Functions
	static bool sendInt(int _int);
	static bool sendPacketType(Packet _packetType);

	//Getting Functions
	static bool getInt(int &_int);
	static bool getPacketType(Packet &_packetType);
	static bool getString(string &_string);

private:
	static SOCKET connection; // the clents connection to the server
	static SOCKADDR_IN addr; // address to be binded to our Connection socket
	static int sizeOFAddr; // needed for connect function
};

static Client *clientptr;