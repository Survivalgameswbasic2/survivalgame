#include"player.h"
#include "expire_tool.h"
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
int newX, newY;
char game_map[3][MAP_HEIGHT][MAP_WIDTH + 1] = {
{
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
	"#          ######       ######x *#",
	"#   ######      ######       ## ##",
	"#   #* xx#       #*   #       #  #",
	"#   #  xx#       #     #      ## #",
	"#   #   x#### #######  ####   #  #",
	"#   #                     #   # ##",
	"#   #######    #####     ###### x#",
	"#         #     ###      #       #",
	"#xxxxx    #     ###      # #######",
	"#         #     ###      #       #",
	"#  x#######     ###      ######  #",
	"#   #                    #       #",
	"#x  #        #### ####   # #######",
	"#   ######   #       #   #       #",
	"# x      #   # #   # #   ####### #",
	"#   #######  #*#   #*#   ##      #",
	"#           #### N ####     #### #",
	"##################################"
},
{
	"##################################",
	"#      ###           ###  x     x#",
	"#     ##*##         ##*##     #  #",
	"#    ##   ##       ##   ##   #*# #",
	"#       #             #          #",
	"#  x   ###       #   ###    ##   #",
	"#    ## * ##    #x#  #     # *## #",
	"#  ###x# #x### #   ## #      ##  #",
	"#   x##  x##     ####     ###    #",
	"#       ##   ###  x   ###   ##   #",
	"#      ####    ##    ##   ## #   #",
	"# x   #  xx#    ######    ##   # #",
	"#   x### x### ###*###x     # # ###",
	"#    x   #   ###x  ##x  x x ##   #",
	"#   #     ## ##x    ##  ##   ###*#",
	"#  #*#     ###x      ## ##   #####",
	"# ## ##     #x         ###     ###",
	"###    # #         #       ##x   #",
	"##   #     x## #     x#####      #",
	"##################################"
}
};






bool is_player_near_npc(player* user, int day_num) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		newX = user->player_x + dx[i];
		newY = user->player_y + dy[i];
		if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
			game_map[day_num][newY][newX] == 'N') {
			return true;
		}
	}
	return false;
}

bool is_player_near_item(player* user, int day_num) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		newX = user->player_x + dx[i];
		newY = user->player_y + dy[i];
		if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT &&
			game_map[day_num][newY][newX] == '*') {
			return true;
		}
	}
	return false;
}

bool is_zombie_position(int x, int y, int day_num) {
	return game_map[day_num][y][x] == 'x';
}

void draw_map(int day_num) {
	// 테두리와 맵 출력
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			setCursorPosition(x * 2 + 1, y + 1);
			switch (game_map[day_num][y][x]) {
			case '#': printf("■"); break;
			case 'x': setColor(12); printf("■"); setColor(7); break; // 좀비
			case '*': setColor(14); printf("★"); setColor(7); break; // 아이템
			case 'N': setColor(9); printf("●"); setColor(7); break; // NPC
			default: printf("  "); break;
			}
		}
	}
}

