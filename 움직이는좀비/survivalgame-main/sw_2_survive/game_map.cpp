#include "expire_tool.h"
#include "player.h"
#include "Windows.h"

#define MAP_WIDTH 34
#define MAP_HEIGHT 20
int newX, newY;
char game_map[20][MAP_HEIGHT][MAP_WIDTH + 1] = {
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
    //day1
    {
          "##################################",
          "#       #  N  #* x #%%*%%%%%%%%%%#",
          "#  ###  # ### #x  x# ### # x  ####",
          "# xx##  #     # x  #%%%%%%%%%%%%*#",
          "#   ##  ### ###    ### ###    ##%#",
          "##x ##        x     x      #  ##%#",
          "#   ##   # ##   ##     ####   ##%#",
          "# #x###### ##  #####   ## ######%#",
          "#    x   # ##%%x%%%%%x%%%%%%%%%%%#",
          "# x      # ##%%%%%x%%%%%%%%%%%%%%#",
          "#xx  #######     ###    #######%%#",
          "# x      # ##  x     x  ##%%%%%%%#",
          "#    x   #x       x    ##N#%%%%%%#",
          "# xx###### ##   ####   ## ######%#",
          "#   ##   ####     ##   ## #   ##%#",
          "#xx ##x                 #  #  ##%#",
          "#  *##x ### ###    #######    ##%#",
          "######  ##   ##    ##*        ##%#",
          "#!     x#######    #######%%%%%%%#",
          "##################################"
       },
    // ���� �޺� ��
    {
       "##################################",
       "#%%%%%%%#%%N%%#*%x%#%%*%%%%%%%%%%#",
       "#%%###%%#%###%#x%%x#%###%#%x%%####",
       "#%x###%%#%   %#%x%%#%   % %%%%  *#",
       "#%% ##%%### ###%%%%### ###%%%%## #",
       "##x ##%%      x%%%% x     %#%%## #",
       "# % ##%% # ##  %##%    #### %%## #",
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
    // ���� �޺� ��
    {
       "##################################",
       "#%%%%%%%#  N  #* x #  *          #",
       "#%%###  # ### #x  x# ### # x  ####",
       "#%xx##  #     # x  #            *#",
       "#%%%##  ### ###    ### ###    ## #",
       "##x%##        x     x      #  ## #",
       "#%%%##   # ##   ##     ####   ## #",
       "#%#x###### ##   ####   ## ###### #",
       "#%%%%x%%%# ##  x     x           #",
       "#%x%%%%%%# ##     x              #",
       "#xx%%#######     ###    #######  #",
       "#%x%%%%%%# ##  x     x  ##       #",
       "#%%%%x%%%#x       x    ##N#      #",
       "#%xx###### ##   ####   ## ###### #",
       "#%%%##   ####     ##   ## #   ## #",
       "#xx%##x                 #  #  ## #",
       "#%%*##x ### ###    #######    ## #",
       "######  ##   ##    ##*        ## #",
       "#!%%%%%x#######    #######       #",
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
    // ���� �޺� ��
    {
       "##################################",
       "#%%%%%%###%%%%%x%%%%%###%%x%%%%%x#",
       "#%%%%%##*##%%%%x%%%%##*##%%%%%#%%#",
       "#%%%%##   ##%%%x%%%##   ##%%%#*#%#",
       "#%%%%   #   %xxx%%%   #   %%%   %#",
       "#%%x%  ###  %%%%%#%  ###  %%##  %#",
       "#%%%%## * ##%%%%#x#  #    %# *##%#",
       "#%%###x# #x###%#   ## #   %  ## %#",
       "#%% x##  x##  %  ####     ###   %#",
       "#%%     ##   ###  x   ###   ##  %#",
       "#%%    ####    ##    ##   ## #  %#",
       "#%x   #  xx#    ######    ##   #%#",
       "#%% x### x### ###*###x     # # ###",
       "#%%  x   #   ###x  ##x  xx  ##   #",
       "#%% #     ## ##x    ##  ##   ###!#",
       "#%%#*#     ###x      ## ##   #####",
       "#%## ##     #x         ###     ###",
       "###    # #         #       ##x   #",
       "##   #     x## #     x#####      #",
       "##################################"
    },
    // ���� �޺� ��
    {
       "##################################",
       "#%%%%%%###     x     ###  x     x#",
       "#%%%%%##*##    x    ##*##     #  #",
       "#%%%%##   ##   x   ##   ##   #*# #",
       "#%%%%%%%#    xxx      #          #",
       "#%%x%%%###       #   ###    ##   #",
       "#%%%%## * ##    #x#  #     # *## #",
       "#%%###x# #x### #   ## #      ##  #",
       "#%%%x##  x##     ####     ###    #",
       "#%%%%%%%##   ###  x   ###   ##   #",
       "#%%%%%%####    ##    ##   ## #   #",
       "#%x%%%#  xx#    ######    ##   # #",
       "#%%%x### x### ###*###x     # # ###",
       "#%%%%x%%%#   ###x  ##x  xx  ##   #",
       "#%%%#     ## ##x    ##  ##   ###!#",
       "#%%#*#     ###x      ## ##   #####",
       "#%## ##     #x         ###     ###",
       "###    # #         #       ##x   #",
       "##   #     x## #     x#####      #",
       "##################################"
    },
    {
       "##################################",
       "#       #  N  #* x #%%*%%%%%%%%%%#",
       "#  ###  # ### #x  x# ### # x  ####",
       "# xx##  #     # x  #%%%%%%%%%%%%*#",
       "#   ##  ### ###    ### ###    ##%#",
       "##x ##        x     x      #  ##%#",
       "#   ##   # ##   ##     ####   ##%#",
       "# #x###### ##  #####   ## ######%#",
       "#    x   # ##%%x%%%%%x%%%%%%%%%%%#",
       "# x      # ##%%%%%x%%%%%%%%%%%%%%#",
       "#xx  #######     ###    #######%%#",
       "# x      # ##  x     x  ##%%%%%%%#",
       "#    x   #x       x    ##N#%%%%%%#",
       "# xx###### ##   ####   ## ######%#",
       "#   ##   ####     ##   ## #   ##%#",
       "#xx ##x                 #  #  ##%#",
       "#  *##x ### ###    #######    ##%#",
       "######  ##   ##    ##*        ##%#",
       "#!     x#######    #######%%%%%%%#",
       "##################################"
    },
    // ���� �޺� ��
    {
       "##################################",
       "#%%%%%%%#%%N%%#*%x%#%%*%%%%%%%%%%#",
       "#%%###%%#%###%#x%%x#%###%#%x%%####",
       "#%x###%%#%   %#%x%%#%   % %%%%  *#",
       "#%% ##%%### ###%%%%### ###%%%%## #",
       "##x ##%%      x%%%% x     %#%%## #",
       "# % ##%% # ##  %##%    #### %%## #",
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
    // ���� �޺� ��
    {
       "##################################",
       "#%%%%%%%#  N  #* x #  *          #",
       "#%%###  # ### #x  x# ### # x  ####",
       "#%xx##  #     # x  #            *#",
       "#%%%##  ### ###    ### ###    ## #",
       "##x%##        x     x      #  ## #",
       "#%%%##   # ##   ##     ####   ## #",
       "#%#x###### ##   ####   ## ###### #",
       "#%%%%x%%%# ##  x     x           #",
       "#%x%%%%%%# ##     x              #",
       "#xx%%#######     ###    #######  #",
       "#%x%%%%%%# ##  x     x  ##       #",
       "#%%%%x%%%#x       x    ##N#      #",
       "#%xx###### ##   ####   ## ###### #",
       "#%%%##   ####     ##   ## #   ## #",
       "#xx%##x                 #  #  ## #",
       "#%%*##x ### ###    #######    ## #",
       "######  ##   ##    ##*        ## #",
       "#!%%%%%x#######    #######       #",
       "##################################"
    }
};




bool is_player_near_npc(player* user, int map_num) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        newX = user->player_x + dx[i];
        newY = user->player_y + dy[i];
        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            game_map[map_num][newY][newX] == 'N') {
            return true;
        }
    }
    return false;
}

bool is_player_near_item(player* user, int map_num) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        newX = user->player_x + dx[i];
        newY = user->player_y + dy[i];
        if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            game_map[map_num][newY][newX] == '*') {
            updateTextBox("�������� ȹ���߽��ϴ�.");
            return true;
        }
        else if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
            game_map[map_num][newY][newX] == '!') {
            updateTextBox("Ư�� �������� ȹ���߽��ϴ�.");
            return true;
        }
    }
    return false;
}

bool is_zombie_position(int x, int y, int map_num) {
    return game_map[map_num][y][x] == 'x';
}

void colorSetBack(int backColor, int textColor) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
}

void draw_map(int day_num) {
    // �׵θ��� �� ���
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            setCursorPosition(x * 2 + 1, y + 1);
            switch (game_map[day_num][y][x]) {
            case '#': std::cout << "��"; break;
            case 'x': setColor(12); std::cout << "��"; setColor(7); break;
            case '*': setColor(14); std::cout << "��"; setColor(7); break;
            case 'N': setColor(9); std::cout << "��"; setColor(7); break;
            case '%': colorSetBack(6, 6); std::cout << "��"; setColor(7); break;
            case '!': setColor(11); std::cout << "��"; setColor(7); break;
            default: std::cout << "  "; break;
            }
        }
    }
}
