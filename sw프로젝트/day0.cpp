#include "NPC��ȭâ.h"
#include "����â.h"
#include "��ȭâ.h"
#include "����â.h"
#include "Ÿ�̸�.h"
#include "�÷��̾�.h"
#include <thread>
#include <conio.h>
#include "����.h"
#include <string>
#include <fstream>




std::string dialogue[] = {
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
char game_map[STAGE_HEIGHT][STAGE_WIDTH + 1] = {
"##################################",
"#              ####              #",
"#             ######             #",
"#    ####    ##xxx ##    ####    #",
"#   ##  ##  ##      ##  ## *##   #",
"#   #    ####        ####    #   #",
"#                            #   #",
"#   ##   x   ###  ###       ##   #",
"#    ###    ##      ##    ###    #",
"#      ## ###        ### ##      #",
"#      ## ###        ### ##      #",
"#    ###    ##      ##    ###    #",
"#   ##       ###  ###       ##   #",
"#    # x                    #    #",
"#   #    ####        ####    #   #",
"#   ## *##  ##      ##  ##N ##   #",
"#    ####    ## xxx##    ####    #",
"#             ######             #",
"#              ####              #",
"##################################"
};



bool isPlayerNearNPC(player * user) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = user->player_x + dx[i];
		int newY = user->player_y + dy[i];
		if (newX >= 0 && newX < STAGE_WIDTH && newY >= 0 && newY < STAGE_HEIGHT &&
			game_map[newY][newX] == 'N') {
			return true;
		}
	}
	return false;
}
bool isPlayerNearItem(player* user) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = user->player_x + dx[i];
		int newY = user->player_y + dy[i];
		if (newX >= 0 && newX < STAGE_WIDTH && newY >= 0 && newY < STAGE_HEIGHT &&
			game_map[newY][newX] == '*') {
			return true;
		}
	}
	return false;
}
bool isZombiePosition(int x, int y) {
	return game_map[y][x] == 'x';
}

void drawStage2() {
	// �׵θ��� �� ���
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1);
			switch (game_map[y][x]) {
			case '#': printf("��"); break;
			case 'x': setColor(12); printf("��"); setColor(7); break; // ����
			case '*': setColor(14); printf("��"); setColor(7); break; // ������
			case 'N': setColor(9); printf("��"); setColor(7); break; // NPC
			default: printf("  "); break;
			}
		}
	}
}
void start_day0(player* user) {
	system("cls");
	int realTimeLimit = 300;
	CommunicationBoxNPC(0,user);
	
	drawStage();         // Ž�� ��
	printstat(user); // ������ â 
	user->drawPlayer(); // �ʱ� ��ġ�� ���ΰ� �׸���
	updateTextBox("");



	drawStage2();


	user->player_x = 5;
	user->player_y = 6;

	std::thread timerThread(timer);
	int cn = 0;
	user->drawPlayer();
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
				if (newY >= 0 && newY < STAGE_HEIGHT && newX >= 0 && newX < STAGE_WIDTH &&
					game_map[newY][newX] == ' ' && !isZombiePosition(newX, newY)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (isZombiePosition(newX, newY)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					std::cout << "�� �����";

					if (user->heart == 0) {
						setCursorPosition(1, 23);
						std::cout << "GAMEOVER";
						break;
					}
				}

				user->drawPlayer();
			}
			else if (key == 13 && isPlayerNearItem(user)) { // ����Ű�� ������ ȹ��
				updateTextBox("�������� ȹ���߽��ϴ�!");
			}
			else if (key == ' ' && isPlayerNearNPC(user)) { // �����̽��ٷ� NPC�� ��ȭ
				setCursorPosition(1, 23);
				std::cout << "                                                                     ";
				setCursorPosition(1, 24);
				std::cout << "                                                                     ";
				setCursorPosition(1, 25);
				std::cout << "                                                                     ";

				setCursorPosition(1, 23);
				std::cout << dialogue[cn++];
				setCursorPosition(1, 24);
				std::cout << dialogue[cn++];
				setCursorPosition(1, 25);
				std::cout << dialogue[cn++];
			}
		}
	}

}