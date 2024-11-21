#ifndef GAME_MAP_H
#define GAME_MAP_H
#include"player.h"
#include "expire_tool.h"
#define MAP_WIDTH 34
#define MAP_HEIGHT 20
extern int newX, newY;
extern char game_map[20][MAP_HEIGHT][MAP_WIDTH + 1];

bool is_player_near_npc(player* user, int day_num);

bool is_player_near_item(player* user, int day_num);

bool is_zombie_position(int x, int y, int day_num);

void draw_map(int day_num);
#endif
