#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>

#define STAGE_WIDTH 34  // �� �ʺ�
#define STAGE_HEIGHT 20 // �� ����
#define MAX_HEALTH 5    // �ִ� ü��

int playerX = 1; // �÷��̾� �ʱ� X ��ǥ
int playerY = 1; // �÷��̾� �ʱ� Y ��ǥ
int health = MAX_HEALTH;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

int currentDay = 0; // ���� ���� (0���� ����)
/*
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
*/

//1����, *(������), x(����), N(npc)
char game_map[STAGE_HEIGHT][STAGE_WIDTH + 1] = {
	"##################################",
	"#          ######       ######x *#",
	"#   ######      ######       ## ##",
	"#   #* xx#       #*   #       #  #",
	"#   #  xx#       #     #      ## #",
	"#   #   x#### #######  ####   #  #",
	"#   #                     #   # ##",
	"#   #######    #####     ###### x#",
	"#         #     ###      #       #",
	"#xxxxx    #     ###      # #######",
	"#         #     ###      #       #",
	"#  x#######     ###      ######  #",
	"#   #                    #       #",
	"#x  #        #### ####   # #######",
	"#   ######   #       #   #       #",
	"# x      #   # #   # #   ####### #",
	"#   #######  #*#   #*#   ##      #",
	"#           #### N ####     #### #",
	"##################################"
};


/*
//2����, *(������), x(����), N(npc)
char game_map[STAGE_HEIGHT][STAGE_WIDTH + 1] = {
	"##################################",
	"#      ###           ###  x     x#",
	"#     ##*##         ##*##     #  #",
	"#    ##   ##       ##   ##   #*# #",
	"#       #             #          #",
	"#  x   ###       #   ###    ##   #",
	"#    ## * ##    #x#  #     # *## #",
	"#  ###x# #x### #   ## #      ##  #",
	"#   x##  x##     ####     ###    #",
	"#       ##   ###  x   ###   ##   #",
	"#      ####    ##    ##   ## #   #",
	"# x   #  xx#    ######    ##   # #",
	"#   x### x### ###*###x     # # ###",
	"#    x   #   ###x  ##x  x x ##   #",
	"#   #     ## ##x    ##  ##   ###*#",
	"#  #*#     ###x      ## ##   #####",
	"# ## ##     #x         ###     ###",
	"###    # #         #       ##x   #",
	"##   #     x## #     x#####      #",
	"##################################"
};
*/
// �ܼ� Ŀ�� ��ġ ���� �Լ�
void setCursorPosition(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// �ܼ� �ؽ�Ʈ ���� ���� �Լ�
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// �ؽ�Ʈ â ������Ʈ �Լ�
void updateTextBox(const std::string& message) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 3;
	int width = STAGE_WIDTH * 2;
	int height = 5;

	setCursorPosition(xOffset, yOffset);
	printf("�ؽ�Ʈ â");

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			setCursorPosition(xOffset + x, yOffset + y + 1);
			if (y == 0) {
				if (x == 0) printf("��");
				else if (x == width - 1) printf("��");
				else printf("��");
			}
			else if (y == height - 1) {
				if (x == 0) printf("��");
				else if (x == width - 1) printf("��");
				else printf("��");
			}
			else {
				if (x == 0 || x == width - 1) printf("��");
				else printf(" ");
			}
		}
	}

	// �ؽ�Ʈ ��� �κ�
	const int maxLineLength = 65;  // �� �ٿ� ǥ���� �ִ� ���� ��
	int currentLine = 0;           // ���� �� ��ȣ
	int xCursorPos = xOffset + 2;  // �ؽ�Ʈ ���� x ��ǥ
	int yCursorPos = yOffset + 2;  // �ؽ�Ʈ ���� y ��ǥ

	for (size_t i = 0; i < message.size(); i += maxLineLength) {
		setCursorPosition(xCursorPos, yCursorPos + currentLine);
		std::cout << message.substr(i, maxLineLength);
		currentLine++;
		if (currentLine >= height - 2) break; // �ؽ�Ʈ â ���̸� �ʰ����� �ʵ��� ����
	}
}
// ����â ��� �Լ�
void printfstat(int heart) {
	SHORT y = 1;
	SHORT x = STAGE_WIDTH * 2 + 4;
	setCursorPosition(x, y);
	printf("������������������������������������������������������");
	setCursorPosition(x, y + 1);
	printf("�� ü�� :     ");
	for (int i = 0; i < heart; i++) printf(" ��");
	for (int i = 0; i < MAX_HEALTH - heart; i++) printf(" ��");
	printf(" ��");
	setCursorPosition(x, y + 8);
	printf("������������������������������������������������������");
}

// ���ΰ� ��ġ ����� �Լ�
void clearPlayer(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1);
	printf("  ");
}

// ���ΰ� �׸��� �Լ�
void drawPlayer(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1);
	setColor(10);
	printf("��");
	setColor(7);
}

// ���� ���� ��ġ Ȯ�� �Լ�
bool canMove(int x, int y) {
	return game_map[y][x] == ' ';
}

// ���� �浹 �Լ�
bool isZombiePosition(int x, int y) {
	return game_map[y][x] == 'x';
}

// NPC ��ó���� ��ȭ ��� �Լ�
void startConversation() {
	std::string filename = "day1" "_script.txt";
	static std::ifstream dialogueFile(filename);
	static bool fileOpened = false;

	if (!fileOpened) {
		dialogueFile.open(filename);
		fileOpened = true;
	}

	if (!dialogueFile.is_open()) {
		updateTextBox("��ȭ ������ �� �� �����ϴ�.");
		return;
	}

	std::string line;
	if (std::getline(dialogueFile, line)) {
		updateTextBox(line);  // �� �پ� �ؽ�Ʈ â�� ���
	}
	else {
		updateTextBox("��ȭ�� �������ϴ�.");
		dialogueFile.close();
		fileOpened = false;
	}
}

// �÷��̾ NPC ��ó�� �ִ��� Ȯ��
bool isPlayerNearNPC() {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = playerX + dx[i];
		int newY = playerY + dy[i];
		if (newX >= 0 && newX < STAGE_WIDTH && newY >= 0 && newY < STAGE_HEIGHT &&
			game_map[newY][newX] == 'N') {
			return true;
		}
	}
	return false;
}

// �÷��̾ ������ ��ó�� �ִ��� Ȯ��
bool isPlayerNearItem() {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = playerX + dx[i];
		int newY = playerY + dy[i];
		if (newX >= 0 && newX < STAGE_WIDTH && newY >= 0 && newY < STAGE_HEIGHT &&
			game_map[newY][newX] == '*') {
			return true;
		}
	}
	return false;
}

// Ž�� �� �� ��Ÿ ��� ��� �Լ�
void drawStage() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1);
			switch (game_map[y][x]) {
			case '#': printf("��"); break;
			case 'x': setColor(12); printf("��"); setColor(7); break;
			case '*': setColor(14); printf("��"); setColor(7); break;
			case 'N': setColor(9);  printf("��"); setColor(7); break;
			default: printf("  "); break;
			}
		}
	}
}

// ���� ����
void gameLoop() {
	drawPlayer(playerX, playerY);
	while (true) {
		if (_kbhit()) {
			int key = _getch();

			if (key == 224) {
				key = _getch();
				int newX = playerX;
				int newY = playerY;

				clearPlayer(playerX, playerY);
				switch (key) {
				case 72: newY--; break; // ��
				case 80: newY++; break; // �Ʒ�
				case 75: newX--; break; // ����
				case 77: newX++; break; // ������
				}

				if (newY >= 0 && newY < STAGE_HEIGHT && newX >= 0 && newX < STAGE_WIDTH &&
					canMove(newX, newY)) {
					playerX = newX;
					playerY = newY;
				}
				else if (isZombiePosition(newX, newY)) {  // ����� �浹
					health--;
					printfstat(health);
					updateTextBox("��, �����!");
					if (health == 0) {
						updateTextBox("Game over!");
						break;
					}
				}
				drawPlayer(playerX, playerY);
			}
			else if (key == 13 && isPlayerNearItem()) { // ����Ű�� ������ ȹ��
				updateTextBox("�������� ȹ���߽��ϴ�!");
			}
			else if (key == ' ' && isPlayerNearNPC()) {
				startConversation();
			}
		}
	}
}

int main() {
	system("cls");
	drawStage();
	printfstat(health);
	updateTextBox("Ž���� �����ϼ���.");
	gameLoop();
	return 0;
}
