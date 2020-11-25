#include "interface.h"
#include <conio.h> // _getch 함수 사용
#include <iostream>
#include <string>
#include <string.h> // strcmp 사용
#include <windows.h> // setcolor 함수 사용

using namespace std;

const int WIDTH = 83;  // 가로 길이
const int HEIGHT = 27; // 세로 길이

void setcolor(int bgcolor, int color) {
    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

void getinitcolor(CONSOLE_SCREEN_BUFFER_INFO& info) {
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void resetcolor(CONSOLE_SCREEN_BUFFER_INFO info) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), info.wAttributes);
}

void print_blank(int num, string T_F) {
    for (int i = 0; i < num; i++)
        cout << " ";
    newline(T_F);
}

void print_hyphen(int num, string T_F) {
    for (int i = 0; i < num; i++)
        cout << "-";
    newline(T_F);
}

void newline(string T_F) {
    if (strcmp(T_F.data(), "T") == 0 || strcmp(T_F.data(), "t") == 0)
        cout << endl;
    else
        return;
}

void check_enter() {
    int check;
    while (1) {
        check = _getch();
        if (check == '\r')
            return;
    }
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void getxy(CONSOLE_SCREEN_BUFFER_INFO& info) {
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void resetxy(CONSOLE_SCREEN_BUFFER_INFO info) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info.dwCursorPosition);
}