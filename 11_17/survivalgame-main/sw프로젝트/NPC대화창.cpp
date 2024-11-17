#include"도구.h"
#include <iostream>
#include "플레이어.h"
#define STAGE_WIDTH 70  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 
#define MAX_HEALTH 5    // 최대 체력
#define stat_Height 9 //스탯창이 끝나는 지점의 높이


// (74,10) ~ (102,26)

//  (74,10)----------------------------(102,10)

			//인물 얼굴
// (74, 20)
			// 응답창
// (74,26) ------------------------------(102,26)

void CommunicationBoxNPC(int flag, player*user) {
	setCursorPosition(STAGE_WIDTH + 4, stat_Height + 1);
	std::cout << "┌─────────────────────────┐";//27개 문자
	for (int i = 0; i < 16; i++) {//세로 10줄
		setCursorPosition(STAGE_WIDTH + 4, stat_Height + 2 + i);
		if (i == 10) {
			printf("├─────────────────────────┤");// 74, 20
		}
		else {
			printf("│                         │");
		}
	}
	setCursorPosition(STAGE_WIDTH + 4, stat_Height + 17);
	std::cout << "└─────────────────────────┘";
	//npc 만난 상태가 아니면 박스 삭제
	if (flag == 0) {
		user->player_face();
	}
	//npc 만난 상태이면 박스 생성
}