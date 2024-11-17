


// ���� ��ġ Ȯ�� �Լ�
bool isZombiePosition(int x, int y) {
	return game_map[y][x] == 'x';
}

// NPC�� ��ȭ ��� �Լ�
void startConversation() {
	const char* npcDialog[] = {
		"�ȳ��ϼ���! ����� ������ ���Դϴ�.",
		"���� ������ �����ϼ���.",
		"������ �ʿ��ϸ� ���� �ɾ��ּ���."
	};
	static int dialogIndex = 0;

	updateTextBox(npcDialog[dialogIndex]);
	dialogIndex = (dialogIndex + 1) % (sizeof(npcDialog) / sizeof(npcDialog[0]));
}