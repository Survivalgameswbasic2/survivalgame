#include <iostream>
#include "����.h"

#define STAGE_WIDTH 70  // ���������� �ʺ�
#define STAGE_HEIGHT 20 // ���������� ���� 

using namespace std;

// Ž�� �ʰ� �׵θ� �׸��� �Լ�
void drawStage() {
	// �׵θ� ���
	for (int i = 0;i <= STAGE_HEIGHT;i++) {
		for (int j = 0;j <= STAGE_WIDTH;j++) {
			setCursorPosition(j, i);
			if (i == 0 && j == 0) {
				cout << " ";
			}
			else if (i == 0 && j == STAGE_WIDTH) {
				cout << " ";
			}
			else if (i == STAGE_HEIGHT && j == 0) {
				cout << " ";
			}
			else if (i == STAGE_HEIGHT && j == STAGE_WIDTH) {
				cout << " ";
			}
			else if (i == 0|| i == STAGE_HEIGHT) {
				cout <<  "";
			}
			else if (j == 0 || j == STAGE_WIDTH) {
				cout << " ";
			}
		}
	}
}
