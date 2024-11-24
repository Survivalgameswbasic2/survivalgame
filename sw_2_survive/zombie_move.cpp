#include "zombie_move.h"
#include"game_map.h"
#include"bad_ending.h"
//������
Zombie::Zombie(int startX, int startY, int dX, int dY, int day)
	: x(startX), y(startY), dx(dX), dy(dY), day(day) {}

void Zombie::move(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
	int next_x = x + dx;
	int next_y = y + dy;

	//��/����/�޺�/�÷��̾ �ε����� �̵����� �ݴ��
	if (map[next_y][next_x] == '#' || map[next_y][next_x] == '%'
		|| map[next_y][next_x] == 'x' || (user->player_x == next_x && user->player_y == next_y)) {
		if (user->player_x == next_x && user->player_y == next_y) {
			user->heart--;
			printstat(user);
			setCursorPosition(1, 23);
			updateTextBox("����");

			if (user->heart == 0) {
				bad_ending();
			}
		}

		dx = -dx;
		dy = -dy;
		next_x = x;
		next_y = y;

	}
	//���� ��ġ �迭 ������Ʈ
	map[y][x] = ' ';
	//���� �����
	setCursorPosition(x * 2 + 1, y + 1);
	std::cout << "  ";

	//��ġ ����
	x = next_x;
	y = next_y;

	//���� ��ġ �迭 ������Ʈ
	map[y][x] = 'x';
	//���� ���
	setCursorPosition(x * 2 + 1, y + 1);
	setColor(12); std::cout << "�� "; setColor(7);
	//1�ʸ��� ������
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 0.5�� ����
}
