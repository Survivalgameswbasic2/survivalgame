#ifndef PLAYER_H
#define PLAYER_H

class player
{
public:// �Ʒ� ���µ��� user->heart--, user->mental++ ���� ���� ���� �����մϴ�.
	int heart;			//ü��	
	int mental;			//���ŷ�
	int food;			//���İ���
	int water;			//������
	int bullet;			//�Ѿ˰���
	int player_x;		//�÷��̾� x��ġ
	int player_y;		//�÷��̾� y��ġ
	int medicine;		//�ళ��

	int itemlist[10];	// ������ ����Ʈ, �� ���ں��� ������ �Ҵ��ϰ� if �� ���ؼ� �����ϸ� �� �� �����ϴ�.

	player();
	// ���ΰ� �׸��� �Լ� (�ʷϻ�)
	void drawPlayer();

	// ���ΰ� ��ġ�� ����� ���� �Լ�
	void clearPlayer();

	void player_face();
};

#endif // !�÷��̾�