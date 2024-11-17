


// 좀비 위치 확인 함수
bool isZombiePosition(int x, int y) {
	return game_map[y][x] == 'x';
}

// NPC와 대화 출력 함수
void startConversation() {
	const char* npcDialog[] = {
		"안녕하세요! 여기는 안전한 곳입니다.",
		"좀비가 많으니 조심하세요.",
		"도움이 필요하면 말을 걸어주세요."
	};
	static int dialogIndex = 0;

	updateTextBox(npcDialog[dialogIndex]);
	dialogIndex = (dialogIndex + 1) % (sizeof(npcDialog) / sizeof(npcDialog[0]));
}