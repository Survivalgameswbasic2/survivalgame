#include "NPC대화창.h"
#include "게임창.h"
#include "대화창.h"
#include "상태창.h"
#include "타이머.h"
#include "플레이어.h"
#include <thread>
#include <conio.h>
#include "도구.h"
#include <string>
#include <fstream>




std::string dialogue[] = {
	   "npc: “아악! 누구세요? 엣 사람? 사람이 왜 여기에? 아니 어떻게 여기에?”",
	   "플레이어: “혹시 사람이세요? 그렇겐 안보이는데...”",
	   "npc: “....사람이거든요. 그쪽은 어떻게 여기에 왔는데요?”",
	   "플레이어: “...기억은 없어요. 그저.... 도망쳐왔다는 기억밖엔...”",
	   "npc: “...그렇군요. 그럼 일단 제가 도와줄게요.”",
	   "npc: “일단 배고프실테니 여기 있는 식량부터.. 앗 없어졌네? 혹시 이미 가져가신...것 같군요. 손버릇이 안좋네요.”",
	   "플레이어: “살기위해선 모든지 해야합니다.”",
	   "npc: “....네.  일단 여기는 제가 피난해있는 동굴이에요.”",
	   "npc: “여기라고 안전한 곳은 아니지만, 그래도 바깥 세상보단 나으니까요.”",
	   "npc: “뭐 일단 설명을 이것저것 드릴게요”",
	   "npc: “제 설명이 튜토리얼 같아보여도 참으세요”",
	   "npc: “일단 여기 주변의 좀비들은 움직이진 않으니까 안심하세요.”",
	   "npc: “그렇다고 너무 가까이 다가가면 공격하니까 조심하시고요.”",
	   "npc: “일단 생존하려면 당연히 잘자고, 잘 먹어야겠죠? 잘이라는 말을 붙이기엔 상황이 안좋지만..”",
	   "npc: “아무튼 일단 식량이 바닥났어요. 사실 아까께 마지막 물과 식량이었는데 당신한테 양보한거라구요?”",
	   "npc: “그래서 밖에 나가서 식량, 물 등을 구해와야해요. 물론 좀비들을 피해서요.”",
	   "npc: “여기는 잠을 자거나 휴식공간으로 쓰셔도 상관없어요.”",
	   "npc: “네 당연히 저도 식량과 물을 구하려 나가봐야죠.”",
	   "npc: “...밖은 위험해요... 당장에 좀비부터 왠지 모르겠지만 햇빛도 너무 쎄요. 오존층이 파괴된건지... 햇빛에 너무 오래 있지 마세요.”",
	   "npc: “일단 당신은 오늘 일어났다고 하셨으니 여기서 쉬세요. 저는 먼저 제가 먹을 물과 식량을 구하러 떠날게요.”",
	   "npc: “네? 식량이나 물을 나눠먹으면 되지 않냐고요?”",
	   "npc: “...일단 물은 하루에 500ml이상 먹지 않으면 진짜 위험해져요.. 제가 겪어봐서 알아요. 식량은 하루정돈 괜찮지만.. 정신적으로 뭔가...”",
	   "npc: “그러니 식량은 일단 그렇다 쳐도 물은 무조건 구해야하기 때문에 가야만해요.”",
	   "npc: “...그럼 이만”",
	   "플레이어: “후 그래 내가 어떻게 여기에 왔는지 기억도 안나지만, 일단 살아야지. 그래 나도 내일부터 다시 돌아다녀 보자.”",
	   "플레이어: “정리하자면. 매일 좀비를 피해 물과 식량을 얻고, 정보를 얻어서 좀비가 없는 안전한 곳으로 가면 되겠지?”"
};
char game_map[STAGE_HEIGHT][STAGE_WIDTH + 1] = {
"##################################",
"#              ####              #",
"#             ######             #",
"#    ####    ##xxx ##    ####    #",
"#   ##  ##  ##      ##  ## *##   #",
"#   #    ####        ####    #   #",
"#                            #   #",
"#   ##   x   ###  ###       ##   #",
"#    ###    ##      ##    ###    #",
"#      ## ###        ### ##      #",
"#      ## ###        ### ##      #",
"#    ###    ##      ##    ###    #",
"#   ##       ###  ###       ##   #",
"#    # x                    #    #",
"#   #    ####        ####    #   #",
"#   ## *##  ##      ##  ##N ##   #",
"#    ####    ## xxx##    ####    #",
"#             ######             #",
"#              ####              #",
"##################################"
};



bool isPlayerNearNPC(player * user) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = user->player_x + dx[i];
		int newY = user->player_y + dy[i];
		if (newX >= 0 && newX < STAGE_WIDTH && newY >= 0 && newY < STAGE_HEIGHT &&
			game_map[newY][newX] == 'N') {
			return true;
		}
	}
	return false;
}
bool isPlayerNearItem(player* user) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		int newX = user->player_x + dx[i];
		int newY = user->player_y + dy[i];
		if (newX >= 0 && newX < STAGE_WIDTH && newY >= 0 && newY < STAGE_HEIGHT &&
			game_map[newY][newX] == '*') {
			return true;
		}
	}
	return false;
}
bool isZombiePosition(int x, int y) {
	return game_map[y][x] == 'x';
}

void drawStage2() {
	// 테두리와 맵 출력
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1);
			switch (game_map[y][x]) {
			case '#': printf("■"); break;
			case 'x': setColor(12); printf("■"); setColor(7); break; // 좀비
			case '*': setColor(14); printf("★"); setColor(7); break; // 아이템
			case 'N': setColor(9); printf("●"); setColor(7); break; // NPC
			default: printf("  "); break;
			}
		}
	}
}
void start_day0(player* user) {
	system("cls");
	int realTimeLimit = 300;
	CommunicationBoxNPC(0,user);
	
	drawStage();         // 탐험 맵
	printstat(user); // 아이템 창 
	user->drawPlayer(); // 초기 위치에 주인공 그리기
	updateTextBox("");



	drawStage2();


	user->player_x = 5;
	user->player_y = 6;

	std::thread timerThread(timer);
	int cn = 0;
	user->drawPlayer();
	while (true) {
		if (_kbhit()) {
			int key = _getch();

			if (key == 224) { // 방향키 입력 확인
				key = _getch();

				user->clearPlayer();
				int newX = user->player_x, newY = user->player_y;
				switch (key) {
				case 72: newY--; break;
				case 80: newY++; break;
				case 75: newX--; break;
				case 77: newX++; break;
				}

				// 이동 가능 여부 확인
				if (newY >= 0 && newY < STAGE_HEIGHT && newX >= 0 && newX < STAGE_WIDTH &&
					game_map[newY][newX] == ' ' && !isZombiePosition(newX, newY)) {
					user->player_x = newX;
					user->player_y = newY;
					updateTextBox("");
				}
				else if (isZombiePosition(newX, newY)) {
					user->heart--;
					printstat(user);
					setCursorPosition(1, 23);
					std::cout << "앗 좀비다";

					if (user->heart == 0) {
						setCursorPosition(1, 23);
						std::cout << "GAMEOVER";
						break;
					}
				}

				user->drawPlayer();
			}
			else if (key == 13 && isPlayerNearItem(user)) { // 엔터키로 아이템 획득
				updateTextBox("아이템을 획득했습니다!");
			}
			else if (key == ' ' && isPlayerNearNPC(user)) { // 스페이스바로 NPC와 대화
				setCursorPosition(1, 23);
				std::cout << "                                                                     ";
				setCursorPosition(1, 24);
				std::cout << "                                                                     ";
				setCursorPosition(1, 25);
				std::cout << "                                                                     ";

				setCursorPosition(1, 23);
				std::cout << dialogue[cn++];
				setCursorPosition(1, 24);
				std::cout << dialogue[cn++];
				setCursorPosition(1, 25);
				std::cout << dialogue[cn++];
			}
		}
	}

}