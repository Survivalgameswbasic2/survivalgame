#ifndef BACKP_H
#define BACKP_H

class BackP
{
public:// 아래 상태들은 user->heart--, user->mental++ 등을 통해 조절 가능합니다.

	int food;			//음식개수
	int water;			//물개수
	int bullet;			//총알개수
	int medicine;		//약개수
	int direction;
	int itemlist[10];	// 아이템 리스트, 각 숫자별로 아이템 할당하고 if 문 통해서 구현하면 될 거 같습니다.
	int gun;
	int radio;
	BackP();
	bool checkweight();
	void unionP(player* user); //가방에 들어있는거 기지에 합치기
	void sepP(player* user); //기지에서 아이템 꺼내가기 
};

#endif // !플레이어
