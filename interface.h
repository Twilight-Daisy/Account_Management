#pragma once
#include <string>
#include <windows.h>

using namespace std;

void setcolor(int bgcolor, int color);	// 색상 지정
void getinitcolor(CONSOLE_SCREEN_BUFFER_INFO& info);	// 현재 색상 저장
void resetcolor(CONSOLE_SCREEN_BUFFER_INFO info);	// 저장된 색상으로 지정

void print_blank(int num, string T_F = "F");	// num만클 공백 출력
void print_hyphen(int num, string T_F = "F");	// num만큼 - 출력
void newline(string T_F);	// T_F에 따라 다른 함수 내에서 개행 실행
void check_enter();	// enter키 입력 확인

void gotoxy(int x, int y);	// 커서 위치 지정
void getxy(CONSOLE_SCREEN_BUFFER_INFO& info);	// 현재 커서 위치 저장
void resetxy(CONSOLE_SCREEN_BUFFER_INFO info);	// 저장된 커서 위치로 지정