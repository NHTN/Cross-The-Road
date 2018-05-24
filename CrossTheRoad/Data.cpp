#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "Data.h"
#include "Screen.h"

#define MaxCar 17 // Số lượng xe
#define CarLength 10 // Độ dài xe
#define HeighConsole 24 // Chiều cao màn hình
#define WidthConsole 60 // Chiều rộng màn hình


// Reset dữ liệu game
void ResetData(int& Move, int& Speed, POINT& Y, POINT**& X, POINT Z[], int& m)
{
	Move = 'D';
	Speed = 1;
	Y = { 18, 19 };
	m = 0;
	memset(Z, 0, sizeof(Z));
	if (X == NULL)
	{
		X = new POINT*[MaxCar];
		for (int i = 0; i < MaxCar; i++)
		{
			X[i] = new POINT[CarLength];
		}

		for (int i = 0; i < MaxCar; i++)
		{
			int temp = (rand() % (WidthConsole - CarLength)) + 1;
			for (int j = 0; j < CarLength; j++)
			{
				X[i][j].x = temp + j;
				X[i][j].y = 2 + i;
			}
		}
	}
}

// Dọn dẹp dữ liệu
void CollectData(POINT**& X)
{
	for (int i = 0; i < MaxCar; i++)
	{
		delete[] X[i];
	}
	delete[] X;
}

