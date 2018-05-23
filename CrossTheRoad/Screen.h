#pragma once
#include <string>
#include <Windows.h>

void FixConsoleWindow();
void gotoXY(int x, int y);
void DrawBoard();
void CursorStatus(DWORD Size, BOOL visible);
void Menu();
void Hello();
void Cleartext();
void TextColor(int color);
int MeNu();