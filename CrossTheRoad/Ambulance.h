#pragma once
#include <Windows.h>
#include "Ambulance.h"

struct Ambulance
{
	POINT Am;
	char Car[3][3];
};

void InitACar(int x, int y, Ambulance& Z);
void DrawAmbulance(int x, int y, Ambulance& Z);
void EraserAmbulance(int x, int y);

void AccidentProcess(POINT**& Car, POINT& Player, POINT CarInEnd[], int mCarInEnd, Ambulance& Z);