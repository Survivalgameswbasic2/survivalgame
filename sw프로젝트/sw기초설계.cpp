#include <iostream>
#include <string.h>



void printfstat(int heart, int mental, int food, int water, int bullet) {
	printf("┌─────────────────────────┐\n");
	printf("│ 체력 :     ");
	for (int i = 0; i < heart; i++) {
		printf("♥");
	}
	for(int i = 0; i < 5 - heart; i++) {
		printf("♡");
	}
	printf("   │\n");

	printf("│ 스트레스 : ");
	for (int i = 0; i < mental; i++) {
		printf("★");
	}
	for (int i = 0; i < 5 - mental; i++) {
		printf("☆");
	}
	printf("   │\n");


	printf("│                         │\n"); 
	printf("│ 식량 X %d                │\n",food); 
	printf("│ 물 X %d                  │\n",water);
	if (bullet != 0) {
		printf("│ 탄환 X %d                │\n", bullet);
	}
	printf("└─────────────────────────┘\n");
}

int main() {
	
	printfstat(1, 2, 3, 4,5);
}