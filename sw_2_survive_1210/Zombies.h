#ifndef ZOMBIE_H
#define ZOMBIE_H
class Zombies {
public:
	int x, y;//���� ��ġ
	int dx, dy; //�̵�����

	Zombies(int startX, int startY, int dX, int dY);
	void move(char game_map[20][35]); //���� �ε����� �̵����� �ݴ�� �����ϴ� �Լ�

};
#endif