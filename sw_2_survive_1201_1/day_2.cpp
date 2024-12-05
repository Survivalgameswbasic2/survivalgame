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
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
// day 2 ��ȭ��
std::vector<std::vector<std::string>> dialogue_2 = {
	// �ʱ� ��ġ�� ��ȭ
	{
		"���� ����� ķ�����̾�������... �ϱ� �̷��� ���� ���� �Ƹ��ٿ� �ڿ��� ������ �����ϱ�. ������ ������ ���� �� �״�� ������������..",
		"�ƹ�ư ���⼭ ������ ��ǰ���� ������ ���̵�, ������ ����, �ķ��̵� ���̵�, ���� �� �ִ� ���� �� ���ϴ°ž�!"
	},
	// ������ �߽߰� ��ȭ
	{
		"�̰�...�� ���� ���� ���� ������ �ֳ�? �Դٰ� �ű⿡ �ǳ�ó�� �ִٰ�?",
		"���� �� ���� ������ ���� ������� ���� ����� �ӽ� �ǳ�ó�� ���� �ǰ�?",
		"����. ���� �������� ������ �ǰ���. �׷� �ű⿣ �и� ����� ��������!",
		"���� ����� ���̱� �����߾�!"
	}
};

std::atomic<bool> terminateZombieThread2(false);
void zombieMoveThread2(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread2) {
		std::this_thread::sleep_for(std::chrono::seconds(1));

		// ���� �̵�	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}

	}
}
void start_day2(player* user) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(2, map);
	draw_map(map);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");


	//���� ����
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
			break;
		}
		if (in_dialogue) {
			// ��ȭ ���� ��
			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // �����̽��ٷ� ��ȭ ����
					if (dialogue_line < dialogue_2[dialogue_num].size()) {
						updateDialogue(dialogue_2[dialogue_num][dialogue_line++]);
					}
					else {
						// ��ȭ ����
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
						if (dialogue_num > 1) {
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
				// �̵� ���� ���� Ȯ��
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					map[newY][newX] == ' ' && !is_zombie_position(newX, newY, map)) {
					user->player_x = newX;
					user->player_y = newY;
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					map[newY][newX] == 'A' && !is_zombie_position(newX, newY, map)) {
					switch (user->direction) {
					case(1):
						if (map[newY + 1][newX] == ' ') {
							map[newY + 1][newX] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(2):
						if (map[newY][newX + 1] == ' ') {
							map[newY][newX + 1] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(3):
						if (map[newY - 1][newX] == ' ') {
							map[newY - 1][newX] = 'A';
							user->player_x = newX;
							user->player_y = newY;
						}
						break;
					case(4):
						if (map[newY][newX - 1] == ' ') {
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
					updateTextBox("�޺��� �������� �޾Ҵ�");
				}
				else if (is_zombie_position(newX, newY, map)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					updateTextBox("���񿡰� �������� �Ծ���.");
					meet_zombie_change_edge();
				}
			}
			else if (key == ' ' && is_player_near_item(user, map)) { // ����Ű�� ������ ȹ��
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_2[dialogue_num][dialogue_line++]);
				in_dialogue = true; // ��ȭ ���� ����
			}
		}
		if (user->heart <= 0) {
			stop_timer_running();
			terminateZombieThread2 = true;
			if (zombieThread2.joinable()) {zombieThread2.join();}
			if (timerThread.joinable()) {timerThread.join();}
			bad_ending_zombie();
		}
		if (user->mental <= 0) {
			stop_timer_running();
			terminateZombieThread2 = true;
			if (zombieThread2.joinable()) { zombieThread2.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			bad_ending_starve();
		}
		map[user->player_y][user->player_x] = 'P';
		draw_map(map);
	}
}