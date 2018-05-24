#pragma comment (lib, "winmm.lib") // Thư viện hỗ trợ chèn âm thanh file "*.wav"
#include <stdio.h>
#include "Screen.h"
#include "Windows.h"
#include <iostream>
#include "Hospital.h"
#include "Player.h"
#include "Car.h"

#define MaxCar 17 // Số lượng xe
#define CarLength 10 // Chiều dài xe

using namespace std;

// Khai báo cấu trúc xe cứu thương
struct Ambulance
{
	POINT Am;
	char Car[3][3];
};

  // Khởi tạo xe cứu thương
void InitACar(int x, int y, Ambulance& Z)
{
	Z.Am.x = x, Z.Am.y = y;
	memset(Z.Car, NULL, sizeof(Z.Car));
	Z.Car[0][0] = Z.Car[2][2] = Z.Car[2][0] = Z.Car[0][2] = 'O';
	Z.Car[1][0] = Z.Car[1][2] = '|';
	Z.Car[0][1] = Z.Car[2][1] = '-';
}

// Vẽ xe cứu thương
void DrawAmbulance(int x, int y, Ambulance& Z)
{
	gotoXY(x, y);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << Z.Car[i][j];
		}
		gotoXY(x, y + i + 1);
	}
}

// Xóa xe cứu thương
void EraserAmbulance(int x, int y)
{
	gotoXY(x, y);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			putchar(' ');
		}
		gotoXY(x, y + i + 1);
	}
}

// Quá trình cứu thương khi xảy ra tai nạn
void AccidentProcess(POINT**& Car, POINT& Player, POINT CarInEnd[], int mCarInEnd, Ambulance& Z)
{
	Beep(659, 500);
	PlaySoundA("sound.wav", NULL, SND_ASYNC);
	for (int i = 4; i < MaxCar; i++)
	{
		for (int j = 0; j < CarLength; j++)
		{
			gotoXY(Car[i][j].x, Car[i][j].y);
			putchar(' ');
		}
	}
	InitACar(Player.x, 21, Z);
	DrawAmbulance(Player.x, 21, Z);
	for (int i = 21; i >= Player.y; i--)
	{
		DrawCarInEnd(CarInEnd, mCarInEnd);
		Hospital(Player.x, 19);
		if (i != Player.y) DrawPlayer(Player, 'Y');
		EraserAmbulance(Player.x, i);
		Z.Am.y--;
		if (i == Player.y) Z.Car[1][1] = 'Y';
		DrawAmbulance(Z.Am.x, Z.Am.y, Z);
		Sleep(200);
	}
	for (int i = Player.y; i <= 19; i++)
	{
		DrawCarInEnd(CarInEnd, mCarInEnd);
		EraserAmbulance(Player.x, i - 1);
		Z.Am.y++;
		if (i == 17)
		{
			for (int j = 0; j < 3; j++)
				Z.Car[2][j] = ' ';
		}
		if (i == 18)
		{
			for (int j = 0; j < 3; j++)
				Z.Car[1][j] = ' ';
		}
		if (i == 19)
		{
			for (int j = 0; j < 3; j++)
				Z.Car[0][j] = ' ';
		}
		DrawAmbulance(Z.Am.x, Z.Am.y, Z);
		Hospital(Player.x, 19);
		Sleep(200);
	}
	PlaySound(NULL, 0, 0);
}