
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
using namespace std;

#define Enter 13
//const int WHITE=15;
#define PASSWORD "abcdef"
//const int WHITE=15;

char* Pwd() {
	char S[40]; int i = 0;
	while ((S[i] = _getch()) != Enter) {
		printf("%c", '*'); i++;
	}
	S[i] = '\0';
	return S;
}

int CheckPwd() {
	int dem = 0;
	for (dem = 1; dem <= 3; dem++) {
		printf("Password :");
		if (strcmp(Pwd(), PASSWORD) == 0)   return 1;
		else printf("\nPassword sai. Hay nhap lai\n");
	}
	return 0;
}

void gotoxy(short x, short y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x,y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

int wherex(void) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}

int wherey(void) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}
void clreol() {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coord.X = info.dwCursorPosition.X;
	coord.Y = info.dwCursorPosition.Y;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
		info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
	gotoxy(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}

void SetColor(WORD color) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color) {
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr() {
	system("cls");
}
//-----------------------------------------------------------NEW ADD----------------------------------------------------------

//Resize Console
void resizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

//Pop up canh bao
void Alert(string str, int x, int y, int color, int sleep, int bgColor = 7) {
	gotoxy(x, y);
	SetColor(color);
	SetBGColor(bgColor);
	std::cout << str;
	Sleep(sleep);
	gotoxy(x, y);
	std::cout << "                                             ";
}

//Lay thong tin phim nhan
int GetKey() {
	char key;
	key = _getch();
	if (key == -32 || key == 0)
		return -_getch();
	else return key;
}

//Turn off buttom cua Them Lop
void turnoffButtonThemLop() {
	gotoxy(20, 24);
	SetColor(15);
	SetBGColor(8);
	cout << " ENTER ";
	SetColor(1);
	SetBGColor(7);
	cout << ":OK";

	gotoxy(36, 24);
	SetColor(15);
	SetBGColor(8);
	cout << " CONTROL ";
	SetColor(1);
	SetBGColor(7);
	cout << ":LEFT-RIGHT";

	gotoxy(60, 24);
	SetColor(15);
	SetBGColor(9);
	cout << " SAVEFILE ";
	SetColor(1);
	SetBGColor(7);
	cout << ":F1";
	return;
}











