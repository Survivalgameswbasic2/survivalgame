#include "windows.h"
#include <iostream>
#include <string>
#include "player.h"
#include <chrono>
#include <atomic>
#include <thread>
#include <string>
#include "mutex_helper.h"
#include <vector>
#define STAGE_WIDTH 68  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 


std::atomic<bool> timerRunning(true); // �ð� �帧 ����
std::atomic<bool> isExplore(true);
std::atomic<int> hour;
// Ŀ�� ��ġ ����
void setCursorPosition(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// �ܼ� �ؽ�Ʈ ���� ����
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// ��ȭâ �׵θ� ��� + ������ ����
void updateTextBox(const char* message) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // �� â �ϴܿ� �ؽ�Ʈ â ��ġ ����  
	int width = STAGE_WIDTH;    // �ؽ�Ʈ â ���� ����
	int height = 6;                 // �ؽ�Ʈ â ���� ����

	// �ؽ�Ʈ â �׵θ��� ���� ���
	std::lock_guard<std::mutex> lock(bufferMutex);
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
	setCursorPosition(1, 23);
	std::cout << "                                                                  ";
	setCursorPosition(1, 23);
	std::cout << message;

}
// ��ȭâ ����ȭ
void dialogue_clear() {
	std::lock_guard<std::mutex> lock(bufferMutex);
	setCursorPosition(1, 23);
	std::cout << "                                                                  ";
	setCursorPosition(1, 24);
	std::cout << "                                                                  ";
	setCursorPosition(1, 25);
	std::cout << "                                                                  ";
	setCursorPosition(1, 26);
	std::cout << "                                                                  ";
}
// ��ȭ ���� ���
void updateDialogue(std::string& message) {
	dialogue_clear();
	std::lock_guard<std::mutex> lock(bufferMutex);
	if (message.length() > 192) {
		std::string part1 = message.substr(0, 64);
		std::string part2 = message.substr(64, 64);
		std::string part3 = message.substr(128,64);
		std::string part4 = message.substr(192);
		setCursorPosition(1, 23);
		std::cout << part1;
		setCursorPosition(1, 24);
		std::cout << part2;
		setCursorPosition(1, 25);
		std::cout << part3;
		setCursorPosition(1, 26);
		std::cout << part4;
	}
	else if (message.length() > 128) {
		std::string part1 = message.substr(0, 64);
		std::string part2 = message.substr(64, 64);
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
// ����â ���
void printstat(player* user) {
	std::lock_guard<std::mutex> lock(bufferMutex);
	//���� 27 ���� 9
	SHORT y = 1;
	SHORT x = 72;
	COORD pos1 = { x ,y };
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->mode == 1) {
		user->maxh = 6;
		user->maxm = 100;
	}
	else if (user->mode == 2) {
		user->maxh = 5;
		user->maxm = 120;
	}
	else {
		user->maxh = 5;
		user->maxm = 100;
	}


	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "������������������������������������������������������";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "�� ü�� : ";
	COORD heart_pos = { pos1.X + 10,pos1.Y };
	for (int i = 0; i < user->heart; i++) {
		setColor(4);
		setCursorPosition(heart_pos.X,heart_pos.Y);
		std::cout << " ��";
		setColor(7);
		heart_pos.X++;
		heart_pos.X++;
	}
	for (int i = 0; i < user->maxh - user->heart; i++) {
		setCursorPosition(heart_pos.X, heart_pos.Y);
		std::cout << " ��";
		heart_pos.X++;
		heart_pos.X++;
	}
	setCursorPosition(pos1.X + 26, pos1.Y);
	std::cout << "��";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);

	std::cout << "�� ��Ʈ���� : ";
	std::cout << user->mental << " ";
	pos1.X = pos1.X + 26;
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "��";
	pos1.X = pos1.X - 26;
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "��                         ��";
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "�� �ķ� X " << user->food;
	SetConsoleCursorPosition(hConsoleOut, pos1);
	pos1.X = pos1.X + 26;
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "��";
	pos1.X = pos1.X - 26;
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "�� �� X " << user->water;
	pos1.X = pos1.X + 26;
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "��";
	pos1.X = pos1.X - 26;
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->bullet != 0) {
		std::cout << "�� źȯ X "<< user->bullet;
		pos1.X = pos1.X + 26;
		SetConsoleCursorPosition(hConsoleOut, pos1);
		std::cout << "��";
		pos1.X = pos1.X - 26;
	}
	else {
		std::cout << "�� --- ";
		pos1.X = pos1.X + 26;
		SetConsoleCursorPosition(hConsoleOut, pos1);
		std::cout << "��";
		pos1.X = pos1.X - 26;
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	if (user->medicine != 0) {
		std::cout << "�� ġ���� X "<<user->medicine;
		pos1.X = pos1.X + 26;
		SetConsoleCursorPosition(hConsoleOut, pos1);
		std::cout << "��";
		pos1.X = pos1.X - 26;
	}
	else {
		std::cout << "�� --- ";
		pos1.X = pos1.X + 26;
		SetConsoleCursorPosition(hConsoleOut, pos1);
		std::cout << "��";
		pos1.X = pos1.X - 26;
	}
	pos1 = { x ,y++ };
	SetConsoleCursorPosition(hConsoleOut, pos1);
	std::cout << "������������������������������������������������������";
}
// npc �� ��� * �̿ϼ� *
void draw_face() {
	std::lock_guard<std::mutex> lock(bufferMutex);
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
// Ÿ�̸� (�ð� + ��) ���
void timer() {
	COORD timer_pos = { 1,0 };
	std::string erase = { "                                     " };
	int current_time = 0;
	{
		std::lock_guard<std::mutex> lock(bufferMutex);
		setColor(12);
		setCursorPosition(timer_pos.X, timer_pos.Y);
		std::cout << erase;
		setCursorPosition(timer_pos.X, timer_pos.Y);
		std::cout << hour<<"��" << current_time << "��";
		setColor(7);
	}
	timerRunning = true;
	isExplore = true;
	int count = 0;
	while (timerRunning) {
		if (isExplore) {
			std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�ʸ��� ����

			current_time+=10;
			if (current_time >= 60) {
				current_time = 0;
				hour += 1;
				if (hour == 21) {
					break;
				}
			}
			{
				std::lock_guard<std::mutex> lock(bufferMutex);
				setColor(12);
				setCursorPosition(timer_pos.X, timer_pos.Y);
				std::cout << erase;
				setCursorPosition(timer_pos.X, timer_pos.Y);
				std::cout << hour << "��" << current_time << "��";
				setColor(7);
			}
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}
void timer2() {
	COORD timer_pos = { 1,0 };
	std::string erase = { "                                                          " };
	std::string gage= {" "};
	int percent = 0;
	int percent_in = 0;
	{
		std::lock_guard<std::mutex> lock(bufferMutex);
		setColor(12);
		setCursorPosition(timer_pos.X, timer_pos.Y);
		std::cout << erase;
		setCursorPosition(timer_pos.X, timer_pos.Y);
		std::cout << percent << "%  " << gage;
		setColor(7);
	}
	timerRunning = true;
	isExplore = true;
	int count = 0;
	while (timerRunning) {
		if (isExplore) {
			std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�ʸ��� ����

			percent += 1;
			percent_in += 1;
			if (percent_in >= 4) {
				percent_in = 0;
				gage += "�� ";
				if (percent >= 100) {
					break;
				}
			}
			{
				std::lock_guard<std::mutex> lock(bufferMutex);
				setColor(12);
				setCursorPosition(timer_pos.X, timer_pos.Y);
				std::cout << erase;
				setCursorPosition(timer_pos.X, timer_pos.Y);
				std::cout << percent << "%  " << gage;
				setColor(7);
			}
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}

// hour ��ȯ
int get_hour() {
	return hour;
}
// hour ����
void set_hour(int h) {
	hour = h;
}
// timer ����
void stop_timer_running() {
	timerRunning = false;
}
// timer ����
void start_timer_running() {
	timerRunning = true;
}

// �� �� �޺� ��ġ �ʱ�ȭ
void erase_sunlight(char map[][35]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 35; j++) {
			if (map[i][j] == '%') {
				map[i][j] = ' ';
			}
		}
	}
}
// �ʿ� ���ο� �޺� ��ġ ����
void draw_sunlight(char map[][35]) {
	switch (hour) {
	case 9:
		erase_sunlight(map);
		for (int h = 18; h >= 12; h--) {
			int w = 32;
			while (w >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if(map[h][w]==' ')
				map[h][w] = '%';
				w--;
			}
		}
		break;
	case 10:
		erase_sunlight(map);
		for (int h = 18; h >= 6; h--) {
			int w = 32;
			while (w >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')
				map[h][w] = '%';
				w--;
			}
		}
		break;
	case 11:
		erase_sunlight(map);
		for (int h = 18; h >= 1; h--) {
			int w = 32;
			while (w >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')
				map[h][w] = '%';
				w--;
			}
		}
		break;
	case 12:
		erase_sunlight(map);
		for (int h = 12; h >= 1; h--) {
			int w = 32;
			while (w >= 0 && map[h][w] != '#' && map[h][w] !='A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				w--;
			}
		}
		for (int w = 32; w >= 24; w--) {
			int h = 1;
			while (h >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				h++;
			}
		}
		break;
	case 13:
		erase_sunlight(map);
		for (int h = 6; h >= 1; h--) {
			int w = 32;
			while (w >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				w--;
			}
		}
		for (int w = 32; w >= 16; w--) {
			int h = 1;
			while (h >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				h++;
			}
		}
		break;
	case 14:
		erase_sunlight(map);
		for (int w = 32; w >= 8; w--) {
			int h = 1;
			while (h >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				h++;
			}
		}
		break;
	case 15:
		erase_sunlight(map);
		for (int w = 32; w >= 1; w--) {
			int h = 1;
			while (h >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				h++;
			}
		}
		break;
	case 16:
		erase_sunlight(map);
		for (int h = 6; h >= 1; h--) {
			int w = 1;
			while (w >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				w++;
			}
		}
		for (int w = 24; w >= 1; w--) {
			int h = 1;
			while (h >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				h++;
			}
		}
		break;
	case 17:
		erase_sunlight(map);
		for (int h = 12; h >= 1; h--) {
			int w = 1;
			while (w >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				w++;
			}
		}
		for (int w = 16; w >= 1; w--) {
			int h = 1;
			while (h >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				h++;
			}
		}
		break;
	case 18:
		erase_sunlight(map);
		for (int h = 18; h >= 1; h--) {
			int w = 1;
			while (w >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				w++;
			}
		}
		for (int w = 8; w >= 1; w--) {
			int h = 1;
			while (h >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				h++;
			}
		}
		break;
	case 19:
		erase_sunlight(map);
		for (int h = 18; h >= 6; h--) {
			int w = 1;
			while (w >= 0 && map[h][w] != '#' && map[h][w] != 'A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				w++;
			}
		}
		break;
	case 20:
		erase_sunlight(map);
		for (int h = 18; h >= 12; h--) {
			int w = 1;
			while (w >= 0 && map[h][w] != '#' && map[h][w] !='A') {
				if (map[h][w] == ' ')map[h][w] = '%';
				w++;
			}
		}
		break;
	case 21:
		erase_sunlight(map);
		break;
	default:
		break;
	}
}
//timer �Ͻ�����
void set_isExplore(bool x) {
	isExplore = x;
}