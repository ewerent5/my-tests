
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <zmouse.h>

#define BACKGROUND_GREEN     0x0020
#define HUI_MORJA 0x01010
#define _WIN32_WINNT 0x0500

/*

My cheat for Dota 2

*/

using std::cout;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость	курсора
	structCursorInfo.dwSize = size; // изменяем размер курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void position(short x, short y) {
	LPPOINT lpPoint;
	lpPoint = new (POINT);
	GetCursorPos(lpPoint);

	keybd_event('8', 0, 0, 0);
	keybd_event('8', 0, KEYEVENTF_KEYUP, 0);
	for (int i = 0; i < 8; i++) {
		SetCursorPos(x, y);
		Sleep(1);
		mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
		Sleep(1);
		mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
		Sleep(1);
	}
	SetCursorPos(lpPoint[0].x, lpPoint[0].y);
	keybd_event('9', 0, 0, 0);
	keybd_event('9', 0, KEYEVENTF_KEYUP, 0);
}

// fun for switch colors on the main screen depending on where the cursor is
void for_consol(char f1, short x, short y) {
	std::string menu[2] = { "Redian", "Dair" };

	if (f1 == 0)
		SetConsoleTextAttribute(hStdOut, 0x0003 | FOREGROUND_INTENSITY);
	else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	GoToXY(x += 10, y);
	cout << menu[0];

	if (f1 == 1)
		SetConsoleTextAttribute(hStdOut, 0x0304 | FOREGROUND_INTENSITY);
	else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	GoToXY(x += 10, y);
	cout << menu[1] << std::endl;
}

// fun for switch colors depending on where the cursor is
void dair(short count, char ss = 0) {

	if (ss == 1)
		SetConsoleTextAttribute(hStdOut, 0x0004 | FOREGROUND_INTENSITY);
	else
		SetConsoleTextAttribute(hStdOut, 0x0004);
	GoToXY(8, 12);
	cout << "Dair: " << count;

	if (ss == 2)
		SetConsoleTextAttribute(hStdOut, 0x0004 | FOREGROUND_INTENSITY);
	else
		SetConsoleTextAttribute(hStdOut, 0x0004);
	GoToXY(8, 14);
	cout << "<- beck ";
}

// fun for switch colors depending on where the cursor is
void redian(short count, char ss = 0) {

	if (ss == 1)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	else
		SetConsoleTextAttribute(hStdOut, 0x0003 | FOREGROUND_INTENSITY);
	GoToXY(8, 12);
	cout << "Redian: " << count;

	if (ss == 2)
		SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	else
		SetConsoleTextAttribute(hStdOut, 0x0003 | FOREGROUND_INTENSITY);
	GoToXY(8, 14);
	cout << "<- beck ";
}

void R_D(bool tf) {
	system("CLS");
	short count = 0;
	char enum_1 = 0;
	short KEY = 0;
	if (tf) {
		dair(count);
		while (enum_1 != 3) { // Dair
			for (short KEY = 8; KEY <= 190; KEY++) {
				if (GetAsyncKeyState(KEY) == -32767) {
					switch (KEY) {
					case 38:
						dair(count, 1);
						enum_1 = 1;
						break;
					case 40:
						dair(count, 2);
						enum_1 = 2;
						break;
					case 49:
						position(248, 836);
						count++;
						dair(count);
						break;
					case 50:
						position(251, 839);
						count++;
						dair(count);
						break;
					case 51:
						position(254, 843);
						count++;
						dair(count);
						break;
					case 13:
						if (enum_1 == 2)
							enum_1 = 3;
						break;
					}
				}
			}
		}
	}

	else {
		redian(count);
		while (enum_1 != 3) { // Redian
			for (short KEY = 8; KEY <= 190; KEY++) {
				if (GetAsyncKeyState(KEY) == -32767) {
					switch (KEY) {
					case 38:
						redian(count, 1);
						enum_1 = 1;
						break;
					case 40:
						redian(count, 2);
						enum_1 = 2;
						break;
					case 49:
						position(50, 1031);

						count++;
						redian(count);
						break;
					case 50:
						position(47, 1027);

						count++;
						redian(count);
						break;
					case 51:
						position(42, 1023);

						count++;
						redian(count);
						break;
					case 13:
						if (enum_1 == 2)
							enum_1 = 3;
						break;

					}
				}
			}
		}
	}
	system("CLS");
	for_consol(0, 8, 12);
	enum_1 = 0;
	count = 0;
}

void while_true() {
	bool tf = false;
	short x{ 8 }, y{ 12 };
	short KEY = 0;

	for_consol(0, x, y);

	while (true) {
		for (short KEY = 8; KEY <= 190; KEY++) {
			if (GetAsyncKeyState(KEY) == -32767) {

				switch (KEY) {

				case 13:
					R_D(tf);
					tf = false;
					break;
				case VK_UP:
					for_consol(2, x, y);
					break;
				case VK_DOWN:
					for_consol(2, x, y);
					break;
				case VK_LEFT:
					for_consol(0, x, y);
					tf = false;
					break;
				case VK_RIGHT:
					for_consol(1, x, y);
					tf = true;
					break;
				}
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	system("mode con cols=50 lines=30"); // размер консоли | size console

	ConsoleCursorVisible(false, 100);
	SetConsoleTitle(L"huki");
	short counter{ 0 };

	while_true();
}

/*
▄▄▄█████▓ ▒█████   ██▀███   ██▓███  ▓█████ ▓█████▄  ▄▄▄
▓  ██▒ ▓▒▒██▒  ██▒▓██ ▒ ██▒▓██░  ██▒▓█   ▀ ▒██▀ ██▌▒████▄
▒ ▓██░ ▒░▒██░  ██▒▓██ ░▄█ ▒▓██░ ██▓▒▒███   ░██   █▌▒██  ▀█▄
░ ▓██▓ ░ ▒██   ██░▒██▀▀█▄  ▒██▄█▓▒ ▒▒▓█  ▄ ░▓█▄   ▌░██▄▄▄▄██
▒██▒ ░ ░ ████▓▒░░██▓ ▒██▒▒██▒ ░  ░░▒████▒░▒████▓  ▓█   ▓██▒
▒ ░░   ░ ▒░▒░▒░ ░ ▒▓ ░▒▓░▒▓▒░ ░  ░░░ ▒░ ░ ▒▒▓  ▒  ▒▒   ▓▒█░
░      ░ ▒ ▒░   ░▒ ░ ▒░░▒ ░      ░ ░  ░ ░ ▒  ▒   ▒   ▒▒ ░
░      ░ ░ ░ ▒    ░░   ░ ░░          ░    ░ ░  ░   ░   ▒
░ ░     ░                 ░  ░   ░          ░  ░
░
*/
