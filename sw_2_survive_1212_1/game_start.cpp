#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "expire_tool.h"



void game_start_screen() {
	// �ܼ� â ũ�� ���� (���� 100, ���� 30)

	// �ܼ� ȭ�� �����
	system("CLS");

	// ���� ���
	setCursorPosition(17, 5);
	printf("  ######   ##     ##  ########  ##       ##  ######### ##       ##  #########");
	setCursorPosition(17, 6);
	printf(" ##    ##  ##     ##  ##    ##   ##     ##      ###     ##     ##   ##");
	setCursorPosition(17, 7);
	printf(" ##        ##     ##  ##    ##   ##     ##      ###     ##     ##   ##");
	setCursorPosition(17, 8);
	printf("  ######   ##     ##  ########    ##   ##       ###      ##   ##    #########");
	setCursorPosition(17, 9);
	printf("       ##  ##     ##  ## ###      ##   ##       ###      ##   ##    ##");
	setCursorPosition(17, 10);
	printf(" ##    ##  ##     ##  ##  ###      ## ##        ###       ## ##     ##");
	setCursorPosition(17, 11);
	printf("  ######    #######   ##   ###      ###      #########     ###      #########");


	setCursorPosition(50, 23);
	// �߰� ������ ���� ���� ���
	std::string subtitle = "Press enter key to start...";
	std::cout << subtitle;
	//printCenteredText(subtitle, consoleWidth);

	// ����ڰ� Ű�� ���� ������ ���
	while (_kbhit() == 0) {
	}
}