#pragma once
#include "Data.h"

// Reset dữ liệu game
void ResetData(int& Move, int& Speed, POINT& Y, POINT**& X, POINT Z[], int& m);

// Dọn dẹp dữ liệu game
void CollectData(POINT**& X);
