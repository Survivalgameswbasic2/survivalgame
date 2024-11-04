#include <iostream>
#include <string.h>
#include <Windows.h>

#define SCEEN_WIDTH 35
#define SCEEN_HEIGHT 20


void printfstat(int heart, int mental, int food, int water, int bullet, int heal) {

	SHORT y = 1;
	SHORT x = SCEEN_WIDTH * 2 + 2;
	COORD pos1 = { x ,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos1);

	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("┌─────────────────────────┐");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 체력 :     ");
	for (int i = 0; i < heart; i++) {
		printf("♥");
	}
	for(int i = 0; i < 5 - heart; i++) {
		printf("♡");
	}
	printf("   │");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);

	printf("│ 스트레스 : ");
	for (int i = 0; i < mental; i++) {
		printf("★");
	}
	for (int i = 0; i < 5 - mental; i++) {
		printf("☆");
	}
	printf("   │");
	pos1 = {x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│                         │"); 
	pos1 = {x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 식량 X %d                │",food); 
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 물 X %d                  │",water);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (bullet != 0) {
		printf("│ 탄환 X %d                │", bullet);
	}
	else {
		printf("│ ---                     │");
	}
	pos1 = {x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (heal != 0) {
		printf("│ 치료제 X %d              │", heal);
	}
	else {
		printf("│ ---                     │");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("└─────────────────────────┘");
}

int main() {
	

	/*for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 35; j++) {
			printf("■");
		}
		printf("\n");
	}*/

	printfstat(1, 2, 3, 4,0,0);

}