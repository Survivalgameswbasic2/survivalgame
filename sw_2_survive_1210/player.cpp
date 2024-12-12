#include "player.h"
#include "expire_tool.h"
#include <iostream>
#include "mutex_helper.h"
// 주인공 그리기 함수 (초록색)

player::player() {
	mode = 0;
	medicine = 3;
	maxh = 5;
	maxm = 100;
	heart = 5;
	mental = 100;
	food = 5;
	water = 5;
	bullet = 3;//테스트용
	player_x = 1;
	player_y = 0;
	direction = 0;
	gun = 1;//테스트용
	radio = 0;
	flag = 0;
}
