#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include<iomanip>
#include<Windows.h>
#include <atomic>
#include<string>

#define STAGE_WIDTH 34  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 
#define MAX_HEALTH 5    // �ִ� ü��
#define stat_Height 12 //����â�� ������ ������ ���� 
int TIMEWIDTH = 27;// 6ĭ����
int TIMEHEIGHT = 5;
void setCursorPosition2(int x, int y); //Ŀ�� ��ġ ����
void CommunicationBoxNPC(int flag); //NPC ���� �ڽ�

// �ܼ� Ŀ�� ��ġ ����
void setCursorPosition(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// �ܼ� �ؽ�Ʈ ���� ����
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Ž�� �� ������ ���� (������ �̵� ������ ����, #�� ��)
char game_map[STAGE_HEIGHT][STAGE_WIDTH + 1] = {
	"##################################",
	"#                                #",
	"#  ####  #  #####      #####     #",
	"#     #  #     #                 #",
	"#  #  #  #####  #####  #####     #",
	"#  #           #         #       #",
	"#  #######  #######  #  #####    #",
	"#  #         #       #           #",
	"#  #  #######  ########  #####   #",
	"#  #        #            #       #",
	"#  #######  #  ########  #  #### #",
	"#     #     #        #           #",
	"#  ####  #######  #####  ####### #",
	"#          #            #        #",
	"#  ######        #######    #### #",
	"#  #      ####             #     #",
	"#  ###########  #######  #####   #",
	"#           #              #     #",
	"#   ######         #####   ###   #",
	"##################################"
};

// ���� ��ġ �迭
int zombie_positions[][2] = {
	{10, 10}, {5, 15}, {20, 3}, {15, 12}, {8, 17}
};
int num_zombies = sizeof(zombie_positions) / sizeof(zombie_positions[0]);

// �ؽ�Ʈ â �ʱ�ȭ �� �޽��� ��� �Լ�
void updateTextBox(const char* message) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 3; // �� â �ϴܿ� �ؽ�Ʈ â ��ġ ����
	int width = STAGE_WIDTH * 2;    // �ؽ�Ʈ â ���� ����
	int height = 5;                 // �ؽ�Ʈ â ���� ����

	// �ؽ�Ʈ â �׵θ��� ���� ���
	setCursorPosition(xOffset, yOffset);
	printf("�ؽ�Ʈ â");

	// �ؽ�Ʈ â �׵θ� �׸���
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

	// �ؽ�Ʈ �޽��� ���
	setCursorPosition(xOffset + 2, yOffset + 2);
	printf("%s", message);
}

// Ž�� �ʰ� �׵θ� �׸��� �Լ�
void drawStage() {
	// �׵θ� ���
	setCursorPosition(0, 0);
	printf("��");
	for (int x = 0; x < STAGE_WIDTH * 2; x++) printf("��");
	printf("��");

	// �� ���ο� �¿� �׵θ�
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		setCursorPosition(0, y + 1);
		printf("��"); // ���� �׵θ�
		for (int x = 0; x < STAGE_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1); // �� ĭ�� �����ϵ��� x * 2 + 1
			if (game_map[y][x] == '#') {
				printf("��"); // ���� ������� ǥ��
			}
			else {
				printf("  "); // �̵� ������ ������ �������� ǥ��
			}
		}
		printf("��"); // ������ �׵θ�
	}

	// �׵θ� �ϴ�
	setCursorPosition(0, STAGE_HEIGHT + 1);
	printf("��");
	for (int x = 0; x < STAGE_WIDTH * 2; x++) printf("��");
	printf("��");
}
//����â&������â 

void printfstat(int heart, int mental, int food, int water, int bullet, int heal) {

	SHORT y = 1;
	SHORT x = STAGE_WIDTH * 2 + 4;
	COORD pos1 = { x ,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos1);

	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("������������������������������������������������������");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("�� ü�� :     ");
	for (int i = 0; i < heart; i++) {
		printf(" ��");
	}
	for (int i = 0; i < 5 - heart; i++) {
		printf(" ��");
	}
	printf("   ��");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);

	printf("�� ��Ʈ���� : ");
	for (int i = 0; i < mental; i++) {
		printf(" ��");
	}
	for (int i = 0; i < 5 - mental; i++) {
		printf(" ��");
	}
	printf("   ��");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("��                         ��");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("�� �ķ� X %d                ��", food);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("�� �� X %d                  ��", water);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (bullet != 0) {
		printf("�� źȯ X %d                ��", bullet);
	}
	else {
		printf("�� ---                     ��");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (heal != 0) {
		printf("�� ġ���� X %d              ��", heal);
	}
	else {
		printf("�� ---                     ��");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("������������������������������������������������������");
}


// ü�� ���� �Լ�
void updateHealth(int health) {
	/*int xOffset = STAGE_WIDTH * 2 + 6;
	int yOffset = 2;
	setCursorPosition(xOffset, yOffset);
	printf("ü��: ");
	setColor(12); // ������ ��Ʈ
	for (int i = 0; i < health; i++) {
		printf("�� ");
	}
	setColor(7); // �⺻ �������� ����
	for (int i = health; i < MAX_HEALTH; i++) {
		printf("  ");
	}*/

	printfstat(health, 2, 3, 4, 0, 0);
}



// ���ΰ� �׸��� �Լ� (�ʷϻ�)
void drawPlayer(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1); // �׵θ� ���ʿ� �°� ��ġ ����
	setColor(10); // �ʷϻ� �÷��̾�
	printf("��");
	setColor(7); // �⺻ �������� ����
}

// ���ΰ� ��ġ�� ����� ���� �Լ�
void clearPlayer(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1); // �׵θ� ���ʿ� �°� ��ġ ����
	printf("  "); // ���� ��ġ �����
}

//���� �׸��� �Լ� (������)
void drawEnemy(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1); // �׵θ� ���ʿ� �°� ��ġ ����
	setColor(12); // ������ ����
	printf("��");
	setColor(7); // �⺻ ����
}

// ���� ��ġ ���� Ȯ��
int isZombiePosition(int x, int y) {
	for (int i = 0; i < num_zombies; i++) {
		if (zombie_positions[i][0] == x && zombie_positions[i][1] == y) {
			return 1; // �ش� ��ġ�� ���� ����
		}
	}
	return 0; //���� ����
}

//Ÿ�̸ӱ���
COORD TIMETABLE = { STAGE_WIDTH * 2 + 4,25 };
COORD NPCANSWER = { STAGE_WIDTH * 2 + 4,17 };
HANDLE handle;
std::atomic<bool> missionFailed(false); // �̼ǽ��� ����
std::atomic<bool> timerRunning(true); // �ð� �帧 ����
std::atomic<bool> isExplore(true);
void createTimeTable() {
	COORD pos = TIMETABLE;
	SetConsoleCursorPosition(handle, pos);
	std::cout << "������������������������������������������������������" << std::endl;
	for (int i = 0; i < TIMEHEIGHT - 2; i++) {
		pos.Y++;
		SetConsoleCursorPosition(handle, pos);
		std::cout << "��      ��                  ��" << std::endl;
	}
	pos.Y++;
	SetConsoleCursorPosition(handle, pos);
	std::cout << "������������������������������������������������������" << std::endl;
}

void timer(int timeLimitSeconds) {
	COORD pos = { TIMETABLE.X + 2, TIMETABLE.Y + TIMEHEIGHT / 2 -1};
	int remainingTime = timeLimitSeconds;

	while (remainingTime > 0 && timerRunning) {
		if (isExplore) {
			std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�ʸ��� ����
			remainingTime--;

			int minutes = remainingTime / 60;
			int seconds = remainingTime % 60;

			SetConsoleCursorPosition(handle, pos);
			std::cout << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	if (remainingTime <= 0) {
		missionFailed = true;
		std::cout << "�ӹ� ����!" << std::endl;
	}
}

int NpcAnswer() {
	isExplore = false;

	SetConsoleCursorPosition(handle, NPCANSWER);
	std::cout << "YES OR NO : ";
	std::string answer;
	std::cin >> answer;
	if (answer == "YES") {
		SetConsoleCursorPosition(handle, NPCANSWER);
		std::cout << "               ";
		isExplore = true;
		return 1;
	}
	else {
		SetConsoleCursorPosition(handle, NPCANSWER);
		std::cout << "               ";
		isExplore = true;
		return 0;
	}
}
//npc��ȭâ ��� �Լ� 

void setCursorPosition2(int x, int y) {
	COORD pos = { x,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos);
	CONSOLE_CURSOR_INFO curCursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
	curCursorInfo.bVisible = 0;
	SetConsoleCursorInfo(hConsoleOut, &curCursorInfo);
}

void CommunicationBoxNPC(int flag) {
	//npc ���� ���°� �ƴϸ� �ڽ� ����
	if (flag == 0) {
		setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 1);
		printf("                                        ");
		for (int i = 0; i < 7; i++) {
			setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 2 + i);
			printf("                                     ");
		}
		setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 8);
		printf("                                             ");
		return;
	}
	//npc ���� �����̸� �ڽ� ����
	setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 1);
	printf("������������������������������������������������������");
	for (int i = 0; i < 7; i++) {
		setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 2 + i);
		printf("��                         ��");
	}
	setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 8);
	printf("������������������������������������������������������");
}

int main() {
	int playerX = 1; // ���ΰ� �ʱ� X ��ǥ
	int playerY = 1; // ���ΰ� �ʱ� Y ��ǥ
	int health = MAX_HEALTH;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int realTimeLimit = 300; // 5��
	

	system("cls"); // �ܼ��ʱ�ȭ
	CommunicationBoxNPC(1);
	createTimeTable();
	std::thread timerThread(timer, realTimeLimit);
	// timerunning�� false�� �ٲٸ� Ÿ�̸� ����
	// timerRunning = false;
	//�ð����Ῡ��
	/*if (timerThread.joinable()) {
		timerThread.join();

		std::cout << "���� ����" << std::endl;
	}*/
	drawStage();         // Ž�� ��
	printfstat(1, 2, 3, 4, 0, 0); // ������ â 
	drawPlayer(playerX, playerY); // �ʱ� ��ġ�� ���ΰ� �׸���
	updateHealth(health);         // �ʱ� ü�� ǥ��
	updateTextBox("");            // �ؽ�Ʈ â

	// �ʱ� ����
	for (int i = 0; i < num_zombies; i++) {
		drawEnemy(zombie_positions[i][0], zombie_positions[i][1]);
	}

	while (1) {
		if (_kbhit()) {
			int key = _getch(); // Ű �Է��� ����

			if (key == 224) { // ����Ű �Է� Ȯ��
				key = _getch(); // ���� ����Ű �� �б�

				// �÷��̾��� ���� ��ġ �����
				clearPlayer(playerX, playerY);

				// ���ο� ��ġ ���
				int newX = playerX;
				int newY = playerY;

				// ����Ű�� ���� ���ο� ��ġ ����
				switch (key) {
				case 72: // ���� ȭ��ǥ
					newY--;
					break;
				case 80: // �Ʒ��� ȭ��ǥ
					newY++;
					break;
				case 75: // ���� ȭ��ǥ
					newX--;
					break;
				case 77: // ������ ȭ��ǥ
					newX++;
					break;
				}

				// �̵� ���� ���� Ȯ��
				if (newY >= 0 && newY < STAGE_HEIGHT && newX >= 0 && newX < STAGE_WIDTH &&
					game_map[newY][newX] == ' ' && !isZombiePosition(newX, newY)) {
					// ���̳� ���� �ƴ� ������ �̵�
					playerX = newX;
					playerY = newY;
					updateTextBox(""); // �ؽ�Ʈ â �ʱ�ȭ
				}
				else if (isZombiePosition(newX, newY)) {
					// ���� ��ġ�� �̵� �õ� �� ü�� ����
					health--;
					updateHealth(health);
					updateTextBox("��, �����!");

					if (health == 0) { // ü���� 0�� �Ǹ� ���� ����
						updateTextBox("Game over!");
						break;
					}
				}

				// ����� ��ġ�� �÷��̾� �׸���
				drawPlayer(playerX, playerY);
				
			}
		}
	}

	return 0;
}