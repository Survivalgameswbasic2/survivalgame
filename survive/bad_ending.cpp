﻿#include<windows.h>
#include<iostream>
#ifdef _WIN32
#include <windows.h>
#include "expire_tool.h"
#include <vector>
#endif
#include <conio.h>

static std::vector<std::string> bad_ending_zombie_dialogue = {
    "당신은 과도한 스트레스를 받았습니다",
    "당신은 버티지 못하고 좀비가 되고 말았습니다",
    "-Bad Ending-"
};

void bad_ending_zombie() {//스트레스
    int dialogue_line = 0;
    int dialogue_num = 0;
    UINT oldCP = GetConsoleOutputCP();
#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    system("cls");
    setCursorPosition(8, 2);
    std::cout << u8"⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⡿⣿⣛⣋⣉⠀⠀⠉⠐⠢⢤⣀⣀⡉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠓⠶⣄⡀⠀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 3);
    std::cout << u8"⠐⠠⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣷⣦⣤⣤⣤⣬⣙⣻⣿⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣶⣤⡀⠀⠀⠀\n";
    setCursorPosition(8, 4);
    std::cout << u8"⠀⢀⣴⣿⣿⣿⣿⡿⠋⠉⠉⠉⠉⡹⠋⠉⠉⠉⠉⠉⠉⠛⠛⠢⡀⠀⠀⠀⠈⠻⣿⣿⣶⡒⠶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣷⡄⠀\n";
    setCursorPosition(8, 5);
    std::cout << u8"⣴⣿⡿⡛⣹⣿⡿⠀⠀⠀⠀⡠⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⠀⠀⠀⠀⠀⠀⠹⣿⡇⠀⠀⠉⣦⡄⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⡀\n";
    setCursorPosition(8, 6);
    std::cout << u8"⡿⡿⢋⡼⠛⣿⠃⠀⣀⡴⠊⠀⠀⠀⠀⠀⢀⣀⣀⣀⣠⡀⠠⢤⡼⢄⡀⠀⠀⠀⠀⠀⠸⠁⠀⠀⠀⣸⣿⡀⠀⠀⠀⠀⠀⠀⢹⣿⣿⡇\n";
    setCursorPosition(8, 7);
    std::cout << u8"⠞⢠⠎⠀⠀⡏⢀⠞⠁⠀⠀⢀⣤⣶⣟⠛⣋⡁⠀⠀⠀⡩⠔⠈⠉⠀⠀⠈⠈⠉⠰⡦⠃⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇\n";
    setCursorPosition(8, 8);
    std::cout << u8"⣰⡏⠀⠀⠀⣇⡇⠀⠀⠀⣀⣾⣿⣿⠟⠁⠉⢻⠒⡤⠉⠀⠀⠀⠀⠀⠀⠘⠂⠀⠀⠈⢢⠀⠀⠀⠀⣿⣿⠁⠀⠀⠀⠀⠀⠀⢸⣿⢿⡇\n";
    setCursorPosition(8, 9);
    std::cout << u8"⣿⡇⠀⠀⠀⣿⣷⠀⣠⢚⣽⠉⠉⠀⠀⠀⠀⠀⣜⠔⠀⡄⢀⠀⠀⠀⠀⠀⢄⡒⠠⠴⣄⠃⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⢀⠟⠁⠀⣷\n";
    setCursorPosition(8, 10);
    std::cout << u8"⡿⠁⠀⠀⣼⣿⣿⡿⠃⣾⣿⡇⠀⠀⠀⠀⠀⠀⣿⣀⣤⣤⣈⢀⠀⠀⠀⠀⠹⠒⠒⢫⠽⢵⠄⠀⠀⠘⡟⠀⠀⠀⢀⡠⠔⠁⠀⠀⠀⢸\n";
    setCursorPosition(8, 11);
    std::cout << u8"⠁⠀⠀⣼⣿⣿⡿⠀⢰⣿⣿⡇⠀⠀⠀⠀⠀⠈⣿⣿⣿⢉⣏⣦⣦⣦⣄⡄⣶⣌⣷⡇⠙⡖⠒⠀⠤⠤⠤⡀⠒⠊⠁⠀⠀⠀⠀⠀⠀⣿\n";
    setCursorPosition(8, 12);
    std::cout << u8"⠀⠀⠀⣿⣿⣿⠀⠀⠀⣿⡟⠀⠀⠀⠀⢀⣤⣤⢼⡏⣷⣿⡛⢻⣟⣿⣿⡿⠿⠿⠛⠀⡼⠁⠀⣠⠀⠀⠀⠙⣄⠀⠀⠀⠀⠀⠀⢀⣼⣿\n";
    setCursorPosition(8, 13);
    std::cout << u8"⣀⠀⣸⣿⣿⢻⠀⠀⠀⢸⠀⠀⠀⣠⣾⡿⠛⢻⠊⠟⠈⠉⠻⡿⠛⠁⠀⢀⡀⠈⣡⡪⢠⠤⣴⠇⢀⡀⠀⠀⠈⢦⢀⠀⠀⠀⢀⣾⣿⠇\n";
    setCursorPosition(8, 14);
    std::cout << u8"⢿⣧⣿⣿⠃⢸⠀⠀⠀⣾⠀⣠⣾⡿⠋⠀⠀⠆⠠⡀⠀⠢⡀⠉⠱⠒⠸⢦⣽⣊⡜⢰⡥⠂⠈⢖⠁⠀⠀⠀⠀⠈⢣⠑⠒⠐⠾⠟⠁⠀\n";
    setCursorPosition(8, 15);
    std::cout << u8"⠀⠀⣿⣿⠀⣸⠀⠀⠀⣿⣾⣿⠟⠁⠀⠀⡜⠀⠀⠘⠦⢀⡈⡀⢠⡴⠖⠃⣴⢣⠀⠚⠀⣀⣠⡼⢀⢠⣇⣀⡀⠤⢄⢣⣀⠀⠀⢀⣀⣴\n";
    setCursorPosition(8, 16);
    std::cout << u8"⠀⠀⢻⣿⠀⣿⡀⠀⠀⠈⢣⠙⠀⠀⠀⠰⡁⡠⡒⠬⠢⢄⢖⠝⠁⠀⣠⣾⣥⡤⠣⣪⠁⠈⠈⣀⠤⣒⣩⣾⣐⣊⠉⠁⠹⡳⢶⣿⣿⣿\n";
    setCursorPosition(8, 17);
    std::cout << u8"⠀⠀⠀⢻⠀⢹⡇⠀⠀⠀⢸⡆⠀⠀⠀⢠⠋⠀⠀⠀⢠⡖⣡⡴⣿⣿⠿⣟⠿⠟⠋⠁⢀⣠⡾⠟⢻⠟⠋⠉⠁⠐⡄⠀⡠⠃⠀⠀⠈⠉\n";
    setCursorPosition(8, 18);
    std::cout << u8"⠀⠀⠀⠈⣷⡌⢿⠀⠀⠀⣼⣿⠀⠀⠀⠈⠃⢀⠤⠴⢿⣿⡿⠿⠛⠚⠉⠀⠀⠉⡉⠁⠉⠁⠀⠀⠘⠼⢄⡢⠤⠵⠃⠈⠀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 19);
    std::cout << u8"⠀⠀⠀⣠⡿⠀⠀⠣⠀⠀⣿⣿⣷⣄⡀⠀⠀⠀⠉⠐⠉⠀⠀⠀⣀⣤⠀⠀⠀⣰⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    SetConsoleOutputCP(oldCP);
    updateTextBox("");
    while (1) {
        if (_kbhit()) {
            int key = _getch();
            if (key == ' ') { // 스페이스바로 대화 진행
                if (dialogue_line < bad_ending_zombie_dialogue.size()) {
                    updateDialogue(bad_ending_zombie_dialogue[dialogue_line++]);
                }
                else {
                    // 대화 종료
                    exit(0);
                }
            }
        }
    }
}

static std::vector<std::string> bad_ending_dead_dialogue = {
    "당신은 부상을 입은 채 무리하여 탐험하였다",
    "탐험 도중 좀비떼에게 둘러싸여 죽고 말았다",
    "-Bad Ending-"
};
void bad_ending_dead() {//시간
    system("cls");
    int dialogue_line = 0;
    int dialogue_num = 0;

    UINT oldCP = GetConsoleOutputCP();
#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    system("cls");
    setCursorPosition(8, 2);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 3);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⣠⠚⠉⠀⠀⠈⠙⣦⣄⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 4);
    std::cout << u8"⠀⠀⠀⠀⠀⢰⠇⠀⠀⠀⠀⠀⠀⢀⢝⣆⠀⠀⠀⠀⠀⠀⢷⠚⠉⠉⠓⠻⠓⡄⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 5);
    std::cout << u8"⠀⠀⠀⠀⠀⠘⠀⡀⠀⠀⠀⠀⢀⣅⢸⠃⠀⠀⠀⢠⣴⡒⠈⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⣠⣪⠥⠤⠤⠭⣝⣦⡀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 6);
    std::cout << u8"⠀⠀⠀⠀⠀⢸⡀⠸⡀⠀⠀⢀⣾⣿⢯⠀⠀⠀⣀⡀⡴⠁⢠⢠⢀⣴⢆⣴⢀⠀⠈⢙⣆⠀⠀⣰⣿⣥⣤⡀⠀⠀⠀⠙⢿⡀⠀⠀⠀⠀";
    setCursorPosition(8, 7);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⢳⠀⡇⠀⠀⠀⣹⠇⢸⠆⡰⠋⠁⠒⠻⠞⣾⣾⣿⣿⣿⣾⣿⣰⡀⠀⡏⠀⠀⡿⣼⣦⣇⣹⠦⣤⣶⣀⢸⡇⠀⠀⠀⠀";
    setCursorPosition(8, 8);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⢸⠀⣡⡀⠀⠀⢉⣾⡞⠀⣇⣴⣦⡀⢠⣼⠏⠀⠀⠀⢼⣿⠘⠛⠉⣷⠀⠀⠀⠱⠀⢈⣁⣀⠤⡬⡍⢁⣾⠁⠀⠀⠀⠀";
    setCursorPosition(8, 9);
    std::cout << u8"⠀⠀⠀⠀⠀⢠⣿⠀⠀⣇⢀⣀⣸⠉⠁⠀⣟⣿⣿⢇⣠⢻⣇⡔⠚⠙⢻⡯⣆⣶⣞⣁⠀⠀⠀⠀⠉⠧⣶⣞⣭⣟⣿⢿⠓⣦⠀⠀⠀⠀";
    setCursorPosition(8, 10);
    std::cout << u8"⠀⠀⠀⢀⡴⠻⢼⡷⢰⠻⠾⢌⡿⠖⠀⠀⠘⡟⣟⠸⠛⠋⣇⣉⢿⡻⢟⣋⠁⠀⢠⢌⠙⢆⠀⡴⠉⠈⢷⠚⠚⠋⣁⣨⠤⠈⢳⡀⠀⠀";
    setCursorPosition(8, 11);
    std::cout << u8"⠀⠀⢀⠞⠀⠀⠀⡇⡏⠷⣄⠀⠀⣀⡤⢤⣀⡙⣿⡴⠚⠉⠁⣠⠀⡜⠹⣿⡶⢤⣮⣯⣆⠬⢿⠁⠀⠀⠀⠉⠉⠉⠉⣠⠃⠀⠀⠹⡄⠀";
    setCursorPosition(8, 12);
    std::cout << u8"⠀⢠⠏⠀⠀⠀⠀⡟⡇⠀⠈⠙⠲⣧⣤⣖⣓⣋⠭⠴⣤⢤⣾⣶⣯⣧⣸⣅⠀⠀⣹⠟⢀⡞⠛⠧⢤⣶⣶⠖⠲⢤⢰⠃⠀⠀⠀⠀⢻⡀";
    setCursorPosition(8, 13);
    std::cout << u8"⢀⡏⠀⣠⠀⠀⠀⠑⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣰⢯⣵⣶⠿⠛⣫⢿⡟⡒⣶⠃⠀⠘⢾⣠⡀⠘⣿⠁⠀⠀⠈⡇⠀⠀⣠⠞⠀⠈⡇";
    setCursorPosition(8, 14);
    std::cout << u8"⡼⠀⢰⡿⠀⠀⠀⠀⠀⠀⠀⠰⡿⣦⣀⠀⠺⡟⠛⢫⠉⠁⠀⠀⠘⠁⣿⣳⠁⠘⣆⠀⠀⠸⢻⢳⠀⢿⠀⠀⠀⠀⡇⠒⠚⠁⠀⠀⠀⡇";
    setCursorPosition(8, 15);
    std::cout << u8"⣇⣴⠧⡇⠀⠀⠀⠀⠀⠀⠀⣸⠁⠀⠉⠛⠋⠁⢠⠏⠀⠀⠀⠀⠀⣰⣿⠇⠀⠀⡸⣆⠀⠀⡼⠚⠀⢀⠀⠀⠀⠀⣣⣄⣀⠀⠀⠀⠀⠁";
    setCursorPosition(8, 16);
    std::cout << u8"⣻⡿⠟⡇⠀⠀⠀⠀⠀⠀⢰⠃⠀⠀⠀⠀⠀⣰⠫⠚⡔⡠⠊⢀⣼⡿⠁⠀⠀⢀⡇⠘⠦⠤⠟⠉⠉⠉⠲⣤⣴⣶⠷⠃⠈⠓⢦⡀⠀⠀";
    setCursorPosition(8, 17);
    std::cout << u8"⡇⠈⠿⢧⠀⠀⠀⠀⠀⢠⠏⠀⠀⠀⠀⠀⣴⠃⠠⠞⠁⠀⠀⠟⠙⠁⠀⠀⠀⣸⠀⠀⠀⠀⠀⠀⠀⠀⢀⡼⠋⠀⠀⠀⠀⠀⠀⠙⢦⡀";
    setCursorPosition(8, 18);
    std::cout << u8"⠇⠀⠸⠿⠀⠀⠀⠀⠀⡟⠀⠀⠀⠀⠀⣀⠬⠛⠉⠉⠉⠉⠉⠉⠉⠛⠒⠲⡤⠏⢀⣀⣀⣀⣀⡀⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙";

    SetConsoleOutputCP(oldCP);
    updateTextBox("");
    while (1) {
        if (_kbhit()) {
            int key = _getch();
            if (key == ' ') { // 스페이스바로 대화 진행
                if (dialogue_line < bad_ending_dead_dialogue.size()) {
                    updateDialogue(bad_ending_dead_dialogue[dialogue_line++]);
                }
                else {
                    // 대화 종료
                    exit(0);
                }
            }
        }
    }
}
static std::vector<std::string> bad_ending_time_dialogue = {
    "시간이 너무 늦어 좀비들이 늘어났다",
    "좀비가 너무 많아 감당하지 못하였다"
    "-Bad Ending-"
};
void bad_ending_time() {//시간
    system("cls");
    int dialogue_line = 0;
    int dialogue_num = 0;
    
    UINT oldCP = GetConsoleOutputCP();
#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    system("cls");
    setCursorPosition(8, 2);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 3);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⣠⠚⠉⠀⠀⠈⠙⣦⣄⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 4);
    std::cout << u8"⠀⠀⠀⠀⠀⢰⠇⠀⠀⠀⠀⠀⠀⢀⢝⣆⠀⠀⠀⠀⠀⠀⢷⠚⠉⠉⠓⠻⠓⡄⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 5);
    std::cout << u8"⠀⠀⠀⠀⠀⠘⠀⡀⠀⠀⠀⠀⢀⣅⢸⠃⠀⠀⠀⢠⣴⡒⠈⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⣠⣪⠥⠤⠤⠭⣝⣦⡀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 6);
    std::cout << u8"⠀⠀⠀⠀⠀⢸⡀⠸⡀⠀⠀⢀⣾⣿⢯⠀⠀⠀⣀⡀⡴⠁⢠⢠⢀⣴⢆⣴⢀⠀⠈⢙⣆⠀⠀⣰⣿⣥⣤⡀⠀⠀⠀⠙⢿⡀⠀⠀⠀⠀";
    setCursorPosition(8, 7);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⢳⠀⡇⠀⠀⠀⣹⠇⢸⠆⡰⠋⠁⠒⠻⠞⣾⣾⣿⣿⣿⣾⣿⣰⡀⠀⡏⠀⠀⡿⣼⣦⣇⣹⠦⣤⣶⣀⢸⡇⠀⠀⠀⠀";
    setCursorPosition(8, 8);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⢸⠀⣡⡀⠀⠀⢉⣾⡞⠀⣇⣴⣦⡀⢠⣼⠏⠀⠀⠀⢼⣿⠘⠛⠉⣷⠀⠀⠀⠱⠀⢈⣁⣀⠤⡬⡍⢁⣾⠁⠀⠀⠀⠀";
    setCursorPosition(8, 9);
    std::cout << u8"⠀⠀⠀⠀⠀⢠⣿⠀⠀⣇⢀⣀⣸⠉⠁⠀⣟⣿⣿⢇⣠⢻⣇⡔⠚⠙⢻⡯⣆⣶⣞⣁⠀⠀⠀⠀⠉⠧⣶⣞⣭⣟⣿⢿⠓⣦⠀⠀⠀⠀";
    setCursorPosition(8, 10);
    std::cout << u8"⠀⠀⠀⢀⡴⠻⢼⡷⢰⠻⠾⢌⡿⠖⠀⠀⠘⡟⣟⠸⠛⠋⣇⣉⢿⡻⢟⣋⠁⠀⢠⢌⠙⢆⠀⡴⠉⠈⢷⠚⠚⠋⣁⣨⠤⠈⢳⡀⠀⠀";
    setCursorPosition(8, 11);
    std::cout << u8"⠀⠀⢀⠞⠀⠀⠀⡇⡏⠷⣄⠀⠀⣀⡤⢤⣀⡙⣿⡴⠚⠉⠁⣠⠀⡜⠹⣿⡶⢤⣮⣯⣆⠬⢿⠁⠀⠀⠀⠉⠉⠉⠉⣠⠃⠀⠀⠹⡄⠀";
    setCursorPosition(8, 12);
    std::cout << u8"⠀⢠⠏⠀⠀⠀⠀⡟⡇⠀⠈⠙⠲⣧⣤⣖⣓⣋⠭⠴⣤⢤⣾⣶⣯⣧⣸⣅⠀⠀⣹⠟⢀⡞⠛⠧⢤⣶⣶⠖⠲⢤⢰⠃⠀⠀⠀⠀⢻⡀";
    setCursorPosition(8, 13);
    std::cout << u8"⢀⡏⠀⣠⠀⠀⠀⠑⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣰⢯⣵⣶⠿⠛⣫⢿⡟⡒⣶⠃⠀⠘⢾⣠⡀⠘⣿⠁⠀⠀⠈⡇⠀⠀⣠⠞⠀⠈⡇";
    setCursorPosition(8, 14);
    std::cout << u8"⡼⠀⢰⡿⠀⠀⠀⠀⠀⠀⠀⠰⡿⣦⣀⠀⠺⡟⠛⢫⠉⠁⠀⠀⠘⠁⣿⣳⠁⠘⣆⠀⠀⠸⢻⢳⠀⢿⠀⠀⠀⠀⡇⠒⠚⠁⠀⠀⠀⡇";
    setCursorPosition(8, 15);
    std::cout << u8"⣇⣴⠧⡇⠀⠀⠀⠀⠀⠀⠀⣸⠁⠀⠉⠛⠋⠁⢠⠏⠀⠀⠀⠀⠀⣰⣿⠇⠀⠀⡸⣆⠀⠀⡼⠚⠀⢀⠀⠀⠀⠀⣣⣄⣀⠀⠀⠀⠀⠁";
    setCursorPosition(8, 16);
    std::cout << u8"⣻⡿⠟⡇⠀⠀⠀⠀⠀⠀⢰⠃⠀⠀⠀⠀⠀⣰⠫⠚⡔⡠⠊⢀⣼⡿⠁⠀⠀⢀⡇⠘⠦⠤⠟⠉⠉⠉⠲⣤⣴⣶⠷⠃⠈⠓⢦⡀⠀⠀";
    setCursorPosition(8, 17);
    std::cout << u8"⡇⠈⠿⢧⠀⠀⠀⠀⠀⢠⠏⠀⠀⠀⠀⠀⣴⠃⠠⠞⠁⠀⠀⠟⠙⠁⠀⠀⠀⣸⠀⠀⠀⠀⠀⠀⠀⠀⢀⡼⠋⠀⠀⠀⠀⠀⠀⠙⢦⡀";
    setCursorPosition(8, 18);
    std::cout << u8"⠇⠀⠸⠿⠀⠀⠀⠀⠀⡟⠀⠀⠀⠀⠀⣀⠬⠛⠉⠉⠉⠉⠉⠉⠉⠛⠒⠲⡤⠏⢀⣀⣀⣀⣀⡀⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙";

    SetConsoleOutputCP(oldCP);
    updateTextBox("");
    while (1) {
        if (_kbhit()) {
            int key = _getch();
            if (key == ' ') { // 스페이스바로 대화 진행
                if (dialogue_line < bad_ending_time_dialogue.size()) {
                    updateDialogue(bad_ending_time_dialogue[dialogue_line++]);
                }
                else {
                    // 대화 종료
                    exit(0);
                }
            }
        }
    }
}


static std::vector<std::string> bad_ending_starve_dialogue = {
     "당신은 물이 부족해 사망했다",
    "-Bad Ending-"

};

void bad_ending_starve() {//식수
    system("cls");
    int dialogue_line = 0;
    int dialogue_num = 0;

    UINT oldCP = GetConsoleOutputCP();
#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    setCursorPosition(8, 2);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ \n";
    setCursorPosition(8, 3);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⢤⣀⣈⣻⠢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 4);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠒⠓⠀⠀⠀⠀⠁⠠⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 5);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣾⠇⠀⠀⠀⠀⠀⠀⠀⠀⡾⣆⡠⠤⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 6);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⠀⠀⠀⠀⠀⠀⠀⠘⠉⣷⢤⡄⠀⠀⠀⠀⠀⠀⢺⠤⠤⠍⢉⡀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 7);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⠉⢹⡴⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢋⢎⠿⠄⠀⠀⠀⠀⡠⣟⣲⠤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 8);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡀⢀⡷⠀⠀⠀⠀⠀⠀⠠⠶⠀⠀⣠⣌⠓⢈⣳⠤⡤⣄⣰⡞⠁⠀⠀⠈⠉⢛⡻⡖⠤⣀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 9);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠋⠀⢀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠿⣱⠂⠉⠩⡑⢆⠀⠀⠀⠀⠀⢉⠹⡢⠬⣁⠀⠀⠀⠀\n";
    setCursorPosition(8, 10);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠁⠀⢠⡄⡤⣀⢀⣀⣀⣀⣀⣀⡽⠛⠀⠀⠀⠀⠈⢑⡄⠀⠀⠀⠀⠀⠉⠓⠢⠄⣁⠀⠀ \n";
    setCursorPosition(8, 11);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⠈⠈⠈⡆⠀⠈⠉⠒⠒⠤⡉⠉⠁⢀⠠⠔⡏⠀⠀⠀⠀⠀⠀⠀⠀⣗⠢⠤⣉⠂⠀\n";
    setCursorPosition(8, 12);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠀⠀⠀⠀⠀⠀⠀⠀⠉⠒⠒⠒⠣⢄⣀⣀⠀⠀⠀⢀⡤⠖⠉⠢⣀⣹⠀⠀⠀⠀⠀⠀⠀⠀⢸⠢⣀⠀⠉⠂\n";
    setCursorPosition(8, 13);
    std::cout << u8"⠀⣠⠞⠉⠉⠉⠉⠙⠒⢋⠏⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠈⢺⡤⢄⡁⠀⠀\n";
    setCursorPosition(8, 14);
    std::cout << u8"⢠⠇⠀⠀⠀⠀⠀⠀⠀⢸⣂⠙⠧⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⠀⢀⣠⠤⠴⠒⠚⢻⠓⠢⠀⠀⠀\n";
    setCursorPosition(8, 15);
    std::cout << u8"⢸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⣄⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠒⠚⠉⠉⠉⠁⠀⠸⠒⠋⠉⠉⠉⠉⠉⠛⢽⣀⠀⠀⠀⠀\n";
    setCursorPosition(8, 16);
    std::cout << u8"⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡨⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⣯⡑⠥⠀⠀ \n";
    setCursorPosition(8, 17);
    std::cout << u8"⠸⡄⠀⠀⠀⠀⠀⠀⠀⢠⠞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠒⢷⠂⠤⠤⣤⢀⣀⣀⠀⡴⢚⡯⢄⡈⠂⠀⠀⠀\n";
    setCursorPosition(8, 18);
    std::cout << u8"⠀⠹⣄⠀⠀⠀⠀⣀⠴⠋⠀⠀⠀⠀⠀⠀⢀⣠⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⢣⠀⠀⠀⠀⠘⣆⡴⠋⠀⠀⠀⠀⢀⡔⠛⠤⡀⠀⠀⠀⠀⠀\n";
    setCursorPosition(8, 19);
    std::cout << u8"⠀⠀⠀⠉⠓⠚⠉⠁⠀⠀⠀⠀⠀⣀⢴⡮⠷⠓⠒⢎⣆⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀⠀⠀⠀⠘⡅⠀⠀⠀⠀⡰⠫⢄⡀⠀⠈⠀⠀⠀⠀⠀\n";
    SetConsoleOutputCP(oldCP);
    updateTextBox("");
    while (1) {
        if (_kbhit()) {
            int key = _getch();
            if (key == ' ') { // 스페이스바로 대화 진행
                if (dialogue_line < bad_ending_starve_dialogue.size()) {
                    updateDialogue(bad_ending_starve_dialogue[dialogue_line++]);
                }
                else {
                    // 대화 종료
                    exit(0);
                }
            }
        }
    }
}
static std::vector<std::string> normal_ending_dialogue = {
    {
    "헬기: 괜찮으십니까! 이제 당신만 남았습니다 어서 타세요!",
"연구원: 저희는 모두 무사합니다! 어서 타세요! 이제 사람이 살아가는 곳으로 돌아가죠!",
"생존자들: 정말 감사합니다! 이제 살았어!",
"연구원: 가서도 알아봐야 할게 산더미입니다. 같이 알아보죠!",
"플레이어: (결국 내가 누군지는 확실히 알진 못했구나..)",
"플레이어: (일단 나는 좀비한테 감염된건 맞잖아...)",
"플레이어: (다른 사람 입장에선 언제 터질지 모르는 폭탄같은 존재인데 과연 같이 살아갈 수 있을까?)",
"플레이어: (언제 좀비로 변해서 사람을 공격할지 모르겠는데 인간과 공존하면서 살아갈 수 있을까?)",
"플레이어: (...모르겠어. 하지만 여기있으면 더 위험할거 같아)",
"플레이어: (연구원 말이 맞아. 연구원이 날 어떻게 생각할진 모르겠지만 나는 사실 여기서 돌아다니는건 한계야)",
"플레이어: (가자 사람들이 사는 곳으로. 가서 공존하면서 살아가는거야)",
"플레이어: (...결국 내가 누군지, 좀비가 뭔지.. 아무것도 모르겠지만 말이야)",
"플레이어: 네 같이 가요!",
"연구원: 네!"
        "그렇게 사람들이 사는 곳으로 나는 무사히 탈출했다.결국 내가 누군지 내가 좀비인지 사람인지 모른체로.그렇게 모른체로 사람들과 공존하면서 살아간다.",
        "연구원과 차차 여러 가지 실험을 하며.이게 맞는지는 모르겠다.확실한건 나는 안전하게 살고 있다는 것.",
        "그래 좀비의 정체가 뭐든 내가 뭐든 살아 있다는 것.그게 제일 중요하지."
}
};
void normal_ending() {
    system("cls");
    int dialogue_line = 0;
    int dialogue_num = 0;

    UINT oldCP = GetConsoleOutputCP();
#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    setCursorPosition(8, 2);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢶⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 3);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⢿⡮⣁⠀⠤⠤⠄⢼⢸⠀⠈⣉⠒⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 4);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣀⠀⠀⡠⠄⠠⠤⡀⠀⠀⠀⡇⡎⠀⠙⠺⣷⣄⠀⠀⠸⣸⠀⠀⠀⠈⢑⠮⣓⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠼⠉⠉⠉⠙⢢";
    setCursorPosition(8, 5);
    std::cout << u8"⠀⠤⢄⠀⠀⠀⠀⠠⡀⠀⠀⠀⠀⠀⠀⢙⠀⠃⠀⠀⠀⠉⠳⠀⠀⢇⠀⠀⣀⣀⣈⣛⣷⣄⠀⣿⡆⠀⠀⠀⠀⠉⠚⢝⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢇⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 6);
    std::cout << u8"⠀⠀⠘⢦⡀⠀⠀⠀⠈⠳⢄⠀⠀⠀⠀⠘⡄⠀⠀⠀⠀⠀⢀⣴⠾⠿⠽⠿⣯⣭⣉⡉⢛⣿⠷⢷⣷⣲⣶⣛⣫⣭⡭⠭⠭⡭⡟⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 7);
    std::cout << u8"⠀⠀⠀⠀⢳⣀⣀⠀⠀⠀⠀⠉⠲⢄⣀⠘⠒⠤⣀⠀⠀⠀⠸⡌⠀⠀⠀⠀⠀⠀⠉⠙⣏⡓⢦⡤⢤⣉⣻⠳⢦⣀⠀⠀⠀⢣⠁⠀⠀⠀⠀⠀⠀⣰⠃⠀⠀⠀⠀⠀⣀⠀";
    setCursorPosition(8, 8);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠈⢹⠀⠀⠀⠀⠀⠀⠀⠉⠑⠒⠬⢍⣳⣄⡀⠘⢦⡀⠀⠀⠀⢿⣓⡲⢼⣼⣫⣗⡞⠥⠛⠀⠀⠈⠳⣄⡠⠮⠇⠀⠀⠐⠒⠚⠛⠓⠉⠓⠉⠉⠉⠀⠀⠀";
    setCursorPosition(8, 9);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⡸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣢⢽⣲⣤⣄⣀⣠⣿⡛⠛⢻⡿⢍⣛⣒⠲⠤⣄⠀⠈⠉⠓⠦⢤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀";
    setCursorPosition(8, 10);
    std::cout << u8"⣀⠀⠀⠀⠀⠀⠀⠉⠓⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠒⢯⣷⣿⡯⣛⡛⢿⣿⣀⣀⣀⣉⣩⠽⠭⠤⠤⠤⠤⠤⢤⣀⣉⠓⠲⢤⣀⣀⣠⠖⢋⡽⠃⠀⠀";
    setCursorPosition(8, 11);
    std::cout << u8"⠀⠑⠦⣀⠀⠀⠀⠀⠀⠓⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢮⠿⠶⠯⠽⢿⣿⡿⣶⣤⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠒⠮⢭⣾⡙⣿⠃⠀⠀⠀";
    setCursorPosition(8, 12);
    std::cout << u8"⠀⠀⠀⠈⠑⠦⢄⣀⠀⠀⢧⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣜⣀⣀⣀⣀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⢿⡽⠀⠀⠀⠀";
    setCursorPosition(8, 13);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠙⠚⠉⠁⠀⠀⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣯⠉⠉⠉⠉⠉⠛⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠒⠲⣄";
    setCursorPosition(8, 14);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⠔⠒⠽⣯⠙⠢⡸⡝⡄⠀⠀⠀⠀⠀⠀⠀⠀⠘⢷⡀⠀⠀⠀⠀⠘⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡤⠤⠤⣼⡄⠀⠘";
    setCursorPosition(8, 15);
    std::cout << u8"⠀⠀⠀⠀⠀⠛⢭⣍⠁⠀⠀⠀⠀⠀⠀⠀⠈⠇⢸⠄⣠⣤⠀⠀⠀⠀⠀⠀⠈⡿⡴⠖⠛⠓⠒⠚⠪⡳⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠁⠀⠀⠀⠀⠁⠀⠀";
    setCursorPosition(8, 16);
    std::cout << u8"⠀⠀⠀⠀⢀⠔⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠈⠳⣄⠀⠀⠀⠀⠀⠀⠀⡹⣧⠀⠀⠀⠀⠀⠀⠈⢢⡈⠓⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡄⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 17);
    std::cout << u8"⠀⠀⠀⢠⡿⣺⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣄⠀⡮⣆⠀⠀⠀⠀⠀⣠⢣⣇⣀⣀⡀⠀⠀⠀⠀⠀⠙⢆⠀⠙⢦⡀⠀⠀⠀⠀⢠⠖⠒⠒⠦⠷⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(8, 18);
    std::cout << u8"⠀⠀⣀⡨⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣼⣄⣟⣆⡇⠈⠀⠀⠀⢀⡴⣡⠏⠑⠒⠤⢭⣉⡒⠢⢤⣀⠀⠈⡇⠀⠀⢳⠀⠀⠀⠀⢈⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀";
    setCursorPosition(8, 19);
    std::cout << u8"⠀⠀⠈⠉⢳⠖⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢹⣇⠉⠻⣅⠀⠀⣠⠴⢋⡴⠁⠀⠀⠀⠀⠀⠀⠈⠉⠒⠦⣝⡦⣥⠀⠀⢸⠀⢰⡋⠙⠚⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠖⠀";
    SetConsoleOutputCP(oldCP);
    updateTextBox("");
    while (1) {
        if (_kbhit()) {
            int key = _getch();
            if (key == ' ') { // 스페이스바로 대화 진행
                if (dialogue_line < normal_ending_dialogue.size()) {
                    updateDialogue(normal_ending_dialogue[dialogue_line++]);
                }
                else {
                    // 대화 종료
                    exit(0);
                }
            }
        }
    }
}
static std::vector<std::string> hidden_ending_dialogue = {
     {
        "헬기: 괜찮으십니까! 이제 당신만 남았습니다 어서 타세요!",
        "연구원: 저희는 모두 무사합니다! 어서 타세요! 이제 사람이 살아가는 곳으로 돌아가죠!",
        "생존자들: 정말 감사합니다! 이제 살았어!",
        "연구원: 가서도 알아봐야 할게 산더미입니다. 같이 알아보죠!",
        "플레이어: (결국 내가 누군지는 확실히 알진 못했구나..)",
        "플레이어: (일단 나는 좀비한테 감염된건 맞잖아...)",
        "플레이어: (다른 사람 입장에선 언제 터질지 모르는 폭탄같은 존재인데 과연 같이 살아갈 수 있을까?)",
        "플레이어: (언제 좀비로 변해서 사람을 공격할지 모르겠는데 인간과 공존하면서 살아갈 수 있을까?)",
        "플레이어: (....아니 어짜피 난 이미 감염된 몸. 확실히 좀비가 뭔지, ...내가 누구인지 알고 싶어)",
        "플레이어: (이미 몇일간 탐험하면서 좀비에 대한 내성과 자신감도 생긴 것 같고)",
        "플레이어: (더이상 좀비한테 당하라거 같은 느낌은 안들어...)",
        "플레이어: (그럼 내가 더 돌아다니다 면서 좀비에 대해, 이 세계의 비밀에 대해 찾아 다니는게 맞지 않을까?)",
        "플레이어: (돌아가봤자 사람과 잘 공존하면서 산다는 보장이 없잖아..)",
        "플레이어: (그래 그게 맞아.)",
        "플레이어: 먼저 돌아가 계세요 다들. 저는 여기서 해야할 일이 남아있어요. 저만 할수 있는 일이.",
        "연구원: 그게 무슨 소리입니까? 같이 가야죠. 여긴 위험합니다.",
        "플레이어: 같이 가더라도 저는 평범한 일상을 보내기 쉽지 않다는거 아시잖아요. 저는 이게 맞아요.",
        "플레이어: 저는 여기서 이만 떠나겠습니다. 좋은 소식을 들고 다시 찾아뵙게요.",
        "연구원: ...당신의 뜻이 그렇겠다면... 죽지는 마십시오.",
        "헬기: 이제 시간이 없으므로 떠나겠습니다!",
        "플레이어: ...다 갔네 그래 그럼 이제 나도 출발해볼까!",
        "플레이어: 일단 다시 동굴로 가자... 거기서 앞으로의 일을 생각하는거야.",
        "플레이어: 하하 다시 동굴로 왔네 처음에 아무것도 모른채로 일어난 곳이었는데 여행의 끝에도 다시 여기로 오다니.",
        "플레이어: 아니, 또다른 시작인가. 이젠 나 혼자서 좀비가 뭔지 알아내는거야.",
        "???: 결국 다시 오게 될줄 알았다. 아니, 역시 그사람이라고 할까.",
        "???: 새로운 동료가 될 사람이 있을거라니.. 진짜 예언이라도 있는거야? 그사람은.",
        "플레이어: 뭡니까 당신. 언제부터 여기에. 누구십니까?",
        "???: 그렇게 경계하지 않아도 되네. 오히려 당신과 같은 존재라고 할 수 있을 테니까.",
        "???: 여기서 하루정도 기다렸다네. 당신이 오기만을 말이지.",
        "플레이어: 그니까 당신 누구냐고!",
        "???: ...좀비의 정체가 뭔지. 왜 좀비세상이 되었는지 알고 싶지 않나?",
        "???: ...그리고 너가 누구인지. 무엇을 했는지 알고 싶지 않나?",
        "플레이어: 내 정체를 알아? 좀비가 뭔지도?",
        "???: 따라와라 나 같은 사람, 아니 우리같은 사람이 있는 곳으로 안내해주겠다.",
        "???: 혼란스럽겠지만, 이거 하나만을 알아주게. 우린 널 해칠생각없는 동료라는걸.",
        "플레이어: (따라간다)...동굴안에 동굴이 있다니...",
        "플레이어: 내가 여기서 깨어난 이유도 알수 있을까?",
        "???: 차차 알려주도록 하지. 일단 들어오게.",
        "플레이어: (여기로 들어가면 또다른 이야기가 펼처질거 같은 느낌이 들어)",
        "플레이어: (이미 여기에 남겠다는 각오를 다진 후부터는 후회는 없어)",
        "플레이어: (그래 나는 앞으로 나가야지. 내가 누군지. 좀비가 뭔지 알기 위해서)",
        "플레이어: 네. 들어가죠!",
        "-hidden ending-"
    }
};

void hidden_ending() {
    int dialogue_line = 0;
    int dialogue_num = 0;
    system("cls");

    UINT oldCP = GetConsoleOutputCP();
#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    setCursorPosition(8, 2);
    std::cout << u8"⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⠠⠀⠄⢀";
    setCursorPosition(8, 3);
    std::cout << u8"⠄⠂⠁⠄⢁⠐⠈⠀⠂⡐⠀⢂⠐⠀⠂⠐⠀⠂⠐⠀⠂⠐⠀⠂⠐⠀⠂⠐⠀⠂⠐⠀⠂⠐⠀⠂⠐⠀⠂⠐⡀⠌⠀⠄";
    setCursorPosition(8, 4);
    std::cout << u8"⠐⠀⡁⠐⠀⠄⢁⠈⠄⠠⠈⢀⠀⡁⢈⠀⡁⢈⠀⡅⡠⠁⠈⠀⡁⠈⡀⢁⠈⡀⢁⠈⡀⢁⠈⢀⠁⢈⠀⡁⢈⠀⢁⠀⡀⣂⣐";
    setCursorPosition(8, 5);
    std::cout << u8"⡀⢁⠠⠈⡀⠂⠄⠂⠐⢀⠈⡀⠄⠠⠀⠂⠠⠀⠄⠈⠘⠱⢅⠄⠀⠠⠀⠀⠄⠀⠠⠀⢀⠠⠀⠠⢀⢄⣠⠠⠤⠔⠔⠒⠘⠈⢉⠈⠀⡀";
    setCursorPosition(8, 6);
    std::cout << u8"⠠⠠⠠⠂⠄⠆⠔⠄⠅⠄⠄⠄⡀⢂⠈⠄⠂⡐⠀⠌⠀⠄⡠⣙⣪⢶⣰⡥⡤⢌⣂⠒⡒⠵⠩⠩⠥⠤⠔⠔⠐⠐⠐⠐⠐⠁⠠⠀⡁⠠";
    setCursorPosition(8, 7);
    std::cout << u8"⢀⠐⠀⢂⠐⠀⢂⠀⠢⡀⠐⢀⠠⠀⠂⠂⠁⡀⠁⠁⠁⠁⡀⣄⢔⠙⠔⠄⡀⠀⠀⢀⠀⡀⠈⡀⠠⠀⠄⠂⠁⠐⠈⡀⠈⠄⠂⠐⢀⠐";
    setCursorPosition(8, 8);
    std::cout << u8"⠄⠂⠁⠄⠠⠁⠄⢀⠁⠂⠅⠀⡀⡐⠈⠀⡁⠀⡈⢀⠐⢄⢂⠺⢙⠑⡑⠁⠄⠱⢤⢀⠀⠠⠀⠄⠂⢀⠂⡀⢁⠈⠠⠀⡈⠠⠈⡀⠂⡀";
    setCursorPosition(8, 9);
    std::cout << u8"⠐⢈⠠⠈⡀⠂⠐⡀⠠⠡⡘⡖⠖⠑⢀⠁⢀⠠⢠⢂⢝⣯⡣⠵⣱⣃⢊⡢⡓⠪⣅⢍⢍⢆⢆⠀⠂⠠⠀⠄⢀⠂⢁⠠⠐⠀⠂⡀⠂⠠";
    setCursorPosition(8, 10);
    std::cout << u8"⢐⠀⡐⢀⠐⠈⡀⠄⠉⢝⠌⢎⠀⠈⢀⠀⠄⢈⠳⠅⣢⢣⠮⡖⣸⣺⠀⣯⢯⠹⣸⡪⠆⠇⡑⢔⣈⠄⠐⠀⠂⠠⠀⠄⠂⢁⠐⢀⠈⠄";
    setCursorPosition(8, 11);
    std::cout << u8"⠀⠄⠐⡀⠄⢁⠀⠄⠐⠈⢎⠔⡀⡈⠠⡀⣂⠢⠩⢸⣪⢸⠽⢕⠸⢚⠈⠎⣍⢄⣂⣢⡄⡤⢤⢰⡠⡔⠀⢁⠈⡀⠂⠐⡀⠂⡀⠂⠐⠈";
    setCursorPosition(8, 12);
    std::cout << u8"⢁⠈⠄⠠⠐⠄⠔⠄⠆⠌⡆⢕⢐⢌⢲⠨⡪⢑⠅⢆⢂⡂⣃⠢⡑⠅⢅⢕⡐⡔⡕⣛⡎⠎⠎⠎⠎⢀⠐⠀⠄⠐⠈⠠⠀⠂⠠⠈⠠⠁";
    setCursorPosition(8, 13);
    std::cout << u8"⡀⠂⡈⢀⠂⢁⠈⠄⠂⢀⠱⠱⠑⠑⠁⡉⠈⠈⠼⢜⠢⡣⡃⠕⡇⡛⢼⢸⢎⢇⠮⣺⣊⠉⠉⠁⠠⠀⠄⠁⠄⢁⠈⠄⠈⠄⢁⠈⠄⡈";
    setCursorPosition(8, 14);
    std::cout << u8"⠄⠂⠐⡀⢐⠀⢂⠐⠈⡀⠠⠐⠀⢂⠠⠀⠂⡀⠂⡾⣎⠂⢀⠈⠀⠈⠀⢗⣿⠈⠀⠋⠛⠀⠠⠈⡀⠂⠠⠁⡐⢀⠐⢈⠠⠈⡀⠐⡀⠄";
    setCursorPosition(8, 15);
    std::cout << u8"⠐⠈⠄⠂⡀⠂⠄⠂⢁⠠⠐⢀⠁⠄⡀⠂⢁⠀⠄⠉⢁⠠⠀⠄⢁⠈⡀⠄⠉⠠⠐⠀⠂⡈⠀⢂⠠⠈⡀⠂⠠⠀⢂⠠⠐⠀⠄⢁⠠⠐";
    setCursorPosition(8, 16);
    std::cout << u8"⠌⠐⡀⠁⠄⡈⠄⡈⠠⠀⢂⠀⠂⠄⠐⠈⡀⠄⠂⡈⢀⠠⠐⠀⢂⠠⠀⠄⡈⠠⠐⠈⠠⠀⠌⠀⠄⠂⠠⠈⠠⠁⠠⠀⠂⡁⢐⠠⠐⠀";
    setCursorPosition(8, 17);
    std::cout << u8"⡁⢐⠀⡁⢂⠀⢂⠀⡂⠁⠄⡈⠐⢈⠀⡁⠌⠠⠐⡀⠄⠂⢀⠂⠁⠄⡀⢂⠐⢀⠐⡀⠡⢀⠡⠀⠡⠐⠈⡀⠁⠂⡁⠈⠄⠁⠄⠠⠀⠂⡁";
    setCursorPosition(8, 18);
    std::cout << u8"⠄⠂⡐⠠⠐⠈⠠⠐⠀⠌⠠⢀⠡⠀⢂⠀⠂⡁⠠⠐⠈⡀⠄⠁⠄⠐⡀⠂⠁⠄⠄⡐⠐⡀⠂⠠⠐⠈⡀⠂⡁⢀⠁⢂⠠⠁⠄⠡⠈⠠⠁⡁⢀";
    setCursorPosition(8, 19);
    std::cout << u8"⠄⠁⠄⠂⡈⠄⠡⠀⠅⠂⡁⠄⠐⢈⠀⠌⠠⠐⢀⠂⢁⠠⠀⠅⠈⠄⠐⡀⠂⢁⠠⠈⠄⠂⡁⠄⠂⡀⢂⠈⠠⠀⢂⠈⠄⠨⠐⢀⠂⠄";
    SetConsoleOutputCP(oldCP);
    updateTextBox("");
    while (1) {
        if (_kbhit()) {
            int key = _getch();
            if (key == ' ') { // 스페이스바로 대화 진행
                if (dialogue_line < hidden_ending_dialogue.size()) {
                    updateDialogue(hidden_ending_dialogue[dialogue_line++]);
                }
                else {
                    exit(0);
                }
                if (dialogue_line == 22) {
                    system("cls");

                    oldCP = GetConsoleOutputCP();
#ifdef _WIN32
                    // Windows에서 UTF-8 인코딩 설정
                    SetConsoleOutputCP(CP_UTF8);
#endif
                    setCursorPosition(8, 2);
                    std::cout << u8"⠀⢀⡴⠋⢀⣴⠋⠀⠀⣀⠔⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠲⣄⡀⠀⠀⠙⠲⢤⣀⠀⠀⠀⠀⠀⠀⠀";
                    setCursorPosition(8, 3);
                    std::cout << u8"⡴⠋⠀⣠⣺⠃⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠲⢤⡀⠀⠀⠀⠉⠓⠦⢄⡀⠀⠀";
                    setCursorPosition(8, 4);
                    std::cout << u8"⠀⠀⡰⡱⠁⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣠⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⢄⠀⠀⠀⠀⠀⠉⠲⡀";
                    setCursorPosition(8, 5);
                    std::cout << u8"⠀⡴⡱⢁⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠖⠒⠊⠉⠉⢅⡀⠀⠀⠀⠈⠳⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙";
                    setCursorPosition(8, 6);
                    std::cout << u8"⡸⣱⣣⠋⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠒⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠢⢄⣀⠀⠀⠙⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
                    setCursorPosition(8, 7);
                    std::cout << u8"⢡⡷⠁⠀⠀⠀⠀⠀⠀⢀⡤⠊⠁⠀⠀⠀⢀⣀⣀⣀⣠⣤⡀⠀⠀⠀⠀⠀⠀⠉⠒⠤⣀⠈⠢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
                    setCursorPosition(8, 8);
                    std::cout << u8"⡟⠀⠀⠀⠀⠀⠀⡠⠚⠁⠀⢠⡶⢲⣿⣿⣿⣿⣿⣿⢸⣿⣿⣆⠀⢀⣀⣠⠖⠲⣶⠀⠀⠉⠲⢌⡢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
                    setCursorPosition(8, 9);
                    std::cout << u8"⠀⠀⠀⠀⢀⢔⡿⠀⠀⠀⣰⣿⡇⣾⣿⣿⣿⣿⣿⡟⣿⣿⣿⣿⣟⡗⠃⠀⠀⠀⠈⠳⡄⠀⠀⠀⠙⢮⣆⠀⠀⠀⠀⠀⠀⠀⢠⣄⣀⡤";
                    setCursorPosition(8, 10);
                    std::cout << u8"⠀⠀⢀⡴⡱⠋⠀⠀⠀⣴⣿⣿⢀⣿⣿⣿⣾⣿⣿⡇⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠳⡧⠀⠀⠀⠀⠀⠘⣷⠃⠉⠀";
                    setCursorPosition(8, 11);
                    std::cout << u8"⠀⢠⠊⡜⠀⠀⠀⠀⣰⣿⣿⡟⢸⣿⣿⡿⣿⣿⣿⣇⣿⣿⡿⠿⠿⣷⣀⠀⠀⠀⠀⣰⢚⡂⠀⠀⠀⠀⠀⠹⡕⢄⠀⢠⠿⠞⠀⠀⠀⠀";
                    setCursorPosition(8, 12);
                    std::cout << u8"⠠⠁⡜⣀⠀⠀⠀⢠⣿⣿⣿⡇⣿⣿⣿⣷⣿⣿⣿⢸⣿⣳⢯⣗⣶⣾⢿⠑⣖⣦⣚⣉⣩⠟⠹⡟⢦⡀⠀⠀⠙⠺⢭⡙⠀⠀⠀⠀⠀⠀";
                    setCursorPosition(8, 13);
                    std::cout << u8"⠀⡴⠊⡟⠀⠀⠀⣼⣿⣿⣿⢠⣿⣿⣿⢹⣿⣿⣿⢸⣿⣷⢿⡏⡇⣠⡾⡷⠳⢬⣙⠦⣄⠀⣀⣙⣼⣿⡄⠀⠀⣜⣁⠀⠀⠀⠀⠀⢀⡀";
                    setCursorPosition(8, 14);
                    std::cout << u8"⠌⠀⠸⠋⢹⣀⡀⣿⣿⣿⡏⣸⠿⣿⣿⣿⣿⣿⡇⣸⣿⣇⣿⡇⣿⠎⣠⡇⠀⠀⠙⢷⢺⠋⠁⠀⠀⠘⣿⡄⠀⢠⣎⠀⠀⢠⡤⠤⠜⠀";
                    setCursorPosition(8, 15);
                    std::cout << u8"⠀⠐⢹⠀⠀⠀⠉⠻⠿⠿⡏⠀⠐⠛⢯⣿⠟⠋⠁⠈⠁⠀⠉⠓⠋⠉⣼⠀⠀⠀⠀⠸⡼⡀⠀⠀⣀⣀⣹⡇⣖⠋⠉⠀⣀⣰⠊⠀⠀⠀";
                    setCursorPosition(8, 16);
                    std::cout << u8"⠀⠀⠸⠀⠀⠂⢒⠀⠀⠸⠓⠒⠦⡀⠀⠹⡄⣀⠀⠀⠀⠀⠀⠀⠀⢀⡇⠀⠀⢠⡄⠀⢷⣳⡖⠋⠉⠀⠉⢧⡞⠂⠀⠀⢃⠀⠀⠀⢀⣤";
                    setCursorPosition(8, 17);
                    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠉⠉⢰⠀⠀⢶⣁⠀⠀⠛⢙⣶⡆⠀⠀⠀⠀⠀⣸⠁⠀⢀⡏⢹⠀⠈⣧⢧⢀⣀⣠⠤⣼⠿⠄⠀⢪⠀⠀⠀⣀⡬⠵";

                    SetConsoleOutputCP(oldCP);
                    updateTextBox("");
                }
            }
        }
    }
}