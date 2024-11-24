#include "expire_tool.h"
#include "item_image.h"
#include "item_image2.h"
#include "map_image.h"
#include "player.h"
#include <windows.h>
#include <conio.h>

using namespace std;
#define STAGE_WIDTH 70  // 스테이지의 너비
#define STAGE_HEIGHT 20 // 스테이지의 높이 


void print_intro(int day) {

	if (day == 0) {
		setCursorPosition(1, 1);
		printf("눈을 떴을 때는 동굴이었다.");
		setCursorPosition(1, 2);
		printf("앞이 보이지 않는 어둠 속에서 희미하게 어떤 소리가 들려온다.");
		setCursorPosition(1, 3);
		printf("우선 내가 어떤 상황에 있는지 알아내자. ");
		setCursorPosition(1, 5);
		printf("목표: 동굴 내부를 탐사하자");
		setCursorPosition(1, 7);
		printf("이동키: a w s d 키");
		setCursorPosition(1, 8);
		printf("상호작용키: 스페이스키");
	}
	else if (day == 1) {
		setCursorPosition(1, 1);
		printf("동굴 안의 사람에게 들은 바로는, 좀비와 햇빛을 피하라고 했었지. ");
		setCursorPosition(1, 2);
		printf("일단은 동굴 바깥쪽의 외딴 집이 있어서, 그 곳으로 가서 ");
		setCursorPosition(1, 3);
		printf("먹을 것이나 도움이 될만한 물건이 있는지 살펴봐야겠다.");
		setCursorPosition(1, 4);
		printf("동쪽에서부터 비춰오는 햇빛을 조심하며 이동하자.");
		setCursorPosition(1, 6);
		printf("목표: 외딴 집을 탐사하자");

	}
	else if (day == 2) {
		setCursorPosition(1, 1);
		printf("사람들의 흔적이 많을 캠핑장에 도착했다.");
		setCursorPosition(1, 2);
		printf("아직 좀비가 된지 얼마 안되서인지 주변을 움직이며 배회하니 조심하도록 하자.");
		setCursorPosition(1, 3);
		printf("살아남은 사람들의 흔적을 조사해서 행방을 알아낼 수 있지않을까?");
		setCursorPosition(1, 4);
		printf("연구원이 말했던 무전기 부품도 찾아보도록 하자.");
		setCursorPosition(1, 6);
		printf("목표:캠핑장에서 사람들의 흔적을 조사하고 무전기부품을 회수하자");
	}
	else if (day == 3) {

	}


	int key = _getch();
	while (_kbhit() == 0) {
	}



	system("cls");

}

void draw_ready_text(player* p, int day) {

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
	printf("이번에 조사할 곳은");

	if (day == 1) {
		printf("동굴 근처의 외딴 집이다.");
		setCursorPosition(xOffset + 1, yOffset + 2);
		printf("밖에 위치한 곳이니 햇볕이 강하고 좀비가 있을 것이다. 조심히 탐사하자.");
	}
	else if (day == 2) {
		printf("사람들의 흔적이 남아있을지도 모르는 캠핑장이다.");
		setCursorPosition(xOffset + 1, yOffset + 2);
		printf("사람들이 많이 모였던 곳이라 좀비가 많이 남아있을테니 주의하자.");
	}
	else if (day == 2) {
		printf("물자를 구할 가능성이 높은 병원이다.");
		setCursorPosition(xOffset + 1, yOffset + 2);
		printf("똑같이 물자를 노리러 온 사람들을 주의하자.");
	}


	int key = _getch();
	while (key == 0) {
	}

	key = 0;



	setCursorPosition(1, 23);
	std::cout << "                                                                     ";
	setCursorPosition(1, 24);
	std::cout << "                                                                     ";


	key = 0;
	while (true) {
		setCursorPosition(xOffset + 1, yOffset + 1);
		printf("체력 또는 스트레스 수치가 위험한 경우, 치료제를 이용하여 회복할 수 있다.");

		setCursorPosition(xOffset + 1, yOffset + 2);
		printf("탐사 전, 치료제를 사용할까? (사용 시 y, 사용하지 않을 시 n키)");

		key = _getch();
		if (key == 'y') {
			if (p->medicine <= 0) {
				setCursorPosition(1, 23);
				std::cout << "                                                                     ";
				setCursorPosition(1, 24);
				std::cout << "                                                                     ";

				setCursorPosition(xOffset + 1, yOffset + 1);
				printf("치료제가 부족합니다.");
				key = 0;
				while (key == 0) {
					key = _getch();
				}
				break;
			}
			else {
				p->medicine--;
				p->heart = p->heart + 2;
				if (p->heart > 5) {
					p->heart = 5;
				}
				p->mental = p->mental + 50;
				if (p->mental > 100) {
					p->mental = 100;
				}
			}

			continue;
		}
		else if (key == 'n') {
			break;

		}
	}



}
void draw_ready_map(int day) {

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

		}
	}


}

void test_print(int x, int y) {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			setCursorPosition(x + i, y + j);
			printf("%c", itemList[0][x][y]);
		}
	}
}

void printInformation(player* p) {

	int food = p->food;
	for (int i = 0; i < 4; i++) {
		setCursorPosition(6, i + 1);
		for (int j = 0; j < 12; j++) {
			printf("%c", itemList2[1][i][j]);
		}
	}
	setCursorPosition(16, 3);
	printf("식량 x %d", food);


	int water = p->water;
	for (int i = 0; i < 5; i++) {
		setCursorPosition(6, i + 5);
		for (int j = 0; j < 8; j++) {
			printf("%c", itemList2[0][i][j]);
		}
	}
	setCursorPosition(16, 8);
	printf("식수 x %d", water);

	int heal = p->medicine;
	for (int i = 0; i < 4; i++) {
		setCursorPosition(6, i + 10);
		for (int j = 0; j < 12; j++) {
			printf("%c", itemList2[2][i][j]);
		}
	}
	setCursorPosition(16, 12);
	printf("치료제 x %d", heal);

	int gun = p->gun;
	int bullet = p->bullet;

	if (1) {
		for (int i = 0; i < 4; i++) {
			setCursorPosition(6, i + 14);
			for (int j = 0; j < 18; j++) {
				printf("%c", itemList2[3][i][j]);
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		setCursorPosition(20, i + 15);
		for (int j = 0; j < 12; j++) {
			printf("%c", itemList2[4][i][j]);
		}
	}

	setCursorPosition(32, 16);
	printf("총알 x %d", bullet);


}


void printInformation2(player* p) {

	int hp = p->heart;
	int mp = p->mental;

	setCursorPosition(38, 3);
	printf("현재 남은 체력 x %d", hp);
	setCursorPosition(38, 5);
	printf("현재 스트레스 수치 x %d", mp);


	setCursorPosition(42, 8);
	printf("	┌──┐");
	setCursorPosition(42, 9);
	printf("	│    │");
	setCursorPosition(42, 10);
	printf("	└──┘");
	setCursorPosition(42, 11);
	printf("┌──────┐");
	setCursorPosition(42, 12);
	printf("│          ♥ │");
	setCursorPosition(42, 13);
	printf("│            │");


}

// 텍스트 창 초기화 및 메시지 출력 함수
void draw_ready(player* p, int day) {
	print_intro(day);

	int xOffset = 0;
	int yOffset = STAGE_HEIGHT + 1; // 맵 창 하단에 텍스트 창 위치 설정  
	int width = STAGE_WIDTH;    // 텍스트 창 가로 길이
	int height = 20;                 // 텍스트 창 세로 길이
	// 텍스트 창 테두리와 제목 출력

	// 텍스트 창 테두리 그리기
	for (int y = 0; y < height; y++) {
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
	}
	//test_print(0, 0);
	printInformation(p);
	printInformation2(p);
	draw_ready_map(day);
	draw_ready_text(p, day);


}




