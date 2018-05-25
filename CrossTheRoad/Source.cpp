#pragma comment (lib, "winmm.lib")
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <thread>
#include <time.h>
#include "Screen.h"
#include "Game.h"
#include "Car.h"
#include "Hospital.h"
#include "Data.h"
#include "Player.h"
#include "Ambulance.h"

#define PauseTime 3 // Khoảng thời gian tạm dừng của xe
#define MAX_SPEED 3 // Tốc độ tối đa
#define MaxCar 17 // Số lượng xe
#define CarLength 10 // Chiều dài xe

using namespace std;

thread t1; 
HANDLE AdGame, AdGameNd;


POINT** Car;  // Xe
POINT Player; // Người chơi
POINT CarInEnd[1000]; // Người chơi về đích
int pause = 0; // Biến quản lí tạm dừng game
int Move; // Biến quản lí phím nhấn nhập vào
int temp; 
int Speed = 1; // Biến quản lí tốc độ 
int mCarInEnd = 0; // Số lượng người chơi đã về đích
Ambulance Z; // Xe cứu thương
bool Alive;  // Biến quản lí trạng thái sống hay chết

// Tiểu trình game
void SubThread()
{
	int Count = 0;
	
	while (1)
	{
		if (Alive)
		{
			Count++;
		
			DrawCarInEnd(CarInEnd, mCarInEnd);
			Menu();
			MovePlayer(Move, Player);	
			
			if (Count % PauseTime == 0)
			{
				EraserCar(Car, Speed);
				MoveCar(Car, Speed);
			}

			DrawCars((char) 182, Car);

			if (IsImpact(Player, Player.y, Car, CarInEnd, mCarInEnd))
			{
				AccidentProcess(Car, Player, CarInEnd, mCarInEnd, Z);
				ProcessDead(Alive);
			}
			else
			if (Player.y <= 5)
			{
				Beep(587, 500);
				ProcessFinish(Player, Speed, Move, CarInEnd, mCarInEnd);
			}
			
			Sleep(100);
		}
	}
}

// Sao chép nhân đôi tiểu trình sang tiểu trình khác
void DuplicateThread(HANDLE& AdGame, HANDLE& AdGameNd)
{
	t1 = thread(SubThread);
	AdGame = t1.native_handle();
	DuplicateHandle(GetCurrentProcess(), AdGame, GetCurrentProcess(), &AdGameNd, DUPLICATE_SAME_ACCESS, 1, 0);
	t1.detach();
}

// Lựa chọn menu đầu vào *Yêu cầu 5
void Select(HANDLE& AdGameNd)
{
	int select = MeNu();
	if (select == 0)
	{
		StartGame(Alive, Move, Speed, Player, Car, CarInEnd, mCarInEnd);
	}
	else
		if (select == 1)
		{
			bool kt = true;
			ResetData(Move, Speed, Player, Car, CarInEnd, mCarInEnd);
			gotoXY(0, 0);
			system("cls");
			StartGame(Alive, Move, Speed, Player, Car, CarInEnd, mCarInEnd);
			PauseGame(AdGameNd);
			gotoXY(0, 0);
			system("cls");
			LoadFileProcess(Car, Player, Speed, Alive, CarInEnd, mCarInEnd, kt);
			while (!kt)
			{
				gotoXY(0, 3);
				cout << "Cannot open this file!";
				gotoXY(0, 4);
				cout << "Press [R] to load file again or Another key to play New game !";
				char T = _getch();
				if (T == 'R' || T == 'r')
				{
					system("cls");
					LoadFileProcess(Car, Player, Speed, Alive, CarInEnd, mCarInEnd, kt);
				}
				else kt = 1;
			}
			system("cls");
			gotoXY(0, 0);
			system("cls");
			DrawBoard();
			ResumeThread(AdGameNd);
		}
		else
		{
			system("cls");
			TerminateThread(AdGameNd, 0);
			temp = 'Z';
			return;
		}
}

void main()
{
	FixConsoleWindow(); // Mặc định kích thước cửa sổ console
	CursorStatus(1, FALSE); // Ẩn con trỏ chuột
	
	srand((int)time(0)); // Random

	DuplicateThread(AdGame, AdGameNd);

	Select(AdGameNd);
	if (temp == 'Z') return; // Nếu chọn Exit thì thoát

	while (1)
	{
		temp = _getch();
		if (Alive)
		{
			if (temp == 27)
			{
				ExitGame(AdGameNd, Car);
				return;
			}
			else
				if ((temp == 'L') || (temp == 'l'))
				{
					PauseGame(AdGameNd);
					SaveFileProcess(Car, Player, Speed, Alive, CarInEnd, mCarInEnd);
					ResumeThread(AdGameNd);
				}
				else
					if ((temp == 'T') || (temp == 't'))
					{
						bool kt = true;
						PauseGame(AdGameNd);
						LoadFileProcess(Car, Player, Speed, Alive, CarInEnd, mCarInEnd, kt);
						
						while (!kt)
						{
							gotoXY(3, 3);
							cout << "Cannot open this file!";
							gotoXY(3, 4);
							cout << "Press [R] to load file again or another key to play game continue ";
							char p = _getch();
							if (p == 'r' || p == 'R')
							{
								LoadFileProcess(Car, Player, Speed, Alive, CarInEnd, mCarInEnd, kt);
							}
							else kt = 1;
						}
						system("cls");
						DrawBoard();
						ResumeThread(AdGameNd);
					}
					else
				if ((temp == 'P' || temp == 'p') && !pause)
				{
					PauseGame(AdGameNd);
					pause = (pause + 1) % 2;
				}
				else
					if ((temp == 'P' || temp == 'p') && pause)
					{
						ResumeThread(AdGameNd);
						pause = (pause + 1) % 2;
					}
					else
						if (temp == 'D' || temp == 'd' || temp == 'A' || temp == 'a' || temp == 'W' || temp == 'w' || temp == 'S' || temp == 's')
						{
							Move = temp;
						}
		}
		else
		{
			if (temp == 'Y' || temp == 'y')
			{
				StartGame(Alive, Move, Speed, Player, Car, CarInEnd, mCarInEnd);
			}
			else
			{
				ExitGame(AdGameNd, Car);
				return;
			}
		}
	}
	
	system("pause>nul");
	return;
};