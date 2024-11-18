#ifndef DAY_0_H
#define DAY_0_H

bool is_player_near_npc(player* user);

bool is_player_near_item(player* user);

bool is_zombie_position(int x, int y);

void draw_map();

void start_day0(player* user);
#endif