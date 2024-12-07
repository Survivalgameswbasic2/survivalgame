#include "expire_tool.h"
#include "item_image.h"
#include "item_image2.h"
#include "map_image.h"
#include "backpack.h"
#include "player.h"
#include <windows.h>
#include <conio.h>
#include "bad_ending.h"

using namespace std;
#define STAGE_WIDTH 70  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 

void draw_ready_text_after(player* p) {

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
	printf("�Ϸ������� �Ѿ�� ��, �ļ��� �ϳ��� �����ؾ��Ѵ�.");

	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("���ڸ� �Һ�����. (�����̽�ī ���� �� �Һ�)");
	int key = _getch();
	while (key == 0) {
	}

	key = 0;

	if (p->water > 0) {
		p->water--;
	}
	else {
		bad_ending_starve();
	}


	setCursorPosition(1, 23);
	std::cout << "                                                                     ";
	setCursorPosition(1, 24);
	std::cout << "                                                                     ";


	key = 0;

	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("���� �Ϸ� ������ ��ġ��, ������ �ῡ ���");
	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("������ Ž�縦 �غ��ؾ��� ���̴�.");
	setCursorPosition(xOffset + 1, yOffset + 3);
	printf("���� ��, ������ �غ��ұ�? (�������� ȿ���� ���������� �����˴ϴ�)");
	key = _getch();
	while (key == 0) {
	}

	setCursorPosition(1, 23);
	std::cout << "                                                                     ";
	setCursorPosition(1, 24);
	std::cout << "                                                                     ";
	setCursorPosition(1, 22);
	std::cout << "                                                                     ";


	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("�� (�ִ�ü�� 1 ����)");

	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("  (��Ʈ���� �Ѱ� 20 ����");

	setCursorPosition(xOffset + 1, yOffset + 3);
	printf("  (������ ȿ���� 2��)");
	int where = 1;
	while (true) {

		key = _getch();
		if (key == '1') {
			setCursorPosition(xOffset + 1, yOffset + where);
			printf(" ");

			where = 1;

			setCursorPosition(xOffset + 1, yOffset + where);
			printf("��");
		}
		else if (key == '2') {
			setCursorPosition(xOffset + 1, yOffset + where);
			printf(" ");

			where = 2;

			setCursorPosition(xOffset + 1, yOffset + where);
			printf("��");
		}
		else if (key == '3') {
			setCursorPosition(xOffset + 1, yOffset + where);
			printf(" ");

			where = 3;

			setCursorPosition(xOffset + 1, yOffset + where);
			printf("��");
		}

		else if (key == ' ') {
			p->mode = where;
			break;
		}
	}


	if (p->mental > 100) {
		bad_ending_starve();
	}




}
void draw_ready_map_after(int day) {

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

			for (int i = 0; i < 6; i++) {
				setCursorPosition(xOffset + 4, yOffset + 11 + i);
				for (int j = 0; j < 16; j++) {
					printf("%c", mapList[1][i][j]);
				}
			}

			if (day >= 2) {

				for (int i = 0; i < 6; i++) {
					setCursorPosition(xOffset + 1, yOffset + 4 + i);
					for (int j = 0; j < 16; j++) {
						printf("%c", mapList[2][i][j]);
					}
				}
			}
		}

	}


}




void printInformation_after(player* p, BackP* b, int day) {


	// Ŭ���� ȭ�� 
	setCursorPosition(6, 0);
	printf("%d ���� ���� - ����  ... �ڿ� ȹ�� ��Ȳ", day);

	int food = b->food;
	setCursorPosition(6, 2);
	printf("�ķ� Ȯ��-");
	for (int k = 0; k < food; k++) {

		for (int i = 0; i < 4; i++) {
			setCursorPosition(6 + k * 8, i + 3);
			for (int j = 0; j < 12; j++) {
				printf("%c", itemList2[1][i][j]);
			}
		}

	}
	printf("%d �� ȹ��", food);


	int water = b->water;
	setCursorPosition(6, 8);
	printf("�ļ� Ȯ��-");
	for (int k = 0; k < water; k++) {
		for (int i = 0; i < 5; i++) {
			setCursorPosition(6 + k * 8, i + 9);
			for (int j = 0; j < 8; j++) {
				printf("%c", itemList2[0][i][j]);
			}
		}
	}
	printf(" %d �� ȹ��", water);

	int heal = b->medicine;
	setCursorPosition(6, 15);
	printf("ġ���� Ȯ��-");
	for (int k = 0; k < heal; k++) {
		for (int i = 0; i < 4; i++) {
			setCursorPosition(6 + k * 8, i + 16);
			for (int j = 0; j < 12; j++) {
				printf("%c", itemList2[2][i][j]);
			}
		}
	}
	printf("%d �� ȹ��", heal);

	int gun = p->gun;
	int bullet = p->bullet;

	setCursorPosition(6, 21);
	printf("��ź ��Ȳ-");
	if (gun == 1) {
		for (int i = 0; i < 4; i++) {
			setCursorPosition(6, i + 22);
			for (int j = 0; j < 18; j++) {
				printf("%c", itemList2[3][i][j]);
			}
		}

		for (int k = 0; k < bullet; k++) {
			for (int i = 0; i < 2; i++) {
				setCursorPosition(20 + k * 8, i + 23);
				for (int j = 0; j < 12; j++) {
					printf("%c", itemList2[4][i][j]);
				}
			}
		}
	}
	printf("%d �� ȹ��", bullet);
	int key = -1;

	printf("\n\n �����̽��� ���� �� ������ ����ǰ� ������ ���ư��ϴ�.");

	while (1) {

		key = _getch();
		if (key == ' ') {
			break;
		}

	}

}


void printInformation2_after(player* p) {

	int hp = p->heart;
	int mp = p->mental;

	setCursorPosition(38, 3);
	printf("���� ���� ü�� x %d", hp);
	setCursorPosition(38, 5);
	printf("���� ��Ʈ���� ��ġ x %d", mp);

	setCursorPosition(42, 8);
	printf(" ��������");
	setCursorPosition(42, 9);
	printf(" ��  ��");
	setCursorPosition(42, 10);
	printf(" ��������");
	setCursorPosition(42, 11);
	printf("������������");
	setCursorPosition(42, 12);
	printf("��  �� ��");
	setCursorPosition(42, 13);
	printf("��    ��");



}

// �ؽ�Ʈ â �ʱ�ȭ �� �޽��� ��� �Լ�
void draw_ready_after(player* p, int day, BackP* b) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // �� â �ϴܿ� �ؽ�Ʈ â ��ġ ����  
	int width = STAGE_WIDTH;    // �ؽ�Ʈ â ���� ����
	int height = 20;                 // �ؽ�Ʈ â ���� ����
	// �ؽ�Ʈ â �׵θ��� ���� ���
	printInformation_after(p, b, day);
	system("cls");


	b->unionP(p);
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
	//���⿡ �������� ��Ʈ ���
	//test_print(0, 0);

	//printInformation2_after(p);
	draw_ready_map_after(day);
	draw_ready_text_after(p);


}
