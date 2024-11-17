#include <iostream>
#include <chrono>
#include <thread>
#include<iomanip>
#include<Windows.h>
#include <atomic>
#include<string>
int TIMEWIDTH = 27;// 6칸차지
int TIMEHEIGHT = 5;
COORD TIMETABLE = { 50,20 };
COORD NPCANSWER = { 60,22 };
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
    COORD pos = { TIMETABLE.X + 2, TIMETABLE.Y + TIMEHEIGHT/2 };
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


int main() {
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int realTimeLimit = 300; // 5분

    createTimeTable();
	std::thread timerThread(timer, realTimeLimit);
    // timerunning을 false로 바꾸면 타이머 종료
    // timerRunning = false;

    //NpcAnswer();
    if (timerThread.joinable()) {
        timerThread.join();
    }

    std::cout << "게임 종료" << std::endl;
    return 0;
}