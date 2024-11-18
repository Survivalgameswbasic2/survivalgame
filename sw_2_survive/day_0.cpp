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
// day 0 ��ȭ��
std::string dialogue_0[] = {
	   "npc: ���ƾ�! ��������? �� ���? ����� �� ���⿡? �ƴ� ��� ���⿡?��",
	   "�÷��̾�: ��Ȥ�� ����̼���? �׷��� �Ⱥ��̴µ�...��",
	   "npc: ��....����̰ŵ��. ������ ��� ���⿡ �Դµ���?��",
	   "�÷��̾�: ��...����� �����. ����.... �����ĿԴٴ� ���ۿ�...��",
	   "npc: ��...�׷�����. �׷� �ϴ� ���� �����ٰԿ�.��",
	   "npc: ���ϴ� ��������״� ���� �ִ� �ķ�����.. �� ��������? Ȥ�� �̹� ��������...�� ������. �չ����� �����׿�.��",
	   "�÷��̾�: ��������ؼ� ����� �ؾ��մϴ�.��",
	   "npc: ��....��.  �ϴ� ����� ���� �ǳ����ִ� �����̿���.��",
	   "npc: �������� ������ ���� �ƴ�����, �׷��� �ٱ� ���󺸴� �����ϱ��.��",
	   "npc: ���� �ϴ� ������ �̰����� �帱�Կ䡱",
	   "npc: ���� ������ Ʃ�丮�� ���ƺ����� �������䡱",
	   "npc: ���ϴ� ���� �ֺ��� ������� �������� �����ϱ� �Ƚ��ϼ���.��",
	   "npc: ���׷��ٰ� �ʹ� ������ �ٰ����� �����ϴϱ� �����Ͻð��.��",
	   "npc: ���ϴ� �����Ϸ��� �翬�� ���ڰ�, �� �Ծ�߰���? ���̶�� ���� ���̱⿣ ��Ȳ�� ��������..��",
	   "npc: ���ƹ�ư �ϴ� �ķ��� �ٴڳ����. ��� �Ʊ ������ ���� �ķ��̾��µ� ������� �纸�ѰŶ󱸿�?��",
	   "npc: ���׷��� �ۿ� ������ �ķ�, �� ���� ���ؿ;��ؿ�. ���� ������� ���ؼ���.��",
	   "npc: ������� ���� �ڰų� �޽İ������� ���ŵ� ��������.��",
	   "npc: ���� �翬�� ���� �ķ��� ���� ���Ϸ� ����������.��",
	   "npc: ��...���� �����ؿ�... ���忡 ������� ���� �𸣰����� �޺��� �ʹ� ���. �������� �ı��Ȱ���... �޺��� �ʹ� ���� ���� ������.��",
	   "npc: ���ϴ� ����� ���� �Ͼ�ٰ� �ϼ����� ���⼭ ������. ���� ���� ���� ���� ���� �ķ��� ���Ϸ� �����Կ�.��",
	   "npc: ����? �ķ��̳� ���� ���������� ���� �ʳİ��?��",
	   "npc: ��...�ϴ� ���� �Ϸ翡 500ml�̻� ���� ������ ��¥ ����������.. ���� �޾���� �˾ƿ�. �ķ��� �Ϸ����� ��������.. ���������� ����...��",
	   "npc: ���׷��� �ķ��� �ϴ� �׷��� �ĵ� ���� ������ ���ؾ��ϱ� ������ ���߸��ؿ�.��",
	   "npc: ��...�׷� �̸���",
	   "�÷��̾�: ���� �׷� ���� ��� ���⿡ �Դ��� ��ﵵ �ȳ�����, �ϴ� ��ƾ���. �׷� ���� ���Ϻ��� �ٽ� ���ƴٳ� ����.��",
	   "�÷��̾�: ���������ڸ�. ���� ���� ���� ���� �ķ��� ���, ������ �� ���� ���� ������ ������ ���� �ǰ���?��"
};


void start_day0(player* user) {
	system("cls");
	int realTimeLimit = 300;

	draw_map(0);         // Ž�� ��
	printstat(user); // ������ â 
	updateTextBox("");

	user->player_x = 5;
	user->player_y = 6;

	std::thread timerThread(timer);

	int dialogue_line = 0;
	int founded_item_count = 0;
	user->drawPlayer();// �ʱ� ��ġ�� ���ΰ� �׸���
	draw_clock(0);
	while (true) {
		if (_kbhit()) {
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

				// �̵� ���� ���� Ȯ��
				if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
					game_map[0][newY][newX] == ' ' && !is_zombie_position(newX, newY,0)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY,0)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					std::cout << "����";

					if (user->heart == 0) {
						bad_ending();
					}
				}
				user->drawPlayer();
			}
			else if (key == ' ' && is_player_near_item(user,0)) { // ����Ű�� ������ ȹ��
				updateTextBox("");
				game_map[0][newY][newX] = ' ';
				founded_item_count++;
				draw_map(0);
				user->drawPlayer();
				if (founded_item_count == 2) {
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					return;
				}
			}
			else if (key == ' ' && is_player_near_npc(user,0)) { // �����̽��ٷ� NPC�� ��ȭ
				dialogue_clear();
				updateDialogue(dialogue_0[dialogue_line++]);
			}
		}
	}

}