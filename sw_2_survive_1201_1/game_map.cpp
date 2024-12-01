#include "expire_tool.h"
#include "player.h"
#include "Windows.h"
#include "mutex_helper.h"
#include "backpack.h"
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
int newX, newY;
char game_map[20][MAP_HEIGHT][MAP_WIDTH + 1] =
{
//0���� ����
    {
    "##################################",
    "#              ####              #",
    "#             ######             #",
    "#    ####    ##xxx ##    ####    #",
    "#   ##  ##  ##      ##  ## F##   #",
    "#   #    ####        ####    #   #",
    "#   A                        #   #",
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
//1���� �ܵ��ǹ�
   {
        "##################################",
        "#        ##     #           F#x !?",
        "#   ######F     ######  #   ### ##",
        "#   #Wxxx# ###  #    ###      #  #",
        "#   #  xx#      #    #        ## #",
        "#   #   Z#### ###### # ####   #  #",
        "#   #          Z          #   # ##",
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
//2���� ķ����
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
    //day3 ,(11,1) : ����  -> (32,10);
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
//4���� : ������
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
//day 5
{
    "#############################?####",
    "#  ####    F#### x ####W    #!   #",
    "#  #    x   #x     #B #     x### #",
    "#x #  #######  #####  ######   #z#",
    "#  #x         ### ###          # #",
    "# x#x #######          x#######  #",
    "#  ######     ###   ####    ####x#",
    "#      x##x  #xx           #     #",
    "#  #### ##   #   # #   # x #zz## #",
    "#x #    ##  x### ### ###   #  #  #",
    "#  #M # ##x   #x  #   #x   #  #M #",
    "#  #### ### # #   # x ### ##  ####",
    "#      x### # #  x#   ### ##     #",
    "#  #######x   ##  ###  ##x    ####",
    "# x#x         ##x      ##   x # F#",
    "#  #  x#    #####     ### #   #  #",
    "#x #   ###### W##  N  ##  #####  #",
    "#  # ###x      #########x       ##",
    "#x          ####B        ##    x #",
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
        case 'F': // �ķ�
            if (user_back->checkweight()) {
                user_back->food++;
                map[newY][newX] = ' ';
                updateTextBox("�ķ�: ������ ������ ���δ�");
                printstat(user);
            }
            else {
                updateTextBox("������ ������ ���� �� ����.");
            }
            break;
        case 'W': // ��
            if (user_back->checkweight()) {
                user_back->water++;
                map[newY][newX] = ' ';
                updateTextBox("��: �ΰ��� �������� �ݵ�� �ʿ��� ���̴�");
                printstat(user);
            }
            else {
                updateTextBox("������ ������ ���� �� ����.");
            }
            break;
        case 'M': // ġ����
            if (user_back->checkweight()) {
                user_back->medicine++;
                map[newY][newX] = ' ';
                updateTextBox("ġ����: �������� ���� ������ �������� ���ٰ� �Ѵ�. �׷��� ����ȭ�� ������ų���� ���� �� ����");
                printstat(user);
            }
            else {
                updateTextBox("������ ������ ���� �� ����.");
            }
            printstat(user);
            break;
        case '!': // ������
            user_back->radio++;
            map[newY][newX] = ' ';
            updateTextBox("�����⸦ ȹ���߽��ϴ�! Ư�� �������Դϴ�!");
            printstat(user);
            break;
        case 'G': // ��
            user_back->gun++;
            map[newY][newX] = ' ';
            updateTextBox("�ѱ�: ������ �ѹ��� ������ �ѱ��!");
            printstat(user);
            break;
        case 'B': // �Ѿ�
            user_back->bullet++;
            map[newY][newX] = ' ';
            updateTextBox("źâ: źâ�ȿ� �Ѿ��� �׷����� �ִ�. �Ѹ� ������ ���� ó���Ҽ���?");
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
            case '#': printf("�� "); break;
            case 'x': setColor(12); printf("�� "); setColor(7); break;
			case 'Z': setColor(13); printf("�� "); setColor(7); break;
            case 'F': setColor(14); printf("�� "); setColor(7); break;
            case 'W': setColor(14); printf("�� "); setColor(7); break;
            case 'M': setColor(14); printf("�� "); setColor(7); break;
            case '!': setColor(11); printf("�� "); setColor(7); break; // ������ (�ϴû�)
            case 'N': setColor(9);  printf("�� "); setColor(7); break;
            /*case '%': colorSetBack(6, 6); std::cout << "  "; setColor(7); break;*/
            case '%': setColor(6); std::cout << "* "; setColor(7); break;
            case '?': setColor(11); printf("�� "); setColor(7); break;
            case 'P': setColor(2); std::cout << "�� "; setColor(7); break;
            case '*': std::cout << "�� "; break;
            case 'G': setColor(15); std::cout << "�� "; setColor(7); break;
            case 'B': setColor(15); std::cout << "�� "; setColor(7); break;
            case 'A': std::cout << "�� ";
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


void is_player_near_explosive_zombie(player* user, char map[][MAP_WIDTH+1]) {
	int flag = 0,ezx, ezy;
	for (int dy = -1; dy <= 1; ++dy) {
		for (int dx = -1; dx <= 1; ++dx) {
			ezx = user->player_x + dx;
			ezy = user->player_y + dy;
			
			if (map[ezy][ezx] == 'Z') {
				flag = 1;
				break;
			}
		}
		if (flag)break;
	}
	if (flag) {
		for (int dy = -1; dy <= 1; ++dy) {
			for (int dx = -1; dx <= 1; ++dx) {
				int nx = ezx + dx;
				int ny = ezy + dy;

				if (nx > 0 && nx < MAP_WIDTH && ny > 0 && ny < MAP_HEIGHT) {
					if (!(nx == user->player_x && ny == user->player_y)) {
						map[ny][nx] = ' ';
					}
				}
			}
		}

		user->heart -= 2;
		printstat(user);
		updateTextBox("���� ���� �����ߴ�! ü���� 2 �����ߴ�.");
	}
	
}


void meet_zombie_change_edge() {
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
	"##################################"
	};
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1);
			if (edge[y][x] == '#') { setColor(12); printf("�� "); setColor(7); }
		}
	}
}