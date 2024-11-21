#include"expire_tool.h"
#include"day_0.h"
#include"game_start.h"
#include"player.h"
#include "day_1.h"
#include "day_2.h"
#include "day_3.h"
#include <Windows.h>
#include "ready_screen.h"
#include "day_7.h"
int main() {
	//Ä¿¼­ ±ôºýÀÓ Á¦°Å
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curCursorInfo;

	GetConsoleCursorInfo(hc, &curCursorInfo);

	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hc, &curCursorInfo);
	
	
	
	game_start_screen();
	player* user = new player();
	start_day0(user);
	system("cls");
	draw_ready(user);
	start_day1(user);
	system("cls");
	draw_ready(user);
	start_day2(user);
	system("cls");
	draw_ready(user);
	start_day3(user);
	system("cls");
}
