#include "player.h"
#include "expire_tool.h"
#include <iostream>
#include "mutex_helper.h"
// ���ΰ� �׸��� �Լ� (�ʷϻ�)

player::player() {
	medicine = 0;
	heart = 5;
	mental = 100;
	food = 0;
	water = 0;
	bullet = 0;
	player_x = 1;
	player_y = 0;
	direction = 0;
	gun = 1;
	radio = 0;
}