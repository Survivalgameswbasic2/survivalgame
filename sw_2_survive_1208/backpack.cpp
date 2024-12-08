#include "player.h"
#include "backpack.h"
#include "expire_tool.h"
#include <iostream>
#include "mutex_helper.h"
// 주인공 그리기 함수 (초록색)

BackP::BackP() {
	medicine = 0;
	food = 0;
	water = 0;
	bullet = 0;
	direction = 0;
	gun = 0;
	radio = 0;
}

bool BackP::checkweight() {  //들어갈 수 있으면 1, 없으면 2 반환 

	int total = 0;

	int limit = 15;

	total = water * 3 + food * 3 + bullet + medicine * 3 + gun * 5;

	if (total <= limit) {
		return 1;
	}
	else {
		return 0;
	}


}

void BackP::unionP(player* user) {
	user->bullet += bullet;
	user->food += food;
	user->water += water;
	user->medicine += medicine;
	bullet = 0;
	food = 0;
	water = 0;
	medicine = 0;

}

void BackP::sepP(player* user) {
	user->bullet -= bullet;
	user->food -= food;
	user->water -= water;
	user->medicine -= medicine;

}