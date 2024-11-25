#include <iostream>
#include"expire_tool.h"
#ifdef _WIN32
#include <windows.h>
#endif


void printplayer() {

    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 75;
    int y = 10;
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


}

void printnpc1() {
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 75;
    int y = 10;
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

}