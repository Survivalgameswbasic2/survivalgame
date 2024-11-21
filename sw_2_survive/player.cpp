#include "player.h"
#include "expire_tool.h"
#include <iostream>
#include "mutex_helper.h"
// 주인공 그리기 함수 (초록색)

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
	direction = 0;
	gun = 1;
}
