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
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
// day 0 ��ȭ��
std::vector<std::vector<std::string>> dialogue_0 = {
	{
		"�÷��̾�: \"���� �Ӹ���\"",
		"�÷��̾�: \"���� �����? �ֺ��� įį��\"",
		"�÷��̾�: \"���� �� ���⿡ �ִ°���?\"",
		"�÷��̾�: \"....�� ����� �ȳ�\"",
		"�÷��̾�: \"...�ϴ� �ֺ��� ���캸��\""
	},
	{
		"npc: \"�ƾ�! ��������? �� ���? ����� �� ���⿡? �ƴ� ��� ���⿡?\"",
		"�÷��̾�: \"Ȥ�� ����̼���? �׷��� �Ⱥ��̴µ�...\"",
		"npc: \"....����̰ŵ��. ������ ��� ���⿡ �Դµ���?\"",
		"�÷��̾�: \"...����� �����. ����.... �����ĿԴٴ� ���ۿ�...\"",
		"npc: \"...�׷�����. �׷� �ϴ� ���� �����ٰԿ�.\"",
		"npc: \"�ϴ� ��������״� ���� �ִ� �ķ�����.. �� ��������? Ȥ�� �̹� ��������...�� ������. �չ����� �����׿�.\"",
		"�÷��̾�: \"������ؼ� ����� �ؾ��մϴ�.\"",
		"npc: \"....��.  �ϴ� ����� ���� �ǳ����ִ� �����̿���.\"",
		"npc: \"������ ������ ���� �ƴ�����, �׷��� �ٱ� ���󺸴� �����ϱ��.\"",
		"npc: \"�� �ϴ� ������ �̰����� �帱�Կ�\"",
		"npc: \"�� ������ Ʃ�丮�� ���ƺ����� ��������\"",
		"npc: \"�ϴ� ���� �ֺ��� ������� �������� �����ϱ� �Ƚ��ϼ���.\"",
		"npc: \"�׷��ٰ� �ʹ� ������ �ٰ����� �����ϴϱ� �����Ͻð���.\"",
		"npc: \"�ϴ� �����Ϸ��� �翬�� ���ڰ�, �� �Ծ�߰���? ���̶�� ���� ���̱⿣ ��Ȳ�� ��������..\"",
		"npc: \"�ƹ�ư �ϴ� �ķ��� �ٴڳ����. ��� �Ʊ ������ ���� �ķ��̾��µ� ������� �纸�ѰŶ󱸿�?\"",
		"npc: \"�׷��� �ۿ� ������ �ķ�, �� ���� ���ؿ;��ؿ�. ���� ������� ���ؼ���.\"",
		"npc: \"����� ���� �ڰų� �޽İ������� ���ŵ� ��������.\"",
		"npc: \"�� �翬�� ���� �ķ��� ���� ���Ϸ� ����������.\"",
		"npc: \"...���� �����ؿ�... ���忡 ������� ���� �𸣰����� �޺��� �ʹ� ���. �������� �ı��Ȱ���... �޺��� �ʹ� ���� ���� ������.\"",
		"npc: \"�ϴ� ����� ���� �Ͼ�ٰ� �ϼ����� ���⼭ ������. ���� ���� ���� ���� ���� �ķ��� ���Ϸ� �����Կ�.\"",
		"npc: \"��? �ķ��̳� ���� ���������� ���� �ʳİ���?\"",
		"npc: \"...�ϴ� ���� �Ϸ翡 500ml�̻� ���� ������ ��¥ ����������.. ���� �޾���� �˾ƿ�. �ķ��� �Ϸ����� ��������.. ���������� ����...\"",
		"npc: \"�׷��� �ķ��� �ϴ� �׷��� �ĵ� ���� ������ ���ؾ��ϱ� ������ ���߸��ؿ�.\"",
		"npc: \"...�׷� �̸�\"",
		"�÷��̾�: \"�� �׷� ���� ��� ���⿡ �Դ��� ��ﵵ �ȳ�����, �ϴ� ��ƾ���. �׷� ���� ���Ϻ��� �ٽ� ���ƴٳ� ����.\"",
		"�÷��̾�: \"�������ڸ�. ���� ���� ���� ���� �ķ��� ���, ������ �� ���� ���� ������ ������ ���� �ǰ���?\"",
		"�÷��̾�: \"�ϴ� ���� ������ �Ƚ�ó�� ��� �ൿ����.\""
	},
};


std::atomic<bool> terminateZombieThread0(false);
void zombieMoveThread0(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread0) {
		// 1�ʸ��� ���� �̵�
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 1�� ���

		// ���� �̵�	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}

	}
}
void start_day0(player* user) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(0, map);
	draw_map(map);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");
	printplayer();

	user->player_x = 5;
	user->player_y = 6;
	//���� ����
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
			// ��ȭ ���� ��
			if (_kbhit()) {
				int key = _getch();
				if (key == ' ') { // �����̽��ٷ� ��ȭ ����
					if (dialogue_line < dialogue_0[dialogue_num].size()) {
						updateDialogue(dialogue_0[dialogue_num][dialogue_line++]);
					}
					else {
						// ��ȭ ����
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
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
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
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
				// �̵� ���� ���� Ȯ��
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					map[newY][newX] == ' ' && !is_zombie_position(newX, newY, map)) {
					user->player_x = newX;
					user->player_y = newY;
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
			else if (key == ' ' && is_player_near_item(user, map)) { // ����Ű�� ������ ȹ��
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_0[dialogue_num][dialogue_line++]);
				in_dialogue = true; // ��ȭ ���� ����
			}
			if (is_player_near_zombie(user,map) == true) {
				user->mental -= 2;
				printstat(user);
				updateTextBox("...�Ҿ���, ������... �ƹ������� ����� ������ �Ȱ���");
			}
		}
		if (user->heart <= 0) {
			bad_ending();
		}
		if (user->mental <= 0) {
			bad_ending();
		}
		map[user->player_y][user->player_x] = 'P';
		draw_map(map);
	}
}