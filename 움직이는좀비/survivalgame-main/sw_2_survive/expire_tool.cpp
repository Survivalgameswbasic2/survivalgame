#include "windows.h"
#include <iostream>
#include <string>
#include "player.h"
#include <chrono>
#include <atomic>
#include <thread>
#include <string>

#define STAGE_WIDTH 68  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 


std::atomic<bool> missionFailed(false); // �̼ǽ��� ����
std::atomic<bool> timerRunning(true); // �ð� �帧 ����
std::atomic<bool> isExplore(true);

//////////////////// �⺻ ��� �Լ�///////////////////////////
// �ܼ� Ŀ�� ��ġ ����
void setCursorPosition(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// �ܼ� �ؽ�Ʈ ���� ����
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//////////////////// ��ȭâ ///////////////////////////

// �ؽ�Ʈ â �ʱ�ȭ �� �޽��� ��� �Լ�  -> ª�� ��ȭ�� ���
void updateTextBox(const char* message) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // �� â �ϴܿ� �ؽ�Ʈ â ��ġ ����  
	int width = STAGE_WIDTH;    // �ؽ�Ʈ â ���� ����
	int height = 5;                 // �ؽ�Ʈ â ���� ����

	// �ؽ�Ʈ â �׵θ��� ���� ���

	// �ؽ�Ʈ â �׵θ� �׸���
	for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(xOffset + x, yOffset + y + 1);
			if (y == 0) {
				if (x == 0) printf("��");
				else if (x == width) printf("��");
				else printf("��");
			}
			else if (y == height - 1) {
				if (x == 0) printf("��");
				else if (x == width) printf("��");
				else printf("��");
			}
			else {
				if (x == 0 || x == width) printf("��");
				else printf(" ");
			}
		}
	}
}
// �� ��ȭ�� ���
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


//////////////////// ����â ///////////////////////////


void printstat(player* user) {
	//���� 27 ���� 9
	SHORT y = 1;
	SHORT x = 75;
	COORD pos1 = { x ,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos1);

	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "������������������������������������������������������";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "�� ü�� :     ";
	for (int i = 0; i < user->heart; i++) {
		std::cout << " ��";
	}
	for (int i = 0; i < 5 - user->heart; i++) {
		std::cout << " ��";
	}
	std::cout << "   ��";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);

	std::cout << "�� ��Ʈ���� : ";
	for (int i = 0; i < user->mental; i++) {
		std::cout << " ��";
	}
	for (int i = 0; i < 5 - user->mental; i++) {
		std::cout << " ��";
	}
	std::cout << "   ��";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "��                         ��";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "�� �ķ� X "<< user->food<< "                ��";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "�� �� X "<<user->water<<"                  ��";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->bullet != 0) {
		std::cout << "�� źȯ X ", user->bullet, "                ��";
	}
	else {
		std::cout << "�� ---                     ��";
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->medicine != 0) {
		std::cout << "�� ġ���� X ", user->medicine, "              ��";
	}
	else {
		std::cout << "�� ---                     ��";
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "������������������������������������������������������";
}

//////////////////// Ÿ�̸� ///////////////////////////

void draw_clock(int time) {
	switch (time) {
	case(0):
		setCursorPosition(3, 0);
		std::cout << "����ð� : 12��";
		break;
	case(3):
		setCursorPosition(3, 0);
		std::cout << "����ð� : 3��";
		break;
	case(6):
		setCursorPosition(3, 0);
		std::cout << "����ð� : 6��";
		break;
	case(9):
		setCursorPosition(3, 0);
		std::cout << "����ð� : 9��";
		break;
	}
	setCursorPosition(80, 10);
	std::cout << "      ____,     ";
	setCursorPosition(80, 11);
	std::cout << "   .       -    ";
	setCursorPosition(80, 12);
	std::cout << "   --------- !  ";
	setCursorPosition(80, 13);
	std::cout << "   ;       ;-.  ";
	setCursorPosition(80, 14);
	std::cout << "   :--/'---- ,. ";
	setCursorPosition(80, 15);
	std::cout << "    ,      .;   ";
	setCursorPosition(80, 16);
	std::cout << "     .-,,!~     ";
	setCursorPosition(80, 17);
	std::cout << "    .~,,~~~  ~  ";
	setCursorPosition(80, 18);
	std::cout << "  ~. :.~,,   ., ";
	setCursorPosition(80, 19);
	std::cout << " .  ,. ,,.    ..";
	setCursorPosition(80, 20);
	std::cout << ",  -,. ..      -";
	setCursorPosition(80, 21);
	std::cout << " .  .~-,.      ~";
	setCursorPosition(80, 22);
	std::cout << ".-~~~:---~---_ _";

}
void timer() {
	COORD timer_pos = { 25,0 };
	std::string erase = { "                                     " };
	int remaining_time = 60;
	setColor(12);
	setCursorPosition(timer_pos.X, timer_pos.Y);
	//std::cout << erase;
	setCursorPosition(timer_pos.X, timer_pos.Y);
	//std::cout << "�����ð� : " << remaining_time << "��";
	setColor(7);
	missionFailed = false;
	timerRunning = true;
	isExplore = true;
	int count = 0;
	while (remaining_time > 0 && timerRunning) {
		if (isExplore) {
			std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�ʸ��� ����
			count++;
			if (count == 1) {
				remaining_time -= 1;
				setColor(12);
				setCursorPosition(timer_pos.X, timer_pos.Y);
				//std::cout << erase;
				setCursorPosition(timer_pos.X, timer_pos.Y);
				//std::cout << "�����ð� : " << remaining_time << "��";
				setColor(7);
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

int is_mission_failed() {
	if (missionFailed == true) {
		return 1;
	}
	return 0;
}