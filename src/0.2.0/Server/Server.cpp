# include "Server.h"

const int Server::MAX_CONNECTIONS = 8;
bool volatile Server::gameStart = false;
int Server::totalConnections = 0;
SOCKET Server::listenSocket = INVALID_SOCKET;
SOCKET Server::clientSockets[MAX_CONNECTIONS] = { INVALID_SOCKET };

int volatile Server::setListenID = -1;
string Server::stringResponse = "";

Server::Server(int port, bool broadcastPublicly) { //port to broadcast on and if you want to broadcast publicly

	// Initialize Winsock
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		MessageBoxA(NULL, "WinSock startup failed.", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	if (broadcastPublicly) {//if server is public
		addr.sin_addr.s_addr = htonl(INADDR_ANY); //Converts from host to network byte order - converts a long //inadd_any = 0
	}
	else {
		InetPton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr); // this uses the non depricated version to conver the string to IPV4 value
	}
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	listenSocket = socket(AF_INET, SOCK_STREAM, NULL);	// Create a SOCKET to listen on


	if ((bind(listenSocket, (SOCKADDR*)&addr, sizeof(addr))) == SOCKET_ERROR) { // Binds the address to the socket.
		string errorMessage = "Failed to bind the address to the listening socket.  Error: " + to_string(WSAGetLastError());
		MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) { // places the socket in a state which is listening for a connection
		string errorMessage = "Failed to listen on listening socket.  Error: " + to_string(WSAGetLastError());
		MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}


	//serverptr=this;
}

bool Server::listenForNewConnection() {

	SOCKET newConnection;

	newConnection = accept(listenSocket, NULL, NULL);
	if (newConnection == INVALID_SOCKET) {
		cout << "Failed to accept connection with error:" << WSAGetLastError();
		return false;
	}
	else { //if client is properly accepted

		if (gameStart) {
			closesocket(newConnection);
			return false;
		}
		cout << "The Client Connected!" << endl;
		clientSockets[totalConnections] = newConnection;

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientHandlerThread, (LPVOID)(totalConnections), NULL, NULL); // Creates thread to receive input from every client.
		totalConnections++;
		return true;
	}

}


bool Server::processPacket(int ID, Packet packetType) {
	switch (packetType) {
	case P_ChatMessage:
	{
		string message;
		if (!getString(ID, message)) { //string to be stored in message
			cout << "9" << endl;
			return false; // if we did not properly get the string
		}
		if (ID != setListenID) {
			for (int i = 0; i < totalConnections; i++) {
				if (i == ID) {//If connection is the person sending the message.
					continue;//Skips to the next player in the room
				}
				if (!sendString(i, message)) {
					cout << "Failed to send message from client ID: " << ID << " to ID: " << i << endl;
				}
			}
		}
		else {
			stringResponse = message;
			setListenID = -1; // sets the listen id back to -1
		}
		cout << "Processed chat message from user ID: " << ID << " message is: " << message << endl;
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

void Server::clientHandlerThread(int ID) {
	Packet packetType;
	// Receive from client until the peer shuts down the connection
	while (true) {
		if (!getPacketType(ID, packetType)) { //getsPacketType
			break;//if there is a problem getting the packet type break
		}
		if (!processPacket(ID, packetType)) { //if the packet is not processed properly
			break; //break out of client handler if packets made no sense.
		}
	}
	cout << "Lost connection to client ID number: " << ID << endl;
	closesocket(clientSockets[ID]);
}

void Server::startFetchingConnections() {
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)fetchConnectionsThread, NULL, NULL, NULL); // Creates thread to receive input from every client.
}

void Server::fetchConnectionsThread() {
	cout << "\nWe are now searching for connections..." << endl;
	for (int i = 0; i < MAX_CONNECTIONS && !gameStart; i++) { // up to max times
		listenForNewConnection(); // accepts new connection if someone tries to connectS
	}
}