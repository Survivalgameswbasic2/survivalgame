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
	int x, y;//���� ��ġ
	int dx, dy; //�̵�����
	int day;//���ε���
	Zombie(int startX, int startY, int dX, int dY, int day);
	void move(char game_map[][20][35], player* user); //���� �ε����� �̵����� �ݴ�� �����ϴ� �Լ�
};
#endif