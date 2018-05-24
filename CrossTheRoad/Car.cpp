#include <Windows.h>
#include <iostream>
#include "Screen.h"

#define MaxCar 17 // Số lượng xe
#define CarLength 10 // Độ dài xe
#define WidthConsole 60 // Chiều rộng màn hình
#define HeightConsole 24 // Chiều dài màn hình

using namespace std;

// Vẽ xe 
void DrawCars(const char s, POINT**& X)
{
	for (int i = 4; i < MaxCar; i++)
	{
		for (int j = 0; j < CarLength; j++)
		{
			gotoXY(X[i][j].x, X[i][j].y);
			putchar(s);
		}
	}
}

// Di chuyển xe
void MoveCar(POINT**& X, int Speed)
{

	for (int i = 5; i < MaxCar; i += 2)
	{
		int cnt = 0;
		do
		{
			cnt++;
			for (int j = 0; j < CarLength-1; j++)
			{
				X[i][j] = X[i][j+1];
			}
			if (X[i][CarLength - 1].x >= WidthConsole - 1)
			{
				X[i][CarLength - 1].x = 1;
			}
			else
				X[i][CarLength - 1].x++;
		} while (cnt < Speed);
	}
	
	for (int i = 4; i < MaxCar; i += 2)
	{
		for (int j = CarLength-1; j >= 0; j--)
		{
			X[i][j].x -= Speed;
			if (X[i][j].x <= 1)
			{
				X[i][j].x = X[i][j].x + WidthConsole - 2;
			}
		}
	}
}

// Xóa xe
void EraserCar(POINT**& X, int Speed)
{
	for (int i = 5; i < MaxCar; i += 2)
	{
		for (int j = 0; j < Speed; j++)
		{
			gotoXY(X[i][j].x, X[i][j].y);
			putchar(' ');
		}
	}

	for (int i = 4; i < MaxCar; i += 2)
	{
		for (int j = 1; j <= Speed; j++)
		{
			gotoXY(X[i][CarLength - j].x, X[i][CarLength - j].y);
			putchar(' ');
		}
	}
}

// Vẽ người về đích
void DrawCarInEnd(POINT CarInEnd[], int mCarInEnd)
{
	for (int i = 0; i < mCarInEnd; i++)
	{
		gotoXY(CarInEnd[i].x, CarInEnd[i].y);
		putchar(' ');
		putchar('Y');
	}
}


