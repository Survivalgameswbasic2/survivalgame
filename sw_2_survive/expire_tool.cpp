#include "windows.h"
#include <iostream>
#include <string>
#include "player.h"
#include <chrono>
#include <atomic>
#include <thread>
#include <string>

#define STAGE_WIDTH 68  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 


std::atomic<bool> missionFailed(false); // 미션실패 유무
std::atomic<bool> timerRunning(true); // 시간 흐름 유무
std::atomic<bool> isExplore(true);

//////////////////// 기본 사용 함수///////////////////////////
// 콘솔 커서 위치 설정
void setCursorPosition(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 콘솔 텍스트 색상 설정
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//////////////////// 대화창 ///////////////////////////

// 텍스트 창 초기화 및 메시지 출력 함수  -> 짧은 대화에 사용
void updateTextBox(const char* message) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = STAGE_WIDTH;    // 텍스트 창 가로 길이
	int height = 5;                 // 텍스트 창 세로 길이

	// 텍스트 창 테두리와 제목 출력

	// 텍스트 창 테두리 그리기
	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(xOffset + x, yOffset + y + 1);
			if (y == 0) {
				if (x == 0) printf("┌");
				else if (x == width) printf("┐");
				else printf("─");
			}
			else if (y == height - 1) {
				if (x == 0) printf("└");
				else if (x == width) printf("┘");
				else printf("─");
			}
			else {
				if (x == 0 || x == width) printf("│");
				else printf(" ");
			}
		}
	}
}
// 긴 대화에 사용
void updateDialogue(std::string& message) {
	if (message.length() > 128) {
		std::string part1 = message.substr(0, 64);
		std::string part2 = message.substr(64, 128);
		std::string part3 = message.substr(128);
		setCursorPosition(1, 23);
		std::cout << part1;
		setCursorPosition(1, 24);
		std::cout << part2;
		setCursorPosition(1, 25);
		std::cout << part3;
	}
	else if (message.length() > 64) {
		std::string part1 = message.substr(0, 64);
		std::string part2 = message.substr(64);
		setCursorPosition(1, 23);
		std::cout << part1;
		setCursorPosition(1, 24);
		std::cout << part2;
	}
	else {
		setCursorPosition(1, 23);
		std::cout << message;
	}
}

void dialogue_clear() {
	setCursorPosition(1, 23);
	std::cout << "                                                                  ";
	setCursorPosition(1, 24);
	std::cout << "                                                                  ";
	setCursorPosition(1, 25);
	std::cout << "                                                                  ";
}


//////////////////// 상태창 ///////////////////////////


void printstat(player* user) {
	//가로 27 세로 9
	SHORT y = 1;
	SHORT x = 75;
	COORD pos1 = { x ,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos1);

	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "┌─────────────────────────┐";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "│ 체력 :     ";
	for (int i = 0; i < user->heart; i++) {
		std::cout << " ♥";
	}
	for (int i = 0; i < 5 - user->heart; i++) {
		std::cout << " ♡";
	}
	std::cout << "   │";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);

	std::cout << "│ 스트레스 : ";
	for (int i = 0; i < user->mental; i++) {
		std::cout << " ★";
	}
	for (int i = 0; i < 5 - user->mental; i++) {
		std::cout << " ☆";
	}
	std::cout << "   │";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "│                         │";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "│ 식량 X "<< user->food<< "                │";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "│ 물 X "<<user->water<<"                  │";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->bullet != 0) {
		std::cout << "│ 탄환 X ", user->bullet, "                │";
	}
	else {
		std::cout << "│ ---                     │";
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->medicine != 0) {
		std::cout << "│ 치료제 X ", user->medicine, "              │";
	}
	else {
		std::cout << "│ ---                     │";
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "└─────────────────────────┘";
}

//////////////////// 타이머 ///////////////////////////

void draw_clock(int time) {
	char clock_0[10][25] = {
	"      *****",
	"   ***  │  ***",
	" **     │     **",
	"*       ○       *",
	" **           **",
	"   ***     ***",
	"      *****"
	};
	char clock_3[10][25] = {
	"     *****",
	"  ***     ***",
	" **           **",
	"*       ○───     *",
	" **           **",
	"  ***     ***",
	"     *****"
	};

	char clock_6[10][25] = {
	"           *****",
	"        ***     ***",
	"      **           **",
	"     *       ○        *",
	"      **     │     **",
	"        ***  │  ***",
	"           *****"
	};
	char clock_9[10][40]{
	"           *****",
	"        ***     ***",
	"      **           **",
	"     *  ───○          *",
	"      **           **",
	"        ***     ***",
	"           *****"
	};
	switch (time) {
	case(0):
		for (int i = 0; i < 7; i++) {
			setCursorPosition(75, 11 + i);
			std::cout << clock_0[i];
		}
		break;
	case(3):
		for (int i = 0; i < 7; i++) {
			setCursorPosition(75, 11 + i);
			std::cout << clock_3[i];
		}
		break;
	case(6):
		for (int i = 0; i < 7; i++) {
			setCursorPosition(75, 11 + i);
			std::cout << clock_6[i];
		}
		break;
	case(9):
		for (int i = 0; i < 7; i++) {
			setCursorPosition(75, 11 + i);
			std::cout << clock_9[i];
		}
		break;
	}
}
void timer() {
	COORD timer_pos = { STAGE_WIDTH + 6,10 };
	std::string erase = { "                                     " };
	std::string time = { "TIMER | ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ " };

	int remaining_time = 5;
	int count = 0;
	setCursorPosition(timer_pos.X, timer_pos.Y);
	std::cout << erase;
	setCursorPosition(timer_pos.X, timer_pos.Y);
	std::cout << time;
	while (remaining_time > 0 && timerRunning) {
		if (isExplore) {
			std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초마다 감소
			count++;
			if (count == 60) {
				setCursorPosition(timer_pos.X, timer_pos.Y);
				std::cout << erase;
				setCursorPosition(timer_pos.X, timer_pos.Y);
				std::cout << time;
				remaining_time--;
				time.pop_back();
				time.pop_back();
				count = 0;
			}
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	if (remaining_time <= 0) {
		missionFailed = true;
	}
	else {
	}
}

void stop_timer_running() {
	timerRunning = false;
}

void start_timer_running() {
	timerRunning = true;
}