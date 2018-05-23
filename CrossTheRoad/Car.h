#pragma once
#include <Windows.h>

void DrawCars(const char s, POINT**& X);
void MoveCar(POINT**& X, int Speed);
void EraserCar(POINT**& X, int Speeds);
void DrawCarInEnd(POINT CarInEnd[], int mCarInEnd);