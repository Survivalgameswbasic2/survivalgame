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
#include "Day_5.h"
void deleteCursorBlink();

int main() {
	keybd_event(VK_MENU, 0, 0, 0);           // Alt 키 누름
	keybd_event(VK_RETURN, 0, 0, 0);         // Enter 키 누름
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); // Alt 키 떼기
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);





	deleteCursorBlink();
	
	
	
	game_start_screen();
	player* user = new player();
	//system("cls");
	//print_intro(0);
	//system("cls");

	//start_day0(user);

	//system("cls");
	//draw_ready(user,1);
	//system("cls");

	//start_day1(user);

	//system("cls");
	////draw_ready_after(user, 1);
	//system("cls");
	////draw_ready(user,2);
	//system("cls");

	//start_day2(user);

	//system("cls");
	////draw_ready_after(user, 2, user_back);
	//system("cls");
	////draw_ready(user,3);
	//system("cls");

	//start_day3(user);

	//system("cls");
	////draw_ready_after(user, 3, user_back);
	//system("cls");
	//draw_ready(user, 4);
	//system("cls");

	start_day4(user);
	start_day5(user);
	system("cls");
	//draw_ready_after(user, 4, user_back);

	start_day7(user);
}




void deleteCursorBlink() {
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curCursorInfo;

	GetConsoleCursorInfo(hc, &curCursorInfo);

	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hc, &curCursorInfo);
}