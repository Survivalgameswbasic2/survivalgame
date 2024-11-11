#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>

#define STAGE_WIDTH 34  // 맵 너비
#define STAGE_HEIGHT 20 // 맵 높이
#define MAX_HEALTH 5    // 최대 체력

int playerX = 1; // 플레이어 초기 X 좌표
int playerY = 1; // 플레이어 초기 Y 좌표
int health = MAX_HEALTH;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

int currentDay = 0; // 현재 일차 (0부터 시작)
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

//1일차, *(아이템), x(좀비), N(npc)
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
//2일차, *(아이템), x(좀비), N(npc)
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
// 콘솔 커서 위치 설정 함수
void setCursorPosition(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 콘솔 텍스트 색상 설정 함수
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 텍스트 창 업데이트 함수
void updateTextBox(const std::string& message) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 3;
	int width = STAGE_WIDTH * 2;
	int height = 5;

	setCursorPosition(xOffset, yOffset);
	printf("텍스트 창");

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			setCursorPosition(xOffset + x, yOffset + y + 1);
			if (y == 0) {
				if (x == 0) printf("┌");
				else if (x == width - 1) printf("┐");
				else printf("─");
			}
			else if (y == height - 1) {
				if (x == 0) printf("└");
				else if (x == width - 1) printf("┘");
				else printf("─");
			}
			else {
				if (x == 0 || x == width - 1) printf("│");
				else printf(" ");
			}
		}
	}

	// 텍스트 출력 부분
	const int maxLineLength = 65;  // 한 줄에 표시할 최대 문자 수
	int currentLine = 0;           // 현재 줄 번호
	int xCursorPos = xOffset + 2;  // 텍스트 시작 x 좌표
	int yCursorPos = yOffset + 2;  // 텍스트 시작 y 좌표

	for (size_t i = 0; i < message.size(); i += maxLineLength) {
		setCursorPosition(xCursorPos, yCursorPos + currentLine);
		std::cout << message.substr(i, maxLineLength);
		currentLine++;
		if (currentLine >= height - 2) break; // 텍스트 창 높이를 초과하지 않도록 설정
	}
}
// 상태창 출력 함수
void printfstat(int heart) {
	SHORT y = 1;
	SHORT x = STAGE_WIDTH * 2 + 4;
	setCursorPosition(x, y);
	printf("┌─────────────────────────┐");
	setCursorPosition(x, y + 1);
	printf("│ 체력 :     ");
	for (int i = 0; i < heart; i++) printf(" ♥");
	for (int i = 0; i < MAX_HEALTH - heart; i++) printf(" ♡");
	printf(" │");
	setCursorPosition(x, y + 8);
	printf("└─────────────────────────┘");
}

// 주인공 위치 지우기 함수
void clearPlayer(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1);
	printf("  ");
}

// 주인공 그리기 함수
void drawPlayer(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1);
	setColor(10);
	printf("■");
	setColor(7);
}

// 벽과 좀비 위치 확인 함수
bool canMove(int x, int y) {
	return game_map[y][x] == ' ';
}

// 좀비 충돌 함수
bool isZombiePosition(int x, int y) {
	return game_map[y][x] == 'x';
}

// NPC 근처에서 대화 출력 함수
void startConversation() {
	std::string filename = "day1" "_script.txt";
	static std::ifstream dialogueFile(filename);
	static bool fileOpened = false;

	if (!fileOpened) {
		dialogueFile.open(filename);
		fileOpened = true;
	}

	if (!dialogueFile.is_open()) {
		updateTextBox("대화 파일을 열 수 없습니다.");
		return;
	}

	std::string line;
	if (std::getline(dialogueFile, line)) {
		updateTextBox(line);  // 한 줄씩 텍스트 창에 출력
	}
	else {
		updateTextBox("대화가 끝났습니다.");
		dialogueFile.close();
		fileOpened = false;
	}
}

// 플레이어가 NPC 근처에 있는지 확인
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

// 플레이어가 아이템 근처에 있는지 확인
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

// 탐험 맵 및 기타 요소 출력 함수
void drawStage() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1);
			switch (game_map[y][x]) {
			case '#': printf("■"); break;
			case 'x': setColor(12); printf("■"); setColor(7); break;
			case '*': setColor(14); printf("★"); setColor(7); break;
			case 'N': setColor(9);  printf("●"); setColor(7); break;
			default: printf("  "); break;
			}
		}
	}
}

// 게임 루프
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
				case 72: newY--; break; // 위
				case 80: newY++; break; // 아래
				case 75: newX--; break; // 왼쪽
				case 77: newX++; break; // 오른쪽
				}

				if (newY >= 0 && newY < STAGE_HEIGHT && newX >= 0 && newX < STAGE_WIDTH &&
					canMove(newX, newY)) {
					playerX = newX;
					playerY = newY;
				}
				else if (isZombiePosition(newX, newY)) {  // 좀비와 충돌
					health--;
					printfstat(health);
					updateTextBox("앗, 좀비다!");
					if (health == 0) {
						updateTextBox("Game over!");
						break;
					}
				}
				drawPlayer(playerX, playerY);
			}
			else if (key == 13 && isPlayerNearItem()) { // 엔터키로 아이템 획득
				updateTextBox("아이템을 획득했습니다!");
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
	updateTextBox("탐험을 시작하세요.");
	gameLoop();
	return 0;
}
