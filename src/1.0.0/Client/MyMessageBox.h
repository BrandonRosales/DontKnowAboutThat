#pragma once
#include "stdafx.h"
#include <string>

class MyMessageBox {
public:
	static const int QUEUE_SIZE = 13;
	void add(std::string _message);
	std::string getMessage(int index);
	int getMessageCount();
private:
	int messageCount = 0;
	std::string queue[QUEUE_SIZE];
};