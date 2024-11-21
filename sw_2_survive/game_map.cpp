#include "expire_tool.h"
#include "player.h"
#include "Windows.h"
#include "mutex_helper.h"
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
int newX, newY;
char game_map[20][MAP_HEIGHT][MAP_WIDTH + 1] =
{
    {
        //day0
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
  },
    {
        "##################################",
        "#        ##     #           *#x !#",
        "#   ######*     ######  #   ### ##",
        "#   #*xxx# ###  #    ###      #  #",
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
        "#   #######  #*#   #*#x  ##      #",
        "#           #### N ####     #### #",
        "##################################"
    },
    //day2
    {
        "##################################",
        "#      ###     x     ###%%x%%%%%x#",
        "#     ##*##    x    ##*##     #%%#",
        "#    ##   ##   x   ##   ##   #*#%#",
        "#       #    xxx      #%%%%%%%%%%#",
        "#  x   ###       #   ###    ##%%%#",
        "#    ## * ##    #x#  #     # *##%#",
        "#  ###x# #x### #   ## #      ##%%#",
        "#   x##  x##     ####     ###%%%%#",
        "#       ##   ###  x   ###   ##%%%#",
        "#      ####    ##    ##   ## #%%%#",
        "# x   #  xx#    ######    ##   #%#",
        "#   x### x### ###*###x     # # ###",
        "#    x   #   ###x  ##x  xx  ##%%%#",
        "#   #     ## ##x    ##  ##   ###!#",
        "#  #*#     ###x      ## ##   #####",
        "# ## ##     #x         ###     ###",
        "###    # #         #       ##x%%%#",
        "##   #     x## #     x#####%%%%%%#",
        "##################################"
    },
    //day3 ,(11,1) : »ç±â²Û  -> (11,5);
    {
        "##################################",
        "#       #  N  #* x #  *          #",
        "#  ###  # ### #x  x# ### # x  ####",
        "# xx##  #     # x  #            *#",
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
        "#  *##x ### ###    #######    ## #",
        "######  ##   ##    ##*        ## #",
        "#!     x#######    #######       #",
        "##################################"
    },
    {//day 7
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
        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            map[newY][newX] == '*') {
            updateTextBox("¾ÆÀÌÅÛÀ» È¹µæÇß½À´Ï´Ù.");
            return true;
        }
        else if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            map[newY][newX] == '!') {
            updateTextBox("Æ¯¼ö ¾ÆÀÌÅÛÀ» È¹µæÇß½À´Ï´Ù.");
            return true;
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
    // Å×µÎ¸®¿Í ¸Ê Ãâ·Â
    std::lock_guard<std::mutex> lock(bufferMutex);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            setCursorPosition(x * 2 + 1, y + 1);
            switch (map[y][x]) {
            case '#': std::cout << "¡á"; break;
            case 'x': setColor(12); std::cout << "¡á"; setColor(7); break;
            case '*': setColor(14); std::cout << "¡Ú"; setColor(7); break;
            case 'N': setColor(9); std::cout << "¡Ü"; setColor(7); break;
            case '%': colorSetBack(6, 6); std::cout << " "; setColor(7); break;
            case '!': setColor(11); std::cout << "¡Ú"; setColor(7); break;
            case 'P': setColor(2); std::cout << "¿ô"; setColor(7); break;
            default: std::cout << "  "; break;
            case 'B':setColor(14); std::cout << "*"; setColor(7); break;
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
