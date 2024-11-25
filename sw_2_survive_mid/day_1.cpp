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
// day 1 ��ȭ��
std::vector<std::vector<std::string>> dialogue_1 = {
	{
		"�÷��̾�: \"������ ������ ���� �� ���� �ֳ�... �� ��¥ �� �������� ��� ����?\"",
		"�÷��̾�: \"�ƹ�ư ���� ���� Ž���غ��� �ķ��̳� ������ �ְ���\""
	},
	{
		"???: \"���� �����, ������ ...�ؾ���..\"",
		"���𰡿� �����ϰ� �ִ� ����̴�."
	},
	{
		"npc2: \"�� ������? �� ��� ����? ���� ���?\"",
		"npc2: \"...�ϴ� �� ���� ������ �� �԰ڼ�. �ʹ� ������ ������ �䵵 ��԰� �־��׿�.\"",
		"npc2: \"����� ����... �ƴ� ���� ������ �޽�ó����.\"",
		"npc2: \"�� ���� �����ϰ� �־��ı���? �׳�. ���� ���ؼ���. ��� ������ ������ �����̾��ŵ��.. �� �����Ҵ� �̹� ��������.\"",
		"npc2: \"������°� ������ �̹� ���� �ð��� ��������, ���� �η��� �ذ����� ���� ���� �ʹ� ���ƿ�. ���� ���κ���, ��ű�����.\"",
		"npc2: \"�̹� ���� �������� �̰� �ذ����� �Ұ����ϴٰ� ���ھ����� ���� �׷��� �������� ����������.\"",
		"npc2: \"������ ���� ������� ���� ������ ��Ȱ�ϴ� ���� ������ �Ǵ� �� ������.\"",
		"npc2: \"...�⼳�� �����. ���⿡�� ����� ������ �ʹ� �幰� �ʹ� �ݰ����� �׸�.\"",
		"npc2: \"�׷��� ��ŵ� ������ �ǳ�ó�� Ż���� �ٶ��ٸ� �׶� �� ���� ����� �˷��൵ ���ڱ���.\"",
		"npc2: \"�ϴ� ���� ����. ����� �ϴ� ���� �Ⱦ��ϴ� �� ���ƿ� Ư�� �޺� �׷��� �㿡 ���� Ȱ���ϰ� �׸��� ��ó���� ���ƴٴ���.\"",
		"npc2: \"....��? �޺��� ������ �ı� ������ ������� �ƴϳİ��? �ƴ�? ���� �����ѵ���?\"",
		"npc2: \"�ƹ�ư ���� ������ڸ� ������ ������� �������� ������ ���, �׵��� ���������� �̲��� ���ƴٴϴ� �� ����.\"",
		"�÷��̾�: \"��....��?\"",
		"npc2: \"�� ���, ����, �г� �� �پ��� �����̿�. ������� �ƹ��͵� �������� ��ó�� �������. ������ ����, ������ ���ϴ��� ���� ���ǽ������� �Ѿƴٴϴ� ��ó��\"",
		"npc2: \"������ ������ �پ��ѵ�, �������ִ� ���� �ִ� �ݸ�, ���� Ư�� �������� �����Ӹ� �ݺ��ϰų�. ������ �̲��� �Ѿƿ��� ����� ��������.\"",
		"npc2: \"����������, ��ſ� ���ؼ���.... �̰� �ƹ��� �˾ƺ��� ������ ���� �ȳ��Ϳ�. �̹� ���� �ڸ� �츱 �� ������ �����Ǹ� ���ϴ� ���� ���� �� ���� ��ó��.\"",
		"npc2: \"������ �������� ���� �� ���� �� ���ƿ�. �׸��� �� ������ ���ϸ� �������� ���������� �°� ������ ��Ʈ���� ���� ������ ���� �ʴ´ٸ�, �ƹ��� ����� �ΰ�ó�� ��� �ִٰ� �����ؿ�. �װ��� ����̶�� �� �ϱ⿣ �ָ��ϰ�����.\"",
		"npc2: \"�ƹ�ư �� �������� �������, �̷����� ���ʰ� �ʿ��ؿ�. Ȥ�� ���߿� ��ȸ �ǽŴٸ� ���ش� �ֽǼ� �ְھ��?\"",
		"npc2: \"��. ���� ���� �� ������ �������� ���� ���ư� ������. �ϴ� �ķ� �����մϴ�.\"",
		"npc2: \"�츮 ������ �� ���� ���� �� ���ƿ�.\""
	},
	{
		"�÷��̾�: \"�� �׷� ���� ��� ���⿡ �Դ��� ��ﵵ �ȳ�����, �ϴ� ��ƾ���. �׷� ���� ���Ϻ��� �ٽ� ���ƴٳ� ����.\"",
		"�÷��̾�: \"�������ڸ�. ���� ���� ���� ���� �ķ��� ���, ������ �� ���� ���� ������ ������ ���� �ǰ���?\"",
		"�÷��̾�: \"�ϴ� ���� ������ �Ƚ�ó�� ��� �ൿ����.\""
	},
	{
		"�÷��̾�: \"�������! �̰ɷ� �����ؼ� �����ڰ� �ִٰ� �ϸ� ��Ⱑ ���� ������?\"",
		"�÷��̾�: \".....���峪�ִ�. �׷��� ������ ��ǰ���� ��� �ٽ� �����⸦ ����ٸ� ��⸦ �θ� �� ���� ������?\"",
		"�÷��̾�: \"����! �� �ؾ� ���� ���� ���̱� �����߾�.\""
	}
};

std::string radio_dialogue[] = {
		"�÷��̾�: \"�������! �̰ɷ� �����ؼ� �����ڰ� �ִٰ� �ϸ� ��Ⱑ ���� ������?\"",
		"�÷��̾�: \".....���峪�ִ�. �׷��� ������ ��ǰ���� ��� �ٽ� �����⸦ ����ٸ� ��⸦ �θ� �� ���� ������?\"",
		"�÷��̾�: \"����! �� �ؾ� ���� ���� ���̱� �����߾�.\""
};
std::atomic<bool> terminateZombieThread1(false);
void zombieMoveThread1(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread1) {
		// 1�ʸ��� ���� �̵�
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 1�� ���

		// ���� �̵�	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}

	}
}
void start_day1(player* user) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(1, map);
	draw_map(map);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");
	printplayer();
	user->player_x = 5;
	user->player_y = 6;


	//���� ����
	std::vector<Zombie> zombies = {
		Zombie(5, 8, 1, 0, 1),
		Zombie(2, 3, 0, 1, 1),
		Zombie(21, 11, 0, 1, 1)
	};
	std::thread zombieThread1(zombieMoveThread1, std::ref(zombies), map, user);


	draw_face();
	set_hour(9);
	std::thread timerThread(timer);

	int dialogue_line = 0;
	bool in_dialogue = true;
	int flag = 0;
	int dialogue_num = 0;
	map[user->player_y][user->player_x] = 'P';
	bool find_radio = false;
	draw_map(map);
	while (true) {
		map[user->player_y][user->player_x] = ' ';
		draw_sunlight(map);
		if (get_hour() == 21) {
			terminateZombieThread1 = true;
			if (zombieThread1.joinable()) {
				zombieThread1.join();
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
					if (dialogue_line < dialogue_1[dialogue_num].size()) {
						updateDialogue(dialogue_1[dialogue_num][dialogue_line++]);
					}
					else {
						// ��ȭ ����
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
						if (dialogue_num == 2) {
							updateTextBox("npc���� �ķ��� ���� �����ְڽ��ϱ�? y/n");
							key = _getch();
							if (key == 'y' || key == 'Y') {
								user->food--;
								user->water--;
								if (user->food < 0) user->food = 0;
								if (user->water < 0)user->water = 0;
								
							}
							else {
								dialogue_num = 1;
							}
							clear_npc_screen();
							printplayer();
						}
						if (dialogue_num == 4) {
							dialogue_num = 3;
							clear_npc_screen();
							printplayer();
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
					terminateZombieThread1 = true;
					if (zombieThread1.joinable()) {
						zombieThread1.join();
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
					user->heart--;
					printstat(user);
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
				if (user->radio == 1 && find_radio==false) {
					int cur_line = 0;
					set_isExplore(false);
					while (cur_line < 3) {
						if (_kbhit()) {
							int key2 = _getch();
							if (key2 == ' ') {
								dialogue_clear();
								updateDialogue(radio_dialogue[cur_line++]);
							}
						}
					}
					set_isExplore(true);
					find_radio = true;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_1[dialogue_num][dialogue_line++]);
				in_dialogue = true; // ��ȭ ���� ����
				if (dialogue_num >= 1) {
					clear_npc_screen();
					printnpc1();
				}
			}
			if (is_player_near_zombie(user, map) == true) {
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