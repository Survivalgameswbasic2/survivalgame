#include"expire_tool.h"
#include"day_0.h"
#include"game_start.h"
#include <Windows.h>
#include "ready_screen.h"
#include "ready_screen_after.h"
#include"player.h"
#include "day_1.h"
#include "day_2.h"
#include "day_3.h"
#include "day_4.h"
#include "day_7.h"
#include "day_5.h"
#include "day_6.h"
#include "backpack.h"

void deleteCursorBlink();

int main() {




	deleteCursorBlink();
	
	
	
	game_start_screen();
	player* user = new player();
	BackP* user_back = new BackP();
	system("cls");
	print_intro(0);
	system("cls");
	
	/*start_day0(user, user_back);
	system("cls");
	print_intro(1);
	system("cls");
	start_day1(user, user_back);
	system("cls");
	draw_ready_after(user, 1, user_back);
	system("cls");
	print_intro(2);
	system("cls");
	start_day2(user, user_back);
	system("cls");
	draw_ready_after(user, 2, user_back);
	system("cls");
	print_intro(3);
	system("cls");
	start_day3(user,user_back);
	system("cls");
	draw_ready_after(user, 3, user_back);
	system("cls");
	print_intro(4);
	system("cls");
	start_day4(user, user_back);
	system("cls");
	draw_ready_after(user, 4, user_back);
	system("cls");
	print_intro(5);
	system("cls");
	start_day5(user, user_back);
	system("cls");
	draw_ready_after(user, 5, user_back);
	system("cls");
	print_intro(6);
	system("cls");
	start_day6(user, user_back);
	system("cls");
	draw_ready_after(user, 6, user_back);
	system("cls");*/
	print_intro(7);
	system("cls");
	start_day7(user, user_back);
}




void deleteCursorBlink() {
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curCursorInfo;

	GetConsoleCursorInfo(hc, &curCursorInfo);

	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hc, &curCursorInfo);
}