#include "player.h"
#include "expire_tool.h"
#include <iostream>
#include "mutex_helper.h"
// ���ΰ� �׸��� �Լ� (�ʷϻ�)

player::player() {
	mode = 0;
	medicine = 3;
	maxh = 5;
	maxm = 100;
	heart = 5;
	mental = 100;
	food = 5;
	water = 5;
	bullet = 3;//�׽�Ʈ��
	player_x = 1;
	player_y = 0;
	direction = 0;
	gun = 1;//�׽�Ʈ��
	radio = 0;
	flag = 0;
}
