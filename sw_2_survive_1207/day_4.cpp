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
std::vector<std::vector<std::string>> dialogue_4 = {
	{
	"플레이어: 여기에 무기가 있다는 건가. 좋아 열심히 찾아보자"
},
{
	"생존자: 앗 사람이다! 저기요 여기 좀 도와주세요!",
	"플레이어: ...여기에 왜 있었죠?",
	"생존자: 일단 도와주셔서 감사합니다.",
	"생존자: 저도 일단 여기서 탐사하며 하루하루를 겨우 살아가는 사람인데요.",
	"생존자: 갑자기 그렇게 많은 좀비는 처음이라 그 좀비들로부터 도망다니다 여기면 안전하지 않을까 하고, 아무래도 경찰서다 보니까.",
	"플레이어: 좀비 사태 전에 제일 안전한 곳으로 본능적으로 움직인 것 같네요.",
	"생존자: 네 그렇게 도망쳐 와보니 여기 경찰서에요.",
	"생존자: 그나저나 아까도 사람이 지나갔는데 그냥 지나가서 실망했는데 이번엔 다행이네요.",
	"플레이어: 아까도 사람이 지나갔다고요?",
	"생존자: 네 정확하게는 이 동네에서 유명한 사기꾼인데 저도 당해봐서 알아요.",
	"생존자: 워낙 개인주의적인 사람이라 자신에게 도움되지 않는 행동은 철저히 무시하는 사람이에요.",
	"플레이어: ...그 사람 어디로 갔는지 아나요?",
	"생존자: 그 사기꾼이요? 아. 혹시 당신도...",
	"생존자: 네 알려드릴게요. 정확히는 모르지만 그 사람은 보통 이 근처 학교에 은신처를 삼고 활동해요. 근처엔 좀비도 많고, 은신처로 갈 때 갖가지 장애물이 있어서 아무도 빼앗긴 물건을 되찾을 생각을 안 해서 문제지만.",
	"플레이어: 그럼 학교로 가면 그 녀석을 만날 수 있다는 거죠? 정보 감사합니다.",
	"생존자: 아 네. 제가 더 감사하죠. 꼭 물건 되찾길 바랄게요! 행운을 빕니다.",
	"플레이어: 그리고 여기 이쪽으로 가면 피난처가 있다고 해요. 그쪽으로 가세요.",
	"생존자: 앗 정보 감사합니다. 확실히 그쪽으로 갈 생각은 못 하긴 했어요. 그럼 먼저 피난처로 가겠습니다. 정말 감사합니다!"
}
};

std::string gun_dialogue = {
	"플레이어:　좋아 이제 총을 얻었으니 탄창만 있으면 좀비를 쓰러뜨릴수 있을 지도 몰라! 빨리 그 사기꾼을 찾아 내 물품을 되찾아야겠어."
};
static std::vector<Zombie> zombies = {
		Zombie(6,1,0,1,4),Zombie(3,5,1,0,4),Zombie(1,7,1,0,4) ,	Zombie(8, 9,1,0,4),Zombie(1, 10,1,0,4),Zombie(10, 7,1,0,4) ,Zombie(15, 5,1,0,4)
		,Zombie(20, 5,0,1,4) ,Zombie(27, 14,1,0,4) ,Zombie(31,12,0,1,4) ,Zombie(32, 12,0,1,4) ,Zombie(5, 17,1,0,4),Zombie(6, 17,1,0,4),Zombie(24, 10,0,1,4),
		Zombie(13, 9,1,0,4),Zombie(13, 13,1,0,4) ,Zombie(24, 14,1,0,4) ,Zombie(18, 10,1,0,4),Zombie(16, 9,0,1,4) ,	Zombie(27, 9,0,1,4)
};

std::atomic<bool> terminateZombieThread4(false);
void zombieMoveThread4(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread4) {
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
static void move_bullets(char map[MAP_HEIGHT][MAP_WIDTH + 1],player*user) {
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
					if ((*zIt).x==b.x && (*zIt).y== b.y) {
						map[zIt->y][zIt->x] = ' ';
						zIt = zombies.erase(zIt);
						hit = true;
						break;
					}
					else if (map[b.y][b.x] =='#') {
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


void start_day4(player* user, BackP* user_back) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(4, map);
	draw_map(map);         // 탐험 맵
	printstat(user); // 아이템 창 
	updateTextBox("");

	//좀비 생성
	std::thread zombieThread4(zombieMoveThread4, std::ref(zombies), map, user);
	std::thread bulletMoveThread(move_bullets, map,user);
	user->player_x = 1;
	user->player_y = 1;
	printplayer();
	set_hour(9);
	std::thread timerThread(timer);

	bool is_food_water_get = false;
	int dialogue_line = 0;
	bool in_dialogue = true;
	int flag = 0;
	int dialogue_num = 0;
	bool get_gun_dialogue = false;
	map[user->player_y][user->player_x] = 'P';
	while (true) {
		map[user->player_y][user->player_x] = ' ';
		draw_sunlight(map);
		if (get_hour() == 21) {
			terminateZombieThread4 = true;
			if (zombieThread4.joinable()) {zombieThread4.join();}
			if (timerThread.joinable()) {timerThread.join();}
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			break;
		}
		if (in_dialogue) {
			// 대화 중일 때
			
			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // 스페이스바로 대화 진행
					if (dialogue_line < dialogue_4[dialogue_num].size()) {
						updateDialogue(dialogue_4[dialogue_num][dialogue_line++]);
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
							if (is_food_water_get == false) {
								user->food++;
								user->water++;
								is_food_water_get = true;
								printstat(user);
							}
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
				case 72: newY--; playerDirection = 0; break; // 위쪽 방향
				case 80: newY++; playerDirection = 1; break; // 아래쪽 방향
				case 75: newX--; playerDirection = 2; break; // 왼쪽 방향
				case 77: newX++; playerDirection = 3; break; // 오른쪽 방향
				}
				if (map[newY][newX] == '?') {
					stop_timer_running();
					terminateZombieThread4 = true;
					if (zombieThread4.joinable()) { zombieThread4.join(); }
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
			else if (key == 's' && user->bullet > 0 && user->gun>=1) { // 's' 키로 총알 발사
				std::lock_guard<std::mutex> lock(bulletMutex);
				user->bullet--;
				bullets.push_back({ user->player_x, user->player_y, playerDirection, 0 });
			}
			else if (key == ' ' && is_player_near_item(user,map, user_back)) { // 엔터키로 아이템 획득
				map[newY][newX] = ' ';
				if (user->gun == 1 && get_gun_dialogue == false) {
					get_gun_dialogue = true;
					updateDialogue(gun_dialogue);
				}
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // 스페이스바로 NPC와 대화
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_4[dialogue_num][dialogue_line++]);
				in_dialogue = true; // 대화 상태 진입
			}
			if (is_player_near_zombie(user, map) == true) {
				user->mental -= 2;
				printstat(user);
				updateTextBox("...불안해, 무서워... 아무리봐도 좀비는 적응이 안가네");
			}
		}
		if (user->heart <= 0) {
			stop_timer_running();
			terminateZombieThread4 = true;
			if (zombieThread4.joinable()) { zombieThread4.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			bad_ending_zombie();
		}
		if (user->mental <= 0) {
			stop_timer_running();
			terminateZombieThread4 = true;
			if (zombieThread4.joinable()) { zombieThread4.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			bad_ending_starve();
		}
		map[user->player_y][user->player_x] = 'P';
		draw_map(map);
	}
}