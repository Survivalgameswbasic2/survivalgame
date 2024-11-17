#include <iostream>
#include "도구.h"

#define STAGE_WIDTH 70  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 

using namespace std;

// 탐험 맵과 테두리 그리기 함수
void drawStage() {
	// 테두리 상단
	for (int i = 0;i <= STAGE_HEIGHT;i++) {
		for (int j = 0;j <= STAGE_WIDTH;j++) {
			setCursorPosition(j, i);
			if (i == 0 && j == 0) {
				cout << " ";
			}
			else if (i == 0 && j == STAGE_WIDTH) {
				cout << " ";
			}
			else if (i == STAGE_HEIGHT && j == 0) {
				cout << " ";
			}
			else if (i == STAGE_HEIGHT && j == STAGE_WIDTH) {
				cout << " ";
			}
			else if (i == 0|| i == STAGE_HEIGHT) {
				cout <<  "";
			}
			else if (j == 0 || j == STAGE_WIDTH) {
				cout << " ";
			}
		}
	}
}
