#pragma once
#include "stdafx.h"
#include "resource.h"

//MOVED OUT OF GLOBAL VARIABLES
static HWND hWnd;
static HINSTANCE hInst;
INT_PTR CALLBACK userNameDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam); // user made
INT_PTR CALLBACK serverAddress(HWND, UINT, WPARAM, LPARAM);

bool processCardsReceived(string _cards);
bool setNames(string *_playerNames,int _numberOfPlayers);
string getName(int ID);

int getTotalAmountOfPlayers();
bool setNumberOfCardsAPlayerHas(int ID, int value);
bool setCardPileCount(int value);
bool setActiveCardValue(string value);
string getActiveCardValue();