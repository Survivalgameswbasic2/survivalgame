#include "expire_tool.h"
#include "item_image.h"
#include "item_image2.h"
#include "map_image.h"
#include "player.h"
#include <windows.h>
#include <conio.h>

using namespace std;
#define STAGE_WIDTH 70  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 

void draw_ready_text(player* p, int day) {

	int xOffset = 0;
	int yOffset = 21; // �� â �ϴܿ� �ؽ�Ʈ â ��ġ ����  
	int width = STAGE_WIDTH;    // �ؽ�Ʈ â ���� ����
	int height = 5;                 // �ؽ�Ʈ â ���� ����

	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(xOffset + x, yOffset + y);
			if (y == 0) {
				if (x == 0) printf("��");
				else if (x == width) printf("��");
				else printf("��");
			}
			else if (y == height - 1) {
				if (x == 0) printf("��");
				else if (x == width) printf("��");
				else printf("��");
			}
			else {
				if (x == 0 || x == width) printf("��");
				else printf(" ");
			}
		}
	}
	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("�̹��� ������ ����");

	if (day == 1) {
		printf("���� ��ó�� �ܵ� ���̴�.");
		setCursorPosition(xOffset + 1, yOffset + 2);
		printf("�ۿ� ��ġ�� ���̴� �޺��� ���ϰ� ���� ���� ���̴�. ������ Ž������.");
	}
	else if (day == 2) {
		printf("������� ������ ������������ �𸣴� ķ�����̴�.");
		setCursorPosition(xOffset + 1, yOffset + 2);
		printf("������� ���� �𿴴� ���̶� ���� ���� ���������״� ��������.");
	}
	else if (day == 2) {
		printf("���ڸ� ���� ���ɼ��� ���� �����̴�.");
		setCursorPosition(xOffset + 1, yOffset + 2);
		printf("�Ȱ��� ���ڸ� �븮�� �� ������� ��������.");
	}


	int key = _getch();
	while (key == 0) {
	}

	key = 0;



	setCursorPosition(1, 23);
	std::cout << "                                                                     ";
	setCursorPosition(1, 24);
	std::cout << "                                                                     ";


	key = 0;
	while (true) {
		setCursorPosition(xOffset + 1, yOffset + 1);
		printf("ü�� �Ǵ� ��Ʈ���� ��ġ�� ������ ���, ġ������ �̿��Ͽ� ȸ���� �� �ִ�.");

		setCursorPosition(xOffset + 1, yOffset + 2);
		printf("Ž�� ��, ġ������ ����ұ�? (��� �� y, ������� ���� �� nŰ)");

		key = _getch();
		if (key == 'y') {
			if (p->medicine <= 0) {
				setCursorPosition(1, 23);
				std::cout << "                                                                     ";
				setCursorPosition(1, 24);
				std::cout << "                                                                     ";

				setCursorPosition(xOffset + 1, yOffset + 1);
				printf("ġ������ �����մϴ�.");
				key = 0;
				while (key == 0) {
					key = _getch();
				}
				break;
			}
			else {
				p->medicine--;
				p->heart = p->heart + 2;
				if (p->heart > 5) {
					p->heart = 5;
				}
				p->mental = p->mental + 50;
				if (p->mental > 100) {
					p->mental = 100;
				}
			}

			continue;
		}
		else if (key == 'n') {
			break;

		}
	}



}
void draw_ready_map(int day) {

	int xOffset = 74;
	int yOffset = 0; // �� â �ϴܿ� �ؽ�Ʈ â ��ġ ����  
	int width = 27;    // �ؽ�Ʈ â ���� ����
	int height = 26;                 // �ؽ�Ʈ â ���� ����

	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(xOffset + x, yOffset + y);
			if (y == 0) {
				if (x == 0) printf("��");
				else if (x == width) printf("��");
				else printf("��");
			}
			else if (y == height - 1) {
				if (x == 0) printf("��");
				else if (x == width) printf("��");
				else printf("��");
			}
			else {
				if (x == 0 || x == width) printf("��");
				else printf(" ");
			}
		}
	}

	if (day >= 0) {

		for (int i = 0; i < 6; i++) {
			setCursorPosition(xOffset + 1, yOffset + 18 + i);
			for (int j = 0; j < 20; j++) {
				printf("%c", mapList[0][i][j]);
			}
		}

		if (day >= 1) {

		}
	}


}

void test_print(int x, int y) {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			setCursorPosition(x + i, y + j);
			printf("%c", itemList[0][x][y]);
		}
	}
}

void printInformation(player* p) {

	int food = p->food;
	for (int i = 0; i < 4; i++) {
		setCursorPosition(6, i + 1);
		for (int j = 0; j < 12; j++) {
			printf("%c", itemList2[1][i][j]);
		}
	}
	setCursorPosition(16, 3);
	printf("�ķ� x %d", food);


	int water = p->water;
	for (int i = 0; i < 5; i++) {
		setCursorPosition(6, i + 5);
		for (int j = 0; j < 8; j++) {
			printf("%c", itemList2[0][i][j]);
		}
	}
	setCursorPosition(16, 8);
	printf("�ļ� x %d", water);

	int heal = p->medicine;
	for (int i = 0; i < 4; i++) {
		setCursorPosition(6, i + 10);
		for (int j = 0; j < 12; j++) {
			printf("%c", itemList2[2][i][j]);
		}
	}
	setCursorPosition(16, 12);
	printf("ġ���� x %d", heal);

	int gun = p->gun;
	int bullet = p->bullet;

	if (1) {
		for (int i = 0; i < 4; i++) {
			setCursorPosition(6, i + 14);
			for (int j = 0; j < 18; j++) {
				printf("%c", itemList2[3][i][j]);
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		setCursorPosition(20, i + 15);
		for (int j = 0; j < 12; j++) {
			printf("%c", itemList2[4][i][j]);
		}
	}

	setCursorPosition(32, 16);
	printf("�Ѿ� x %d", bullet);


}


void printInformation2(player* p) {

	int hp = p->heart;
	int mp = p->mental;

	setCursorPosition(38, 3);
	printf("���� ���� ü�� x %d", hp);
	setCursorPosition(38, 5);
	printf("���� ��Ʈ���� ��ġ x %d", mp);


	setCursorPosition(42, 8);
	printf("	��������");
	setCursorPosition(42, 9);
	printf("	��    ��");
	setCursorPosition(42, 10);
	printf("	��������");
	setCursorPosition(42, 11);
	printf("����������������");
	setCursorPosition(42, 12);
	printf("��          �� ��");
	setCursorPosition(42, 13);
	printf("��            ��");


}

// �ؽ�Ʈ â �ʱ�ȭ �� �޽��� ��� �Լ�
void draw_ready(player* p, int day) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // �� â �ϴܿ� �ؽ�Ʈ â ��ġ ����  
	int width = STAGE_WIDTH;    // �ؽ�Ʈ â ���� ����
	int height = 20;                 // �ؽ�Ʈ â ���� ����
	// �ؽ�Ʈ â �׵θ��� ���� ���

	// �ؽ�Ʈ â �׵θ� �׸���
	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(x, y);
			if (y == 0) {
				if (x == 0) printf("��");
				else if (x == width) printf("��");
				else printf("��");
			}
			else if (y == height - 1) {
				if (x == 0) printf("��");
				else if (x == width) printf("��");
				else printf("��");
			}
			else {
				if (x == 0 || x == width) printf("��");
				else printf(" ");
			}
		}
	}
	//test_print(0, 0);
	printInformation(p);
	printInformation2(p);
	draw_ready_map(day);
	draw_ready_text(p, day);


}




