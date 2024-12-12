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
#include "backpack.h"
#include <windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;
#define MAP_WIDTH 34
#define MAP_HEIGHT 20

// day 3 ��ȭ��
std::vector<std::vector<std::string>> dialogue_3 = {
	{
	"�÷��̾�: ���⿡ �������� ���� ġ������ �ִٰ� ����...",
	"???: �� ��Ҹ� ���? ���⿡��! ���⿡ ����� �־��!"
	},
{
	"�÷��̾�: ��������? ��°�� ���⿡ �ֳ���?",
	"np3: �� ���� ���� ���� ���شٴϴٰ� �Ѿ����� ��ó ġ���� ���Ѱ� ���� Ȯ�� �Ϸ���...",
	"�÷��̾�: ���⵵ ���� ������ ��������?",
	"np3: �� �̹� �����߰ŵ��. �̷����� �̹� �������� �� ���� ���̶��ϴ�.",
	"np3: �̹� ���� ���شٴ��� 3�ְ� �Ѿ��. ������ ���� ���� �� ��Ȳ�� ���� �ִٰ� �����ſ�.",
	"�÷��̾�: ...Ż���� ������ �ֳ���?",
	"np3: �翬����. ���� ��� ���� �ɿ�. �ٸ� ������� Ư���� �˱� ���� ���� �����ϰ� �ٴ� �̴ϴ�.",
	"np3: �Դٰ� Ż���ϰ� �; ������ ���� �� ���ͼ�...",
	"�÷��̾�: ���� Ż�� ����� ��ó�� �ǳ�ó�� �˰� �ֽ��ϴ�. ���� ������.",
	"np3: ��? �װ� �����̿���? �װ� ���?",
	"�÷��̾�: ���� �̰����� ���ƴٴϴ� �˰� �Ǿ����ϴ�. �ϴ� �ǳ�ó�� �� ��ó�̰�, Ż����� ������ ��ǰ�� ���ش� ����� �ſ�.",
	"np3: ������ ����?",
	"�÷��̾�: �� �ڼ��ϰԴ� �����ϱ� �������� �ƹ�ư �׷����ϴ�.",
	"np3: �׷�����... �˷��༭ �����մϴ�. ���� ����Կ�.",
	"�÷��̾�: �� �˰ڽ��ϴ�.",
	"np3: ���� Ȥ�� �Ѱ����� ��..... ���� ����ļ� �׷��� �ķ��ϰ� ���� ������ �� �ֳ���?",
	"�÷��̾�: .....�������� ���� ������ �ķ��� �帱�Կ�.",
	"np3: ���� �����մϴ�. �и� ���� ��Ȳ�� �� �˾Ҵµ� �̷��� �����ֽôٴ�. ������ ������ �ֳ� ������.",
	"�÷��̾�: �������� ������. ���� ���� ��Ȳ�� ��Ÿ��� ������ ���� �� ���� �����ִ� �̴ϴ�.",
	"np3: �������� ���Ͻ� ���̱���.",
	"np3: ...������ ����ϰǵ� �׷� �������� ���� ���� ���󿡼��� ���� ���� �̴ϴ�.",
	"np3: ������ ������ ������ �� ���� �����ο�. ����� ������ �ڽ��� ������ �����ϴ� �� ���ƿ�.",
	"�÷��̾�: ..��� �����մϴ�. �ϴ� ���������� ���� �ٴϸ鼭 Ž������.",
	"�÷��̾�: �ƹ��� �׷��� ȥ�ں��� ������ �ൿ�ϴ� �� ������ �������� �ʽ��ϱ�.",
	"np3: �װ͵� ���� ���� ����� ������ ���� �ѵ�.. ����� �������� ���� �Ͼ �ǰھ��. ���ƿ� ���� �ٳ��.",
	"�÷��̾�: �׷��� ���⿡ ���� ������ ����� ���� �ٴϴ� �Ƚ��Դϴ�. �� ��Ź�帳�ϴ�.",
	"np3: �� �� ��Ź�ؿ�.",
},
{
	"np3: ���� �����ݾƿ�. ����� ������ ������ ������ �ڱ� �ڽ��� ������ ���� �ൿ�϶��, ���� ���� ������� �� ���̰� Ȯ���϶��.",
	"np3: ���� ��Ʈ�� ��ȴµ� ��ġä�� ���� �� ����Դϴ�. ����� �����ؼ� �̷��� �� ����� �ſ���.",
	"np3: �����մϴ�. ���� ���� �˾ƺ� �� �� �˾ƺ����� ���� �����߰ھ��. ���� �����մϴ�.",
	"np3: �׸��� ����� ���� ��� �͵� �� ���Կ�~ ��Ƽ� ������.",
	"�÷��̾�: ��Ŵ��ߴ�... ��� �̷� ����... ���� �� ������� �� �߸��߱淡...",
	"�÷��̾�: �� ������ �� �������. �������� �ķ��� �� �Ϸ�ġ�� ���ΰ�...",
	"�÷��̾�: �뼭�� �� ����. �̷� ������ ó�� ��������.",
	"�÷��̾�: ������ ������� ����... �������� ���� �г��� ������ ������ np3�� �������� �����ߴ�.",
	"�÷��̾�: ��... �ٽ� �� ��Ƽ� ������.... �ݵ��... ������.",
},
{
	"������: ����� �輼��?",
	"�÷��̾�: ��������?",
	"������: �� ����̿���!! �� �� �����ּ���!",
	"�÷��̾�: ������ �����ϸ� ���͵帮�ڽ��ϴ�. Ȥ�� ���⿡ ���� ������ ��� �������� ����� �� ���̽��ϱ�?",
	"������: ���? ��...���� ���⿡ ��� ���� �־ �𸣰ڴµ� ���ڱ� �Ҹ��� ���ĸ��� ���� �������� �鸮�� �߾��.",
	"������: �Ƹ� �� ����� ������.",
	"�÷��̾�: ...�����մϴٸ�. ���͵帱 �� ���ڳ׿�. ���� ���� �� �ִ� �� �ƹ��͵� ���. �� �ڰ� ���ڳ׿�.",
	"������: �ƹ��͵� ���ٱ���. �ϴ� �ķ��� �� �ϳ��� �帱 �� �ְ�... Ȥ�� ���� ����ĥ ����� �ֳ���?",
	"�÷��̾�: ����! �����? �׷� �� �� �� ������ ������. ���Ⱑ �ֳ���?",
	"������: ���⿡ ����� �����. ���ʿ� �־ ���� ������ ��Ⱑ �� ���� ��� ���⿡ �־��� �ſ���.",
	"������: �ƹ�ư ����� �����Ŀ� �濡 �� ���� ���Ⱑ ���� ���� ��Ҹ� �߰��߾��. �ٷ� ��������!",
	"�÷��̾�: �״ϱ� �������� ���� ���� ���� �� ���� ���̴�?",
	"������: �� ����ġ�鼭 �������� ������ źâ�� �������� ���� �ѱⰡ ��� �� ���� �����µ� �ű⼭ �ѱ⸦ ������ ���� �����߸� �� ������ �����!",
	"�÷��̾�: �׷�����. �ٷ� �����ڽ��ϴ�. ��� ���� ������ ���� ���� ������. �ǳ�ó�ο�.",
	"������: !!�� �����մϴ�. ���� �����մϴ�.",
	"�÷��̾�: �� �׷� �̸� �����ڽ��ϴ�."
}
};
std::atomic<bool> terminateZombieThread3(false);
void zombieMoveThread3(std::vector<Zombie>& zombies, char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread3) {
		// 1�ʸ��� ���� �̵�
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���

		// ���� �̵�	
		for (auto& zombie : zombies) {
			zombie.move(map, user);
		}
	}
}
void start_day3(player* user, BackP* user_back) {
	system("cls");
	char map[MAP_HEIGHT][MAP_WIDTH + 1];
	copy_map(3, map);
	draw_map(map);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");

	//���� ����
	std::vector<Zombie> zombies = {
		Zombie(7, 18,0,1,3),
		Zombie(5, 8,1,0,3),
		Zombie(2, 11,1,0,3),
		Zombie(27, 2,1,0,3),
		Zombie(14, 5,1,0,3),
		Zombie(20, 5,1,0,3),
		Zombie(16, 3,1,0,3),
		Zombie(6, 15,1,0,3),
		Zombie(15, 8,0,1,3),
		Zombie(21, 8,1,0,3),
		Zombie(15, 11,1,0,3),
		Zombie(21, 11,0,1,3),
		Zombie(18, 9,1,0,3),
		Zombie(18, 12,1,0,3)
	};
	std::thread zombieThread3(zombieMoveThread3, std::ref(zombies), map, user);

	user->player_x = 5;
	user->player_y = 6;
	printplayer();
	set_hour(9);
	std::thread timerThread(timer);

	int dialogue_line = 0;
	bool in_dialogue = true;
	int flag = 0;
	int dialogue_num = 0;
	map[user->player_y][user->player_x] = 'P';
	draw_map(map);
	set_isExplore(false);// Ȯ��
	while (true) {
		map[user->player_y][user->player_x] = ' ';
		draw_sunlight(map);
		if (get_hour() == 21) {
			terminateZombieThread3 = true;
			if (zombieThread3.joinable()) {
				zombieThread3.join();
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
					if (dialogue_line < dialogue_3[dialogue_num].size()) {
						updateDialogue(dialogue_3[dialogue_num][dialogue_line++]);
					}
					else {
						// ��ȭ ����
						dialogue_clear();
						in_dialogue = false;
						set_isExplore(true);
						dialogue_line = 0;
						dialogue_num++;
						if (dialogue_num == 2) {
							user->food--;
							user->water--;
							if (user->food < 0) user->food = 0;
							if (user->water < 0)user->water = 0;
							map[1][11] = ' ';
							map[10][32] = 'N';
						}
						else if (dialogue_num == 3) {
							map[10][32] = ' ';
							if (user->food > 1) user->food = 1;
							if (user->water > 1) user->water = 1;
							printstat(user);
						}
						else if(dialogue_num==4){
							dialogue_num = 3;
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
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}
				if (map[newY][newX] == '?') {
					stop_timer_running();
					terminateZombieThread3 = true;
					if (zombieThread3.joinable()) {
						zombieThread3.join();
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
					user->sunlight++;
					if (user->sunlight >= 3) {
						user->sunlight = 0;
						user->heart--;
						printstat(user);
						PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
					}
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
			else if (key == ' ' && is_player_near_item(user, map, user_back)) { // ����Ű�� ������ ȹ��
				map[newY][newX] = ' ';
			}
			else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
				set_isExplore(false);
				dialogue_clear();
				updateDialogue(dialogue_3[dialogue_num][dialogue_line++]);
				in_dialogue = true; // ��ȭ ���� ����
				if (dialogue_num < 3) {
					clear_npc_screen();
					printnpc3();
				}
				else {
					clear_npc_screen();
					printnpc4();
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
		}
		if (user->heart <= 0) {
			stop_timer_running();
			terminateZombieThread3 = true;
			if (zombieThread3.joinable()) {zombieThread3.join();}
			if (timerThread.joinable()) {timerThread.join();}
			bad_ending_zombie();
		}
		if (user->mental >= user->maxm) {
			stop_timer_running();
			terminateZombieThread3 = true;
			if (zombieThread3.joinable()) { zombieThread3.join(); }
			if (timerThread.joinable()) { timerThread.join(); }
			bad_ending_zombie();
		}
		map[user->player_y][user->player_x] = 'P';
		draw_map(map);
	}
}