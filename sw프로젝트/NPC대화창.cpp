#include"����.h"
#include <iostream>
#include "�÷��̾�.h"
#define STAGE_WIDTH 70  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 
#define MAX_HEALTH 5    // �ִ� ü��
#define stat_Height 9 //����â�� ������ ������ ����


// (74,10) ~ (102,26)

//  (74,10)----------------------------(102,10)

			//�ι� ��
// (74, 20)
			// ����â
// (74,26) ------------------------------(102,26)

void CommunicationBoxNPC(int flag, player*user) {
	setCursorPosition(STAGE_WIDTH + 4, stat_Height + 1);
	std::cout << "������������������������������������������������������";//27�� ����
	for (int i = 0; i < 16; i++) {//���� 10��
		setCursorPosition(STAGE_WIDTH + 4, stat_Height + 2 + i);
		if (i == 10) {
			printf("������������������������������������������������������");// 74, 20
		}
		else {
			printf("��                         ��");
		}
	}
	setCursorPosition(STAGE_WIDTH + 4, stat_Height + 17);
	std::cout << "������������������������������������������������������";
	//npc ���� ���°� �ƴϸ� �ڽ� ����
	if (flag == 0) {
		user->player_face();
	}
	//npc ���� �����̸� �ڽ� ����
}