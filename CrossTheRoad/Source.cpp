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

#define PauseTime 3
#define MAX_SPEED 3
#define MaxCar 17
#define CarLength 10

using namespace std;

thread t1;
HANDLE AdGame, AdGameNd;


POINT** Car; 
POINT Player;
POINT CarInEnd[1000];
int pause = 0;
int Move;
int temp;
int Speed = 1; 
int mCarInEnd = 0;
Ambulance Z;
bool Alive; 


void SubThread()
{
	int Count = 0;
	gotoXY(0, 0);
	while (1)
	{
		if (Alive)
		{
			Count++;
			gotoXY(25, 1);
			cout << "ROUND : " << Speed << endl;

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

void DuplicateThread(HANDLE& AdGame, HANDLE& AdGameNd)
{
	t1 = thread(SubThread);
	AdGame = t1.native_handle();
	DuplicateHandle(GetCurrentProcess(), AdGame, GetCurrentProcess(), &AdGameNd, DUPLICATE_SAME_ACCESS, 1, 0);
	t1.detach();
}

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
			ResetData(Move, Speed, Player, Car, CarInEnd, mCarInEnd);
			gotoXY(0, 0);
			system("cls");
			StartGame(Alive, Move, Speed, Player, Car, CarInEnd, mCarInEnd);
			PauseGame(AdGameNd);
			gotoXY(0, 0);
			system("cls");
			LoadFileProcess(Car, Player, Speed, Alive, CarInEnd, mCarInEnd);
			gotoXY(0, 0);
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
	FixConsoleWindow();
	CursorStatus(1, FALSE);
	
	srand((int)time(0));

	DuplicateThread(AdGame, AdGameNd);

	Select(AdGameNd);
	if (temp == 'Z') return;
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
						PauseGame(AdGameNd);
						LoadFileProcess(Car, Player, Speed, Alive, CarInEnd, mCarInEnd);
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