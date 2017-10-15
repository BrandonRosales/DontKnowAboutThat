#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Client.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

	SOCKET Client::connection = INVALID_SOCKET; // moved from client.h
	SOCKADDR_IN Client::addr;
	int Client::sizeOFAddr = sizeof(addr); // moved from client.h

Client::Client(string IP, int port) {

	// Initialize Winsock

	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) {// Also check compatibility
		MessageBoxA(NULL, "Winsocket startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr(IP.c_str()); // puts the ipadress in from the constructor
	addr.sin_port = htons(port); // puts in the port number entered from the constructor
	addr.sin_family = AF_INET;//This is the IP family so, ONLY ACCEPTS IPv4
	clientptr = this;
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
		cout << message << endl;
		break;
	}
	case P_IDKATGame:
		cout << "IDKATGame packet received." << endl;
		break;
	default:
		cout << "Unrecognized Packet" << packetType << endl;
		break;
	}
	return true;
}

bool Client::closeConnection() {
	if (closesocket(connection) == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAENOTSOCK) { //If is already closed
			return true; // since socket was already closed
		}
	string errorMessage = "Failed to closed the socket.  Winsock Error: " + to_string(WSAGetLastError())+".";
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
	cout << "Lost connection to the server" << endl;

	if (closeConnection()) {
		cout << "Socket to the server was closed successfully" << endl;
	}
	else {
		cout << "Socket was not able to be closed" << endl;
	}

}