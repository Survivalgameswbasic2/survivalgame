#include <iostream>
#include <chrono>
#include <thread>
#include<iomanip>
#include<Windows.h>
#include <atomic>
#include<string>
int TIMEWIDTH = 27;// 6ĭ����
int TIMEHEIGHT = 5;
COORD TIMETABLE = { 50,20 };
COORD NPCANSWER = { 60,22 };
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
    COORD pos = { TIMETABLE.X + 2, TIMETABLE.Y + TIMEHEIGHT/2 };
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


int main() {
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int realTimeLimit = 300; // 5��

    createTimeTable();
	std::thread timerThread(timer, realTimeLimit);
    // timerunning�� false�� �ٲٸ� Ÿ�̸� ����
    // timerRunning = false;

    //NpcAnswer();
    if (timerThread.joinable()) {
        timerThread.join();
    }

    std::cout << "���� ����" << std::endl;
    return 0;
}