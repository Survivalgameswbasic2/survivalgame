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
// day 2 ��ȭ��
std::string dialogue_2[] = {
	"������ ����� ķ���� �̾�������... �ϱ� �̷��� ���� ���� �Ƹ��ٿ� �ڿ��� ������ �����ϱ�. ������ ������ ���� ���״�� ������������..��",
	"���ƹ�ư ���⼭ ������ ��ǰ���� ������ ���̵�, ������ ����, �ķ��̵� ���̵�, ���� �� �ִ� ���� �� ���ϴ°ž�!��",
	"",
	"������ �߰�:",
	"���̰�...�� ���� ���� ���� ������ �ֳ�? �Դٰ� �ű⿡ �ǳ�ó�� �ִٰ�? ���� �� ���� ������ ���� ������� ���� ����� �ӽ� �ǳ�ó�� ���� �ǰ�?��",
	"������. ���� �������� ������ �ǰ���. �׷� �ű⿣ �и� ����� ��������!��",
	"������ ����� ���̱� �����߾�!��"
};


void start_day2(player* user) {
	//3��
	system("cls");
	draw_map(4);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");
	user->player_x = 1;
	user->player_y = 1;
	std::thread timerThread(timer);
	int dialogue_line = 0;
	int founded_item_count = 0;
	user->drawPlayer();// �ʱ� ��ġ�� ���ΰ� �׸���
	draw_clock(3);
	int flag=0;
	while (true) {
		if (_kbhit()) {
			if (is_mission_failed() == 1) {
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
					game_map[4][newY][newX] == ' ' && !is_zombie_position(newX, newY, 4)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[4][newY][newX] == '%' && !is_zombie_position(newX, newY, 4)) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY, 1)) {
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
			else if (key == ' ' && is_player_near_item(user, 4)) { // ����Ű�� ������ ȹ��
				game_map[4][newY][newX] = ' ';
				founded_item_count++;
				draw_map(4);
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
			else if (key == ' ' && is_player_near_npc(user, 4)) { // �����̽��ٷ� NPC�� ��ȭ
				dialogue_clear();
				updateDialogue(dialogue_2[dialogue_line++]);
			}
		}
	}
	//6��
	system("cls");
	draw_map(5);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");
	user->player_x = 5;
	user->player_y = 6;
	start_timer_running();
	dialogue_line = 0;
	founded_item_count = 0;
	user->drawPlayer();// �ʱ� ��ġ�� ���ΰ� �׸���
	draw_clock(6);
	flag = 0;
	while (true) {
		if (_kbhit()) {
			if (is_mission_failed() == 1) {
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
					game_map[5][newY][newX] == ' ' && !is_zombie_position(newX, newY, 5)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[5][newY][newX] == '%' && !is_zombie_position(newX, newY, 5)) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY, 5)) {
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
			else if (key == ' ' && is_player_near_item(user, 5)) { // ����Ű�� ������ ȹ��
				game_map[5][newY][newX] = ' ';
				founded_item_count++;
				draw_map(5);
				user->drawPlayer();
				if (founded_item_count == 4) {//�����۰���
					updateTextBox("");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, 5)) { // �����̽��ٷ� NPC�� ��ȭ
				dialogue_clear();
				updateDialogue(dialogue_2[dialogue_line++]);
			}
		}
	}
	//9��
	system("cls");
	draw_map(6);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");
	user->player_x = 5;
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
					game_map[6][newY][newX] == ' ' && !is_zombie_position(newX, newY, 6)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[6][newY][newX] == '%' && !is_zombie_position(newX, newY, 6)) {
					setCursorPosition(user->player_x * 2 + 1, user->player_y);
					flag = 1;
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY, 6)) {
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
			else if (key == ' ' && is_player_near_item(user, 6)) { // ����Ű�� ������ ȹ��
				game_map[6][newY][newX] = ' ';
				founded_item_count++;
				draw_map(6);
				user->drawPlayer();
				if (founded_item_count == 4) {//�����۰���
					updateTextBox("");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					break;
				}
			}
			else if (key == ' ' && is_player_near_npc(user, 6)) { // �����̽��ٷ� NPC�� ��ȭ
				dialogue_clear();
				updateDialogue(dialogue_2[dialogue_line++]);
			}
		}
	}
}