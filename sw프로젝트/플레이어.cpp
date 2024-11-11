#include "플레이어.h"
#include "도구.h"
#include <iostream>

// 주인공 그리기 함수 (초록색)
void player::drawPlayer() {
	setCursorPosition(player_x * 2 + 1, player_y + 1); // 테두리 안쪽에 맞게 위치 조정
	setColor(10); // 초록색 플레이어
	std::cout << "■";
	setColor(7); // 기본 색상으로 복원
}

// 주인공 위치를 지우기 위한 함수
void player::clearPlayer() {
	setCursorPosition(player_x * 2 + 1, player_y + 1); // 테두리 안쪽에 맞게 위치 조정
	std::cout << "  "; // 기존 위치 지우기
}

void player::player_face() {
	setCursorPosition(75, 11);
	std::cout << "@@@@@@@@@--- --@@@@@@@@@@";
	setCursorPosition(75, 12);
	std::cout << "@@@@@@@@------- --@@@@@@@";
	setCursorPosition(75, 13);
	std::cout << "@@@@@@@--------- --@@@@@@";
	setCursorPosition(75, 14);
	std::cout << "@@@@@@@--------- --@@@@@@";
	setCursorPosition(75, 15);
	std::cout << "@@@@@@@---... -- --@@@@@@";
	setCursorPosition(75, 16);
	std::cout << "@@@@@@@            @@@@@@";
	setCursorPosition(75, 17);
	std::cout << "@@@@@@@   ○, , ○   @@@@@@";
	setCursorPosition(75, 18);
	std::cout << "@@@@@@@@@        @@@@@@@@";
	setCursorPosition(75, 19);
	std::cout << "@@@@@@@@@@      @@@@@@@@@";
	setCursorPosition(75, 20);
	std::cout << "@@@@@@@@@@      @@@@@@@@@";
	setCursorPosition(75, 21);
	std::cout << "@@@@@@@@@@@    @@@@@@@@@@";
	setCursorPosition(75, 22);
	std::cout << "@@@@@@@@@@@    @@@@@@@@@@";
	setCursorPosition(75, 23);
	std::cout << "@@@@@@@@@@@    @@@@@@@@@@";
	setCursorPosition(75, 24);
	std::cout << "@@@@@@@@          @@@@@@@";
	setCursorPosition(75, 25);
	std::cout << "@@@@@@@            @@@@@@";
}
player::player() {
	medicine = 0;
	heart = 5;
	mental = 5;
	food = 0;
	water = 0;
	bullet = 0;
	player_x = 1;
	player_y = 0;
}
