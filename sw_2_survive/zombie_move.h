#ifndef ZOMBIE_MOVE_H
#define ZOMBIE_MOVE_H
class Zombie {
public:
	int x, y;//���� ��ġ
	int dx, dy; //�̵�����

	Zombie(int startX, int startY, int dX, int dY);
	void move(char (&game_map)[20][35]); //���� �ε����� �̵����� �ݴ�� �����ϴ� �Լ�

};
#endif