#define STAGE_WIDTH 70  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 

#include "도구.h"
#include <iostream>
#include <string>
//71, 0
//72
//73
//74
//75,0


// 텍스트 창 초기화 및 메시지 출력 함수
void updateTextBox(const char* message) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = STAGE_WIDTH;    // 텍스트 창 가로 길이
	int height = 5;                 // 텍스트 창 세로 길이

	// 텍스트 창 테두리와 제목 출력

	// 텍스트 창 테두리 그리기
	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(xOffset + x, yOffset + y + 1);
			if (y == 0) {
				if (x == 0) printf("┌");
				else if (x == width) printf("┐");
				else printf("─");
			}
			else if (y == height - 1) {
				if (x == 0) printf("└");
				else if (x == width ) printf("┘");
				else printf("─");
			}
			else {
				if (x == 0 || x == width) printf("│");
				else printf(" ");
			}
		}
	}
}
