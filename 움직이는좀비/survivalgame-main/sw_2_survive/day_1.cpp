#include "expire_tool.h"
#include "player.h"
#include <string>
#include <conio.h>
#include <thread>
#include <iostream>
#include "bad_ending.h"
#include "game_map.h"
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
#include<chrono>
#include"zombie_move.h"
#include<vector>
#include <atomic>
// day 1 ��ȭ��
std::string dialogue_1[] = {
	   "???: ������ �����, ������ ...�ؾ���..��",
	   "���𰡿� �����ϰ� �ִ� ����̴�.",
	   "npc2: ���� ������? �� ��� ����? ���� ���?��",
	   "npc2: ��...�ϴ� �� ���� ������ �� �԰ڼ�. �ʹ� ������ ������ �䵵 ��԰� �־��׿�.��",
	   "npc2: ������� ����... �ƴ� ���� ������ �޽�ó����.��",
	   "npc2: ���� ���� �����ϰ� �־��ı���? �׳�. ���� ���ؼ���. ��� ������ ������ �����̾��ŵ��.. �� �����Ҵ� �̹� ��������.��",
	   "npc2: ��������°� ������ �̹� ���� �ð��� ��������, ���� �η��� �ذ����� ���� ���� �ʹ� ���ƿ�. ���� ���κ���, ��ű�����.��",
	   "npc2: ���̹� ���� �������� �̰� �ذ����� �Ұ����ϴٰ� ���ھ����� ���� �׷��� �������� ����������. ������ ���� ������� ���� ������ ��Ȱ�ϴ� ���� ������ �Ǵ� �� ������.��",
	   "npc2: ��...�⼳�� �����. ���⿡�� ����� ������ �ʹ� �幰� �ʹ� �ݰ����� �׸�.��",
	   "npc2: ���׷��� ��ŵ� ������ �ǳ�ó�� Ż���� �ٶ��ٸ� �׶� �� ���� ����� �˷��൵ ���ڱ���.��",
	   "npc2: ���ϴ� ���� ����. ����� �ϴ� ���� �Ⱦ��ϴ� �� ���ƿ� Ư�� �޺� �׷��� �㿡 ���� Ȱ���ϰ� �׸��� ��ó���� ���ƴٴ���.��",
	   "npc2: ��....��? �޺��� ������ �ı� ������ ������� �ƴϳİ��? �ƴ�? ���� �����ѵ���?��",
	   "npc2: ���ƹ�ư ���� ������ڸ� ������ ������� �������� ������ ���, �׵��� ���������� �̲��� ���ƴٴϴ� �� ����.��",
	   "�÷��̾�: ����....��?��",
	   "npc2: ���� ���, ����, �г� �� �پ��� �����̿�. ������� �ƹ��͵� �������� ��ó�� �������. ������ ����, ������ ���ϴ��� ���� ���ǽ������� �Ѿƴٴϴ� ��ó����",
	   "npc2: �������� ������ �پ��ѵ�, �������ִ� ���� �ִ� �ݸ�, ���� Ư�� �������� �����Ӹ� �ݺ��ϰų�. ������ �̲��� �Ѿƿ��� ����� ��������.��",
	   "npc2: ������������, ��ſ� ���ؼ���.... �̰� �ƹ��� �˾ƺ��� ������ ���� �ȳ��Ϳ�. �̹� ���� �ڸ� �츱 �� ������ �����Ǹ� ���ϴ� ���� ���� �� ���� ��ó��.��",
	   "npc2: �������� �������� ���� �� ���� �� ���ƿ�. �׸��� �� ������ ���ϸ� �������� ���������� �°� ������ ��Ʈ���� ���� ������ ���� �ʴ´ٸ�, �ƹ��� ����� �ΰ�ó�� ��� �ִٰ� �����ؿ�. �װ��� ����̶�� �� �ϱ⿣ �ָ��ϰ�����.��",
	   "npc2: ���ƹ�ư �� �������� �������, �̷����� ���ʰ� �ʿ��ؿ�. Ȥ�� ���߿� ��ȸ �ǽŴٸ� ���ش� �ֽǼ� �ְھ��?��",
	   "npc2: ����. ���� ���� �� ������ �������� ���� ���ư� ������. �ϴ� �ķ� �����մϴ�.��",
	   "npc2: ���츮 ������ �� ���� ���� �� ���ƿ�.��",
	   "�÷��̾�: ���� �׷� ���� ��� ���⿡ �Դ��� ��ﵵ �ȳ�����, �ϴ� ��ƾ���. �׷� ���� ���Ϻ��� �ٽ� ���ƴٳ� ����.��",
	   "�÷��̾�: ���������ڸ�. ���� ���� ���� ���� �ķ��� ���, ������ �� ���� ���� ������ ������ ���� �ǰ���?��",
	   "�÷��̾�: ���ϴ� ���� ������ �Ƚ�ó�� ��� �ൿ����.��"
};

std::atomic<bool> terminateZombieThread1(false);
void zombieMoveThread1(std::vector<Zombie>& zombies, char game_map[][MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	while (!terminateZombieThread1) {
		// 1�ʸ��� ���� �̵�
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���

		// ���� �̵�	
		for (auto& zombie : zombies) {
			zombie.move(game_map, user);
		}

	}
}
void start_day1(player* user) {

	//3��
	int realTimeLimit = 300;
	system("cls");
	draw_map(1);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");

	//���� ����
	std::vector<Zombie> zombies = {
		Zombie(5, 8, 1, 0, 1),
		Zombie(2, 3, 0, 1, 1),
		Zombie(21, 11, 0, 1, 1)
	};//x��ǥ,y��ǥ,dX, dY,���ε��� 
	//tip) x,y��ǥ�� ���� �����ʿ��� ù��°#�� �����ʿ� Ŀ�� ������ �����̴¸�ŭ
	//���� �̵� ���� ������
	std::thread zombieThread(zombieMoveThread1, std::ref(zombies), game_map, user);

	user->player_x = 6;
	user->player_y = 6;
	//draw_clock(3);
	std::thread timerThread(timer);
	int dialogue_line = 0;
	int founded_item_count = 0;
	user->drawPlayer();// �ʱ� ��ġ�� ���ΰ� �׸���
	int flag = 0;
	while (true) {
		if (_kbhit()) {
			if (is_mission_failed() == 1) {
				terminateZombieThread1 = true;
				if (zombieThread.joinable()) {
					zombieThread.join();
				}
				if (timerThread.joinable()) {
					timerThread.join();
				}
				break;
			}
			int key = _getch();

			if (key == 224) { // ����Ű �Է� Ȯ��
				key = _getch();

				user->clearPlayer();
				int newX = user->player_x, newY = user->player_y;
				switch (key) {
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}
				if (flag == 1) {
					setCursorPosition(user->player_x * 2+1, user->player_y+1);
					setColor(6); std::cout << "��"; setColor(7);
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
					flag = 0;
				}
				// �̵� ���� ���� Ȯ��
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[1][newY][newX] == ' ' && !is_zombie_position(newX, newY,1)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[1][newY][newX] == '%' && !is_zombie_position(newX, newY, 1)) {
					setCursorPosition(user->player_x*2+1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY,1)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					updateTextBox("����");

					if (user->heart == 0) {
						bad_ending();
					}
				}

				user->drawPlayer();
			}
			else if (key == ' ' && is_player_near_item(user,1)) { // ����Ű�� ������ ȹ��
				game_map[1][newY][newX] = ' ';
				founded_item_count++;
				draw_map(1);
				user->drawPlayer();
				if (founded_item_count == 2) {//�����۰���
					updateTextBox("");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
			}
			else if (key == ' ' && is_player_near_npc(user,1)) { // �����̽��ٷ� NPC�� ��ȭ
				dialogue_clear();
				updateDialogue(dialogue_1[dialogue_line++]);
			}
		}
	}
	//6��
	flag = 0;
	system("cls");
	draw_map(2);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");
	user->player_x = 30;
	user->player_y = 12;
	start_timer_running();
	dialogue_line = 0;
	founded_item_count = 0;
	user->drawPlayer();// �ʱ� ��ġ�� ���ΰ� �׸���
	draw_clock(6);
	while (true) {
		if (_kbhit()) {
			if (is_mission_failed() == 1) {
				terminateZombieThread1 = true;
				if (zombieThread.joinable()) {
					zombieThread.join();
				}
				if (timerThread.joinable()) {
					timerThread.join();
				}
				break;
			}


			int key = _getch();

			if (key == 224) { // ����Ű �Է� Ȯ��
				key = _getch();

				user->clearPlayer();
				int newX = user->player_x, newY = user->player_y;
				switch (key) {
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}

				if (flag == 1) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y + 1);
					setColor(6); std::cout << "��"; setColor(7);
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
					flag = 0;
				}

				// �̵� ���� ���� Ȯ��
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[2][newY][newX] == ' ' && !is_zombie_position(newX, newY, 2)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[2][newY][newX] == '%' && !is_zombie_position(newX, newY, 2)) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}

				else if (is_zombie_position(newX, newY, 2)) {
					user->heart--;
					printstat(user);
					setCursorPosition(2, 23);
					updateTextBox("����");

					if (user->heart == 0) {
						bad_ending();
					}
				}

				user->drawPlayer();
			}
			else if (key == ' ' && is_player_near_item(user, 2)) { // ����Ű�� ������ ȹ��
				game_map[2][newY][newX] = ' ';
				founded_item_count++;
				draw_map(2);
				user->drawPlayer();
				if (founded_item_count == 3) {//�����۰���
					updateTextBox("");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, 2)) { // �����̽��ٷ� NPC�� ��ȭ
				dialogue_clear();
				updateDialogue(dialogue_1[dialogue_line++]);
			}
		}
	}
	//9��
	system("cls");
	realTimeLimit = 300;
	draw_map(3);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");
	user->player_x = 6;
	user->player_y = 6;
	start_timer_running();
	dialogue_line = 0;
	founded_item_count = 0;
	user->drawPlayer();// �ʱ� ��ġ�� ���ΰ� �׸���
	draw_clock(9);
	flag = 0;
	while (true) {
		if (_kbhit()) {
			if (is_mission_failed() == 1) {
				terminateZombieThread1 = true;
				if (zombieThread.joinable()) {
					zombieThread.join();
				}
				if (timerThread.joinable()) {
					timerThread.join();
				}
				break;
			}
			int key = _getch();

			if (key == 224) { // ����Ű �Է� Ȯ��
				key = _getch();

				user->clearPlayer();
				int newX = user->player_x, newY = user->player_y;
				switch (key) {
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}
				if (flag == 1) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y + 1);
					setColor(6); std::cout << "��"; setColor(7);
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
					flag = 0;
				}

				// �̵� ���� ���� Ȯ��
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[3][newY][newX] == ' ' && !is_zombie_position(newX, newY, 3)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[3][newY][newX] == '%' && !is_zombie_position(newX, newY, 3)) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY, 3)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					updateTextBox("����");

					if (user->heart == 0) {
						bad_ending();
					}
				}

				user->drawPlayer();
			}
			else if (key == ' ' && is_player_near_item(user, 3)) { // ����Ű�� ������ ȹ��
				game_map[3][newY][newX] = ' ';
				founded_item_count++;
				draw_map(3);
				user->drawPlayer();
				if (founded_item_count == 4) {//�����۰���
					terminateZombieThread1 = true;
					if (zombieThread.joinable()) {
						zombieThread.join();
					}
					updateTextBox("");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, 3)) { // �����̽��ٷ� NPC�� ��ȭ
				dialogue_clear();
				updateDialogue(dialogue_1[dialogue_line++]);
			}
		}
	}

}