#include "Zombies.h"
#include<thread>
#include<chrono>

//������
Zombies::Zombies(int startX, int startY, int dX, int dY) : x(startX), y(startY), dx(dX), dy(dY) {}


void Zombies::move(char game_map[20][35]) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	int next_x = x + dx;
	int next_y = y + dy;


	game_map[y][x] = ' ';
	//���� �ε����� �̵����� �ݴ��, ���� ��?H���ٸ� 1�ʰ� ����
	if (game_map[next_y][next_x] == '#' || game_map[next_y][next_x] == 'P') {
		dx = -dx;
		dy = -dy;
		next_x = x;
		next_y = y;
	}
	//��ġ ����
	x = next_x;
	y = next_y;

	//���� ��ġ ���� ����
	game_map[y][x] = 'x';

}