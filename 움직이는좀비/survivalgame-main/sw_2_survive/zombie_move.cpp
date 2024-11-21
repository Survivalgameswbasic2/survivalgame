#include "zombie_move.h"
#include"game_map.h"
#include"bad_ending.h"
//생성자
Zombie::Zombie(int startX, int startY, int dX, int dY, int day) 
	: x(startX), y(startY), dx(dX), dy(dY) , day(day){}

void Zombie::move(char game_map[][MAP_HEIGHT][MAP_WIDTH+1] ,player* user) {
	int next_x = x + dx;
	int next_y = y + dy;
		
	//벽/좀비/햇빛/플레이어에 부딪히면 이동방향 반대로
	if (game_map[day][next_y][next_x] == '#'|| game_map[day][next_y][next_x] == '%' 
		|| game_map[day][next_y][next_x] == 'x' ||( user->player_x  == next_x && user->player_y == next_y)) {
		if (user->player_x == next_x && user->player_y == next_y) {
			user->heart--;
			printstat(user);
			setCursorPosition(1, 23);
			updateTextBox("으윽");

			if (user->heart == 0) {
				bad_ending();
			}
		}

		dx = -dx;
		dy = -dy;
		next_x = x;
		next_y = y;

	}
	//좀비 위치 배열 업데이트
	game_map[day][y][x] = ' ';
	//좀비 지우기
	setCursorPosition(x * 2 + 1, y + 1);
	std::cout << "  ";
	
	//위치 업뎃
	x = next_x;
	y = next_y;

	//좀비 위치 배열 업데이트
	game_map[day][y][x] = 'x';
	//좀비 출력
	setCursorPosition(x * 2 + 1, y+1);
	setColor(12); std::cout << "■"; setColor(7);
	//1초마다 움직임
	std::this_thread::sleep_for(std::chrono::seconds(1/2));
}
