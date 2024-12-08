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

// day 4 ��ȭ��
std::vector<std::vector<std::string>> dialogue_5 = {
	{
	"�����: �ƴ� ���� ���?",
"������: ���� �г��� ������ ������ ������� �Դ�. ���� �� ���� ������!",
"�����: �����ٰ� ������ ������ �ʾҰ���. ��ã�� ������ �ʵ� �ٽ� ������ ��.",
"������: ...�׷� ������ ������.",
"�����: �׷� �װž�. ������ ������ Ưȭ�� ���� �߰� �Ǿ�����. ������, ���� ���󿡼��� ������ ���� �ƴ϶� �ΰ��̴�.",
"������: �׷�... ������� �����ϰ� �Ǿ���. �� ������ ���񺸴� ������� �ΰ��̶���!"
},
{
"�����: ��, ���� ���������...",
"������: ...�� �̷��� ���� �ϴ°ž�. �ʵ� ��Ƴ��� �ٸ� � ��Ƴ��� ����� �־����� �ƴϾ�.",
"�����: ������ ���� �Ҹ��� �ϰ� �ֱ���. �ִٰ� �ϴ��� Ȯ���� ������ �����ؾ���.",
"�����: �� Ȯ���� ���� ������� ��Ƴ��Ҵ�. ����ϸ�, ȥ�ڼ� ���ƴٴϸ� ���� ����ϸ鼭.",
"������: ������ �����ⱺ.",
"�����: �׷� ������� ���⼭ �����ϴ°� �³�����. ������ ����ض� ������ �ʵ� �����Ⱑ �� �� �ִٴ� ����",
"������: ���� ��ó���� ���� ���� �Ŵ�. �ΰ��� ������ ������ ���� �ž�.",
"�����: ���� ������ ���� ����ΰ�ó�� ���ϴ±�, �� ��� ���� ������.",
"�����: ������ ���ؼ� ��ó�� ����, ���� ���� �������� ������ ������. �� ������ ����.",
"������: ����, ���� �� ���� ���� �ʰڴ�.",
"�����: ...����� �ض�",
"������: �߰���, �ٽ� ���� ����."
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
		// 1�ʸ��� ���� �̵�
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���

		// ���� �̵�	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}
	}
}
static int playerDirection = 3; // 0: ��, 1: �Ʒ�, 2: ����, 3: ������ (�ʱ� ���� ������)

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


void start_day5(player* user, BackP* user_back) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(5, map);
	draw_map(map);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");

	//���� ����
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
			// ��ȭ ���� ��

			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // �����̽��ٷ� ��ȭ ����
					if (dialogue_line < dialogue_5[dialogue_num].size()) {
						updateDialogue(dialogue_5[dialogue_num][dialogue_line++]);
					}
					else {
						// ��ȭ ����
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
			continue; // ��ȭ �߿��� �Ʒ� ������ �����ϰ� ���� ������ �̵�
		}
		if (_kbhit()) {
			int key = _getch();

			if (key == 224) { // ����Ű �Է� Ȯ��
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
					updateTextBox("����... ���� �޺���  ������ ���� ������ �ȵ� �� ����.");
				}
				else if (is_zombie_position(newX, newY, map)) {
					user->heart--;
					printstat(user);
					updateTextBox("ũ��, �������� ���߾�");
					meet_zombie_change_edge();
				}
			}
			else if (key == 's' && user->bullet > 0 && user->gun >= 1) { // 's' Ű�� �Ѿ� �߻�
				std::lock_guard<std::mutex> lock(bulletMutex);
				user->bullet--;
				bullets.push_back({ user->player_x, user->player_y, user->direction, 0 });
			}
			else if (key == ' ' && is_player_near_item(user, map, user_back)) { // ����Ű�� ������ ȹ��
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_5[dialogue_num][dialogue_line++]);
				in_dialogue = true; // ��ȭ ���� ����
			}
			if (is_player_near_zombie(user, map) == true) {
				user->mental -= 2;
				printstat(user);
				updateTextBox("...�Ҿ���, ������... �ƹ������� ����� ������ �Ȱ���");
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