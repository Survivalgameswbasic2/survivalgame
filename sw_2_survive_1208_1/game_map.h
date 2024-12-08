#ifndef GAME_MAP_H
#define GAME_MAP_H
#include"player.h"
#include "expire_tool.h"
#include "backpack.h"

#define MAP_WIDTH 34
#define MAP_HEIGHT 20
extern int newX, newY;
extern char game_map[20][MAP_HEIGHT][MAP_WIDTH + 1];

bool is_player_near_npc(player* user, char map[][MAP_WIDTH + 1]);
bool is_player_near_zombie(player* user, char map[][MAP_WIDTH + 1]);
bool is_player_near_item(player* user, char map[][MAP_WIDTH + 1], BackP* user_back);

bool is_zombie_position(int x, int y, char map[][MAP_WIDTH + 1]);

void copy_map(int day_num, char map[][MAP_WIDTH+1]);
void draw_map(char map[][MAP_WIDTH + 1]);
void meet_zombie_change_edge();
void handle_explosion(int ezx, int ezy, player* user, char map[][MAP_WIDTH + 1]);
void is_player_near_explosive_zombie(player* user, char map[][MAP_WIDTH + 1]);
void handle_zombie_death_effect(int zx, int zy, char map[][MAP_WIDTH + 1]);


#endif
