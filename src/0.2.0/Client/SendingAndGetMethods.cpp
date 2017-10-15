#include "Client.h"

bool Client::sendInt(int _int) {
	int RetnCheck = send(connection, (char*)&_int, sizeof(int), NULL); // send the packet of expected data to be - send int: _int
	if (RetnCheck == SOCKET_ERROR) { // if int failed to send due to connection issues
		return false; // connection issues
	}
	return true; // sucessfully sent

}

bool Client::getInt(int &_int) {
	int RetnCheck = recv(connection, (char*)&_int, sizeof(int), NULL); // receive int
	if (RetnCheck == SOCKET_ERROR) { // if int failed to receive due to connection issues
		return false; // return false if we did not get int.
	}
	return true; // return true if we got the int

}

bool Client::sendPacketType(Packet _packetType) {
	int RetnCheck = send(connection, (char*)&_packetType, sizeof(Packet), NULL); // Sends the packet of data to be - sends Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to send due to connection issues
		return false; // return false if could not send packet
	}
	return true; // return true if we sent the packet

}

bool Client::getPacketType(Packet &_packetType) {
	int RetnCheck = recv(connection, (char*)&_packetType, sizeof(Packet), NULL); // receives the packet of data to be - gets Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to receive due to connection issues
		return false; // return false if we did not get packettype.
	}
	return true; // return true if we got the packettype
}

bool Client::sendString(string &_string) {
	if (!sendPacketType(P_ChatMessage)) {//sends packet type: Chat Message, if 
		return false; // return false if could not send packet
	}
	int bufferLength = _string.size(); // finds string buffer length
	if (!sendInt(bufferLength)) { // sends length of string buffer 
		return false;// return false if could not send int
	}
	int RetnCheck = send(connection, _string.c_str(), bufferLength, NULL); // Sends the packet of data to be - sends Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to send due to connection issues
		return false; // return false if could not send string 
	}
	return true; // return true if string was sucessfully sent
}

bool Client::getString(string &_string) {
	int bufferLength = _string.size(); // Holds buffer length
	if (!getInt(bufferLength)) {//get length of buffer and stroe it in variable
		return false; // return false if int wasnt received
	}
	char * buffer = new char[bufferLength + 1]; // Allocates buffer
	buffer[bufferLength] = '\0';//sets last character to null terminator, so we don't print junk
	int RetnCheck = recv(connection, buffer, bufferLength, NULL); // receives the message
	_string = buffer;
	delete[] buffer;
	if (RetnCheck == SOCKET_ERROR) { // if string failed to get due to connection issues
		return false; // return false if could not get string 
	}
	return true; // return true if string was sucessfully received
}