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
#define MAP_WIDTH 34
#define MAP_HEIGHT 20

// day 4 ��ȭ��
std::vector<std::vector<std::string>> dialogue_4 = {
	{
	"�÷��̾�: ���⿡ ���Ⱑ �ִٴ� �ǰ�. ���� ������ ã�ƺ���"
},
{
	"�÷��̾�:������ ���� ���� ������� źâ�� ������ ���� �����߸��� ���� ���� ����! ���� �� ������ ã�� �� ��ǰ�� ��ã�ƾ߰ھ�."
},
{
	"������: �� ����̴�! ����� ���� �� �����ּ���!",
"�÷��̾�: ...���⿡ �� �־���?",
"������: �ϴ� �����ּż� �����մϴ�.",
"������: ���� �ϴ� ���⼭ Ž���ϸ� �Ϸ��Ϸ縦 �ܿ� ��ư��� ����ε���.",
"������: ���ڱ� �׷��� ���� ����� ó���̶� �� �����κ��� �����ٴϴ� ����� �������� ������ �ϰ�, �ƹ����� �������� ���ϱ�.",
"�÷��̾�: ���� ���� ���� ���� ������ ������ ���������� ������ �� ���׿�.",
"������: �� �׷��� ������ �ͺ��� ���� ����������.",
"������: �׳����� �Ʊ ����� �������µ� �׳� �������� �Ǹ��ߴµ� �̹��� �����̳׿�.",
"�÷��̾�: �Ʊ ����� �������ٰ��?",
"������: �� ��Ȯ�ϰԴ� �� ���׿��� ������ �����ε� ���� ���غ��� �˾ƿ�.",
"������: ���� ������������ ����̶� �ڽſ��� ������� �ʴ� �ൿ�� ö���� �����ϴ� ����̿���.",
"�÷��̾�: ...�� ��� ���� ������ �Ƴ���?",
"������: �� �����̿�? ��. Ȥ�� ��ŵ�...",
"������: �� �˷��帱�Կ�. ��Ȯ���� ������ �� ����� ���� �� ��ó �б��� ����ó�� ��� Ȱ���ؿ�. ��ó�� ���� ����, ����ó�� �� �� ������ ��ֹ��� �־ �ƹ��� ���ѱ� ������ ��ã�� ������ �� �ؼ� ��������.",
"�÷��̾�: �׷� �б��� ���� �� �༮�� ���� �� �ִٴ� ����? ���� �����մϴ�.",
"������: �� ��. ���� �� ��������. �� ���� ��ã�� �ٶ��Կ�! ����� ���ϴ�.",
"�÷��̾�: �׸��� ���� �������� ���� �ǳ�ó�� �ִٰ� �ؿ�. �������� ������.",
"������: �� ���� �����մϴ�. Ȯ���� �������� �� ������ �� �ϱ� �߾��. �׷� ���� �ǳ�ó�� ���ڽ��ϴ�. ���� �����մϴ�!"
}
};
std::atomic<bool> terminateZombieThread4(false);
void zombieMoveThread4(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread4) {
		// 1�ʸ��� ���� �̵�
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 1�� ���

		// ���� �̵�	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}
	}
}
void start_day4(player* user) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(4, map);
	draw_map(map);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");

	//���� ����
	std::vector<Zombie> zombies = {
		Zombie(6,1,0,1,4),
		Zombie(3,5,1,0,4),
		Zombie(1,7,1,0,4) ,
		Zombie(8, 9,1,0,4),
		Zombie(1, 10,1,0,4),
		Zombie(10, 7,1,0,4) ,
		Zombie(15, 5,1,0,4) ,
		Zombie(20, 5,0,1,4) ,
		Zombie(27, 14,1,0,4) ,
		Zombie(31,12,0,1,4) ,
		Zombie(32, 12,0,1,4) ,
		Zombie(5, 17,1,0,4),
		Zombie(6, 17,1,0,4),
		Zombie(24, 10,0,1,4),
		Zombie(13, 9,1,0,4),
		Zombie(13, 13,1,0,4) ,
		Zombie(24, 14,1,0,4) ,
		Zombie(18, 10,1,0,4),
		Zombie(16, 9,0,1,4) ,
		Zombie(27, 9,0,1,4)
	};
	std::thread zombieThread4(zombieMoveThread4, std::ref(zombies), map, user);

	user->player_x = 1;
	user->player_y = 1;
	draw_face();
	set_hour(9);
	std::thread timerThread(timer);

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
			if (zombieThread4.joinable()) {
				zombieThread4.join();
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
					if (dialogue_line < dialogue_4[dialogue_num].size()) {
						updateDialogue(dialogue_4[dialogue_num][dialogue_line++]);
					}
					else {
						// ��ȭ ����
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
						if (dialogue_num == 1) {
							map[1][11] = ' ';
							map[10][32] = 'N';
						}
						else if (dialogue_num == 2) {
							map[10][32] = ' ';
						}
						else if (dialogue_num == 3) {
							dialogue_num = 2;
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
					terminateZombieThread4 = true;
					if (zombieThread4.joinable()) {
						zombieThread4.join();
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
				if (user->gun == 1 && get_gun_dialogue == false) {
					in_dialogue = true;
					get_gun_dialogue = true;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_4[dialogue_num][dialogue_line++]);
				in_dialogue = true; // ��ȭ ���� ����
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