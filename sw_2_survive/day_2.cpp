#include "expire_tool.h"
#include "player.h"
#include <string>
#include <conio.h>
#include <thread>
#include <iostream>
#include "bad_ending.h"
#include "game_map.h"
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
// day 2 대화문
std::string dialogue_2[] = {
	"“원래 여기는 캠핑장 이었나보네... 하긴 이렇게 여기 강과 아름다운 자연의 흔적이 있으니까. 지금은 오염된 강과 말그대로 흔적뿐이지만..”",
	"“아무튼 여기서 무전기 부품으로 쓸만한 것이든, 지연제 재료든, 식량이든 물이든, 구할 수 있는 것은 다 구하는거야!”",
	"",
	"전단지 발견:",
	"“이건...앗 멀지 않은 곳에 도심이 있네? 게다가 거기에 피난처도 있다고? 미쳐 다 빠져 나가지 못한 사람들이 서로 도우며 임시 피난처를 만든 건가?”",
	"“좋아. 슬슬 도심으로 나가도 되겠지. 그래 거기엔 분명 사람도 있을꺼야!”",
	"“슬슬 희망이 보이기 시작했어!”"
};


void start_day2(player* user) {
	//3시
	system("cls");
	draw_map(4);         // 탐험 맵
	printstat(user); // 아이템 창 
	updateTextBox("");
	user->player_x = 1;
	user->player_y = 1;
	std::thread timerThread(timer);
	int dialogue_line = 0;
	int founded_item_count = 0;
	user->drawPlayer();// 초기 위치에 주인공 그리기
	draw_clock(3);
	int flag=0;
	while (true) {
		if (_kbhit()) {
			if (is_mission_failed() == 1) {
				if (timerThread.joinable()) {
					timerThread.join();
				}
				break;
			}
			int key = _getch();

			if (key == 224) { // 방향키 입력 확인
				key = _getch();

				user->clearPlayer();
				int newX = user->player_x, newY = user->player_y;
				switch (key) {
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}
				if (flag == 1) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y + 1);
					setColor(6); std::cout << "●"; setColor(7);
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
					flag = 0;
				}
				// 이동 가능 여부 확인
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[4][newY][newX] == ' ' && !is_zombie_position(newX, newY, 4)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[4][newY][newX] == '%' && !is_zombie_position(newX, newY, 4)) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY, 1)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					updateTextBox("으윽");

					if (user->heart == 0) {
						bad_ending();
					}
				}

				user->drawPlayer();
			}
			else if (key == ' ' && is_player_near_item(user, 4)) { // 엔터키로 아이템 획득
				game_map[4][newY][newX] = ' ';
				founded_item_count++;
				draw_map(4);
				user->drawPlayer();
				if (founded_item_count == 2) {//아이템개수
					updateTextBox("");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, 4)) { // 스페이스바로 NPC와 대화
				dialogue_clear();
				updateDialogue(dialogue_2[dialogue_line++]);
			}
		}
	}
	//6시
	system("cls");
	draw_map(5);         // 탐험 맵
	printstat(user); // 아이템 창 
	updateTextBox("");
	user->player_x = 5;
	user->player_y = 6;
	start_timer_running();
	dialogue_line = 0;
	founded_item_count = 0;
	user->drawPlayer();// 초기 위치에 주인공 그리기
	draw_clock(6);
	flag = 0;
	while (true) {
		if (_kbhit()) {
			if (is_mission_failed() == 1) {
				if (timerThread.joinable()) {
					timerThread.join();
				}
				break;
			}
			int key = _getch();

			if (key == 224) { // 방향키 입력 확인
				key = _getch();

				user->clearPlayer();
				int newX = user->player_x, newY = user->player_y;
				switch (key) {
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}
				if (flag == 1) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y + 1);
					setColor(6); std::cout << "●"; setColor(7);
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
					flag = 0;
				}
				// 이동 가능 여부 확인
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[5][newY][newX] == ' ' && !is_zombie_position(newX, newY, 5)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[5][newY][newX] == '%' && !is_zombie_position(newX, newY, 5)) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY, 5)) {
					user->heart--;
					printstat(user);
					setCursorPosition(2, 23);
					updateTextBox("으윽");

					if (user->heart == 0) {
						bad_ending();
					}
				}

				user->drawPlayer();
			}
			else if (key == ' ' && is_player_near_item(user, 5)) { // 엔터키로 아이템 획득
				game_map[5][newY][newX] = ' ';
				founded_item_count++;
				draw_map(5);
				user->drawPlayer();
				if (founded_item_count == 4) {//아이템개수
					updateTextBox("");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, 5)) { // 스페이스바로 NPC와 대화
				dialogue_clear();
				updateDialogue(dialogue_2[dialogue_line++]);
			}
		}
	}
	//9시
	system("cls");
	draw_map(6);         // 탐험 맵
	printstat(user); // 아이템 창 
	updateTextBox("");
	user->player_x = 5;
	user->player_y = 6;
	start_timer_running();
	dialogue_line = 0;
	founded_item_count = 0;
	user->drawPlayer();// 초기 위치에 주인공 그리기
	draw_clock(9);
	flag = 0;
	while (true) {
		if (_kbhit()) {
			if (is_mission_failed() == 1) {
				if (timerThread.joinable()) {
					timerThread.join();
				}
				break;
			}
			int key = _getch();

			if (key == 224) { // 방향키 입력 확인
				key = _getch();

				user->clearPlayer();
				int newX = user->player_x, newY = user->player_y;
				switch (key) {
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}
				if (flag == 1) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y + 1);
					setColor(6); std::cout << "●"; setColor(7);
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
					flag = 0;
				}
				// 이동 가능 여부 확인
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[6][newY][newX] == ' ' && !is_zombie_position(newX, newY, 6)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[6][newY][newX] == '%' && !is_zombie_position(newX, newY, 6)) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY, 6)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					updateTextBox("으윽");

					if (user->heart == 0) {
						bad_ending();
					}
				}

				user->drawPlayer();
			}
			else if (key == ' ' && is_player_near_item(user, 6)) { // 엔터키로 아이템 획득
				game_map[6][newY][newX] = ' ';
				founded_item_count++;
				draw_map(6);
				user->drawPlayer();
				if (founded_item_count == 4) {//아이템개수
					updateTextBox("");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, 6)) { // 스페이스바로 NPC와 대화
				dialogue_clear();
				updateDialogue(dialogue_2[dialogue_line++]);
			}
		}
	}
}