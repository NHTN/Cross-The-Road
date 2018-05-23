#include <Windows.h>
#include <stdio.h>
#include "Screen.h"
#include <iostream>

using namespace std;

void Hospital(int x, int y)
{
	char p[3][5];
	memset(p, NULL, sizeof(p));
	p[0][0] = (char)218;
	p[2][4] = (char)217;
	p[0][1] = p[0][2] = p[0][3] = p[2][1] = p[2][2] = p[2][3] = (char)196;
	p[2][0] = (char)192;
	p[0][4] = (char)191;
	p[1][0] = p[1][4] = (char)179;


	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	p[1][2] = (char)43;
	gotoXY(x, y);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 1 && j == 2)
				SetConsoleTextAttribute(hConsoleColor, 4);
			else SetConsoleTextAttribute(hConsoleColor, 7);
			cout << p[i][j];
		}
		gotoXY(x, y + i + 1);
	}
}