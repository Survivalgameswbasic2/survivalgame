#include "도구.h"
#include "NPC대화창.h"
#include "게임창.h"
#include "대화창.h"
#include "상태창.h"
#include "타이머.h"
#include "플레이어.h"
#include "day0.h"
#include "게임시작화면.h"
#include <Windows.h>
int main() {
	//커서 깜빡임 제거
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curCursorInfo;

	GetConsoleCursorInfo(hc,&curCursorInfo);

	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hc, &curCursorInfo);
	game_start_screen();
	player* user = new player();
	start_day0(user);
	while (1) {

	}
}
