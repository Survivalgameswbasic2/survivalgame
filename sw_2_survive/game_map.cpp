#include "expire_tool.h"
#include "player.h"
#include "Windows.h"
#include "mutex_helper.h"
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
int newX, newY;
char game_map[20][MAP_HEIGHT][MAP_WIDTH + 1] =
{
//0일차 동굴
    {
    "##################################",
    "#              ####              #",
    "#             ######             #",
    "#    ####    ##xxx ##    ####    #",
    "#   ##  ##  ##      ##  ## F##   #",
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
    "#   ## W##  ##      ##  ##N ##   #",
    "#    ####    ## xxx##    ##?#    #",
    "#             ######             #",
    "#              ####              #",
    "##################################"
},
//1일차 외딴건물
   {
        "##################################",
        "#        ##     #           F#x !?",
        "#   ######F     ######  #   ### ##",
        "#   #Wxxx# ###  #    ###      #  #",
        "#   #  xx#      #    #        ## #",
        "#   #   x#### ###### # ####   #  #",
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
        "#   #######  #*#   #W#x  ##      #",
        "#           #### N ####     #### #",
        "##################################"
},
//2일차 캠핑장
    {
        "##################################",
        "#      ###     x     ###  x     x#",
        "#     ##F##    x    ##W##     #  #",
        "#    ##   ##   x   ##   ##   #F# #",
        "#       #    xxx      #          #",
        "#  x   ###       #   ###    ##   #",
        "#    ## W ##    #x#  #     #  ## #",
        "#  ###x# #x### #   ## #      ##  #",
        "#   x##  x##     ####     ###    #",
        "#       ##   ###  x   ###   ##   #",
        "#      ####    ##    ##   ## #   #",
        "# x   #  xx#    ######    ##   # #",
        "#   x### x### ###F###x     # # ###",
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
        "#       #  N  #F x #  W          #",
        "#  ###  # ### #x  x# ### # x  ####",
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
        "# xx###### ##   ####   ## ###### #",
        "#   ##   ####     ##   ## #   ## #",
        "#xx ##x                 #  #  ## #",
        "#  W##x ### ###    #######    ## #",
        "######  ##   ##    #?!        ## #",
        "#M     x#######    #######       #",
        "##################################"
},
//4일차 : 경찰서
 {
   "################################?#",
   "#     x #  #F   #   #   W# M#  x!#",
   "#  x       # xx   #   xx #x #   x#",
   "#    x  #  #    #   #    #  #  xx#",
   "#x  #####  ####### ####### x###xx#",
   "#  x#        ##x    x##x     x#  #",
   "#   #  ###   ##      ##  ###  # x#",
   "#x  # B###x       x   ##  ###B#  #",
   "#   ######    ### ###    ######x #",
   "#       x#   x##x  ##x   # x     #",
   "#x       #    F#  x#W   x#      x#",
   "######   #######   #######  ######",
   "#   #G   #x            #    #W xx#",
   "#   ######   x#######    ######  #",
   "#   x   x     #F   N#   x##x     #",
   "#x    x x     ### ###    ##   #  #",
   "#   #####  ###### ######x   #    #",
   "#  x#xx        ## ##             #",
   "#MB #F ## #    ##    ##          #",
   "##################################"
},
//day 7
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

bool is_player_near_item(player* user, char map[][MAP_WIDTH + 1]) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        newX = user->player_x + dx[i];
        newY = user->player_y + dy[i];
        char item_type = map[newY][newX];
        switch (item_type) {
        case 'F': // 식량
            user->food++;
            map[newY][newX] = ' ';
            updateTextBox("식량: 딱봐도 맛없어 보이는");
            printstat(user);
            break;
        case 'W': // 물
            user->water++;
            map[newY][newX] = ' ';
            updateTextBox("물: 인간의 생존에는 반드시 필요한 물이다");
            printstat(user);
            break;
        case 'M': // 치료제
            user->medicine++;
            map[newY][newX] = ' ';
            updateTextBox("치료제: 연구원의 말에 따르면 좀비백신은 없다고 한다. 그러나 좀비화는 지연시킬수도 있을 것 같다");
            printstat(user);
            break;
        case '!': // 무전기
            user->radio++;
            map[newY][newX] = ' ';
            updateTextBox("무전기를 획득했습니다! 특수 아이템입니다!");
            printstat(user);
            break;
        case 'G': // 총
            user->gun++;
            map[newY][newX] = ' ';
            updateTextBox("총기: 강력한 한발을 때리는 총기다!");
            printstat(user);
            break;
        case 'B': // 총알
            user->bullet++;
            map[newY][newX] = ' ';
            updateTextBox("탄창: 탄창안에 총알이 그럭저럭 있다. 총만 있으면 좀비를 처리할수도?");
            printstat(user);
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
            case '#': printf("■"); break;
            case 'x': setColor(12); printf("■ "); setColor(7); break;
            case 'F': setColor(14); printf("★ "); setColor(7); break;
            case 'W': setColor(14); printf("★ "); setColor(7); break;
            case 'M': setColor(14); printf("★ "); setColor(7); break;
            case '!': setColor(11); printf("★ "); setColor(7); break; // 무전기 (하늘색)
            case 'N': setColor(9);  printf("● "); setColor(7); break;
            /*case '%': colorSetBack(6, 6); std::cout << "  "; setColor(7); break;*/
            case '%': setColor(6); std::cout << "*"; setColor(7); break;
            case '?': setColor(11); printf("■"); setColor(7); break;
            case 'P': setColor(3); std::cout << "웃"; setColor(7); break;
            case '*': std::cout << "¤"; break;
            case 'G': setColor(15); std::cout << "￢"; setColor(7); break;
            case 'B': setColor(15); std::cout << "ㆍ"; setColor(7); break;
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
