#include "expire_tool.h"
#include "item_image.h"
using namespace std;
#define STAGE_WIDTH 70  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 

void draw_ready_text() {

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
}
void draw_ready_map() {

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

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			setCursorPosition(x + i, y + j);
			printf("%c", itemList[0][x][y]);
		}
	}
}


// �ؽ�Ʈ â �ʱ�ȭ �� �޽��� ��� �Լ�
void draw_ready() {
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
	test_print(0, 0);

	draw_ready_text();
	draw_ready_map();

	//Sleep(500);

}

