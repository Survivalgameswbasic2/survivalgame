#include "expire_tool.h"
#include "item_image.h"
#include "item_image2.h"
#include "map_image.h"
#include "backpack.h"
#include "player.h"
#include <windows.h>
#include <conio.h>
#include "bad_ending.h"

using namespace std;
#define STAGE_WIDTH 70  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 

void draw_ready_text_after(player* p) {

	int xOffset = 0;
	int yOffset = 21; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = STAGE_WIDTH;    // 텍스트 창 가로 길이
	int height = 5;                 // 텍스트 창 세로 길이

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

	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("하루일차가 넘어가기 전, 식수를 하나씩 섭취해야한다.");

	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("물자를 소비하자. (스페이스카 누를 시 소비)");
	int key = _getch();
	while (key == 0) {
	}

	key = 0;

	if (p->water > 0) {
		p->water--;
	}
	else {
		bad_ending_starve();
	}


	setCursorPosition(1, 23);
	std::cout << "                                                                     ";
	setCursorPosition(1, 24);
	std::cout << "                                                                     ";


	key = 0;

	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("오늘 하루 일차를 마치며, 이제는 잠에 들고");
	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("다음의 탐사를 준비해야할 때이다.");
	setCursorPosition(xOffset + 1, yOffset + 3);
	printf("잠들기 전, 무엇을 준비할까? (선택지의 효과는 다음일차에 한정됩니다)");
	key = _getch();
	while (key == 0) {
	}

	setCursorPosition(1, 23);
	std::cout << "                                                                     ";
	setCursorPosition(1, 24);
	std::cout << "                                                                     ";
	setCursorPosition(1, 22);
	std::cout << "                                                                     ";


	setCursorPosition(xOffset + 1, yOffset + 1);
	printf("▶ 1. 몸을 단련한다. (최대체력 1 증가)");

	setCursorPosition(xOffset + 1, yOffset + 2);
	printf("  2. 마음을 가다듬으며 진정한다.(스트레스 한계 20 증가)");

	setCursorPosition(xOffset + 1, yOffset + 3);
	printf("  3. 얻은 물자들을 정리한다. (아이템 효과가 2배)");
	int where = 1;
	while (true) {

		key = _getch();
		if (key == '1') {
			setCursorPosition(xOffset + 1, yOffset + where);
			printf(" ");

			where = 1;

			setCursorPosition(xOffset + 1, yOffset + where);
			printf("▶");
		}
		else if (key == '2') {
			setCursorPosition(xOffset + 1, yOffset + where);
			printf(" ");

			where = 2;

			setCursorPosition(xOffset + 1, yOffset + where);
			printf("▶");
		}
		else if (key == '3') {
			setCursorPosition(xOffset + 1, yOffset + where);
			printf(" ");

			where = 3;

			setCursorPosition(xOffset + 1, yOffset + where);
			printf("▶");
		}

		else if (key == ' ') {
			p->mode = where;
			break;
		}
	}

	if (p->mode == 1) {
		p->maxh = 6;
		p->maxm = 100;
		p->heart;
	}
	else if (p->mode == 2) {
		p->maxh = 5;
		p->maxm = 120;
	}
	else {
		p->maxh = 5;
		p->maxm = 100;
	}


	if (p->mental >= 100) {
		bad_ending_zombie();
	}




}
void draw_ready_map_after(int day) {

	int xOffset = 74;
	int yOffset = 0; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = 27;    // 텍스트 창 가로 길이
	int height = 26;                 // 텍스트 창 세로 길이

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

	if (day >= 0) {

		for (int i = 0; i < 6; i++) {
			setCursorPosition(xOffset + 1, yOffset + 18 + i);
			for (int j = 0; j < 20; j++) {
				printf("%c", mapList[0][i][j]);
			}
		}

		if (day >= 1) {

			for (int i = 0; i < 6; i++) {
				setCursorPosition(xOffset + 4, yOffset + 11 + i);
				for (int j = 0; j < 16; j++) {
					printf("%c", mapList[1][i][j]);
				}
			}

			if (day >= 2) {

				for (int i = 0; i < 6; i++) {
					setCursorPosition(xOffset + 1, yOffset + 4 + i);
					for (int j = 0; j < 16; j++) {
						printf("%c", mapList[2][i][j]);
					}
				}
			}
		}

	}


}




void printInformation_after(player* p, BackP* b, int day) {


	// 클리어 화면 
	setCursorPosition(6, 0);
	printf("%d 일차 종료 - 생존  ... 자원 획득 현황", day);

	int food = b->food;
	setCursorPosition(6, 2);
	printf("식량 확보-");
	for (int k = 0; k < food; k++) {

		for (int i = 0; i < 4; i++) {
			setCursorPosition(6 + k * 8, i + 3);
			for (int j = 0; j < 12; j++) {
				printf("%c", itemList2[1][i][j]);
			}
		}

	}
	printf("%d 개 획득", food);


	int water = b->water;
	setCursorPosition(6, 8);
	printf("식수 확보-");
	for (int k = 0; k < water; k++) {
		for (int i = 0; i < 5; i++) {
			setCursorPosition(6 + k * 8, i + 9);
			for (int j = 0; j < 8; j++) {
				printf("%c", itemList2[0][i][j]);
			}
		}
	}
	printf(" %d 개 획득", water);

	int heal = b->medicine;
	setCursorPosition(6, 15);
	printf("치료제 확보-");
	for (int k = 0; k < heal; k++) {
		for (int i = 0; i < 4; i++) {
			setCursorPosition(6 + k * 8, i + 16);
			for (int j = 0; j < 12; j++) {
				printf("%c", itemList2[2][i][j]);
			}
		}
	}
	printf("%d 개 획득", heal);

	int gun = p->gun;
	int bullet = p->bullet;

	setCursorPosition(6, 21);
	printf("총탄 현황-");
	if (gun == 1) {
		for (int i = 0; i < 4; i++) {
			setCursorPosition(6, i + 22);
			for (int j = 0; j < 18; j++) {
				printf("%c", itemList2[3][i][j]);
			}
		}

		for (int k = 0; k < bullet; k++) {
			for (int i = 0; i < 2; i++) {
				setCursorPosition(20 + k * 8, i + 23);
				for (int j = 0; j < 12; j++) {
					printf("%c", itemList2[4][i][j]);
				}
			}
		}
	}
	printf("%d 개 획득", bullet);
	int key = -1;

	printf("\n\n 스페이스를 누를 시 일차가 종료되고 기지로 돌아갑니다.");

	while (1) {

		key = _getch();
		if (key == ' ') {
			break;
		}

	}

}


void printInformation2_after(player* p) {

	int hp = p->heart;
	int mp = p->mental;

	setCursorPosition(38, 3);
	printf("현재 남은 체력 x %d", hp);
	setCursorPosition(38, 5);
	printf("현재 스트레스 수치 x %d", mp);

	setCursorPosition(42, 8);
	printf(" ┌──┐");
	setCursorPosition(42, 9);
	printf(" │  │");
	setCursorPosition(42, 10);
	printf(" └──┘");
	setCursorPosition(42, 11);
	printf("┌────┐");
	setCursorPosition(42, 12);
	printf("│  ♥ │");
	setCursorPosition(42, 13);
	printf("│    │");



}

// 텍스트 창 초기화 및 메시지 출력 함수
void draw_ready_after(player* p, int day, BackP* b) {
	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = STAGE_WIDTH;    // 텍스트 창 가로 길이
	int height = 20;                 // 텍스트 창 세로 길이
	// 텍스트 창 테두리와 제목 출력
	printInformation_after(p, b, day);
	system("cls");


	b->unionP(p);
	// 텍스트 창 테두리 그리기
	/*for (int y = 0; y < height; y++) {
		for (int x = 0; x <= width; x++) {
			setCursorPosition(x, y);
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
	}*/




	UINT oldCP = GetConsoleOutputCP();

#ifdef _WIN32
	// Windows에서 UTF-8 인코딩 설정
	SetConsoleOutputCP(CP_UTF8);
#endif
	int x = 9;
	int y = 1;
	setCursorPosition(x, y);
	// 유니코드 출력
	std::cout << u8"⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠲⠦⠤⣤⣀⣀⣀⣀⡀⠀⠀⠀⠑⢄⠈⠻⣿⢿⠻⣶⡀⠀⠀⠈⠃⠀⠀⠀⢂⠀⠀";
	setCursorPosition(x, y + 1);
	std::cout << u8"⣿⣿⣿⣿⣿⣿⠟⠋⠁⠀⠀⠀⠀⠀⠀⡀⠄⠀⠀⠀⠀⠀⠀⠈⠉⠻⢿⣿⣷⠀⠀⣀⠀⠑⢄⠘⠀⠀⠈⠙⣆⠀⢀⠀⠀⠀⢤⠸⠀⠀";
	setCursorPosition(x, y + 2);
	std::cout << u8"⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⣠⠞⠀⠀⠐⢄⣀⣀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣷⣮⣻⣦⡌⠂⠀⢤⠀⠀⠈⠀⠀⢢⠀⠈⠈⡇⠀⠀";
	setCursorPosition(x, y + 3);
	std::cout << u8"⣿⣿⣿⣿⠟⠁⠀⢠⡂⠀⠀⠀⣼⠃⠀⠀⠀⠀⠀⢙⡛⠛⠳⠦⢄⣀⣀⡀⠈⠻⣿⣿⣿⣟⣿⣦⠀⠈⢳⠠⢤⣀⠀⠀⢀⠀⡄⡇⠀⠀";
	setCursorPosition(x, y + 4);
	std::cout << u8"⣿⣿⢟⡥⠀⠀⠀⠈⢻⡄⠀⢸⡏⠀⠀⠀⠀⢀⣔⣁⣇⣹⣉⣿⣒⣬⠻⣷⣄⣀⠀⠀⠈⠙⢎⠛⢷⡀⠉⠀⠈⢻⣧⣀⠘⡇⠃⠀⠀";
	setCursorPosition(x, y + 5);
	std::cout << u8"⡿⢣⡾⠁⠀⠀⡀⠀⠀⠻⢀⡼⠋⠀⠀⠀⠀⣎⣇⣰⣇⣿⣀⣿⣀⣿⣦⠈⠙⠻⣷⡄⠀⠀⠈⠀⠈⣇⠀⠀⠀⠀⠉⣿⠐⠀⠀⠀⠀⠀";
	setCursorPosition(x, y + 6);
	std::cout << u8"⣰⣿⠃⠀⠀⣼⠃⠀⢠⡶⠁⠀⢠⠀⢀⠀⠀⡧⡧⢼⡧⣿⠤⣿⠤⣿⠤⡷⡄⠀⠈⠣⠀⠀⠀⣀⣴⣿⠀⠀⠀⠀⢀⠏⠀⠀⠀⢠⠀⠀";
	setCursorPosition(x, y + 7);
	std::cout << u8"⣿⡟⠀⠀⣾⠇⠀⡀⠏⠀⡎⠀⠘⠀⣼⠀⠸⡗⡗⢺⡗⣿⠒⣿⠒⣿⠒⡗⣺⠀⠀⠀⠀⣰⣿⣿⣿⣿⠇⠀⠀⢠⠎⠀⠀⠀⠀⠸⠀⢀";
	setCursorPosition(x, y + 8);
	std::cout << u8"⣿⠁⠀⠀⡟⢀⡾⠀⠀⠀⠘⠀⠀⡀⠘⠀⠀⢯⡟⢻⡟⣿⠛⣿⠛⣿⠛⣿⢿⠀⠀⣸⣿⣿⣿⣿⣿⣟⠔⠀⠀⠀⠀⠀⠀⠀⢰⡆⠀⢸";
	setCursorPosition(x, y + 9);
	std::cout << u8"⡟⠀⠀⢠⡇⣸⡷⠀⠀⠀⠀⢀⡆⣿⡄⠀⠀⢸⡯⢽⣯⣿⣭⣿⣭⣿⠭⠯⠟⠀⠀⣿⣿⣿⣿⣿⣿⠁⠀⢀⣀⣀⠀⠀⠀⠀⣸⡇⢰⣿";
	setCursorPosition(x, y + 10);
	std::cout << u8"⡇⠀⠀⡞⠀⢿⡏⠀⠀⠀⠀⣾⠀⣿⣿⣷⣄⣠⢉⣏⣿⣉⡹⠉⠤⠟⠀⠠⣕⣤⣾⣿⣿⣿⣿⣿⣿⠀⢀⠔⠋⠁⠉⠉⢢⡀⣿⣇⣼⣿";
	setCursorPosition(x, y + 11);
	std::cout << u8"⣿⠀⠀⠇⠀⠈⢷⣦⡀⠀⠀⠁⢸⣿⣿⣿⡿⢹⠂⢎⠱⡉⠉⢾⡉⢵⣏⠉⣉⣙⣿⣿⣿⣿⣿⣿⠃⠀⢸⢣⡀⠀⠀⠀⠀⣿⣿⣿⣿⡿";
	setCursorPosition(x, y + 12);
	std::cout << u8"⣿⣿⣇⠘⠀⢹⣛⡭⣭⠭⣭⠭⠭⠭⠭⠭⠭⠭⣵⢶⠎⡜⠫⣟⠟⢷⡶⠿⠻⣏⠉⠉⠙⢿⣿⠙⠃⠀⠀⣾⢿⣧⡀⠀⢀⣰⠿⣿⣿⣿⣧";
	setCursorPosition(x, y + 13);
	std::cout << u8"⣿⣿⡀⠀⢸⢸⡇⣿⠀⡏⠳⣖⠒⠛⠛⠛⠛⣿⢨⠩⢙⡎⠙⢦⠄⠙⢦⡀⣈⢳⣩⡲⠜⠃⠢⣄⢀⢠⣿⣎⠶⠛⠚⣚⡤⠖⣾⣿⣿⣿";
	setCursorPosition(x, y + 14);
	std::cout << u8"⣿⣿⣷⣤⢸⡼⡇⣿⠀⡟⢦⡘⢦⡀⠀⠀⠀⢿⢸⡖⠓⠒⠿⢔⣞⠩⠍⠪⢮⢅⣤⡍⠷⣖⠛⢁⣀⡽⠋⠉⠉⠒⠚⠳⣄⣀⣸⢿⣿⣿";
	setCursorPosition(x, y + 15);
	std::cout << u8"⣿⣿⣿⣿⢸⡇⡇⣿⠀⡇⠀⠳⣄⠹⣄⠀⠀⢸⢸⡗⠒⠒⢒⣖⡟⣗⠶⢞⡉⠉⠙⢶⣉⣨⠟⠭⢉⠀⠀⠀⣀⣀⣀⣠⡞⠉⠉⠉⠛⢿";
	setCursorPosition(x, y + 16);
	std::cout << u8"⣿⣿⣿⣿⣾⠇⣷⣿⠀⡇⠀⠀⠈⠳⡌⢳⡀⢸⢸⡇⠀⣰⠏⡼⡇⣧⡗⣴⠚⣻⡍⡉⢹⠎⢄⠀⠀⠉⣠⣚⡜⠉⡁⠤⠀⠀⠀⠀⠀⠀";
	setCursorPosition(x, y + 17);
	std::cout << u8"⣿⣿⣿⣿⣽⠀⣿⣿⠀⡇⠀⠀⠀⠀⠙⢦⡙⢾⢸⣇⡼⢡⠞⠀⡇⣿⣇⡜⠗⠂⠉⠉⠀⠀⠀⠂⠀⡰⣏⠱⡀⠘⠀⠀⠀⠀⠀⠀⠀⠀";


	SetConsoleOutputCP(oldCP);

	//여기에 동굴내부 아트 출력
	//test_print(0, 0);

	//printInformation2_after(p);
	//draw_ready_map_after(day);
	printstat(p);
	draw_ready_text_after(p);


}
