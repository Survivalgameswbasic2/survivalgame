#ifndef BACKP_H
#define BACKP_H

class BackP
{
public:// �Ʒ� ���µ��� user->heart--, user->mental++ ���� ���� ���� �����մϴ�.

	int food;			//���İ���
	int water;			//������
	int bullet;			//�Ѿ˰���
	int medicine;		//�ళ��
	int direction;
	int itemlist[10];	// ������ ����Ʈ, �� ���ں��� ������ �Ҵ��ϰ� if �� ���ؼ� �����ϸ� �� �� �����ϴ�.
	int gun;
	int radio;
	BackP();
	bool checkweight();
	void unionP(player* user); //���濡 ����ִ°� ������ ��ġ��
	void sepP(player* user); //�������� ������ �������� 
};

#endif // !�÷��̾�
