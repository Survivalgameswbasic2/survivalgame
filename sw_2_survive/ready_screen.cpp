#include "expire_tool.h"
#include "item_image.h"
using namespace std;
#define STAGE_WIDTH 70  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 

void draw_ready_text() {

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
}
void draw_ready_map() {

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

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			setCursorPosition(x + i, y + j);
			printf("%c", itemList[0][x][y]);
		}
	}
}


// 텍스트 창 초기화 및 메시지 출력 함수
void draw_ready() {
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
	test_print(0, 0);

	draw_ready_text();
	draw_ready_map();

	//Sleep(500);

}

