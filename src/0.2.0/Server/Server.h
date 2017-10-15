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

using namespace std;

enum Packet {
	P_ChatMessage, P_IDKATGame
};

class Server {
public:
	Server(int port, bool broadcastPublicly = false);
	static void startFetchingConnections();
	static void fetchConnectionsThread();
	static bool listenForNewConnection();

	static bool sendPacketType(int ID, Packet _packetType);
	static bool sendString(int ID, string &_string);
	static void sendStringToAll(string &_string);

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
private:
	static SOCKET listenSocket;
	static SOCKET clientSockets[];


	// MULTIPLE
	SOCKADDR_IN addr; // address the listen socket will be binded to.
	int addrLength = sizeof(addr); // length of addr - required for accept call
};