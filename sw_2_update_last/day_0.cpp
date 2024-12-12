#include "expire_tool.h"
#include "player.h"
#include <string>
#include <conio.h>
#include <thread>
#include <iostream>
#include "bad_ending.h"
#include "game_map.h"
#include "npc_image.h"
#include<chrono>
#include"zombie_move.h"
#include<vector>
#include <atomic>
#include "backpack.h"
#include <windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
// day 0 대화문
std::vector<std::vector<std::string>> dialogue_0 = {
	{
		"플레이어: \"으으 머리야\"",
		"플레이어: \"여긴 어디지? 주변이 캄캄해\"",
		"플레이어: \"내가 왜 여기에 있는거지?\"",
		"플레이어: \"....윽 기억이 안나\"",
		"플레이어: \"...일단 주변을 살펴보자\""
	},
	{
		"npc: \"아악! 누구세요? 엣 사람? 사람이 왜 여기에? 아니 어떻게 여기에?\"",
		"플레이어: \"혹시 사람이세요? 그렇겐 안보이는데...\"",
		"npc: \"....사람이거든요. 그쪽은 어떻게 여기에 왔는데요?\"",
		"플레이어: \"...기억은 없어요. 그저.... 도망쳐왔다는 기억밖엔...\"",
		"npc: \"...그렇군요. 그럼 일단 제가 도와줄게요.\"",
		"npc: \"일단 배고프실테니 여기 있는 식량부터.. 앗 없어졌네? 혹시 이미 가져가신...것 같군요. 손버릇이 안좋네요.\"",
		"플레이어: \"살기위해선 모든지 해야합니다.\"",
		"npc: \"....네.  일단 여기는 제가 피난해있는 동굴이에요.\"",
		"npc: \"여기라고 안전한 곳은 아니지만, 그래도 바깥 세상보단 나으니까요.\"",
		"npc: \"뭐 일단 설명을 이것저것 드릴게요\"",
		"npc: \"제 설명이 튜토리얼 같아보여도 참으세요\"",
		"npc: \"일단 여기 주변의 좀비들은 움직이진 않으니까 안심하세요.\"",
		"npc: \"그렇다고 너무 가까이 다가가면 공격하니까 조심하시고요.\"",
		"npc: \"일단 생존하려면 당연히 잘자고, 잘 먹어야겠죠? 잘이라는 말을 붙이기엔 상황이 안좋지만..\"",
		"npc: \"아무튼 일단 식량이 바닥났어요. 사실 아까께 마지막 물과 식량이었는데 당신한테 양보한거라구요?\"",
		"npc: \"그래서 밖에 나가서 식량, 물 등을 구해와야해요. 물론 좀비들을 피해서요.\"",
		"npc: \"여기는 잠을 자거나 휴식공간으로 쓰셔도 상관없어요.\"",
		"npc: \"네 당연히 저도 식량과 물을 구하려 나가봐야죠.\"",
		"npc: \"...밖은 위험해요... 당장에 좀비부터 왠지 모르겠지만 햇빛도 너무 쎄요. 오존층이 파괴된건지... 햇빛에 너무 오래 있지 마세요.\"",
		"npc: \"일단 당신은 오늘 일어났다고 하셨으니 여기서 쉬세요. 저는 먼저 제가 먹을 물과 식량을 구하러 떠날게요.\"",
		"npc: \"네? 식량이나 물을 나눠먹으면 되지 않냐고요?\"",
		"npc: \"...일단 물은 하루에 500ml이상 먹지 않으면 진짜 위험해져요.. 제가 겪어봐서 알아요. 식량은 하루정돈 괜찮지만.. 정신적으로 뭔가...\"",
		"npc: \"그러니 식량은 일단 그렇다 쳐도 물은 무조건 구해야하기 때문에 가야만해요.\"",
		"npc: \"...그럼 이만\"",
		"플레이어: \"후 그래 내가 어떻게 여기에 왔는지 기억도 안나지만, 일단 살아야지. 그래 나도 내일부터 다시 돌아다녀 보자.\"",
		"플레이어: \"정리하자면. 매일 좀비를 피해 물과 식량을 얻고, 정보를 얻어서 좀비가 없는 안전한 곳으로 가면 되겠지?\"",
		"플레이어: \"일단 여기 동굴을 안식처로 삼고 행동하자.\""
	},
};


std::atomic<bool> terminateZombieThread0(false);
void zombieMoveThread0(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread0) {
		// 1초마다 좀비를 이동
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 대기

		// 좀비 이동	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}

	}
}
void start_day0(player* user, BackP* user_back) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(0, map);
	draw_map(map);         // 탐험 맵
	printstat(user); // 아이템 창 
	updateTextBox("");
	printplayer();

	user->player_x = 5;
	user->player_y = 6;
	//좀비 생성
	std::vector<Zombie> zombies = {
		Zombie(9, 7, 1, 0, 0)
	};
	std::thread zombieThread0(zombieMoveThread0, std::ref(zombies), map, user);


	set_hour(9);
	std::thread timerThread(timer);

	int dialogue_line = 0;
	bool in_dialogue = true;
	int flag = 0;
	int dialogue_num = 0;
	map[user->player_y][user->player_x] = 'P';
	draw_map(map);
	while (true) {
		map[user->player_y][user->player_x] = ' ';
		draw_sunlight(map);
		if (get_hour() == 21) {
			terminateZombieThread0 = true;
			if (zombieThread0.joinable()) {
				zombieThread0.join();
			}
			if (timerThread.joinable()) {
				timerThread.join();
			}
			break;
		}
		if (in_dialogue) {
			// 대화 중일 때
			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // 스페이스바로 대화 진행
					if (dialogue_line < dialogue_0[dialogue_num].size()) {
						updateDialogue(dialogue_0[dialogue_num][dialogue_line++]);
					}
					else {
						// 대화 종료
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
						if (dialogue_num == 2) {
							dialogue_num = 1;
						}
						clear_npc_screen();
						printplayer();
						terminateZombieThread0 = false;
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
				case 72: newY--; user->direction = 3; break;
				case 80: newY++; user->direction = 1; break;
				case 75: newX--; user->direction = 4; break;
				case 77: newX++; user->direction = 2; break;
				}
				if (map[newY][newX] == '?') {
					stop_timer_running();
					terminateZombieThread0 = true;
					if (zombieThread0.joinable()) {
						zombieThread0.join();
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
						if (map[newY + 1][newX] == ' '||map[newY + 1][newX] =='%') {
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
					user->heart--;
					printstat(user);
					PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
					updateTextBox("으윽... 역시 햇빛은  따갑네 오래 있으면 안될 것 같아.");
				}
				else if (is_zombie_position(newX, newY, map)) {
					user->heart--;
					printstat(user);
					PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
					updateTextBox("크흑, 좀비한테 당했어");
					meet_zombie_change_edge();
				}
			}
			else if (key == ' ' && is_player_near_item(user,map, user_back)) { // 엔터키로 아이템 획득
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // 스페이스바로 NPC와 대화
				set_isExplore(false);
				terminateZombieThread0 = true;
				dialogue_clear();
				updateDialogue(dialogue_0[dialogue_num][dialogue_line++]);
				in_dialogue = true; // 대화 상태 진입
				clear_npc_screen();
				printnpc2();
				
			}
			else if (key == '1') { // 아이템 사용
				if (user->food > 0) {
					user->food--;
					if (user->mode == 3) {
						user->mental += 40;
						if (user->mental > user->maxm) {
							user->mental = user->maxm;
						}
					}
					else {
						user->mental += 20;
						if (user->mental > user->maxm) {
							user->mental = user->maxm;
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
							user->heart > user->maxh;
						}
					}
					else {
						user->heart++;
						if (user->heart > user->maxh) {
							user->heart > user->maxh;
						}
					}
					printstat(user);
					updateTextBox("치료제를 사용하니 몸이 회복되는 것이 느껴진다.");
				}
				else {
					updateTextBox("사용할 수 있는 치료제가 없다...");
				}
			}
			if (is_player_near_zombie(user,map) == true) {
				user->mental -= 2;
				printstat(user);
				updateTextBox("...불안해, 무서워... 아무리봐도 좀비는 적응이 안가네");
			}
		}
		if (user->heart <= 0) {
			stop_timer_running();
			terminateZombieThread0 = true;
			if (zombieThread0.joinable()) {
				zombieThread0.join();
			}
			if (timerThread.joinable()) {
				timerThread.join();
			}
			bad_ending_zombie();
		}
		if (user->mental <= 0) {
			stop_timer_running();
			terminateZombieThread0 = true;
			if (zombieThread0.joinable()) {zombieThread0.join();}
			if (timerThread.joinable()) {timerThread.join();}
			bad_ending_zombie();
		}
		map[user->player_y][user->player_x] = 'P';
		draw_map(map);
	}
}