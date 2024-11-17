#include <iostream>
#include <Windows.h>
#include "플레이어.h"

#define STAGE_WIDTH 70  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 
#define MAX_HEALTH 5    // 최대 체력
#define stat_Height 12 //스탯창이 끝나는 지점의 높이 

void printstat(player* user) {

	SHORT y = 1;
	SHORT x = STAGE_WIDTH + 4;
	COORD pos1 = { x ,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos1);

	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("┌─────────────────────────┐");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 체력 :     ");
	for (int i = 0; i < user->heart; i++) {
		printf(" ♥");
	}
	for (int i = 0; i < 5 - user->heart; i++) {
		printf(" ♡");
	}
	printf("   │");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);

	printf("│ 스트레스 : ");
	for (int i = 0; i < user->mental; i++) {
		printf(" ★");
	}
	for (int i = 0; i < 5 - user->mental; i++) {
		printf(" ☆");
	}
	printf("   │");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│                         │");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 식량 X %d                │", user->food);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 물 X %d                  │", user->water);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->bullet != 0) {
		printf("│ 탄환 X %d                │", user->bullet);
	}
	else {
		printf("│ ---                     │");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->medicine != 0) {
		printf("│ 치료제 X %d              │", user->medicine);
	}
	else {
		printf("│ ---                     │");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("└─────────────────────────┘");
}
