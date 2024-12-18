#include "expire_tool.h"
#include "player.h"
#include "Windows.h"
#include "mutex_helper.h"
#include "backpack.h"
#include "item_image.h"
#include "npc_image.h"
#include <conio.h>
#include <windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;

#define MAP_WIDTH 34
#define MAP_HEIGHT 20
int newX, newY;
char game_map[20][MAP_HEIGHT][MAP_WIDTH + 1] =
//0일차 동굴
{{
"##################################",
"#              ####              #",
"#             ######             #",
"#    ####    ##xxx ##    ####    #",
"#   ##  ##  ##      ##  ## F##   #",
"#   #    ####        ####    #   #",
"#   #                        #   #",
"#   ##   x   ###  ###       ##   #",
"#    ###    ##      ##    ###    #",
"#      ## ###        ### ##      #",
"#      ## ###        ### ##      #",
"#    ###    ##      ##    ###    #",
"#   ## x     ###  ###       ##   #",
"#    #                      #    #",
"#   #    ####        ####    #   #",
"#   ## W##  ##      ##  ##N ##   #",
"#    ####    ## xxx##    ##?#    #",
"#             ######             #",
"#              ####              #",
"##################################"
},
//1일차 외딴건물
   {
        "##################################",
        "#        ##     #           F#  !?",
        "#   ######M     ######  #   ### ##",
        "#   #Wxxx# ###  #    ###      #  #",
        "#   #  xx#      #    #        ## #",
        "#   #    #### ###### # ####   #  #",
        "#   #                     #   # ##",
        "#   ####### x  #####  x  ###### x#",
        "#      xx #     # #      #       #",
        "#xxxxx x  #  x       x   # #######",
        "#x       x#     # #      #       #",
        "#  x#######  x  ###  x   ######  #",
        "#   #    x      x        #       #",
        "#x  #        #### ####   # #######",
        "#   ######   #       #   #       #",
        "# x      #   # #   # #   ####### #",
        "#   #######  # #   #W#x  ##      #",
        "#           #### N ####     #### #",
        "##################################"
   },
    //2일차 캠핑장
    {
        "##################################",
        "#      ###     x     ###  x     x#",
        "#     ##F##    x    ##F##     #  #",
        "#    ##   ##   x   ##   ##   #M# #",
        "#       #    xxx      #          #",
        "#  x   ###       #   ###    ##   #",
        "#    ## W ##    #x#  #     #  ## #",
        "#  ###x# #x### #   ## #      ##  #",
        "#   x##  x##     ####     ###    #",
        "#       ##   ###  x   ###   ##   #",
        "#      ####    ##    ##   ## #   #",
        "# x   #  xx#    ######    ##   # #",
        "#   x### x### ###M###x     # # ###",
        "#    x   #   ###x  ##x  xx  ##   #",
        "#   #     ## ##x    ##  ##   ###!#",
        "#  #W#     ###x      ## ##   ###?#",
        "# ## ##     #x         ###     ###",
        "###    # #         #       ##x   #",
        "##   #     x## #     x#####      #",
        "##################################"
    },
    //day3 ,(11,1) : 사기꾼  -> (32,10);
     {
        "##################################",
        "#       #  N  #M   #  W          #",
        "#  ###  # ### #   Z# ### # x  ####",
        "# xx##  #     # x  #            F#",
        "#   ##  ### ###    ### ###    ## #",
        "##x ##        x     x      #  ## #",
        "#   ##   # ##   ##     ####   ## #",
        "# #x###### ##  #####   ## ###### #",
        "#    x   # ##  x     x           #",
        "# x      # ##     x              #",
        "#xx  #######     ###    #######  #",
        "# x      # ##  x     x  ##       #",
        "#    x   #x       x    ##N#      #",
        "# xZ###### ##   ####   ## ###### #",
        "#   ##   ####     ##   ## #   ## #",
        "#Zx ##x                 #  #  ## #",
        "#  W##x ### ###    #######    ## #",
        "######  ##   ##    #?!        ## #",
        "#M     x#######    #######       #",
        "##################################"
     },

    //4일차 : 경찰서
 {
   "################################?#",
   "#     x #  #M   #   #   W# M#x  !#",
   "#  x       # xx   #   xx #x #    #",
   "#    x  #  #    #   #    #  #  xx#",
   "#x  #####  ####### ####### x###Zx#",
   "#  x#        ##x    x##x     x#  #",
   "#   #  ###   ##      ##  ###  # x#",
   "#x  # B###x       x   ##  ###B#  #",
   "#   ######    ### ###    ######x #",
   "#       x#   x##x  ##x   # x     #",
   "#x       #    F#  x#W   x#      x#",
   "######   #######   #######  ######",
   "#   #G   #x            #    #W xx#",
   "#   ######   x#######    ######  #",
   "#   x    Z    #x   N#   x##x     #",
   "#x    x Z     ### ###    ##   #  #",
   "#   #####  ###### ######x   #    #",
   "#  x#xx        ## ##             #",
   "#MB #F ## #    ##    ##          #",
   "##################################"
 },
    //day 5
{//2,7 -> 19,16
    "#############################?####",
    "#  ####    F#### x ####W    #!   #",
    "#  #    x   #x     #B #    A ### #",
    "#x #  #######  #####  ######   # #",
    "#  #x         ### ###          # #",
    "# x#x #######          x#######  #",
    "#  ######     ###   ####    ####x#",
    "# N    x##x  #xx           #     #",
    "#  #### ##   #   # #   # x #ZZ## #",
    "#x #    ##  x###A###A###   #  #  #",
    "#  #M # ##x   #x  #   #x   #  #M #",
    "#  #### ### # #   # x ### ##  ####",
    "#      x### # #  x#   ### ##     #",
    "#  #######x   ##  ###  ##x    ####",
    "#Ax#x         ##x      ##   x # F#",
    "#  #  x#    ######### ### #  Z#  #",
    "#  #   ###### W##    A  #######  #",
    "#  # ###x      ###### ##x       ##",
    "#x          ####B    #   ##    x #",
    "##################################"
},
//day 6
   {// 15,2         5,12     
   "##################################",
   "#    #x   F#       #     #      x#",
   "#    #    x#   N   #  M  #Z  x   #",
   "# ####     ####### #   x # ###   #",
   "#   A  #  ##  x    ####### #x    #",
   "#### #    #Z       ##    #####   #",
   "#    #  xW#    x  x  B   #x#x#x  #",
   "#   x#####  ############## x #   #",
   "# A                              #",
   "#    #  #################### ### #",
   "#   x#  #        #   #      A  # #",
   "#x  ### #  ######## ###x#####  # #",
   "### # x #  #  Z         #  M#   x#",
   "#   #W  #  #  #####x#####   #x   #",
   "# #######  #            x   ## ###",
   "#   #N  x     ############  ##   #",
   "### #   #### ## A         ##### B#",
   "#   #####       x#######       ###",
   "#  x    B########       !#####   ?",
   "##################################"
   },
//day 7  2,2         31,2          2,17         31,17
{
        "##################################",
        "##################################",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##                              ##",
        "##################################",
        "##################################"
    }
};




bool is_player_near_npc(player* user, char map[][MAP_WIDTH + 1]) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        newX = user->player_x + dx[i];
        newY = user->player_y + dy[i];
        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            map[newY][newX] == 'N') {
            return true;
        }
    }
    return false;
}

bool is_player_near_zombie(player* user, char map[][MAP_WIDTH + 1]) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        newX = user->player_x + dx[i];
        newY = user->player_y + dy[i];
        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            map[newY][newX] == 'x') {
            return true;
        }
    }
    return false;
}
bool is_player_near_item(player* user, char map[][MAP_WIDTH + 1], BackP* user_back) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        newX = user->player_x + dx[i];
        newY = user->player_y + dy[i];
        char item_type = map[newY][newX];
        switch (item_type) {
        case 'F': // 식량
            user_back->food++;
                user->food++;
                map[newY][newX] = ' ';
                updateTextBox("식량: 딱봐도 맛없어 보인다");
                clear_npc_screen();
                drawitem(0);
                printstat(user);
                _getch();
                printplayer();
            break;
        case 'W': // 물
            user_back->water++;
                user->water++;
                map[newY][newX] = ' ';
                updateTextBox("물: 인간의 생존에는 반드시 필요한 물이다");
                clear_npc_screen();
                drawitem(1);
                printstat(user);
                _getch();
                printplayer();
            break;
        case 'M': // 치료제
            user_back->medicine++;
                user->medicine++;
                map[newY][newX] = ' ';
                updateTextBox("치료제: 체력을 회복시킨다");
                clear_npc_screen();
                drawitem(4);
                printstat(user);
            
                _getch();
                printplayer();
            break;
        case '!': // 무전기
            user->radio++;
            user_back->radio++;
            map[newY][newX] = ' ';
            updateTextBox("무전기를 획득했습니다! 특수 아이템입니다!");
            printstat(user);
            break;
        case 'G': // 총
            user->gun++;
            user_back->gun++;
            map[newY][newX] = ' ';
            updateTextBox("총기: 강력한 한발을 때리는 총기다!");
            clear_npc_screen();
            drawitem(2);
            printstat(user);
            _getch();
            printplayer();
            break;
        case 'B': // 총알
            user_back->bullet = user_back->bullet+3;
            user->bullet= user->bullet+3;
            map[newY][newX] = ' ';
            updateTextBox("탄창: 탄창안에 총알이 그럭저럭 있다.");
            clear_npc_screen();
            drawitem(3);
            printstat(user);
            _getch();
            printplayer();
            break;
        }
    }
    return false;
}

bool is_zombie_position(int x, int y, char map[][MAP_WIDTH + 1]) {
    return map[y][x] == 'x';
}

void colorSetBack(int backColor, int textColor) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
}

void draw_map(char map[][MAP_WIDTH + 1]) {
    std::lock_guard<std::mutex> lock(bufferMutex);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            setCursorPosition(x * 2 + 1, y + 1);
            switch (map[y][x]) {
            case '#': printf("■ "); break;
			case 'b':  printf("\033[38;5;202m※\033[0m");		break;//좀비 폭발할 때
            case 'x': setColor(12); printf("▲ "); setColor(7); break;
			case 'Z': setColor(13); printf("▲ "); setColor(7); break;
            case 'F': setColor(14); printf("★ "); setColor(7); break;
            case 'W': setColor(14); printf("★ "); setColor(7); break;
            case 'M': setColor(14); printf("★ "); setColor(7); break;
            case '!': setColor(11); printf("★ "); setColor(7); break; // 무전기 (하늘색)
            case 'N': setColor(9);  printf("● "); setColor(7); break;
            /*case '%': colorSetBack(6, 6); std::cout << "  "; setColor(7); break;*/
            case '%': setColor(6); std::cout << "* "; setColor(7); break;
            case '?': setColor(11); printf("■ "); setColor(7); break;
            case 'P': setColor(2); std::cout << "ⓟ "; setColor(7); break;
            case '*': std::cout << "¤ "; break;
            case 'G': setColor(15); std::cout << "￢ "; setColor(7); break;
            case 'B': setColor(15); std::cout << "ㆍ "; setColor(7); break;
            case 'A': std::cout << "□ ";
            default: printf("  "); break;
            }
        }
    }
}

void copy_map(int day_num, char map[][MAP_WIDTH+1]) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j <= MAP_WIDTH; j++) {
            map[i][j] = game_map[day_num][i][j];
        }
    }
}

void meet_zombie_change_edge() {
    std::lock_guard<std::mutex> lock(bufferMutex);
	char edge[MAP_HEIGHT][MAP_WIDTH + 1] =
	{
	"##################################",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
	"#                                #",
    "##################################"
	};
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1);
			if (edge[y][x] == '#') { setColor(12); printf("■ "); setColor(7); }
		}
	}
}

void handle_explosion(int ezx, int ezy, player* user, char map[][MAP_WIDTH + 1]) {
    {
        // std::lock_guard<std::mutex> lock(bufferMutex);
        PlaySound(TEXT("bomb.wav"), NULL, SND_ASYNC);
        for (int blink = 0; blink < 4; ++blink) {
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = ezx + dx;
                    int ny = ezy + dy;
                    if (nx > 0 && nx < MAP_WIDTH && ny > 0 && ny < MAP_HEIGHT) {
                        if (!(nx == user->player_x && ny == user->player_y)) {
                            map[ny][nx] = (blink % 2 == 0) ? 'b' : ' ';
                        }
                    }
                }
            }
            draw_map(map);
        }
        meet_zombie_change_edge();
    }
}
void is_player_near_explosive_zombie(player* user, char map[][MAP_WIDTH + 1]) {

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int ezx = user->player_x + dx;
            int ezy = user->player_y + dy;

            if (ezx > 0 && ezx < MAP_WIDTH && ezy > 0 && ezy < MAP_HEIGHT) {
                if (map[ezy][ezx] == 'Z') {
                    handle_explosion(ezx, ezy, user, map);
                    user->heart -= 2;
                    printstat(user);
                    updateTextBox("자폭 좀비가 폭발했다! 체력이 2 감소했다!!");
                    meet_zombie_change_edge();
                    return;
                }
            }
        }
    }
}

void handle_zombie_death_effect(int zx, int zy, char map[][MAP_WIDTH + 1]) {
    //std::lock_guard<std::mutex> lock(bufferMutex);
    for (int blink = 0; blink < 2; blink++) {
        map[zy][zx] = (blink % 2 == 0) ? 'b' : ' ';
        draw_map(map);
    }
}