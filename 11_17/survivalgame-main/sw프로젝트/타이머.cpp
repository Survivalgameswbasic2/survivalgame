#include "����.h";
#include <windows.h>
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <string>
#include "����.h"
#define STAGE_WIDTH 34  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ����  

HANDLE handle;
std::atomic<bool> missionFailed(false); // �̼ǽ��� ����
std::atomic<bool> timerRunning(true); // �ð� �帧 ����
std::atomic<bool> isExplore(true);

void timer() {
	COORD timer_pos = { STAGE_WIDTH*2+6,0 };
	std::string erase = { "                                     " };
	std::string time = { "TIMER | �� �� �� �� �� �� �� �� �� �� " };
	int remaining_time = 5;
	while (remaining_time > 0 && timerRunning) {
		if (isExplore) {
			setCursorPosition(timer_pos.X, timer_pos.Y);
			std::cout << erase;
			setCursorPosition(timer_pos.X, timer_pos.Y);
			std::cout << time;
			std::this_thread::sleep_for(std::chrono::minutes(1)); // 1�ʸ��� ����
			remaining_time--;
			time.pop_back();
			time.pop_back();
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	if (remaining_time <= 0) {
		missionFailed = true;
		std::cout << "�ӹ� ����!" << std::endl;
	}
}

