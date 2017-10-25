#include "Server.h"
#include "DKATGame.h"

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

bool Server::sendPacketTypeToAll(Packet _packetType) {
	for (int i = 0; i < totalConnections; i++) {
		sendPacketType(i, _packetType);
	}
	return true;
}

bool Server::getPacketType(int ID, Packet &_packetType) {
	int RetnCheck = recv(clientSockets[ID], (char*)&_packetType, sizeof(Packet), NULL); // receives the packet of data to be - gets Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to receive due to connection issues
		cout << "3" << endl;
		return false; // return false if we did not get packettype.
	}
	return true; // return true if we got the packettype

}

bool Server::sendChatString(int ID, string &_string) {
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

void Server::sendChatStringToAll(string &_string) {
	for (int i = 0; i < totalConnections; i++) {
		sendChatString(i, _string);
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

bool Server::sendCards(int ID) {
	if (!sendPacketType(ID, P_SendCards)) {//sends packet type: Chat Message, if 
		cout << "12" << endl;
		return false; // return false if could not send packet
	}
	string _string = DKATGame::players[ID].cardNamesToStringNoName();
	int bufferLength = _string.size(); // finds string buffer length
	if (!sendInt(ID, bufferLength)) { // sends length of string buffer 
		cout << "13" << endl;
		return false;// return false if could not send int
	}
	int RetnCheck = send(clientSockets[ID], _string.c_str(), bufferLength, NULL); // Sends the packet of data to be - sends Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to send due to connection issues
		cout << "14" << endl;
		return false; // return false if could not send string 
	}
	return true; // return true if string was sucessfully sent
}

bool Server::sendCardsToAll() {
	for (int i = 0; i < totalConnections; i++) {
		sendCards(i);
	}

	return true;
}

bool Server::sendNamesToPlayer(int ID) {
	if (!sendPacketType(ID, P_SendNames)) {//sends packet type: Chat Message, if 
		cout << "15" << endl;
		return false; // return false if could not send packet
	}

	if (!sendInt(ID, totalConnections)) { // sends the ammount of Players to send
		cout << "16" << endl;
		return false;// return false if could not send int
	}

	for (int i = 0; i < totalConnections; i++) { // sends seperate strings of each players name seperately

		string _string = DKATGame::players[i].name;
		int bufferLength = _string.size(); // finds string buffer length
		if (!sendInt(ID, bufferLength)) { // sends length of string buffer 
			cout << "17" << endl;
			return false;// return false if could not send int
		}
		int RetnCheck = send(clientSockets[ID], _string.c_str(), bufferLength, NULL); // Sends the packet of data to be - sends Packet: _packetType
		if (RetnCheck == SOCKET_ERROR) { // if packet failed to send due to connection issues
			cout << "18" << endl;
			return false; // return false if could not send string 
		}

	}

	return true; // return true if strings was sucessfully sent
}

bool Server::sendNamesToPlayersAll() {
	for (int i = 0; i < totalConnections; i++) {
		sendNamesToPlayer(i);
	}
	return true;
}

bool Server::sendCardAmounts(int ID) {
	if (!sendPacketType(ID, P_SendCardAmounts)) {//sends packet type: numbers on cards for that player
		cout << "19" << endl;
		return false; // return false if could not send packet
	}
	for (int i = 0; i < totalConnections; i++) {  // The client should already know how many players there are
		int _int = DKATGame::players[i].cardCount;
		if (!sendInt(ID, _int)) { // sends amount of cards for that specific player 
			cout << "20" << endl;
			return false;// return false if could not send int
		}
	}
	return true;
}

bool Server::sendCardAmountsToAll() {
	for (int i = 0; i < totalConnections; i++) {
		sendCardAmounts(i);
	}
	return true;
}

bool Server::sendCardPileAmount(int ID) {
	if (!sendPacketType(ID, P_SendPileCount)) {//sends packet type: Chat Message, if 
		cout << "21" << endl;
		return false; // return false if could not send packet
	}
	int _int = DKATGame::cardPile.cardCount;
	if (!sendInt(ID,_int)) { 
		cout << "22" << endl;
		return false; // return false if could not send packet
	}
}

bool Server::sendCardPileAmountToAll() {
	for (int i = 0; i < totalConnections; i++) {
		sendCardPileAmount(i);
	}
	return true;
}

bool Server::sendActiveCardValue(int ID) {
	if (!sendPacketType(ID, P_SendActiveCardValue)) {//sends packet type: activecardValue
		cout << "23" << endl;
		return false; // return false if could not send packet
	}
	string _string = DKATGame::activeCardValue;
	int bufferLength = _string.size(); // finds string buffer length
	if (!sendInt(ID, bufferLength)) { // sends length of string buffer 
		cout << "24" << endl;
		return false;// return false if could not send int
	}
	int RetnCheck = send(clientSockets[ID], _string.c_str(), bufferLength, NULL); // Sends the packet of data to be - sends Packet: _packetType
	if (RetnCheck == SOCKET_ERROR) { // if packet failed to send due to connection issues
		cout << "25" << endl;
		return false; // return false if could not send string 
	}


	return true;
}

bool Server::sendActiveCardValueToAll() {
	for (int i = 0; i < totalConnections; i++) {
		sendActiveCardValue(i);
	}
	return true;
}

bool Server::sendActivationAndPush(int ID) {
	sendPacketType(ID, P_SendActivatePlayer);
	return true;
}

bool Server::sendResponseNotification(int ID, int activePlayerID, int numberOfCardsSubmitted) {
	sendPacketType(ID, P_YesNoResponse);
	if (!sendInt(ID, activePlayerID)) {
		cout << "26" << endl;
		return false; // return false if could not send packet
	}
	if (!sendInt(ID, numberOfCardsSubmitted)) {//sends packet type:  
		cout << "27" << endl;
		return false; // return false if could not send packet
	}
}