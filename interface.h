#pragma once
#include <string>
#include <windows.h>

using namespace std;

void setcolor(int bgcolor, int color);
void getinitcolor(CONSOLE_SCREEN_BUFFER_INFO& info);
void resetcolor(CONSOLE_SCREEN_BUFFER_INFO info);

void print_blank(int num, string T_F = "F");
void print_hyphen(int num, string T_F = "F");
void newline(string T_F);
void check_enter();

void gotoxy(int x, int y);
void getxy(CONSOLE_SCREEN_BUFFER_INFO& info);
void resetxy(CONSOLE_SCREEN_BUFFER_INFO info);