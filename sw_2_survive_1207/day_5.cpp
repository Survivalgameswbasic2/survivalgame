#include "expire_tool.h"
#include "player.h"
#include <string>
#include <conio.h>
#include <thread>
#include <iostream>
#include "bad_ending.h"
#include "game_map.h"
#include <vector>
#include<chrono>
#include"zombie_move.h"
#include <atomic>
#include "npc_image.h"
#include <mutex>
#include "mutex_helper.h"
#include "backpack.h"
#define MAP_WIDTH 34
#define MAP_HEIGHT 20

// day 4 대화문
std::vector<std::vector<std::string>> dialogue_5 = {
	{
	"배신자: 아니 여긴 어떻게?",
"생존자: 오직 분노의 감정을 가지고 여기까지 왔다. 빨리 내 물건 돌려줘!",
"배신자: 돌려줄거 같으면 뺏지도 않았겠지. 되찾고 싶으면 너도 다시 뺏으면 돼.",
"생존자: ...그래 끝까지 가보자.",
"배신자: 그래 그거야. 이제야 생존에 특화된 눈을 뜨게 되었구만. 덤벼라, 좀비 세상에서의 주적은 좀비가 아니라 인간이다.",
"생존자: 그래... 어느정도 동의하게 되었다. 너 때문에 좀비보다 무서운건 인간이란걸!"
},
{
"배신자: 윽, 나도 여기까진가...",
"생존자: ...왜 이렇게 까지 하는거야. 너도 살아남고 다른 삶도 살아남는 방법이 있었을거 아니야.",
"배신자: 아직도 약한 소리를 하고 있구나. 있다고 하더라도 확률이 높은걸 선택해야지.",
"배신자: 난 확률이 높은 방식으로 살아남았다. 배신하며, 혼자서 돌아다니며 남을 희생하면서.",
"생존자: 끝까지 쓰레기군.",
"배신자: 그래 쓰레기는 여기서 퇴장하는게 맞나보군. 하지만 기억해라 언젠간 너도 쓰레기가 될 수 있다는 것을",
"생존자: 나는 너처럼은 되지 않을 거다. 인간의 감정을 버리지 않을 거야.",
"배신자: 나는 감정을 버린 사람인것처럼 말하는군, 뭐 어느 정돈 맞지만.",
"배신자: 생존을 위해선 나처럼 연민, 애정 같은 쓸데없는 감정을 버려라. 내 마지막 충고다.",
"생존자: 꺼져, 이제 너 말은 듣지 않겠다.",
"배신자: ...맘대로 해라",
"생존자: 잘가라, 다신 보지 말자."
}
};
static std::vector<Zombie> zombies = {
		Zombie(7,7,0,1,5),Zombie(7,12,1,0,5),Zombie(1,18,1,0,5),Zombie(8,17,1,0,5),
		Zombie(10,13,0,1,5),Zombie(10,10,1,0,5),Zombie(13,2,0,1,5),Zombie(23,5,1,0,5),
		Zombie(23,10,1,0,5),Zombie(31,18,0,1,5),Zombie(24,17,1,0,5),Zombie(16,14,1,0,5),
		Zombie(14,7,1,0,5),Zombie(15,7,1,0,5),Zombie(28,2,0,1,5),Zombie(25,13,1,0,5),
		Zombie(23,16,1,0,5)
};


std::atomic<bool> terminateZombieThread5(false);
void zombieMoveThread5(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread5) {
		// 1초마다 좀비를 이동
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 대기

		// 좀비 이동	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}
	}
}
static int playerDirection = 3; // 0: 위, 1: 아래, 2: 왼쪽, 3: 오른쪽 (초기 값은 오른쪽)

static struct Bullet {
	int x;
	int y;
	int direction;
	int distanceTraveled;
};

static std::vector<Bullet> bullets;
static std::mutex bulletMutex;
static void move_bullets(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 0.1초 대기
		std::lock_guard<std::mutex> lock(bulletMutex);

		for (auto it = bullets.begin(); it != bullets.end();) {
			Bullet& b = *it;

			// 현재 총알 위치 지움
			map[b.y][b.x] = ' ';

			// 방향에 따라 이동
			switch (b.direction) {
			case 0: b.y--; break;
			case 1: b.y++; break;
			case 2: b.x--; break;
			case 3: b.x++; break;
			}

			b.distanceTraveled++;

			// 충돌 감지
			bool hit = false;
			{
				std::lock_guard<std::mutex> zombieLock(zombieMutex2);
				for (auto zIt = zombies.begin(); zIt != zombies.end();) {
					if ((*zIt).x == b.x && (*zIt).y == b.y) {
						map[zIt->y][zIt->x] = ' ';
						zIt = zombies.erase(zIt);
						hit = true;
						break;
					}
					else if (map[b.y][b.x] == '#') {
						hit = true;
						break;
					}
					else {
						++zIt;
					}
				}
			}

			// 충돌 또는 경계 초과 처리
			if (hit || b.x < 0 || b.x >= MAP_WIDTH || b.y < 0 || b.y >= MAP_HEIGHT || b.distanceTraveled > 7) {
				it = bullets.erase(it);
				continue;
			}

			// 맵에 총알 위치 표시
			map[b.y][b.x] = '*';
			++it;
		}
	}
}


void start_day5(player* user, BackP* user_back) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(5, map);
	draw_map(map);         // 탐험 맵
	printstat(user); // 아이템 창 
	updateTextBox("");

	//좀비 생성
	std::thread zombieThread5(zombieMoveThread5, std::ref(zombies), map, user);
	std::thread bulletMoveThread(move_bullets, map, user);
	user->player_x = 1;
	user->player_y = 1;
	printplayer();
	set_hour(9);
	std::thread timerThread(timer);

	bool is_food_water_get = false;
	int dialogue_line = 0;
	bool in_dialogue = false;
	int flag = 0;
	int dialogue_num = 0;
	map[user->player_y][user->player_x] = 'P';
	while (true) {
		if (user->flag == 1) {
			in_dialogue = true;
			user->flag = 0;
		}
		map[user->player_y][user->player_x] = ' ';
		draw_sunlight(map);
		if (get_hour() == 21) {
			terminateZombieThread5 = true;
			if (zombieThread5.joinable()) { zombieThread5.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			break;
		}
		if (in_dialogue) {
			// 대화 중일 때

			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // 스페이스바로 대화 진행
					if (dialogue_line < dialogue_5[dialogue_num].size()) {
						updateDialogue(dialogue_5[dialogue_num][dialogue_line++]);
					}
					else {
						// 대화 종료
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
						if (dialogue_num == 1) {
							map[7][2] = ' ';
							map[16][19] = 'N';
						}
						if (dialogue_num == 2) {
							dialogue_num = 1;
						}
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
					terminateZombieThread5 = true;
					if (zombieThread5.joinable()) { zombieThread5.join(); }
					if (timerThread.joinable()) { timerThread.join(); }
					if (bulletMoveThread.joinable()) bulletMoveThread.join();
					break;
				}
				// 이동 가능 여부 확인
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					map[newY][newX] == ' ' && !is_zombie_position(newX, newY, map)) {
					user->player_x = newX;
					user->player_y = newY;
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					map[newY][newX] == 'A') {
					switch (user->direction) {
					case(1):
						if (map[newY + 1][newX] == ' ' || map[newY + 1][newX] == '%') {
							map[newY + 1][newX] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(2):
						if (map[newY][newX + 1] == ' ' || map[newY][newX + 1] == '%') {
							map[newY][newX + 1] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(3):
						if (map[newY - 1][newX] == ' ' || map[newY - 1][newX] == '%') {
							map[newY - 1][newX] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(4):
						if (map[newY][newX - 1] == ' ' || map[newY][newX - 1] == '%') {
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
					user->mental--;
					updateTextBox("으윽... 역시 햇빛은  따갑네 오래 있으면 안될 것 같아.");
				}
				else if (is_zombie_position(newX, newY, map)) {
					user->heart--;
					printstat(user);
					updateTextBox("크흑, 좀비한테 당했어");
					meet_zombie_change_edge();
				}
			}
			else if (key == 's' && user->bullet > 0 && user->gun >= 1) { // 's' 키로 총알 발사
				std::lock_guard<std::mutex> lock(bulletMutex);
				user->bullet--;
				bullets.push_back({ user->player_x, user->player_y, user->direction, 0 });
			}
			else if (key == ' ' && is_player_near_item(user, map, user_back)) { // 엔터키로 아이템 획득
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // 스페이스바로 NPC와 대화
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_5[dialogue_num][dialogue_line++]);
				in_dialogue = true; // 대화 상태 진입
			}
			if (is_player_near_zombie(user, map) == true) {
				user->mental -= 2;
				printstat(user);
				updateTextBox("...불안해, 무서워... 아무리봐도 좀비는 적응이 안가네");
			}
			is_player_near_explosive_zombie(user,map);
		}
		if (user->heart <= 0) {
			stop_timer_running();
			terminateZombieThread5 = true;
			if (zombieThread5.joinable()) { zombieThread5.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			bad_ending_zombie();
		}
		if (user->mental <= 0) {
			stop_timer_running();
			terminateZombieThread5 = true;
			if (zombieThread5.joinable()) { zombieThread5.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			bad_ending_starve();
		}
		map[user->player_y][user->player_x] = 'P';
		draw_map(map);
	}
}