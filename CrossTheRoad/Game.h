#pragma once
#include <Windows.h>

void StartGame(bool& Alive, int& Move, int& Speed, POINT& Y, POINT**& X, POINT Z[], int& m);
void ExitGame(HANDLE t, POINT**& X);
void PauseGame(HANDLE t);

void ProcessDead(bool& Alive);
void ProcessFinish(POINT& p, int& Speed, int& Move, POINT Z[], int& m);


bool IsImpact(POINT& p, int d, POINT**& X, POINT Z[], int m);

void SaveFile(const char* file, POINT** X, POINT& Y, int Speed, bool Alive, POINT Z[], int m);
void LoadFile(const char* file, POINT**& X, POINT &Y, POINT Z[], int &Speed, bool& Alive, int& m);


void SaveFileProcess(POINT** & Car, POINT& Player, int Speed, bool Alive, POINT CarInEnd[], int& mCarInEnd);
void LoadFileProcess(POINT** & Car, POINT& Player, int Speed, bool Alive, POINT CarInEnd[], int& mCarInEnd);