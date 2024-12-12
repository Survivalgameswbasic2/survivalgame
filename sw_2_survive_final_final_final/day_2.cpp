#include "expire_tool.h"
#include "player.h"
#include <string>
#include <conio.h>
#include <thread>
#include <iostream>
#include "bad_ending.h"
#include "game_map.h"
#include<chrono>
#include"zombie_move.h"
#include<vector>
#include <atomic>
#include "npc_image.h"
#include "backpack.h"
#include <windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
// day 2 대화문
std::vector<std::vector<std::string>> dialogue_2 = {
	// 초기 위치시 대화
	{
		"원래 여기는 캠핑장이었나보네... 하긴 이렇게 여기 강과 아름다운 자연의 흔적이 있으니까. 지금은 오염된 강과 말 그대로 흔적뿐이지만..",
		"아무튼 여기서 무전기 부품으로 쓸만한 것이든, 지연제 재료든, 식량이든 물이든, 구할 수 있는 것은 다 구하는거야!"
	},
	// 전단지 발견시 대화
	{
		"이건...앗 멀지 않은 곳에 도심이 있네? 게다가 거기에 피난처도 있다고?",
		"미쳐 다 빠져 나가지 못한 사람들이 서로 도우며 임시 피난처를 만든 건가?",
		"좋아. 슬슬 도심으로 나가도 되겠지. 그래 거기엔 분명 사람도 있을꺼야!",
		"슬슬 희망이 보이기 시작했어!"
	}
};

std::atomic<bool> terminateZombieThread2(false);
void zombieMoveThread2(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread2) {
		std::this_thread::sleep_for(std::chrono::seconds(1));

		// 좀비 이동	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}

	}
}
void start_day2(player* user, BackP* user_back) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(2, map);
	draw_map(map);         // 탐험 맵
	printstat(user); // 아이템 창 
	updateTextBox("");


	//좀비 생성
	std::vector<Zombie> zombies = {
		Zombie(13, 16, 1, 0, 2),
		Zombie(15, 14, 1, 0, 2),
		Zombie(14,15, 1, 0, 2),
		Zombie(16,13, 1, 0, 2),
		Zombie(3, 5, 1, 0, 2),
		Zombie(32, 1, 0, 1, 2),
		Zombie(26, 1, 0, 1, 2),
		Zombie(11, 18, 1,0, 2),
		Zombie(14, 4, 0, 1, 2),
		Zombie(13, 4, 0,1, 2),
		Zombie(18, 9, 1,0, 2),
		Zombie(21, 12, 1,0, 2)
	};
	std::thread zombieThread2(zombieMoveThread2, std::ref(zombies), map, user);


	user->player_x = 1;
	user->player_y = 1;
	printplayer();
	set_hour(9);
	std::thread timerThread(timer);

	int dialogue_line = 0;
	bool in_dialogue = true;
	int flag = 0;
	int dialogue_num = 0;
	map[user->player_y][user->player_x] = 'P';
	draw_map(map);
	set_isExplore(false);
	while (true) {
		map[user->player_y][user->player_x] = ' ';
		draw_sunlight(map);
		if (get_hour() == 21) {
			terminateZombieThread2 = true;
			if (zombieThread2.joinable()) {
				zombieThread2.join();
			}
			if (timerThread.joinable()) {
				timerThread.join();
			}
			bad_ending_time();
		}
		if (in_dialogue) {
			// 대화 중일 때
			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // 스페이스바로 대화 진행
					if (dialogue_line < dialogue_2[dialogue_num].size()) {
						updateDialogue(dialogue_2[dialogue_num][dialogue_line++]);
					}
					else {
						// 대화 종료
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
						if (dialogue_num > 1) {
							dialogue_num = 1;
						}
						clear_npc_screen();
						printplayer();
					}
				}
			}
			continue; // 대화 중에는 아래 로직을 무시하고 다음 루프로 이동
		}
		if (_kbhit()) {
			int key = _getch();

			if (key == 224) { // 방향키 입력 확인
				key = _getch();
				int newX = user->player_x, newY = user->player_y;
				switch (key) {
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}
				if (map[newY][newX] == '?') {
					stop_timer_running();
					terminateZombieThread2 = true;
					if (zombieThread2.joinable()) {
						zombieThread2.join();
					}
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
				// 이동 가능 여부 확인
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					map[newY][newX] == ' ' && !is_zombie_position(newX, newY, map)) {
					user->player_x = newX;
					user->player_y = newY;
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					map[newY][newX] == 'A' && !is_zombie_position(newX, newY, map)) {
					switch (user->direction) {
					case(1):
						if (map[newY + 1][newX] == ' ' || map[newY + 1][newX] == '%') {
							map[newY + 1][newX] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(2):
						if (map[newY][newX + 1] == ' ' || map[newY + 1][newX] == '%') {
							map[newY][newX + 1] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(3):
						if (map[newY - 1][newX] == ' ' || map[newY + 1][newX] == '%') {
							map[newY - 1][newX] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(4):
						if (map[newY][newX - 1] == ' ' || map[newY + 1][newX] == '%') {
							map[newY][newX - 1] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					}
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					map[newY][newX] == '%' && !is_zombie_position(newX, newY, map)) {
					user->player_x = newX;
					user->player_y = newY;
					user->sunlight++;
					if (user->sunlight >= 3) {
						user->sunlight = 0;
						user->heart--;
						printstat(user);
						PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
					}
					updateTextBox("으윽... 역시 햇빛은  따갑네 오래 있으면 안될 것 같아.");
				}
				else if (is_zombie_position(newX, newY, map)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
					updateTextBox("좀비에게 데미지를 입었다.");
					meet_zombie_change_edge();
				}
			}
			else if (key == ' ' && is_player_near_item(user, map, user_back)) { // 엔터키로 아이템 획득
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // 스페이스바로 NPC와 대화
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_2[dialogue_num][dialogue_line++]);
				in_dialogue = true; // 대화 상태 진입
				if (dialogue_num < 3) {
					clear_npc_screen();
					printnpc3();
				}
				else {
					clear_npc_screen();
					printnpc4();
				}
			}
			else if (key == '1') { // 아이템 사용
				if (user->food > 0) {
					user->food--;
					if (user->mode == 3) {
						user->mental -= 40;
						if (user->mental < 0) {
							user->mental = 0;
						}
					}
					else {
						user->mental -= 20;
						if (user->mental < 0) {
							user->mental = 0;
						}
					}
					updateTextBox("식량을 먹으니 한결 든든해진 기분이다.");
					printstat(user);
				}
				else {
					updateTextBox("먹을 수 있는 식량이 없다...");
				}
			}
			else if (key == '2') { // 아이템 사용
				if (user->medicine > 0) {
					user->medicine--;
					if (user->mode == 3) {
						user->heart += 2;
						if (user->heart > user->maxh) {
							user->heart = user->maxh;
						}
					}
					else {
						user->heart++;
						if (user->heart > user->maxh) {
							user->heart = user->maxh;
						}
					}
					printstat(user);
					updateTextBox("치료제를 사용하니 몸이 회복되는 것이 느껴진다.");
				}
				else {
					updateTextBox("사용할 수 있는 치료제가 없다...");
				}
			}
			if (is_player_near_zombie(user, map) == true) {
				user->mental += 2;
				printstat(user);
				updateTextBox("...불안해, 무서워... 아무리봐도 좀비는 적응이 안가네");
			}
		}
		if (user->heart <= 0) {
			stop_timer_running();
			terminateZombieThread2 = true;
			if (zombieThread2.joinable()) {zombieThread2.join();}
			if (timerThread.joinable()) {timerThread.join();}
			bad_ending_dead();
		}
		if (user->mental >= user->maxm) {
			stop_timer_running();
			terminateZombieThread2 = true;
			if (zombieThread2.joinable()) { zombieThread2.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			bad_ending_zombie();
		}
		map[user->player_y][user->player_x] = 'P';
		draw_map(map);
	}
}