#include "expire_tool.h"
#include "item_image.h"
#include "item_image2.h"
#include "player.h"
#include <windows.h>
#include <conio.h>

using namespace std;
#define STAGE_WIDTH 70  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 

void draw_ready_text(player* p) {

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
	printf("�Ϸ������� �Ѿ�� �� �ķ�, �ļ��� �ϳ��� �����ؾ��Ѵ�.");

	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("���ڸ� �Һ�����. (�ƹ� Ű�� ���� �� �Һ� �� ���� ������ �Ѿ�ϴ�.)");
	int key = _getch();
	while (key == 0) {
	}

	key = 0;

	p->food--;
	p->water--;

	dialogue_clear();

	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("ü���� ������ ���, ġ������ �̿��ؼ� ü���� ä�� �� �ִ�.");

	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("ġ������ ����ұ�? (��� �� ����Ű, �׳� �Ѿ�� ->����Ű)");

	while (true) {
		if (key == ' ') {
			p->medicine--;
			break;
		}
		else if (key != 77) {
			break;
		}
	}






}
void draw_ready_map(player*user) {

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
		setCursorPosition(22, i + 14);
		for (int j = 0; j < 12; j++) {
			printf("%c", itemList2[4][i][j]);
		}
	}

	setCursorPosition(36, 16);
	printf("�Ѿ� x %d", bullet);






}


void printInformation2(player* p) {

	int hp = p->heart;
	int mp = p->mental;

	setCursorPosition(38, 3);
	printf("���� ���� ü�� x %d", hp);
	setCursorPosition(38, 5);
	printf("���� ��Ʈ���� ��ġ x %d", mp);

}

// �ؽ�Ʈ â �ʱ�ȭ �� �޽��� ��� �Լ�
void draw_ready(player* p) {
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
	draw_ready_map(p);
	draw_ready_text(p);


	while (_kbhit() == 0) {
	}

}




