#include "expire_tool.h"
#include "item_image.h"
#include "item_image2.h"
#include "player.h"
#include <windows.h>
#include <conio.h>

using namespace std;
#define STAGE_WIDTH 70  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 

void draw_ready_text(player* p) {

	int xOffset = 0;
	int yOffset = 21; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = STAGE_WIDTH;    // 텍스트 창 가로 길이
	int height = 5;                 // 텍스트 창 세로 길이

	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(xOffset + x, yOffset + y);
			if (y == 0) {
				if (x == 0) printf("┌");
				else if (x == width) printf("┐");
				else printf("─");
			}
			else if (y == height - 1) {
				if (x == 0) printf("└");
				else if (x == width) printf("┘");
				else printf("─");
			}
			else {
				if (x == 0 || x == width) printf("│");
				else printf(" ");
			}
		}
	}
	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("하루일차가 넘어가기 전 식량, 식수를 하나씩 섭취해야한다.");

	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("물자를 소비하자. (아무 키나 누를 시 소비 후 다음 일차로 넘어갑니다.)");
	int key = _getch();
	while (key == 0) {
	}

	key = 0;

	p->food--;
	p->water--;

	dialogue_clear();

	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("체력이 부족할 경우, 치료제를 이용해서 체력을 채울 수 있다.");

	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("치료제를 사용할까? (사용 시 엔터키, 그냥 넘어갈시 ->방향키)");

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
	int yOffset = 0; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = 27;    // 텍스트 창 가로 길이
	int height = 26;                 // 텍스트 창 세로 길이

	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(xOffset + x, yOffset + y);
			if (y == 0) {
				if (x == 0) printf("┌");
				else if (x == width) printf("┐");
				else printf("─");
			}
			else if (y == height - 1) {
				if (x == 0) printf("└");
				else if (x == width) printf("┘");
				else printf("─");
			}
			else {
				if (x == 0 || x == width) printf("│");
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
	printf("식량 x %d", food);


	int water = p->water;
	for (int i = 0; i < 5; i++) {
		setCursorPosition(6, i + 5);
		for (int j = 0; j < 8; j++) {
			printf("%c", itemList2[0][i][j]);
		}
	}
	setCursorPosition(16, 8);
	printf("식수 x %d", water);

	int heal = p->medicine;
	for (int i = 0; i < 4; i++) {
		setCursorPosition(6, i + 10);
		for (int j = 0; j < 12; j++) {
			printf("%c", itemList2[2][i][j]);
		}
	}
	setCursorPosition(16, 12);
	printf("치료제 x %d", heal);

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
	printf("총알 x %d", bullet);






}


void printInformation2(player* p) {

	int hp = p->heart;
	int mp = p->mental;

	setCursorPosition(38, 3);
	printf("현재 남은 체력 x %d", hp);
	setCursorPosition(38, 5);
	printf("현재 스트레스 수치 x %d", mp);

}

// 텍스트 창 초기화 및 메시지 출력 함수
void draw_ready(player* p) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = STAGE_WIDTH;    // 텍스트 창 가로 길이
	int height = 20;                 // 텍스트 창 세로 길이
	// 텍스트 창 테두리와 제목 출력

	// 텍스트 창 테두리 그리기
	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(x, y);
			if (y == 0) {
				if (x == 0) printf("┌");
				else if (x == width) printf("┐");
				else printf("─");
			}
			else if (y == height - 1) {
				if (x == 0) printf("└");
				else if (x == width) printf("┘");
				else printf("─");
			}
			else {
				if (x == 0 || x == width) printf("│");
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




