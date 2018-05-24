#include <Windows.h>
#include <iostream>
#include "Screen.h"
#include "Game.h"

#define HeighConsole 24
#define WidthConsole 60

using namespace std;

// Vẽ nhân vật người chơi
void DrawPlayer(POINT& Y, char s)
{
	gotoXY(Y.x, Y.y);
	putchar(s);
}

// Di chuyển nhân vật sang Phải
void MoveRight(POINT& Y)
{
	DrawPlayer(Y, ' ');
	Y.x++;
	DrawPlayer(Y, 'Y');
}

// Di chuyển nhân vật sang Trái
void MoveLeft(POINT& Y)
{
	DrawPlayer(Y, ' ');
	Y.x--;
	DrawPlayer(Y, 'Y');
}

// Di chuyển nhân vật xuống Dưới
void MoveDown(POINT& Y)
{
	if (Y.y < HeighConsole - 1)
	{
		DrawPlayer(Y, ' ');
		Y.y++;
		DrawPlayer(Y, 'Y');
	}
}

// Di chuyển nhân vật lên Trên
void MoveUp(POINT& Y)
{
	if (Y.y > 1)
	{
		DrawPlayer(Y, ' ');
		Y.y--;
		DrawPlayer(Y, 'Y');
	}
}

// Di chuyển nhân vật Player theo key
void MovePlayer(int& key, POINT& Player)
{
	if (key == 'A' || key == 'a') MoveLeft(Player);
	else
		if (key == 'D' || key == 'd') MoveRight(Player);
		else
			if (key == 'S' || key == 's') MoveDown(Player);
			else
				if (key == 'W' || key == 'w') MoveUp(Player);
	key = ' ';
}