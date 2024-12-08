#ifndef ZOMBIE_H
#define ZOMBIE_H
class Zombies {
public:
	int x, y;//현재 위치
	int dx, dy; //이동방향

	Zombies(int startX, int startY, int dX, int dY);
	void move(char game_map[20][35]); //벽에 부딪히면 이동방향 반대로 설정하는 함수

};
#endif