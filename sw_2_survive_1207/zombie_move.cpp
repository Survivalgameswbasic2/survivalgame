#include "zombie_move.h"
#include"game_map.h"
#include"bad_ending.h"
#include "mutex_helper.h"
//생성자
Zombie::Zombie(int startX, int startY, int dX, int dY, int day)
	: x(startX), y(startY), dx(dX), dy(dY), day(day) {}

void Zombie::move(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	std::lock_guard<std::mutex> lock(zombieMutex2);
	int next_x = x + dx;
	int next_y = y + dy;

	//벽/좀비/햇빛/플레이어에 부딪히면 이동방향 반대로
	if (map[next_y][next_x] == '#' || map[next_y][next_x] == '%'|| map[next_y][next_x] == 'x' || (user->player_x == next_x && user->player_y == next_y)|| map[next_y][next_x]=='A') {
		if (user->player_x == next_x && user->player_y == next_y) {
			user->heart--;
			printstat(user);
			updateTextBox("으윽");

			if (user->heart == 0) {
				bad_ending_zombie();
			}
		}

		dx = -dx;
		dy = -dy;
		next_x = x;
		next_y = y;

	}
	if (map[next_y][next_x] == 'N') {
		user->flag = 1;
	}
	//좀비 위치 배열 업데이트
	map[y][x] = ' ';
	

	//위치 업뎃
	x = next_x;
	y = next_y;

	//좀비 위치 배열 업데이트
	map[y][x] = 'x';
}