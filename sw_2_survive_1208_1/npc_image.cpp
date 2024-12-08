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
    int x = 72;
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

void draw_npcbox() {

    int xOffset = 74;
    int yOffset = 9; // 맵 창 하단에 텍스트 창 위치 설정  
    int width = 36;    // 텍스트 창 가로 길이
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
                else printf(" ");
            }
        }
    }
}
//연구원
void printnpc1() {
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 72;
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
//0일차 동굴
void printnpc2() {
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 75;
    int y = 10;
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


}
//사기꾼
void printnpc3() {
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 75;
    int y = 10;
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

}
//day 4
void printnpc4() {
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 75;
    int y = 10;
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

}
//day 5
void printnpc5() {
    UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
    // Windows에서 UTF-8 인코딩 설정
    SetConsoleOutputCP(CP_UTF8);
#endif
    int x = 75;
    int y = 10;
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

}


void clear_npc_screen() {
    int x = 72;
    int y = 10;
    for (int i = 0; i < 12; i++) {
        setCursorPosition(x, y + i);
        std::cout << "                                ";
    }
}