#pragma once
#include "Ambulance.h"

// Cấu trúc xe cứu thương
struct Ambulance
{
	POINT Am;
	char Car[3][3];
};

// Khởi tạo xe cứu thương
void InitACar(int x, int y, Ambulance& Z);

// Vẽ xe cứu thương
void DrawAmbulance(int x, int y, Ambulance& Z);

// Xóa xe cứu thương
void EraserAmbulance(int x, int y);

// Quá trình cứu thương khi xảy ra tai nạn
void AccidentProcess(POINT**& Car, POINT& Player, POINT CarInEnd[], int mCarInEnd, Ambulance& Z);