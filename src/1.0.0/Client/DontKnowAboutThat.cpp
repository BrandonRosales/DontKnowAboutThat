// DontKnowAboutThat.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DontKnowAboutThat.h"



#define MAX_LOADSTRING 100

// Global Variables:                              // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

bool paintWindow(HWND &hWnd);

Client myClient("127.0.0.1", 2222); //Creates a connection to my laptop on the local network

std::string cardsReceived[52] = { "" };
int numberOfCardsReceived = 0;

std::string playerNames[8] = { "Waiting","For","Server","To","Start","The","Game","!" };
int numberAllOfCardsAllPlayersHave[8] = { 4,8,15,16,23,43,0,0 };
int numberOfPlayers = 8;

int cardPileCount = 0;

std::string activeCardValue = "NA";

std::string cardsSubmitting[4]; // contains the cards you are submitting
int cardsSubmittingCount = 0;


bool clearCards();

//Handes for objects onscreen:
HWND submitButton;
//end


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_DONTKNOWABOUTTHAT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DONTKNOWABOUTTHAT));

	MSG msg;




	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DONTKNOWABOUTTHAT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DONTKNOWABOUTTHAT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:call
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 950, 650, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:// ONCREATE
	{
		submitButton = CreateWindow(L"BUTTON", L"Submit", WS_VISIBLE | WS_CHILD,
			120, 500, 60, 20,
			hWnd, (HMENU)IDB_SUBMITBUTTON, NULL, NULL);


	}
	break;
	case WM_COMMAND:// any command pressed
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_CONNECT:
			if (!myClient.isConnected) {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ServerAddress), hWnd, serverAddress);
			}
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////////
		case IDB_SUBMITBUTTON://WHAT HAPPENS WHEN SUBMIT BUTTIN IS PRESSED
			if (myClient.myTurn&&cardsSubmittingCount != 0) {
				stringstream ss;
				for (int i = 0; i < cardsSubmittingCount; i++) {
					ss << cardsSubmitting[i];
					if (i + 1 < cardsSubmittingCount) {
						ss << ",";
					}
				}
				myClient.sendCardsSubmition(ss.str()); // sends cards in to server

				for (int i = 0; i < cardsSubmittingCount; i++) { // clear the cards held in storage
					cardsSubmitting[i] = "";
				}
				cardsSubmittingCount = 0;
				myClient.myTurn = false;
				InvalidateRect(hWnd, 0, true); // refreshes screen
			}

			break;
			/////////////////////////////////////////////////////////////////////////////////////////////////////

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	//YES!
	case WM_LBUTTONDOWN:
	{
		char szFileName[MAX_PATH];
		HINSTANCE hInstance = GetModuleHandle(NULL);

		//GetModuleFileNameA(hInstance, szFileName, MAX_PATH);
		//MessageBoxA(hWnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);

		int mousePosx = LOWORD(lParam);
		int mousePosy = HIWORD(lParam);

		if (myClient.myTurn) {
			for (int i = 0, j = 0; i < numberOfCardsReceived; i++) {
				if ((i - 1) % 9 == 8) {
					j++;
				}
				if (300 + (i % 9 * 70) < mousePosx && mousePosx < 360 + (i % 9 * 70)) { // Checks x Positions
					if (20 + (90 * j) < mousePosy && mousePosy < 100 + (90 * j)) { // checks y position
						//std::stringstream ss;
						//ss << cardsReceived[i];
						//ss << " was pressed!";
						//MessageBoxA(hWnd, ss.str().c_str(), "Card Pressed!", MB_OK | MB_ICONINFORMATION);
						bool removeCard = false;
						for (int k = 0; k < cardsSubmittingCount; k++) {
							if (cardsSubmitting[k] == cardsReceived[i]) {
								for (int l = k; l < cardsSubmittingCount; l++) {
									if (l + 1 < cardsSubmittingCount) {
										cardsSubmitting[l] = cardsSubmitting[l + 1];
									}
								}
								removeCard = true;
								cardsSubmittingCount--;
							}
						}
						if (!removeCard) {
							if (cardsSubmittingCount != 4) { // stops it from going over 4
								cardsSubmitting[cardsSubmittingCount++] = cardsReceived[i]; // increments card count
							}
							else {
								MessageBoxA(hWnd, "You can not add more then 4 cards!\nIf you want to switch the cards you want to submit,\nreclick the cards you've already submitted.", "OH NO!", MB_OK);
							}
						}

						InvalidateRect(hWnd, 0, true); // refreshes screen

					}
				}
			}
		}

	}
	break;

	case WM_PAINT:
	{
		paintWindow(hWnd);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK serverAddress(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			char ipAddress[16];
			char portNumber[6];
			GetDlgItemTextA(hDlg, IDC_IP, ipAddress, 16);
			GetDlgItemTextA(hDlg, IDC_PORT, portNumber, 6);
			stringstream ss;
			ss << string(portNumber); //converts char to string
			int port;
			ss >> port; //converts string to int

			/////////////////CREATE SERVER CONECTION!
			myClient = Client(string(ipAddress), port);
			if (!myClient.connectToServer()) {//if the connection fails
				return false;
			}
			myClient.isConnected = true;
			/////////////////////////////////////////

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK userNameDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);


	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK
	) {
			char title[20];
			GetWindowTextA(hWnd, title, 20); // stores current window title in title
			char value[20]; // Value that user types is stored in here.
			GetDlgItemTextA(hDlg, IDC_User_Name, value, 20);
			std::stringstream ss;
			ss << title;
			ss << " - ";
			ss << value;
			std::string newTitle = ss.str();
			SetWindowTextA(hWnd, newTitle.c_str()); // Creates new title name with "- (username)" at the end

			//sends string message
			myClient.sendPlayerName(value);


			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			//MAKE A CASE TO RETURN THE VALUE "NO NAME" // or null.
			return false;
		}
		break;

	}
	return (INT_PTR)FALSE;
}

bool processCardsReceived(string _cards) {
	clearCards();

	//reads string input and puts it into cardsSubmitted array as integers;
	size_t pos = 0;  //LEARN MORE ABOUT SIZE_T
	std::string token;
	std::stringstream ss;

	//////////////
	std::string cardsToProcess = _cards;
	if (_cards != "") {
	//SPLITS STRING and stores it in cardsSubmitted[]
	while ((pos = cardsToProcess.find(" ")) != std::string::npos) { //Stops so it doesn't go pass EOF 
		token = cardsToProcess.substr(0, pos);
		ss << token;
		ss >> cardsReceived[numberOfCardsReceived++];
		ss.clear();
		ss.str(std::string()); // empties string stream buffer
		cardsToProcess.erase(0, pos + 1); //Moves the buffer to the start of the next number
	}
	ss << cardsToProcess;
	ss >> cardsReceived[numberOfCardsReceived++];
	}

	//////////// Prints out the cards processed
	ss.clear();
	ss.str(std::string());
	ss << "Number of cards read in " << numberOfCardsReceived;
	paintWindow(hWnd);

	InvalidateRect(hWnd, 0, true); // refreshes screen
	return true;
}

bool clearCards() {
	for (int i = 0; i < numberOfCardsReceived; i++) {
		cardsReceived[i] = { "" };
	}
	numberOfCardsReceived = 0;
	return true;
}


bool setNames(string *_playerNames, int _numberOfPlayers) { //run once to set number of players and player names
	numberOfPlayers = _numberOfPlayers;
	for (int i = 0; i < _numberOfPlayers; i++) {
		playerNames[i] = _playerNames[i];
	}
	return true;
}

string getName(int ID) {
	return playerNames[ID];
}

int getTotalAmountOfPlayers() {
	return numberOfPlayers;
}

bool setNumberOfCardsAPlayerHas(int ID, int value) {
	numberAllOfCardsAllPlayersHave[ID] = value;
	return true;
}

bool setCardPileCount(int value) {
	cardPileCount = value;
	return true;
}

bool setActiveCardValue(string value) {
	activeCardValue = value;
	return true;
}

string getActiveCardValue() {
	return activeCardValue;
}


bool paintWindow(HWND &hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code that uses hdc here...
	SetBkMode(hdc, TRANSPARENT);

	//PAINTS CARDS TO WINDOW!
	for (int i = 0, j = 0; i < numberOfCardsReceived; i++) {
		if ((i - 1) % 9 == 8) { // This alters how many cards there are per row
			j++;
		}
		Rectangle(hdc, 300 + (i % 9 * 70), 20 + (90 * j), 360 + (i % 9 * 70), 100 + (90 * j)); //(i spaces them out vertically - j modifies the hight
		TextOutA(hdc, 302 + (i % 9 * 70), 20 + (90 * j), cardsReceived[i].c_str(), 3);
	}

	//Paints Player Box to WINDOW
	Rectangle(hdc, 30, 20, 280, 210);
	//Paints Pile in box
	{ // this is here to stop the stream string from exiting this scope
		std::stringstream ss;
		ss << "Card Pile: " << cardPileCount;
		TextOutA(hdc, 32, 20, ss.str().c_str(), ss.tellp());
	}
	//Paints players in player box
	for (int i = 0; i < numberOfPlayers; i++) {
		std::stringstream ss;
		ss << playerNames[i] << ": " << numberAllOfCardsAllPlayersHave[i];
		TextOutA(hdc, 32, 50 + 20 * i, ss.str().c_str(), ss.tellp());
	}
	{
		std::stringstream ss;
		ss << "Active card value: " << activeCardValue;
		TextOutA(hdc, 80, 420, ss.str().c_str(), ss.tellp()); //prints out the active card Value
	}
	{
		std::stringstream ss;

		ss << "Cards you are submitting: ";
		for (int i = 0; i < cardsSubmittingCount; i++) {
			ss << cardsSubmitting[i];
			if (i + 1 < cardsSubmittingCount) {
				ss << ",";
			}
		}
		TextOutA(hdc, 20, 460, ss.str().c_str(), ss.tellp()); // prints out the cards you are planning to submit
	}
	/////paints messageBox
	Rectangle(hdc, 30, 220, 280, 420);
	/////Paints recent messages
	for (int i = 0; i < myClient.messageBox.getMessageCount(); i++) {
		stringstream ss;
		ss << myClient.messageBox.getMessage(i);
		TextOutA(hdc, 32, 220 + (i * 15), ss.str().c_str(), ss.tellp()); // prints out the most recent message
	}

	EndPaint(hWnd, &ps);
	return true;
}




