#include "����.h"
#include "NPC��ȭâ.h"
#include "����â.h"
#include "��ȭâ.h"
#include "����â.h"
#include "Ÿ�̸�.h"
#include "�÷��̾�.h"
#include "day0.h"
#include "���ӽ���ȭ��.h"
#include <Windows.h>
int main() {
	//Ŀ�� ������ ����
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
