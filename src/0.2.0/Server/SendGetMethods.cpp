#include "Server.h"

bool Server::sendInt(int ID, int _int) {
	int RetnCheck = send(clientSockets[ID], (char*)&_int, sizeof(int), NULL); // send the packet of expected data to be - send int: _int
	if (RetnCheck == SOCKET_ERROR) { // if int failed to send due to connection issues
		cout << "0" << endl;
		return false; // connection issues
	}

	return true; // sucessfully sent

}

bool Server::getInt(int ID, int &_int) {
	int RetnCheck = recv(clientSockets[ID], (char*)&_int, sizeof(int), NULL); // receive int
	if (RetnCheck == SOCKET_ERROR) { // if int failed to receive due to connection issues
		cout << "1" << endl;
		return false; // return false if we did not get int.
	}

	return true; // return true if we got the int

}

bool Server::sendPacketType(int ID, Packet _packetType) {
	int RetnCheck = send(clientSockets[ID], (char*)&_packetType, sizeof(Packet), NULL); // Sends the packet of data to be - sends Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to send due to connection issues
		cout << "2" << endl;
		return false; // return false if could not send packet
	}
	return true; // return true if we sent the packet
}

bool Server::getPacketType(int ID, Packet &_packetType) {
	int RetnCheck = recv(clientSockets[ID], (char*)&_packetType, sizeof(Packet), NULL); // receives the packet of data to be - gets Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to receive due to connection issues
		cout << "3" << endl;
		return false; // return false if we did not get packettype.
	}
	return true; // return true if we got the packettype

}

bool Server::sendString(int ID, string &_string) {
	if (!sendPacketType(ID, P_ChatMessage)) {//sends packet type: Chat Message, if 
		cout << "4" << endl;
		return false; // return false if could not send packet
	}
	int bufferLength = _string.size(); // finds string buffer length
	if (!sendInt(ID, bufferLength)) { // sends length of string buffer 
		cout << "5" << endl;
		return false;// return false if could not send int
	}
	int RetnCheck = send(clientSockets[ID], _string.c_str(), bufferLength, NULL); // Sends the packet of data to be - sends Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to send due to connection issues
		cout << "6" << endl;
		return false; // return false if could not send string 
	}
	return true; // return true if string was sucessfully sent
}

void Server::sendStringToAll(string &_string) {
	for (int i = 0; i < totalConnections;i++) {
		sendString(i,_string);
	}
}

bool Server::getString(int ID, string &_string) {
	int bufferLength = _string.size(); // Holds buffer length
	if (!getInt(ID, bufferLength)) {//get length of buffer and stroe it in variable
		cout << "7" << endl;
		return false; // return false if int wasnt received
	}
	char * buffer = new char[bufferLength + 1]; // Allocates buffer
	buffer[bufferLength] = '\0';//sets last character to null terminator, so we don't print junk
	int RetnCheck = recv(clientSockets[ID], buffer, bufferLength, NULL); // receives the message
	_string = buffer;
	delete[] buffer;
	if (RetnCheck == SOCKET_ERROR) { // if string failed to get due to connection issues
		cout << "8" << endl;
		return false; // return false if could not get string 
	}
	return true; // return true if string was sucessfully received
}