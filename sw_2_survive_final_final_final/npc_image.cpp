#include <iostream>
#include"expire_tool.h"
#include "mutex_helper.h"
#ifdef _WIN32
#include <windows.h>
#endif

void draw_npcbox() {
    int xOffset = 72;
    int yOffset = 10; // 맵 창 하단에 텍스트 창 위치 설정  
    int width = 26;    // 텍스트 창 가로 길이
    int height = 14;                 // 텍스트 창 세로 길이

    for (int y = 0; y < height; y++) {
        for (int x = 0; x <= width; x++) {
            setCursorPosition(xOffset + x, yOffset + y);
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

            }
        }
    }
    setCursorPosition(xOffset+1, yOffset + height);
    std::cout << "숫자키 1:식량 사용(정신력)";
    setCursorPosition(xOffset + 1, yOffset + height+1);
    std::cout << "숫자키 2:치료제사용(체력)";
   
}

void printplayer() {

    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    std::lock_guard<std::mutex> lock(bufferMutex);
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 72;
    int y = 11;
    setCursorPosition(x, y);
    // 유니코드 출력
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠠⠤⠄⢀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 1);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⡀⠤⠒⠉⠉⠉⠁⠀⠀⠀⠀⠠⢀⡀⠀⠀⠀";
    setCursorPosition(x, y + 2);
    std::cout << u8"⠀⠀⠀⠀⠈⣩⠏⠀⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠈⣆⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 3);
    std::cout << u8"⠀⠀⠀⠀⢘⡮⠀⢀⣾⣽⡄⠀⢰⡀⢀⠀⠀⠀⠀⠀⠹⡂⠀⠀⠀⠀";
    setCursorPosition(x, y + 4);
    std::cout << u8"⠀⠀⠀⠀⠸⣧⢰⣼⣻⣹⢣⢰⡿⡿⡌⣧⣆⢣⠀⠀⠀⡇⠀⠀⠀⠀";
    setCursorPosition(x, y + 5);
    std::cout << u8"⠀⠀⠀⠀⠀⠈⢿⣃⣀⣈⡁⠙⠋⢉⣉⣉⡓⣹⣦⡄⣄⠁⠀⠀⠀⠀";
    setCursorPosition(x, y + 6);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠸⡄⠧⠼⠁⡆⠈⠣⡠⠃⠁⠋⠀⢱⠋⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 7);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠈⠀⠀⠀⠀⠀⠀⣀⠴⠃⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 8);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠈⢦⡀⠀⠠⠄⠀⠀⡠⢊⠇⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 9);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠲⡤⠤⠒⠉⠀⢸⡀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 10);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⢀⣠⠴⡞⠁⠀⠀⠀⠀⠀⣹⠖⠤⣀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 11);
    std::cout << u8"⠀⠀⠀⣀⡤⣔⡎⠍⠀⠀⠘⢂⢀⣀⡀⠤⠒⠁⠀⠤⣄⣌⠑⠒⠤⡀";

    SetConsoleOutputCP(oldCP);
    draw_npcbox();

}

//연구원
void printnpc1() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 72;
    int y = 11;
    setCursorPosition(x, y);
    // 유니코드 출력
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠬⢕⣖⢄⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 1);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⣠⡾⠛⠉⠀⠀⠀⠀⠁⠃⠠⢄⠀⠀⠀⠀";
    setCursorPosition(x, y + 2);
    std::cout << u8"⠀⠀⠀⠀⢠⠾⠁⠀⢀⣴⣋⣻⣷⡄⠀⠀⠀⠈⢳⠀⠀⠀⠀";
    setCursorPosition(x, y + 3);
    std::cout << u8"⠀⠀⠀⢠⣯⠆⠀⠀⢸⠁⠀⠀⠀⠁⠑⢦⡀⠀⠐⣧⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 4);
    std::cout << u8"⠀⠀⠀⢸⣾⠀⠃⢸⣷⠲⠀⠀⠠⠶⠤⢤⢷⠀⠀⣯⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 5);
    std::cout << u8"⠀⠀⠀⠀⠀⣸⣺⠤⠤⠤⡟⠀⠧⣤⣤⣀⡾⠁⢀⡇⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 6);
    std::cout << u8"⠀⠀⠀⠀⢀⠗⠙⢆⠀⠀⠀⠀⠀⠀⠀⠀⣤⡖⠋⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 7);
    std::cout << u8"⠀⠀⠀⠀ ⠀⠀⠈⠳⣄⠈⠛⠀⣀⡤⢾⠏⠃⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 8);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⡽⣍⣉⣡⠤⠞⢲⣄⡀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 9);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⣀⡴⠛⢹⣴⢋⠳⡇⣀⡤⡞⠂⢹⠣⢄⡀⠀⠀⠀⠀";
    setCursorPosition(x, y + 10);
    std::cout << u8"⠀⠀⣀⣤⠶⢋⠏⠀⠀⡇⠛⠈⠆⠉⠁⢸⠁⠀⢸⡇⠀⠈⠓⢦⡀⠀";
    setCursorPosition(x, y + 11);
    std::cout << u8"⣠⠿⠋⠀⠀⠿⣲⠟⢠⠇⠀⢰⠀⠀⠀⣼⠠⣖⠚⠃⠀⠀⠀⠀⠈⢢";

    SetConsoleOutputCP(oldCP);
    draw_npcbox();
}
//0일차 동굴
void printnpc2() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 72;
    int y = 11;
    setCursorPosition(x, y);
    // 유니코드 출력
    std::cout << u8"⠀⠀⠀⠀⠀⠠⢚⡻⠷⠂⠈⠉⠑⠆⠠⠤⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 1);
    std::cout << u8"⠀⠀⠀⠀⣀⠴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢣⡀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 2);
    std::cout << u8"⠀⠀⠀⡜⠁⠀⠀⠀⠀⢀⠔⢠⠀⠀⠀⠀⠀⠀⠀⢳⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 3);
    std::cout << u8"⠀⠀⡜⠀⡀⠀⢠⢃⡴⢻⠀⡏⠀⠀⠀⡀⠀⠀⠀⠘⡇⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 4);
    std::cout << u8"⠀⠀⡇⣼⠁⣠⠿⠯⢄⣸⣸⢳⣀⣢⡤⣷⠀⠀⠀⠀⡇⠀⠀⠀⠀";
    setCursorPosition(x, y + 5);
    std::cout << u8"⠀⠀⠻⠘⡎⢹⠒⢲⢦⣄⠛⠌⢧⡷⡷⣾⢀⡤⢦⡀⡇⠀⠀⠀";
    setCursorPosition(x, y + 6);
    std::cout << u8"⠀⠀⠀⠀⠹⣜⡄⠰⠤⠃⠀⠀⠰⠤⠏⢹⡸⠀⠀⡷⣧⠀⠀⠀";
    setCursorPosition(x, y + 7);
    std::cout << u8"⠀⠀⠀⠀⠀⢸⡇⠀⠀⠠⠀⠀⠀⠀⠀⠘⢁⡠⡾⠁⠈⠀⠀⠀";
    setCursorPosition(x, y + 8);
    std::cout << u8"⠀⠀⠀⠀⢀⣾⠷⣄⠀⠀⡤⠄⠀⠀⢀⣰⢡⣄⡇⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 9);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠸⣷⣄⡈⣁⡠⡴⠋⢻⣇⠘⠃⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 10);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⢀⡠⣼⡿⣷⠟⠋⠀⠀⠀⡹⠙⠲⢤⣀⡀⠀⠀";
    setCursorPosition(x, y + 11);
    std::cout << u8"⠀⠀⠀⢀⡤⠞⠁⠀⠘⢯⠁⣀⣀⣀⢠⠔⠁⠀⠀⠀⢰⠱⢤⣀";
    SetConsoleOutputCP(oldCP);
    draw_npcbox();
}
//사기꾼
void printnpc3() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 72;
    int y = 11;
    setCursorPosition(x, y);
    // 유니코드 출력
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠒⠦⡀⠒⠪⡕⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 1);
    std::cout << u8"⠀⠀⠀⢀⣀⣀⠰⠛⠀⠀⠀⠀⠀⠀⠀⠛⠛⠳⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 2);
    std::cout << u8"⠀⠀⠀⢀⠜⠁⠀⠀⠀⣩⡸⠱⡠⠤⠤⣀⠀⠀⢏⠁⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 3);
    std::cout << u8"⠀⠀⢠⡡⠎⠀⢀⠀⡌⣫⡐⠂⠀⠤⠿⠔⠓⠀⠀⢃⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 4);
    std::cout << u8"⠀⠀⠀⢸⢠⢸⣐⣓⣒⡛⠓⢒⣚⣛⣻⠊⣬⢐⠢⢌⣆⡀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 5);
    std::cout << u8"⠀⠀⠀⠸⠹⣸⠛⡒⠂⡄⠀⠠⡤⠤⠤⠄⢻⠖⢌⡹⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 6);
    std::cout << u8"⠀⠀⠀⠀⠛⠘⡀⠛⠞⠀⠀⠀⠳⠶⠃⡀⠘⠀⢘⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 7);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⡇⠀⠀⠐⠀⠀⠀⠀⠠⠄⢠⢴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 8);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠘⢄⠀⠀⠤⠠⠀⠀⣉⡔⢸⠁⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 9);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⠀⠩⢦⡄⠤⠔⢊⣁⡿⠽⠀⠰⣁⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 10);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⣠⠇⠀⣩⠽⣮⣭⠤⢈⣁⣠⡤⢼⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 11);
    std::cout << u8"⠀⠀⠀⠀⢀⣰⠞⠘⠶⠿⠛⡿⠃⠀⠀⠀⠀⠀⠀⠛⠻⢶⡀⠀⠀⠀⠀⠀";


    SetConsoleOutputCP(oldCP);
    draw_npcbox();
}
//day 4
void printnpc4() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 72;
    int y = 11;
    setCursorPosition(x, y);
    // 유니코드 출력
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠤⠒⠒⠒⠒⠒⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 1);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⢠⠃⠀⠀⠀⠀⠀⠀  ⠀⠀⠀⠘⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 2);
    std::cout << u8"⠀⠀⠀⠀⠀⠠⠁⢀⣀⣀⣀⣀⠀⠀⠀⠀⠀ ⠀⠀⢳⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 3);
    std::cout << u8"⠀⠀⠀⢀⠔⠛⠉⠁⠀⠀⠀⠉⠉⠓⠶⣄⣀⡀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 4);
    std::cout << u8"⠀⠀⣔⣁⣤⢤⠤⠤⠤⡤⢤⣀⣀⣠⣖⣻⠀⠉⠙⠺⡀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 5);
    std::cout << u8"⠀⠀⠀⠀⡖⡼⠒⡒⢶⠄⠀⠀⡤⢤⠤⢼⡀⠄⠢⣀⣥⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 6);
    std::cout << u8"⠀⠀⠀⠀⠛⠘⡀⠛⠞⠀⠀⠀⠳⠶⠃⡀⠘⠀⢘⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 7);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⡇⠀⠀⠐⠀⠀⠀⠀⠠⠄⢠⢴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 8);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠘⢄⠀⠀⠤⠠⠀⠀⣉⡔⢸⠁⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 9);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠈⡭⠌⠦⣌⡭⠔⠚⠉⠉⠉⠉⡀⡇⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 10);
    std::cout << u8"⠀⠀⠀⠀⠀⠀⣶⠣⠄⡈⠀⠀⠀⠀⠀⢀⢀⡪⠄⠊⡦⡀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 11);
    std::cout << u8"⠀⠀⠀⢀⡤⠊⠈⠢⣈⠐⠉⠀⠀⠐⡨⡖⠁⠀⡌⢠⠀⠈⠓⢤⡀⠀⠀⠀";


    SetConsoleOutputCP(oldCP);
    draw_npcbox();
}
//day 5
void printnpc5() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 72;
    int y = 11;
    setCursorPosition(x, y);
    // 유니코드 출력
    std::cout << u8"⠀⠀⠀⠀⠀⠀⠀⡠⠖⠉⠀⠀⠀⠉⠉⠉⠐⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 1);
    std::cout << u8"⠀⠀⠀⠀⠀⡠⠊⢀⡠⠤⠒⠲⢤⣀⠀⠀⠀⠀⠈⢢⡀⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 2);
    std::cout << u8"⠀⠀⠀⠀⠰⡠⠔⠁⠀⡄⠀⠀⠀⠈⠑⢦⡀⠀⠀⠀⢳⠀⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 3);
    std::cout << u8"⠀⠀⠀⠀⣼⠀⠀⠀⡜⡇⠀⠀⡶⠀⠀⢀⠙⡆⠀⠀⠀⡆⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 4);
    std::cout << u8"⠀⠀⠀⠀⣿⠀⡀⣦⣁⣇⡀⡀⣇⣇⣀⣎⡄⢠⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 5);
    std::cout << u8"⠀⠀⠀⠀⣿⠀⢰⢸⠛⢾⢆⡕⣇⠾⢪⡒⠂⣼⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 6);
    std::cout << u8"⠀⠀⠀⠀⢸⢆⡼⡈⠑⠋⠀⠁⠀⠑⠊⡸⣾⣻⠀⠀⠀⢡⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 7);
    std::cout << u8"⠀⠀⠀⠠⢸⠈⢿⡇⠀⠀⠀⠀⠀⠀⢰⢳⣮⢿⠀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 8);
    std::cout << u8"⠀⠀⠀⢰⡇⠀⡜⡨⣦⡀⠀⠔⡲⠀⠰⡶⡺⠪⡆⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 9);
    std::cout << u8"⠀⠀⠀⠸⣇⣀⡋⠐⠕⣏⣲⡤⠤⠔⢋⣀⠤⠞⠀⣀⡠⠞⠀⠀⠀⠀⠀⠀⠀";
    setCursorPosition(x, y + 10);
    std::cout << u8"⠀⠀⠀⠀⠈⠉⢉⠝⠉⢱⡯⠣⠔⣮⠍⠐⠒⠌⠑⠀⠈⠒⠤⢄⡀⠀⠀⠀⠀";
    setCursorPosition(x, y + 11);
    std::cout << u8"⠀⠀⣀⡀⠤⠂⠁⠀⠀⢦⠃⠀⢰⡘⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠌⠑⢤⠀⠀";


    SetConsoleOutputCP(oldCP);
    draw_npcbox();
}


void clear_npc_screen() {
    std::lock_guard<std::mutex> lock(bufferMutex);
    int x = 72;
    int y = 11;
    for (int i = 0; i < 12; i++) {
        setCursorPosition(x, y + i);
        std::cout << "                                ";
    }
}