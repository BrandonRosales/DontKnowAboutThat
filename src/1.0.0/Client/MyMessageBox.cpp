#include "stdafx.h"
#include "MyMessageBox.h"

void MyMessageBox::add(std::string message) {
	if (messageCount == QUEUE_SIZE) {
		for (int i = 0; i < messageCount; i++) {
			queue[i] = queue[i + 1];
			if (i + 1 == messageCount) {
				break;
			}
		}
		queue[messageCount-1] = message;
	}
	else {
		queue[messageCount++] = message;
	}
}

std::string MyMessageBox::getMessage(int index) {
	return queue[index];
}

int MyMessageBox::getMessageCount() {
	return messageCount;
}