#include "Zombies.h"
#include<thread>
#include<chrono>
#include "mutex_helper.h"
//������
Zombies::Zombies(int startX, int startY, int dX, int dY) : x(startX), y(startY), dx(dX), dy(dY) {}


void Zombies::move(char game_map[20][35]) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::lock_guard<std::mutex> lock(zombieMutex2);
	int next_x = x + dx;
	int next_y = y + dy;

	{
		std::lock_guard<std::mutex> lock(zombieMutex2);
		game_map[y][x] = ' ';
		//���� �ε����� �̵����� �ݴ��, ���� ��?H���ٸ� 1�ʰ� ����
		if (game_map[next_y][next_x] != ' ') {
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
}