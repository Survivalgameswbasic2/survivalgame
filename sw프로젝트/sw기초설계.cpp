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

#define STAGE_WIDTH 34  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 
#define MAX_HEALTH 5    // 최대 체력
#define stat_Height 12 //스탯창이 끝나는 지점의 높이 
int TIMEWIDTH = 27;// 6칸차지
int TIMEHEIGHT = 5;
void setCursorPosition2(int x, int y); //커서 위치 지정
void CommunicationBoxNPC(int flag); //NPC 소통 박스

// 콘솔 커서 위치 설정
void setCursorPosition(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 콘솔 텍스트 색상 설정
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 탐험 맵 데이터 정의 (공백은 이동 가능한 공간, #은 벽)
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

// 좀비 위치 배열
int zombie_positions[][2] = {
	{10, 10}, {5, 15}, {20, 3}, {15, 12}, {8, 17}
};
int num_zombies = sizeof(zombie_positions) / sizeof(zombie_positions[0]);

// 텍스트 창 초기화 및 메시지 출력 함수
void updateTextBox(const char* message) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 3; // 맵 창 하단에 텍스트 창 위치 설정
	int width = STAGE_WIDTH * 2;    // 텍스트 창 가로 길이
	int height = 5;                 // 텍스트 창 세로 길이

	// 텍스트 창 테두리와 제목 출력
	setCursorPosition(xOffset, yOffset);
	printf("텍스트 창");

	// 텍스트 창 테두리 그리기
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

	// 텍스트 메시지 출력
	setCursorPosition(xOffset + 2, yOffset + 2);
	printf("%s", message);
}

// 탐험 맵과 테두리 그리기 함수
void drawStage() {
	// 테두리 상단
	setCursorPosition(0, 0);
	printf("┌");
	for (int x = 0; x < STAGE_WIDTH * 2; x++) printf("─");
	printf("┐");

	// 맵 내부와 좌우 테두리
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		setCursorPosition(0, y + 1);
		printf("│"); // 왼쪽 테두리
		for (int x = 0; x < STAGE_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1); // 두 칸씩 차지하도록 x * 2 + 1
			if (game_map[y][x] == '#') {
				printf("■"); // 벽은 블록으로 표시
			}
			else {
				printf("  "); // 이동 가능한 공간은 공백으로 표시
			}
		}
		printf("│"); // 오른쪽 테두리
	}

	// 테두리 하단
	setCursorPosition(0, STAGE_HEIGHT + 1);
	printf("└");
	for (int x = 0; x < STAGE_WIDTH * 2; x++) printf("─");
	printf("┘");
}
//상태창&아이템창 

void printfstat(int heart, int mental, int food, int water, int bullet, int heal) {

	SHORT y = 1;
	SHORT x = STAGE_WIDTH * 2 + 4;
	COORD pos1 = { x ,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos1);

	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("┌─────────────────────────┐");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 체력 :     ");
	for (int i = 0; i < heart; i++) {
		printf(" ♥");
	}
	for (int i = 0; i < 5 - heart; i++) {
		printf(" ♡");
	}
	printf("   │");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);

	printf("│ 스트레스 : ");
	for (int i = 0; i < mental; i++) {
		printf(" ★");
	}
	for (int i = 0; i < 5 - mental; i++) {
		printf(" ☆");
	}
	printf("   │");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│                         │");
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 식량 X %d                │", food);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("│ 물 X %d                  │", water);
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (bullet != 0) {
		printf("│ 탄환 X %d                │", bullet);
	}
	else {
		printf("│ ---                     │");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (heal != 0) {
		printf("│ 치료제 X %d              │", heal);
	}
	else {
		printf("│ ---                     │");
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	printf("└─────────────────────────┘");
}


// 체력 감소 함수
void updateHealth(int health) {
	/*int xOffset = STAGE_WIDTH * 2 + 6;
	int yOffset = 2;
	setCursorPosition(xOffset, yOffset);
	printf("체력: ");
	setColor(12); // 빨간색 하트
	for (int i = 0; i < health; i++) {
		printf("♥ ");
	}
	setColor(7); // 기본 색상으로 복원
	for (int i = health; i < MAX_HEALTH; i++) {
		printf("  ");
	}*/

	printfstat(health, 2, 3, 4, 0, 0);
}



// 주인공 그리기 함수 (초록색)
void drawPlayer(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1); // 테두리 안쪽에 맞게 위치 조정
	setColor(10); // 초록색 플레이어
	printf("■");
	setColor(7); // 기본 색상으로 복원
}

// 주인공 위치를 지우기 위한 함수
void clearPlayer(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1); // 테두리 안쪽에 맞게 위치 조정
	printf("  "); // 기존 위치 지우기
}

//좀비 그리기 함수 (빨간색)
void drawEnemy(int x, int y) {
	setCursorPosition(x * 2 + 1, y + 1); // 테두리 안쪽에 맞게 위치 조정
	setColor(12); // 빨간색 좀비
	printf("■");
	setColor(7); // 기본 색상
}

// 좀비 위치 여부 확인
int isZombiePosition(int x, int y) {
	for (int i = 0; i < num_zombies; i++) {
		if (zombie_positions[i][0] == x && zombie_positions[i][1] == y) {
			return 1; // 해당 위치에 좀비가 있음
		}
	}
	return 0; //좀비가 없음
}

//타이머구현
COORD TIMETABLE = { STAGE_WIDTH * 2 + 4,25 };
COORD NPCANSWER = { STAGE_WIDTH * 2 + 4,17 };
HANDLE handle;
std::atomic<bool> missionFailed(false); // 미션실패 유무
std::atomic<bool> timerRunning(true); // 시간 흐름 유무
std::atomic<bool> isExplore(true);
void createTimeTable() {
	COORD pos = TIMETABLE;
	SetConsoleCursorPosition(handle, pos);
	std::cout << "┌─────────────────────────┐" << std::endl;
	for (int i = 0; i < TIMEHEIGHT - 2; i++) {
		pos.Y++;
		SetConsoleCursorPosition(handle, pos);
		std::cout << "│      │                  │" << std::endl;
	}
	pos.Y++;
	SetConsoleCursorPosition(handle, pos);
	std::cout << "└─────────────────────────┘" << std::endl;
}

void timer(int timeLimitSeconds) {
	COORD pos = { TIMETABLE.X + 2, TIMETABLE.Y + TIMEHEIGHT / 2 -1};
	int remainingTime = timeLimitSeconds;

	while (remainingTime > 0 && timerRunning) {
		if (isExplore) {
			std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초마다 감소
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
		std::cout << "임무 실패!" << std::endl;
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
//npc대화창 출력 함수 

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
	//npc 만난 상태가 아니면 박스 삭제
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
	//npc 만난 상태이면 박스 생성
	setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 1);
	printf("┌─────────────────────────┐");
	for (int i = 0; i < 7; i++) {
		setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 2 + i);
		printf("│                         │");
	}
	setCursorPosition2(STAGE_WIDTH*2 + 4, stat_Height + 8);
	printf("└─────────────────────────┘");
}

int main() {
	int playerX = 1; // 주인공 초기 X 좌표
	int playerY = 1; // 주인공 초기 Y 좌표
	int health = MAX_HEALTH;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int realTimeLimit = 300; // 5분
	

	system("cls"); // 콘솔초기화
	CommunicationBoxNPC(1);
	createTimeTable();
	std::thread timerThread(timer, realTimeLimit);
	// timerunning을 false로 바꾸면 타이머 종료
	// timerRunning = false;
	//시간종료여부
	/*if (timerThread.joinable()) {
		timerThread.join();

		std::cout << "게임 종료" << std::endl;
	}*/
	drawStage();         // 탐험 맵
	printfstat(1, 2, 3, 4, 0, 0); // 아이템 창 
	drawPlayer(playerX, playerY); // 초기 위치에 주인공 그리기
	updateHealth(health);         // 초기 체력 표시
	updateTextBox("");            // 텍스트 창

	// 초기 좀비
	for (int i = 0; i < num_zombies; i++) {
		drawEnemy(zombie_positions[i][0], zombie_positions[i][1]);
	}

	while (1) {
		if (_kbhit()) {
			int key = _getch(); // 키 입력을 받음

			if (key == 224) { // 방향키 입력 확인
				key = _getch(); // 실제 방향키 값 읽기

				// 플레이어의 현재 위치 지우기
				clearPlayer(playerX, playerY);

				// 새로운 위치 계산
				int newX = playerX;
				int newY = playerY;

				// 방향키에 따라 새로운 위치 설정
				switch (key) {
				case 72: // 위쪽 화살표
					newY--;
					break;
				case 80: // 아래쪽 화살표
					newY++;
					break;
				case 75: // 왼쪽 화살표
					newX--;
					break;
				case 77: // 오른쪽 화살표
					newX++;
					break;
				}

				// 이동 가능 여부 확인
				if (newY >= 0 && newY < STAGE_HEIGHT && newX >= 0 && newX < STAGE_WIDTH &&
					game_map[newY][newX] == ' ' && !isZombiePosition(newX, newY)) {
					// 벽이나 좀비가 아닌 곳으로 이동
					playerX = newX;
					playerY = newY;
					updateTextBox(""); // 텍스트 창 초기화
				}
				else if (isZombiePosition(newX, newY)) {
					// 좀비 위치로 이동 시도 시 체력 감소
					health--;
					updateHealth(health);
					updateTextBox("앗, 좀비다!");

					if (health == 0) { // 체력이 0이 되면 게임 종료
						updateTextBox("Game over!");
						break;
					}
				}

				// 변경된 위치에 플레이어 그리기
				drawPlayer(playerX, playerY);
				
			}
		}
	}

	return 0;
}