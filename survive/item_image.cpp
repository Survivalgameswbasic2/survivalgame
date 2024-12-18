#include <iostream>
#include "expire_tool.h"
#include "mutex_helper.h"

char itemList[5][10][16]{
	{
		"               ",
		"        .:'    ",
		"    __ :'__    ",
		" .'`  `-'  ``. ",
		":             :",
		":    food     :",
		" :           : ",
		"  `.__.-.__.'  ",
		"               ",
		"               "
	},
	{   "      [~]      ",
		"      |=|      ",
		"  . - ' ' - .  ",
		"  | ------- |  ",
		"  |   ~~~   |  ",
		"  |   ~~~   |  ",
		"  |  water  |  ",
		"  | ------- |  ",
		"  '---------'  "
	},
	{
		"               ",
		"               ",
		"   _______ = __",
		"  // @([]____()",
		"  _//| _]      ",
		" /    /( )     ",
		"/ __ |'--'     ",
		"/___/          ",
		"         gun   ",
		"               "

	},
	{
		"               ",
		"	     -``-   ",
		"	    /   )   ",
		"      /   /    ",
		"     /   /     ",
		"    /___/      ",
		"   /   /       ",
		"  /   /        ",
		"  `-_/  bullet ",
		"               "

	},
	{
		"          '-,_ ",
		"          //   ",
		"       /   /   ",
		"      /   /    ",
		"     /   /     ",
		"    /-,_/      ",
		"   /-,_/       ",
		"   //          ",
		"  //           ",
		" |/     heal   ",


	}

};

void drawitem(int mode) {
	int xOffset = 72;
	int yOffset = 10; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = 26;    // 텍스트 창 가로 길이
	int height = 14;                 // 텍스트 창 세로 길이
	std::lock_guard<std::mutex> lock(bufferMutex);
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
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			setCursorPosition(xOffset + j + 3, yOffset + i + 2);
			printf("%c", itemList[mode][i][j]);
		}
	}

}


void clear_item_screen() {
	std::lock_guard<std::mutex> lock(bufferMutex);
	int x = 72;
	int y = 11;
	for (int i = 0; i < 12; i++) {
		setCursorPosition(x, y + i);
		std::cout << "                                ";
	}
}