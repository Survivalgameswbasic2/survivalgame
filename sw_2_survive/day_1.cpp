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

void start_day1(player* user) {
	system("cls");
	int realTimeLimit = 300;

	draw_map(1);         // Ž�� ��
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
					game_map[1][newY][newX] == ' ' && !is_zombie_position(newX, newY,1)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (is_zombie_position(newX, newY,1)) {
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
			else if (key == ' ' && is_player_near_item(user,1)) { // ����Ű�� ������ ȹ��
				updateTextBox("�������� ȹ���߽��ϴ�!");
				game_map[1][newY][newX] = ' ';
				founded_item_count++;
				draw_map(1);
				user->drawPlayer();
				if (founded_item_count == 4) {
					updateTextBox("�� Ŭ����!!");
					stop_timer_running();
					if (timerThread.joinable()) {
						timerThread.join();
					}
					std::cout << "clear";
					return;
				}
			}
			else if (key == ' ' && is_player_near_npc(user,1)) { // �����̽��ٷ� NPC�� ��ȭ
				dialogue_clear();
				updateDialogue(dialogue_1[dialogue_line++]);
			}
		}
	}

}