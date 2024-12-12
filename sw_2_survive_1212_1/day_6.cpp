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

//npc ��ȭ �� ������� ����
std::vector<std::vector<std::string>> dialogue_6 = {
	{
"�÷��̾�: ��, ���� ����ڸ� óġ�ؼ� �� ���ǵ� ��ã�Ұ�, ���� ������ ��ǰ�� ���� �� ��� ����.",
"�÷��̾�: �ϴ� �ٽ� ù���� �ô� ������� ���� ���Ŀ� ��� �ؾ� �ϴ��� ������߰ھ�",
"�÷��̾�: ....�ܵ����� �����߱� ������, ����� �ƹ��� ���ݾ�?",
"�÷��̾�: ���� ������ ���� �ֳ�. ���� ���⿡ ���̾��µ� �μ��� ������ �־�...",
"�÷��̾�: �ϴ� ���� ����� ã�ƺ���",
"�÷��̾�: ...���� ����, ���� ���� ������ ������ ����... ���� ���� �ü��̾���?"
},
{
"������: ...���",
"�÷��̾�: ������� �������� �ô�? ���� ���̼���?",
"������: ...��� �� �������� ���߳���. ���� ������ �𸣰�����.",
"������: �ʶ� ������� ���ƴٴϴٰ� ��� ���� ���ڱ� �г�, ���� �� ������ �䵿ġ�� ���� ������.",
"������: �׷��� ����� �¼� �� ���ڱ� ���� ���� �̻��� ������ �����ϰ� �ƾ�.",
"������: ���� ���ϴ°� �ƴ� �ν������� �ʹٰ� �����ϸ鼭 �浿������ �����߰ŵ�.",
"�÷��̾�: ������ �䵿ģ�ٴ� �ǰ���?",
"������: �׷�, ���� �̻��ϴٴ� ���� ������ ���� �ܵ������� ���� ����� ���� �쿬�� �������� ���� ���� ���� ���� �־���.",
"�÷��̾� : �׷� ���� �ִ� ����� �������̾��� �ǰ���? �׷��� ���⼭ ���� �����߱���.",
"������ : �ʵ� �ƴ� ����̾���? �ƹ�ư �������� �� �� ���¸� ���Ǹ鼭 Ȯ�εȰ�, ����� �޺��� ������ �Ӹ��� ������ �� ȸ���Ѵ�. ��� ������ �ı� �̷��� ������ ����.",
"������: �׸��� ����� ������ �ִ� ���翡�� �浿������ �̲�����. ����� ������ �̼��� ����� ����, �׷��� ������ ���ؼ� �̲����� �� ����.",
"������: �� �̹� ���� ���� ���¿���, �׷��� �޺���, ������ �䵿�ƴ�����..",
"�÷��̾�: ��ø���, �׸��� ����ΰ���?",
"������: ���� ������ ���� �� ����̾�. �����ƾ �Ϲ� ����� ���̾����� Ư�� ������� ������ �䵿ġ�� ���� ����ȭ�� �Ǵ� ����̾�.",
"������: �׷��� ������ ������ ���ϰų�, ���� �Ǳ� ���� ������ ���õ� ������ ġ�Ḧ �ް� �Ǹ� ��� ���� ȣ���Ǵ� �͵� Ȯ���߾�.",
"�÷��̾�: �ƴ� ��ø���, ���ݱ��� ���� �����ϸ� ����...",
"������: Ȯ������ ������, Ȯ���� ����.",
"�÷��̾�: ���� ��ﵵ ���� ������..",
"������: ���� ���� �������� ������. ���� ��δ� ���� ��������",
"�÷��̾�: �׷� ����... �׷� �� ��ü...",
"������: �ϴ� �ʵ� ���������� ���� Ȯ���غ�.",
"������: �ʰ� ���� ���� �� �̹� �վ� �浵�� ���� �Ǿ��� ������ ������ ������� ����� ���������.",
"������: ...���� ���� �Ѱ��. ���� ���⿡ �����ִ� �������� ã�ư�. ����",
"�÷��̾�: �ȵǿ� ��Ƽ����. ���� ���� ������!",
"������: ���� ��.. ���� �̹� ���ƾƾ�!",
"�÷��̾�: ũ��"
},
{
	"������: ���� ������ ������!",
"������: ������������. ������!",
"������: ��� ��? �� ��ĥ����!",
"�÷��̾�: �� �� ��� �¾ƿ�! ��ü�� ���� ���� �־���? ���� �����ΰ���? �ʴ� �����ΰ���? �ϴ� ������ ��ǰ�� ���� �� ã�Ҿ��!",
"������: ��� �ϳ��� ���ϼ���. �ϴ� ��� ���� ��� �¾ƿ�! ..��������",
"������: �ϴ� ����� �������� �����Ȱ� �¾ƿ�. ������ �Ȱ��ŵ��.",
"������: ������ ���� ����� �ƴϿ���! �ô��� �𸣰����� �Ȱ��� ������ ����� �̹� �ʾ����� ����� �� �ʾ����!"
"�÷��̾�: �ƴ�! ���� �𸣰ھ��!",
"������: ���� �г븦 ��ü ���ؼ� ����ڶ� �����⵵ �߰�, ���� óġ�� �� �ķ��԰� ��, �г���� �䵿ġ�� �� ���ٱ���!",
"������: ������ ���� ������ ���ݾƿ�! �����ϰڴٴ� ������. �� ������ ������ ��ǰ�� �� ����ݾƿ�.",
"�÷��̾�: �� �������� 6�ϵ��� ���ƴٴϸ鼭 �����! ...�׷� ���� ��� �ؾ��ϳ���. �̴�� ���� �� ���� �����!",
"������: ...��ø���. ���� 6�ϵ��� �����ǵ� �̼��� �ֳ���? ������ �ֳ���?",
"�÷��̾�: ������ ���� ������ �𸣰����� ����� 7������ �ƾ��.",
"������: 7�� �����̳� ��Ƽ�ٴ�... �̹� ������ �ٽ����� ���� ���ǰ�? �ƴ� �ٸ� ��Ұ� �ֳ�?",
"�÷��̾�: �װ� �� ���� ������?",
"������: ���������� �����Ǹ� ���� 2,3�� ������ ������ ��ü�� �� ��������, ���� �����ٰ� ������ �̼��� �Ұ� ���� �ǰŵ�� ����.������ �־.",
"������: ������ 7���̳� ���ƴٴϸ鼭 ������ ������ �ٽ��� �� �ִٴ�. �̰� ���� ġ���� �ٽ��� ������ �����!"
"�÷��̾�: ���� ��ü��� �Ҹ�����?",
"������: ���� �������� ���� ���ϴ� ������, �� ġ����� ���ٰ� �����ؿ�. ������ �� ����� ��Ȳ������ ���ı��� ��ſ��� �ִٰ� �����ϰ� �Ǿ��׿� ���.",
"�÷��̾�: ���� ���� ���� ������, ���� ������ ��������� �𸣴µ�.",
"������: �ϴ� Ż���ϰ� ��������, ���� ���� �����̶� ��ư�����. ���� ���⼭�� ������ ���� �������ϰ� ���� ����� ��� ������ ���ư��� �;��.",
"�÷��̾�: ��, ��ó�� �ǳ�ó�� �ִ� �����ڵ鵵 �־����. �ٰ��� Ż������. �ϴ� ��������� �ٽ� ��������. ���� Ż���ϴ� �ſ���.",
"������: �� ����, Ż���غ���. �����⸦ ���� ��⸦ �θ���.",
"�÷��̾�: ��, �ϴ� ������� Ż���ҰԿ�. ���翡 �־��ּ���.",
"������: ���⼭ ����ġ�� ���� ���� ���ڵ��� ��������. Ȥ�ø��� �ֺ��� �ִ� źâ���� ì��� ���߱���. ��ŵ� ���� ������ �ִ°� ���� ���� �� ì�ܰ�����.",
"�÷��̾�: ...źâ�� �����ϱ���. ���ƴٴϴµ� �Ѿ��� ���� ������ ������ ���⿡ �־��ٴ�..",
"�÷��̾�: �ϴ� �Ѿ� �����մϴ�. ���� ������.",
"������ : ���� ì�ܰ�����. ���� �ִٸ� ����κ��� ��Ʈ������ �� ���� �̴ϴ�"
"�÷��̾�: �����մϴ�. ���� Ż���غ���"
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
		// 1�ʸ��� ���� �̵�
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���

		// ���� �̵�	
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
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 0.1�� ���
		std::lock_guard<std::mutex> lock(bulletMutex);

		for (auto it = bullets.begin(); it != bullets.end();) {
			Bullet& b = *it;

			// ���� �Ѿ� ��ġ ����
			map[b.y][b.x] = ' ';

			// ���⿡ ���� �̵�
			switch (b.direction) {
			case 0: b.y--; break;
			case 1: b.y++; break;
			case 2: b.x--; break;
			case 3: b.x++; break;
			}

			b.distanceTraveled++;

			// �浹 ����
			bool hit = false;
			{
				std::lock_guard<std::mutex> zombieLock(zombieMutex2);
				for (auto zIt = zombies.begin(); zIt != zombies.end();) {
					//�̵� ����
					if ((*zIt).x == b.x && (*zIt).y == b.y) {
						handle_zombie_death_effect(b.x, b.y, map);
						zIt = zombies.erase(zIt);
					}
					//���� ����
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
					//�Ϲ� ����
					else if (map[b.y][b.x] == 'x') {
						handle_zombie_death_effect(b.x, b.y, map);
						updateTextBox("�Ϲ� ���� �׿����ϴ�!");
					}
					else if (!(map[b.y][b.x] == 'x' || map[b.y][b.x] == 'Z' || map[b.y][b.x] == ' ' || (*zIt).x == b.x && (*zIt).y == b.y)) {
						hit = true;
						break;
					}
					else 	++zIt;
				}
			}

			// �浹 �Ǵ� ��� �ʰ� ó��
			if (hit || b.x < 0 || b.x >= MAP_WIDTH || b.y < 0 || b.y >= MAP_HEIGHT || b.distanceTraveled > 7) {
				it = bullets.erase(it);
				continue;
			}

			// �ʿ� �Ѿ� ��ġ ǥ��
			map[b.y][b.x] = '*';
			++it;
		}
	}
}


void start_day6(player* user, BackP* user_back) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(6, map);
	draw_map(map);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");

	//���� ����
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
			// ��ȭ ���� ��

			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // �����̽��ٷ� ��ȭ ����
					if (dialogue_line < dialogue_6[dialogue_num].size()) {
						updateDialogue(dialogue_6[dialogue_num][dialogue_line++]);
					}
					else {
						// ��ȭ ����
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
			continue; // ��ȭ �߿��� �Ʒ� ������ �����ϰ� ���� ������ �̵�
		}
		if (_kbhit()) {
			int key = _getch();

			if (key == 224) { // ����Ű �Է� Ȯ��
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
				// �̵� ���� ���� Ȯ��
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
					updateTextBox("����... ���� �޺���  ������ ���� ������ �ȵ� �� ����.");
				}
				else if (is_zombie_position(newX, newY, map)) {
					user->heart--;
					PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
					printstat(user);
					updateTextBox("ũ��, �������� ���߾�");
					meet_zombie_change_edge();
				}
			}
			else if (key == 's' && user->bullet > 0 && user->gun >= 1) { // 's' Ű�� �Ѿ� �߻�
				std::lock_guard<std::mutex> lock(bulletMutex);
				PlaySound(TEXT("gun.wav"), NULL, SND_ASYNC);
				user->bullet--;
				printstat(user);
				bullets.push_back({ user->player_x, user->player_y, user->direction, 0 });
			}
			else if (key == ' ' && is_player_near_item(user, map, user_back)) { // ����Ű�� ������ ȹ��
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_6[dialogue_num][dialogue_line++]);
				in_dialogue = true; // ��ȭ ���� ����
				if (dialogue_num <=1) {
					clear_npc_screen();
					printnpc2();
				}
				else {
					clear_npc_screen();
					printnpc1();
				}
			}
			else if (key == '1') { // ������ ���
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
					updateTextBox("�ķ��� ������ �Ѱ� ������� ����̴�.");
					printstat(user);
				}
				else {
					updateTextBox("���� �� �ִ� �ķ��� ����...");
				}
			}
			else if (key == '2') { // ������ ���
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
					updateTextBox("ġ������ ����ϴ� ���� ȸ���Ǵ� ���� ��������.");
				}
				else {
					updateTextBox("����� �� �ִ� ġ������ ����...");
				}
			}
			if (is_player_near_zombie(user, map) == true) {
				user->mental += 2;
				printstat(user);
				updateTextBox("...�Ҿ���, ������... �ƹ������� ����� ������ �Ȱ���");
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