#include <Windows.h>
#include <iostream>
#include <fstream>
#include "Data.h"
#include "Screen.h"
#include "Data.h"
#include "Player.h"

#define HeighConsole 24 
#define WidthConsole 60
#define CarLength 10
#define MaxCar 17

using namespace std;

// Bắt đầu 
void StartGame(bool& Alive, int& Move, int& Speed, POINT& Y, POINT**& X, POINT Z[], int& m)
{
	system("cls");
	ResetData(Move, Speed, Y, X, Z, m);
	DrawBoard();
	Alive = 1;
}

// Thoát game
void ExitGame(HANDLE t, POINT**& X)
{
	system("cls");
	TerminateThread(t, 0);
	CollectData(X);
}

// Tạm dừng game
void PauseGame(HANDLE t)
{
	SuspendThread(t);
}

// Chết
void ProcessDead(bool& Alive)
{
	Alive = 0;
	gotoXY(8, 3);
	cout << "Dead, Pres Y to Continue or Anykey to Exit!";
}

// Kiểm tra va chạm xe
bool IsImpact(POINT& p, int d, POINT**& X, POINT Z[], int m)
{
	for (int i = 0; i < m; i++)
	{
		if (p.x -1  == Z[i].x && p.y == Z[i].y)
		{
			return true;
		}
	}
	for (int i = 4; i < MaxCar; i++)
	{
		for (int j = 0; j < CarLength; j++)
		{
			if (p.x == X[i][j].x && p.y == X[i][j].y) return true;
		}
	}
	return false;
}

// Kết thúc
void ProcessFinish(POINT& p, int& Speed, int& Move, POINT Z[], int& m)
{
	Speed += (Speed == 3) ? (-2) : 1;
	Z[m].x  = p.x-1;
	Z[m].y = p.y;
	m++;
	p = { 18, 19 };
	Move = 'D';
}

// Lưu file
void SaveFile(const char* file, POINT** X, POINT& Y, int Speed, bool Alive, POINT Z[], int m)
{
	ofstream fo(file, ios::out| ios::binary);
	if (!fo)
	{
		cout << "Cannot open file ";
		return;
	}

	fo.write((char*)&Speed, sizeof(int));
	fo.write((char*)&Alive, sizeof(bool));
	fo.write((char*)&m, sizeof(int));

	for (int i = 0; i < m; i++)
	{
		fo.write((char*)&Z[i], sizeof(POINT));
	}

	for (int i = 0; i < MaxCar; i++)
		for (int j = 0; j < CarLength; j++)
			fo.write((char*)&X[i][j], sizeof(POINT));
	fo.close();
}

// Load file
void LoadFile(const char* file, POINT**& X, POINT &Y, POINT Z[], int &Speed, bool& Alive, int& m)
{
	ifstream fi(file, ios::in|ios::binary);
	if (!fi)
	{
		cout << "Cannot open file ";
		return;
	}
	else
	{
		gotoXY(15, 3);
		Beep(800, 300);
		cout << "Your file is loading successful !" << endl;
		Sleep(500);
		gotoXY(0, 0);
		system("cls");
	}
	fi.read((char*)&Speed, sizeof(int));
	fi.read((char*)&Alive, sizeof(bool));
	fi.read((char*)&m, sizeof(int));

	for (int i = 0; i < m; i++)
	{
		fi.read((char*)&Z[i], sizeof(POINT));
	}

	for (int i = 0; i < MaxCar; i++)
		for (int j = 0; j < CarLength; j++)
			fi.read((char*)&X[i][j], sizeof(POINT));
	
	fi.close();
}

// Quá trình lưu file
void SaveFileProcess(POINT** & Car, POINT& Player, int Speed, bool Alive, POINT CarInEnd[], int& mCarInEnd)
{
	char a[100];
	gotoXY(2, 3);
	cout << "Ten file ban muon luu : ";
	gotoXY(30, 3);
	gets_s(a, 100);
	gotoXY(2, 3);
	for (int i = 0; i < 45; i++)
		putchar(' ');
	SaveFile(a, Car, Player, Speed, Alive, CarInEnd, mCarInEnd);	
}

// Quá trình tải file
void LoadFileProcess(POINT** & Car, POINT& Player, int Speed, bool Alive, POINT CarInEnd[], int& mCarInEnd)
{
	char a[100];
	gotoXY(2, 3);
	cout << "Ten file ban muon load : ";
	gotoXY(30, 3);
	gets_s(a, 100);
	gotoXY(2, 3);
	for (int i = 0; i < 45; i++)
		putchar(' ');

	for (int i = 5; i < MaxCar; i += 2)
		for (int j = 0; j < CarLength; j++)
		{
			gotoXY(Car[i][j].x, Car[i][j].y);
			putchar(' ');
		}
	for (int i = 4; i < MaxCar; i += 2)
		for (int j = CarLength - 1; j >= 0; j--)
		{
			gotoXY(Car[i][j].x, Car[i][j].y);
			putchar(' ');
		}
	LoadFile(a, Car, Player, CarInEnd, Speed, Alive, mCarInEnd);

}