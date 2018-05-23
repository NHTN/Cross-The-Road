#pragma once
#include <Windows.h>

void DrawPlayer(POINT& Y, char s);

void MoveRight(POINT& Y);
void MoveLeft(POINT& Y);
void MoveUp(POINT& Y);
void MoveDown(POINT& Y);

void MovePlayer(int& key, POINT& Player);