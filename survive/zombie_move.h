#ifndef ZOMBIE_MOVE_H
#define ZOMBIE_MOVE_H
#include"player.h"
#include<iostream>
#include<thread>
#include<chrono>
#include<vector>
#define MAP_WIDTH 34
#define MAP_HEIGHT 20

class Zombie {
	Zombie();
public:
	int x, y;//현재 위치
	int dx, dy; //이동방향
	int day;//맵인덱스
	Zombie(int startX, int startY, int dX, int dY, int day);
	void move(char map[20][35], player* user); //벽에 부딪히면 이동방향 반대로 설정하는 함수

};
#endif