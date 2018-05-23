#include <Windows.h>
#include <iostream>
#include "Screen.h"
#include <string>
#include <conio.h>
#define HeighConsole 24
#define WidthConsole 60
#define MauNen 11
#define MauChu 7

using namespace std;


enum Status { Up, Down, Left, Right, Enter };

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void CursorStatus(DWORD Size, BOOL visible)
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = Size;
	cci.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void DrawBoard()
{
	char s = (char) 219;
	gotoXY(0, 2);
	for (int i = 0; i < WidthConsole; i++) cout << s;
	for (int i = 2; i < HeighConsole; i++)
	{
		gotoXY(0, i);
		cout << s;
		gotoXY(WidthConsole, i);
		cout << s;
	}
	gotoXY(0, HeighConsole);
	for (int i = 0; i <= WidthConsole; i++) cout << s;
	gotoXY(0, 0);
}

void Menu()
{
	gotoXY(63, 10);
	cout << "(ESC) EXIT GAME";
	gotoXY(63, 11);
	cout << "(P)   PAUSE GAME";
	gotoXY(67, 12);
	cout << "  RESUME GAME";
	gotoXY(63, 13);
	cout << "(L)   SAVE GAME";
	gotoXY(63, 14);
	cout << "(T)   LOAD GAME";
}

void Cleartext()
{
	for (int i = 0; i < 3; i++)
	{
		gotoXY(35, 9 + i);
		putchar(' ');
	}
}

void Hello()
{
	gotoXY(30, 8);
	cout << ">> CROSS THE ROAD <<";


	gotoXY(0, 24);
	cout << (char)200;
	for (int i = 0; i < 78; i++) cout << (char)205;

	gotoXY(0, 1);
	for (int i = 0; i < 23; i++) cout << (char)186 << endl;

	gotoXY(79, 1);
	for (int i = 0; i < 23; i++)
	{
		cout << (char)186;
		gotoXY(79, i + 2);
	}

	gotoXY(79, 0);
	cout << (char)187;

	gotoXY(79, 24);
	cout << (char)188;
	gotoXY(0, 0);
	cout << char(201);
	for (int i = 0; i < 78; i++) cout << (char)205;

}

void TextColor(int color)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, color);
}

Status key(int z)
{
	if (z == 224)
	{
		char c;
		c = _getch();
		if (c == 72) return Up;
		if (c == 80) return Down;
		if (c == 77) return Right;
		if (c == 75) return Left;
	}
	else
		if (z == 13) return Enter;
}

int MeNu()
{
	string A[3] = { "New Game", "Load Game", "Exit" };
	int n = 3;
	int Cnt = 0;
	int *Color = new int[n];
	for (int i = 0; i < n; i++)
		Color[i] = MauChu;
	Color[0] = MauNen;

	TextColor(MauChu);
	Hello();

	while (1)
	{
		Cleartext();
		for (int i = 0; i < n; i++)
		{
			gotoXY(35, 9 + i);
			TextColor(Color[i]);
			cout << A[i] << endl;
		}
		int z = _getch();
		Status stt = key(z);
		switch (stt)
		{
		case Up:
		{
			if (Cnt == 0)
			{
				Cnt = n - 1;
			}
			else
			{
				Cnt--;
			}
			break;
		}
		case Down:
		{
			if (Cnt == n - 1)
			{
				Cnt = 0;
			}
			else
			{
				Cnt++;
			}
			break;
		}
		case Enter: return Cnt;
		}

		for (int i = 0; i < n; i++)
			Color[i] = MauChu;
		Color[Cnt] = MauNen;
	}
}