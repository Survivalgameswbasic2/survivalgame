#include <iostream>
#include <Windows.h>
#include "�÷��̾�.h"

#define STAGE_WIDTH 70  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 
#define MAX_HEALTH 5    // �ִ� ü��
#define stat_Height 12 //����â�� ������ ������ ���� 

void printstat(player* user) {

	SHORT y = 1;
	SHORT x = STAGE_WIDTH + 4;
	COORD pos1 = { x ,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos1);

	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("������������������������������������������������������");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("�� ü�� :     ");
	for (int i = 0; i < user->heart; i++) {
		printf(" ��");
	}
	for (int i = 0; i < 5 - user->heart; i++) {
		printf(" ��");
	}
	printf("   ��");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);

	printf("�� ��Ʈ���� : ");
	for (int i = 0; i < user->mental; i++) {
		printf(" ��");
	}
	for (int i = 0; i < 5 - user->mental; i++) {
		printf(" ��");
	}
	printf("   ��");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("��                         ��");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("�� �ķ� X %d                ��", user->food);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("�� �� X %d                  ��", user->water);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->bullet != 0) {
		printf("�� źȯ X %d                ��", user->bullet);
	}
	else {
		printf("�� ---                     ��");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->medicine != 0) {
		printf("�� ġ���� X %d              ��", user->medicine);
	}
	else {
		printf("�� ---                     ��");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("������������������������������������������������������");
}
