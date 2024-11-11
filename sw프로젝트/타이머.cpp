#include "도구.h";
#include <windows.h>
#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>
#include <string>
#include "도구.h"
#define STAGE_WIDTH 34  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이  

HANDLE handle;
std::atomic<bool> missionFailed(false); // 미션실패 유무
std::atomic<bool> timerRunning(true); // 시간 흐름 유무
std::atomic<bool> isExplore(true);

void timer() {
	COORD timer_pos = { STAGE_WIDTH*2+6,0 };
	std::string erase = { "                                     " };
	std::string time = { "TIMER | ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ " };
	int remaining_time = 5;
	while (remaining_time > 0 && timerRunning) {
		if (isExplore) {
			setCursorPosition(timer_pos.X, timer_pos.Y);
			std::cout << erase;
			setCursorPosition(timer_pos.X, timer_pos.Y);
			std::cout << time;
			std::this_thread::sleep_for(std::chrono::minutes(1)); // 1초마다 감소
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
		std::cout << "임무 실패!" << std::endl;
	}
}

