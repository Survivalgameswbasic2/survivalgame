#ifndef PLAYER_H
#define PLAYER_H

class player
{
public:// �Ʒ� ���µ��� user->heart--, user->mental++ ���� ���� ���� �����մϴ�.
	int mode; //�������� ȿ�� ������ 1.�ִ�ü��1���� 2.��Ʈ�����Ѱ�20���� 3.������ȿ��2��
	int heart;			//ü��	
	int mental;			//���ŷ�
	int food;			//���İ���
	int maxh;
	int maxm;
	int water;			//������
	int bullet;			//�Ѿ˰���
	int player_x;		//�÷��̾� x��ġ
	int player_y;		//�÷��̾� y��ġ
	int medicine;		//�ళ��
	int direction;
	int itemlist[10];	// ������ ����Ʈ, �� ���ں��� ������ �Ҵ��ϰ� if �� ���ؼ� �����ϸ� �� �� �����ϴ�.
	int gun;
	int radio;
	int flag;			//��ȣ�� ����
	int sunlight;
	player();
	void player_face();
};

#endif // !�÷��̾�