#ifndef DAY_1_H
#define DAY_1_H

bool is_player_near_npc(player* user);

bool is_player_near_item(player* user);

bool is_zombie_position(int x, int y);

void draw_map();

void start_day1(player* user);
#endif