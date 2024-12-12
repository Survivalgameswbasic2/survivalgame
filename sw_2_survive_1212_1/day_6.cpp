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
#include <windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;
#define MAP_WIDTH 34
#define MAP_HEIGHT 20

//npc 대화 후 사라지게 조절
std::vector<std::vector<std::string>> dialogue_6 = {
	{
"플레이어: 후, 이제 배신자를 처치해서 내 물건도 되찾았고, 이제 무전기 부품도 거의 다 모아 간다.",
"플레이어: 일단 다시 첫날에 봤던 사람한테 가서 이후에 어떻게 해야 하는지 물어봐야겠어",
"플레이어: ....외딴집에 도착했긴 했지만, 사람이 아무도 없잖아?",
"플레이어: 여기 숨겨진 문이 있네. 원래 여기에 벽이었는데 부서진 흔적이 있어...",
"플레이어: 일단 들어가서 사람을 찾아보자",
"플레이어: ...뭐야 여기, 여러 가지 실험의 흔적과 좀비... 여기 연구 시설이었어?"
},
{
"생존자: ...살려",
"플레이어: “당신은 동굴에서 봤던? 무슨 일이세요?",
"생존자: ...사실 나 좀비한테 당했나봐. 언제 당한진 모르겠지만.",
"생존자: 너랑 헤어지고 돌아다니다가 어느 순간 갑자기 분노, 슬픔 등 감정이 요동치는 것을 느꼈어.",
"생존자: 그러다 좀비와 맞설 때 갑자기 몸과 뇌에 이상이 생김을 인지하게 됐어.",
"생존자: 좀비를 피하는게 아닌 부숴버리고 싶다고 생각하면서 충동적으로 돌진했거든.",
"플레이어: 감정이 요동친다는 건가요?",
"생존자: 그래, 내가 이상하다는 것을 느끼고 여기 외딴집으로 몸을 숨겼고 여기 우연히 연구원과 만나 여러 가지 돕고 있었지.",
"플레이어 : 그럼 여기 있던 사람이 연구원이었던 건가요? 그래서 여기서 좀비를 연구했구나.",
"생존자 : 너도 아는 사람이었니? 아무튼 연구원과 내 몸 상태를 살피면서 확인된건, 좀비는 햇빛을 받으면 머리에 고통이 와 회피한다. 사실 오존층 파괴 이런건 없었던 거지.",
"생존자: 그리고 좀비는 감정이 있는 존재에게 충동적으로 이끌린다. 좀비는 감정과 이성이 마비된 상태, 그래서 감정을 원해서 이끌리는 것 같아.",
"생존자: 난 이미 좀비에 당한 상태였고, 그래서 햇빛과, 감정이 요동쳤던거지..",
"플레이어: 잠시만요, 그말이 사실인가요?",
"생존자: 여러 실험을 했을 땐 사실이야. 감염됐어도 일반 사람과 차이없지만 특정 사건으로 감정이 요동치면 점점 좀비화가 되는 모양이야.",
"생존자: 그래서 감정을 관리를 잘하거나, 좀비가 되기 전에 감정과 관련된 정신적 치료를 받게 되면 어느 정도 호전되는 것도 확인했어.",
"플레이어: 아니 잠시만요, 지금까지 말을 종합하면 저도...",
"생존자: 확실하지 않지만, 확률은 높지.",
"플레이어: 저는 기억도 나지 않은데..",
"생존자: 나도 언제 물린지도 몰랐어. 감염 경로는 아직 미지수야",
"플레이어: 그럴 수가... 그럼 전 대체...",
"생존자: 일단 너도 연구원한테 가서 확인해봐.",
"생존자: 너가 오기 전에 난 이미 손쓸 방도가 없게 되었고 나에게 반응한 좀비들이 여기로 몰려들었어.",
"생존자: ...나도 슬슬 한계야. 빨리 여기에 숨어있는 연구원을 찾아가. 으윽",
"플레이어: 안되요 버티세요. 좀비가 되지 마세요!",
"생존자: 빨리 가.. 나는 이미 으아아악!",
"플레이어: 크윽"
},
{
	"연구원: 으악 가까이 오지마!",
"생존자: 정신차리세요. 저에요!",
"연구원: 사람 말? 앗 며칠전의!",
"플레이어: 네 그 사람 맞아요! 도체제 무슨 일이 있었죠? 저는 누구인가요? 너는 좀비인가요? 일단 무전기 부품을 거의 다 찾았어요!",
"연구원: 잠깐 하나씩 말하세요. 일단 당신 아직 사람 맞아요! ..아직은요",
"연구원: 일단 당신은 좀비한테 감염된건 맞아요. 증상이 똑같거든요.",
"연구원: 하지만 아직 좀비는 아니에요! 봤는지 모르겠지만 똑같은 증상의 사람은 이미 늦었지만 당신은 안 늦었어요!"
"플레이어: 아뇨! 저도 모르겠어요!",
"연구원: 저도 분노를 주체 못해서 배신자랑 다투기도 했고, 좀비를 처치할 때 후련함과 희열, 분노등이 요동치는 것 같다구요!",
"연구원: 하지만 아직 의지가 있잖아요! 생존하겠다는 의지가. 그 의지로 무전기 부품을 다 모았잖아요.",
"플레이어: 네 뼈빠지게 6일동안 돌아다니면서 모았죠! ...그럼 저는 어떻게 해야하나요. 이대로 좀비가 될 수는 없어요!",
"연구원: ...잠시만요. 지금 6일동안 감염되도 이성이 있나요? 감정이 있나요?",
"플레이어: 감염이 언제 된지는 모르겠지만 깨어난지 7일정도 됐어요.",
"연구원: 7일 동안이나 버티다니... 이미 감정을 다스리는 법을 배운건가? 아님 다른 요소가 있나?",
"플레이어: 그건 또 무슨 말이죠?",
"연구원: “좀비한테 감염되면 보통 2,3일 지나면 감정을 주체할 수 없어지고, 그후 터지다가 감정과 이성을 잃고 좀비가 되거든요 보통.가만히 있어도.",
"연구원: 하지만 7일이나 돌아다니면서 아직도 감정을 다스릴 수 있다니. 이건 좀비 치료의 핵심이 될지도 몰라요!"
"플레이어: 제가 항체라는 소린가요?",
"연구원: 저는 아직까지 흔히 말하는 좀비백신, 즉 치료법은 없다고 생각해요. 하지만 이 답없는 상황에서의 돌파구가 당신에게 있다고도 생각하게 되었네요 방금.",
"플레이어: 아직 저도 제가 누군지, 제가 좀빈지 사람인지도 모르는데.",
"연구원: 일단 탈출하고 생각하죠, 여기 좀비 투성이라 어렵겠지만. 이제 여기서의 연구도 슬슬 마무리하고 저도 사람이 사는 곳으로 돌아가고 싶어요.",
"플레이어: 네, 근처에 피난처에 있는 생존자들도 있었어요. 다같이 탈출하죠. 일단 무전기부터 다시 만들어봐요. 내일 탈출하는 거에요.",
"연구원: 네 같이, 탈출해봐요. 무전기를 만들어서 헬기를 부르죠.",
"플레이어: 네, 일단 여기부터 탈출할게요. 제곁에 있어주세요.",
"연구원: 여기서 도망치기 전에 여러 물자들을 가져가죠. 혹시몰라 주변에 있는 탄창들을 챙기기 잘했군요. 당신도 총을 가지고 있는걸 보니 여기 다 챙겨가세요.",
"플레이어: ...탄창이 많긴하군요. 돌아다니는데 총알이 많이 없었던 이유가 여기에 있었다니..",
"플레이어: 일단 총알 감사합니다. 이제 나가죠.",
"연구원 : 방어구도 챙겨가시죠. 방어구가 있다면 좀비로부터 스트레스도 덜 받을 겁니다"
"플레이어: 감사합니다. 이제 탈출해보죠"
}
};
static std::vector<Zombie> zombies = {
		Zombie(4,7,1,0,6), Zombie(4,10,1,0,6), Zombie(1,11,1,0,6),
		Zombie(3,18,0,1,6), Zombie(14,4,1,0,6), Zombie(15,6,0,1,6),
		Zombie(10,2,1,0,6), Zombie(8,6,0,1,6), Zombie(23,3,0,1,6),
		Zombie(26,6,0,1,6), Zombie(28,6,0,1,6), Zombie(30,6,1,0,6),
		Zombie(28,4,1,0,6), Zombie(29,2,0,1,6), Zombie(32,12,1,0,6),
		Zombie(29,13,0,1,6), Zombie(19,13,0,1,6), Zombie(16,17,1,0,6),
};


std::atomic<bool> terminateZombieThread6(false);
void zombieMoveThread6(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread6) {
		// 1초마다 좀비를 이동
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 대기

		// 좀비 이동	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}
	}
}

static struct Bullet {
	int x;
	int y;
	int direction;
	int distanceTraveled;
};

static std::vector<Bullet> bullets;
static std::mutex bulletMutex;

static bool bullet_moving = true;
static void move_bullets(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (bullet_moving) {
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
					//이동 좀비
					if ((*zIt).x == b.x && (*zIt).y == b.y) {
						handle_zombie_death_effect(b.x, b.y, map);
						zIt = zombies.erase(zIt);
					}
					//자폭 좀비
					else if (map[b.y][b.x] == 'Z') {
						for (int dy = -1; dy <= 1; ++dy) {
							for (int dx = -1; dx <= 1; ++dx) {
								int temp_x = b.x + dx;
								int temp_y = b.y + dy;
								if (temp_x == zIt->x && temp_y == zIt->y) {
									zIt = zombies.erase(zIt);
								}
							}
						}
						handle_explosion(b.x, b.y, user, map);
					}
					//일반 좀비
					else if (map[b.y][b.x] == 'x') {
						handle_zombie_death_effect(b.x, b.y, map);
						updateTextBox("일반 좀비를 죽였습니다!");
					}
					else if (!(map[b.y][b.x] == 'x' || map[b.y][b.x] == 'Z' || map[b.y][b.x] == ' ' || (*zIt).x == b.x && (*zIt).y == b.y)) {
						hit = true;
						break;
					}
					else 	++zIt;
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


void start_day6(player* user, BackP* user_back) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(6, map);
	draw_map(map);         // 탐험 맵
	printstat(user); // 아이템 창 
	updateTextBox("");

	//좀비 생성
	std::thread zombieThread6(zombieMoveThread6, std::ref(zombies), map, user);
	std::thread bulletMoveThread(move_bullets, map, user);
	user->player_x = 1;
	user->player_y = 1;
	printplayer();
	set_hour(9);
	std::thread timerThread(timer);

	int dialogue_line = 0;
	bool in_dialogue =true;
	set_isExplore(false);
	int flag = 0;
	int dialogue_num = 0;
	map[user->player_y][user->player_x] = 'P';
	draw_map(map);
	while (true) {
		map[user->player_y][user->player_x] = ' ';
		draw_sunlight(map);
		if (get_hour() == 21) {
			terminateZombieThread6 = true;
			bullet_moving = false;
			if (zombieThread6.joinable()) { zombieThread6.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			break;
		}
		if (in_dialogue) {
			// 대화 중일 때

			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // 스페이스바로 대화 진행
					if (dialogue_line < dialogue_6[dialogue_num].size()) {
						updateDialogue(dialogue_6[dialogue_num][dialogue_line++]);
					}
					else {
						// 대화 종료
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
						if (dialogue_num == 2) {
							if (user->player_y<=5) {
								map[2][15] = 'x';
							}
							else {
								map[12][5] = 'x';
							}
							draw_map(map);
						}
						if (dialogue_num == 3) {
							dialogue_num = 2;
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
				case 72: newY--; user->direction = 0; break;
				case 80: newY++; user->direction = 1; break;
				case 75: newX--; user->direction = 2; break;
				case 77: newX++; user->direction = 3; break;
				}
				if (map[newY][newX] == '?') {
					stop_timer_running();
					terminateZombieThread6 = true;
					bullet_moving = false;
					if (zombieThread6.joinable()) { zombieThread6.join(); }
					if (timerThread.joinable()) { timerThread.join(); }
					if (bulletMoveThread.joinable()) bulletMoveThread.join();
					return;
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
					case(3):
						if (map[newY][newX + 1] == ' ' || map[newY][newX+1] == '%') {
							map[newY][newX + 1] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(0):
						if (map[newY - 1][newX] == ' ' || map[newY - 1][newX] == '%') {
							map[newY - 1][newX] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(2):
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
					user->heart--;
					PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
					printstat(user);
					updateTextBox("으윽... 역시 햇빛은  따갑네 오래 있으면 안될 것 같아.");
				}
				else if (is_zombie_position(newX, newY, map)) {
					user->heart--;
					PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
					printstat(user);
					updateTextBox("크흑, 좀비한테 당했어");
					meet_zombie_change_edge();
				}
			}
			else if (key == 's' && user->bullet > 0 && user->gun >= 1) { // 's' 키로 총알 발사
				std::lock_guard<std::mutex> lock(bulletMutex);
				PlaySound(TEXT("gun.wav"), NULL, SND_ASYNC);
				user->bullet--;
				printstat(user);
				bullets.push_back({ user->player_x, user->player_y, user->direction, 0 });
			}
			else if (key == ' ' && is_player_near_item(user, map, user_back)) { // 엔터키로 아이템 획득
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // 스페이스바로 NPC와 대화
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_6[dialogue_num][dialogue_line++]);
				in_dialogue = true; // 대화 상태 진입
				if (dialogue_num <=1) {
					clear_npc_screen();
					printnpc2();
				}
				else {
					clear_npc_screen();
					printnpc1();
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
			is_player_near_explosive_zombie(user, map);
		}
		if (user->heart <= 0) {
			stop_timer_running();
			terminateZombieThread6 = true;
			bullet_moving = false;
			if (zombieThread6.joinable()) { zombieThread6.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			bad_ending_zombie();
		}
		if (user->mental >= user->maxm) {
			stop_timer_running();
			terminateZombieThread6 = true;
			bullet_moving = false;
			if (zombieThread6.joinable()) { zombieThread6.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			if (bulletMoveThread.joinable()) bulletMoveThread.join();
			bad_ending_zombie();
		}
		map[user->player_y][user->player_x] = 'P';
		draw_map(map);
	}
}