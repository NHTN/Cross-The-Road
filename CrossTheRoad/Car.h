#pragma once
#include "Car.h"

// Vẽ xe
void DrawCars(const char s, POINT**& X);

// Di chuyển xe
void MoveCar(POINT**& X, int Speed);

// Xóa xe
void EraserCar(POINT**& X, int Speeds);

// Vẽ người về đích
void DrawCarInEnd(POINT CarInEnd[], int mCarInEnd);