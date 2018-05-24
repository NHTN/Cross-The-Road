#pragma once
#include "Player.h"
#include <Windows.h>

// Vẽ nhân vật người chơi
void DrawPlayer(POINT& Y, char s);

// Các hàm hỗ trợ di chuyển
void MoveRight(POINT& Y);
void MoveLeft(POINT& Y);
void MoveUp(POINT& Y);
void MoveDown(POINT& Y);

// Hàm di chuyển nhân vật Player theo key
void MovePlayer(int& key, POINT& Player);