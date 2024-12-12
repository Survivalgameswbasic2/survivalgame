#include "expire_tool.h"
#include "player.h"
#include <string>
#include <conio.h>
#include <thread>
#include <iostream>
#include "bad_ending.h"
#include "game_map.h"
#include <vector>
#include "Zombies.h"
#include <mutex>
#include "npc_image.h"
#include "backpack.h"
#include <windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;
#define MAP_WIDTH 34
#define MAP_HEIGHT 20

//좀비 가 다가와서 공격할때 체력 안담
//좀비 이펙트 존재하지 않음
std::vector<std::vector<std::string>> dialogue_7 = { {
    "연구원: 다 만들었어요. 무전기. 수신 장",
"연구원: 이걸로 저희 위치를 알려주면 구해주러 헬기가 올거에요.",
"플레이어: 네, 피난처에 있는 생존자들오 안전하게 데리고 왔어요. 다같이 탈출하죠 이제",
"생존자들: 드디어 탈출하는구나! 감사합니다.",
"연구원: 그럼 이제 구조 요청을 보낼게요!",
"연구원: ...보냈어요. 저희 위치를 확인하고 이제 오는 것 같아요",
"플레이어: 잠시만요. 여기에 좀비가 모이는 것 같아요!",
"연구원: 저희는 아직 뭔가 기척을 못느끼겠는데. 감각이 예민하군요.",
"연구원: 그 말이 사실이면 큰일 인데요. 아직 헬기가 오려면 조금 걸릴 텐데.",
"플레이어: 일단 같이 구석에 숨어있으세요. 제가 시간을 끌어 볼게요.",
"연구원: 그게 무슨! 같이 숨어있죠",
"플레이어: 아뇨, 숨어있어 봤자 여기 여러사람의 감정에 반응해서 분명 들킬 거에요.",
"플레이어: 제가 좀비를 처치하면서 유인할테니. 헬기가 오면 먼저 타면서 탈출할 준비를 하세요.",
"플레이어: 제가 끝까지 남아 좀비를 유인하다가 마지막에 탈게요!",
"연구원: ...반박하고 싶지만 그게 제일 합리적인거 같네요. 총알은 넉넉하니 무운을 빌게요!",
"연구원: 당신은 어쩌면 좀비사태의 유일한 돌파구라고 생각하고 꼭 생존하십쇼! 좀비가 돼서도 안돼요!",
"플레이어: 물론이죠. 걱정마세요. 슬슬 좀비가 오는거 같은데 빨리 숨으세요.",
"플레이어: ...하 이게 마지막인거 같은 느낌이 드네... 좋아 해보자고!"
}
};

std::vector<Zombies*> zombies;
std::mutex zombieMutex;
static int bullet_num = 3;
static int playerDirection = 3; // 0: 위, 1: 아래, 2: 왼쪽, 3: 오른쪽 (초기 값은 오른쪽)

static struct Bullet {
    int x;
    int y;
    int direction;
    int distanceTraveled;
};

static std::vector<Bullet> bullets;
static std::mutex bulletMutex;

static bool zombie_spawning = true;
static void spawn_zombies(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user, int spawn_x, int spawn_y) {
    while (zombie_spawning) {
        std::this_thread::sleep_for(std::chrono::seconds(6)); // 3초 대기

        std::lock_guard<std::mutex> lock(zombieMutex); // 뮤텍스 잠금
        Zombies* newZombie = new Zombies(spawn_x, spawn_y, 1, 0);
        zombies.push_back(newZombie);
        map[spawn_y][spawn_x] = 'x'; // 맵에 좀비 표시
    }
}

static bool zombie_moving = true;
static void move_zombies(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
    while (zombie_moving){
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 대기

        std::lock_guard<std::mutex> lock(zombieMutex); // 뮤텍스 잠금
        for (auto it = zombies.begin(); it != zombies.end();) {
            Zombies* z = *it;

            // 현재 좀비 위치를 지움
            map[z->y][z->x] = ' ';

            // 플레이어를 향한 이동 계산
            if (z->x < user->player_x && map[z->y][z->x+1]!='x') z->x++;
            else if (z->x > user->player_x && map[z->y][z->x - 1] != 'x') z->x--;
            if (z->y < user->player_y && map[z->y+1][z->x] != 'x') z->y++;
            else if (z->y > user->player_y && map[z->y-1][z->x] != 'x') z->y--;

            // 충돌 체크
            if (z->x == user->player_x && z->y == user->player_y) {
                user->heart--; // 플레이어 체력 감소
                PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
                if (user->heart > 0) {
                    printstat(user);
                }
                meet_zombie_change_edge();
                updateTextBox("좀비에게 공격당했습니다!");
                delete z;       // 좀비 제거
                it = zombies.erase(it);
                continue;
            }

            // 맵에 새 위치 업데이트
            map[z->y][z->x] = 'x';
            ++it;
        }
    }
}
static bool bullet_moving = true;
static void move_bullets(char map[MAP_HEIGHT][MAP_WIDTH + 1]) {
    while (bullet_moving) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 0.1초 대기
        std::lock_guard<std::mutex> lock(bulletMutex);

        for (auto it = bullets.begin(); it != bullets.end();) {
            Bullet& b = *it;

            // 현재 총알 위치 지움
            map[b.y][b.x] = ' ';

            // 방향에 따라 이동
            switch (b.direction) {
            case 0: b.y--; break;
            case 1: b.y++; break;
            case 2: b.x--; break;
            case 3: b.x++; break;
            }

            b.distanceTraveled++;

            // 충돌 감지
            bool hit = false;
            {
                std::lock_guard<std::mutex> zombieLock(zombieMutex);
                for (auto zIt = zombies.begin(); zIt != zombies.end();) {
                    Zombies* z = *zIt;
                    if (map[b.y][b.x] == '#') {
                        hit = true;
                        break;
                    }
                    if (std::abs(z->x - b.x) <= 0 && std::abs(z->y - b.y) <= 0) {
                        map[z->y][z->x] = ' ';
                        delete z;
                        zIt = zombies.erase(zIt);
                        break;
                    }
                    else {
                        ++zIt;
                    }
                }
            }

            // 충돌 또는 경계 초과 처리
            if (hit || b.x < 0 || b.x >= MAP_WIDTH || b.y < 0 || b.y >= MAP_HEIGHT || b.distanceTraveled > 7) {
                it = bullets.erase(it);
                continue;
            }

            // 맵에 총알 위치 표시
            map[b.y][b.x] = '*';
            ++it;
        }
    }
}


void start_day7(player* user,BackP*user_back) {
    system("cls");
    char map[MAP_HEIGHT][MAP_WIDTH + 1];
    copy_map(7, map);
    draw_map(map);         // 탐험 맵
    printstat(user); // 아이템 창 
    updateTextBox("");

    user->player_x = 10;
    user->player_y = 10;
    printplayer();
    int dialogue_line = 0;
    bool in_dialogue = true;
    set_isExplore(false);
    int flag = 0;
    int dialogue_num = 0;
    map[user->player_y][user->player_x] = 'P';
    clear_npc_screen();
    printnpc1();
    while (1) {
        if (in_dialogue) {
            // 대화 중일 때

            if (_kbhit()) {
                int key = _getch();
                if (key == ' ') { // 스페이스바로 대화 진행
                    if (dialogue_line < dialogue_7[dialogue_num].size()) {
                        updateDialogue(dialogue_7[dialogue_num][dialogue_line++]);
                    }
                    else {
                        // 대화 종료
                        dialogue_clear();
                        in_dialogue = false;
                        set_isExplore(true);
                        dialogue_line = 0;
                        dialogue_num++;
                        if (dialogue_num == 1) {
                            clear_npc_screen();
                            printplayer();
                            break;
                        }
                    }
                }
            }
            continue; // 대화 중에는 아래 로직을 무시하고 다음 루프로 이동
        }
    }
    set_hour(9);
    std::thread timerThread(timer2);
    std::thread zombieSpawnThread(spawn_zombies, map, user, 3, 3);
    std::thread zombieSpawnThread2(spawn_zombies, map, user, 3, 17);
    std::thread zombieSpawnThread5(spawn_zombies, map, user, 15, 3);
    std::thread zombieSpawnThread3(spawn_zombies, map, user, 31, 4);
    std::thread zombieSpawnThread4(spawn_zombies, map, user, 31, 17);
    std::thread zombieSpawnThread6(spawn_zombies, map, user, 15, 17);
    std::thread zombieMoveThread(move_zombies, map, user);
    std::thread bulletMoveThread(move_bullets, map);
    while (true) {
        map[user->player_y][user->player_x] = ' ';
        if (get_hour() == 21) {
            stop_timer_running();
            zombie_moving = false;
            zombie_spawning = false;
            bullet_moving = false;
            if (timerThread.joinable()) { timerThread.join(); }
            if (zombieSpawnThread.joinable()) zombieSpawnThread.join();
            if (zombieMoveThread.joinable()) zombieMoveThread.join();
            if (bulletMoveThread.joinable()) bulletMoveThread.join();
            PlaySound(TEXT("helicopter.wav"), NULL, SND_ASYNC);
            int line = 0;
            for (line = 31; line >= 0; line -= 2) {
                if (line <= 29) {
                    for (int row = 2; row <= 17; row++) {
                        if (map[row][line + 2] == '*') {
                            map[row][line + 2] = ' ';
                        }
                        if (map[row][line + 1] == '*') {
                            map[row][line + 1] = ' ';
                        }
                    }
                }
                for (int row = 2; row <= 17; row++) {
                    if (map[row][line] != '#') {
                        map[row][line] = '*';
                    }
                    if (map[row][line-1] != '#' ) {
                        map[row][line-1] = '*';
                    }
                }
                map[user->player_y][user->player_x] = 'P';
                draw_map(map);

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            break;
        }
        
        if (_kbhit()) {
            int key = _getch();

            if (key == 224) { // 방향키 입력 확인
                key = _getch();
                int newX = user->player_x, newY = user->player_y;
                switch (key) {
                case 72: newY--; playerDirection = 0; break; // 위쪽 방향
                case 80: newY++; playerDirection = 1; break; // 아래쪽 방향
                case 75: newX--; playerDirection = 2; break; // 왼쪽 방향
                case 77: newX++; playerDirection = 3; break; // 오른쪽 방향
                }

                // 이동 가능 여부 확인
                if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
                    map[newY][newX] == ' ' && !is_zombie_position(newX, newY, map)) {
                    user->player_x = newX;
                    user->player_y = newY;
                }
                else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
                    map[newY][newX] == 'A' && !is_zombie_position(newX, newY, map)) {
                    switch (user->direction) {
                    case(1):
                        if (map[newY + 1][newX] == ' ') {
                            map[newY + 1][newX] = 'A';
                            user->player_x = newX;
                            user->player_y = newY;
                        }
                        break;
                    case(2):
                        if (map[newY][newX + 1] == ' ') {
                            map[newY][newX + 1] = 'A';
                            user->player_x = newX;
                            user->player_y = newY;
                        }
                        break;
                    case(3):
                        if (map[newY - 1][newX] == ' ') {
                            map[newY - 1][newX] = 'A';
                            user->player_x = newX;
                            user->player_y = newY;
                        }
                        break;
                    case(4):
                        if (map[newY][newX - 1] == ' ') {
                            map[newY][newX - 1] = 'A';
                            user->player_x = newX;
                            user->player_y = newY;
                        }
                        break;
                    }
                }
                else if (newY >= 0 && newY < MAP_HEIGHT && newX >= 0 && newX < MAP_WIDTH &&
                    map[newY][newX] == '%' && !is_zombie_position(newX, newY, map)) {
                    user->player_x = newX;
                    user->player_y = newY;
                    user->heart--;
                    PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
                    printstat(user);
                    updateTextBox("햇빛에 스트레스를 받았다");
                }
                else if (is_zombie_position(newX, newY, map)) {
                    user->heart--;
                    PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
                    if (user->heart > 0) {
                        printstat(user);
                    }
                    updateTextBox("좀비에게 데미지를 입었다.");
					meet_zombie_change_edge();	
                }
            }
            else if (key == 's' && user->bullet>0&&user->gun>=1) { // 's' 키로 총알 발사
                PlaySound(TEXT("gun.wav"), NULL, SND_ASYNC);
                std::lock_guard<std::mutex> lock(bulletMutex);
          
                user->bullet--;
                printstat(user);
                bullets.push_back({ user->player_x, user->player_y, playerDirection, 0 });
            }
            else if (key == ' ' && is_player_near_item(user, map, user_back)) { // 엔터키로 아이템 획득
                map[user->player_y][user->player_x] = ' ';
            }
            else if (key == '1') { // 아이템 사용
                if (user->food > 0) {
                    user->food--;
                    if (user->mode == 3) {
                        user->mental -= 40;
                        if (user->mental < 0) {
                            user->mental = 0;
                        }
                    }
                    else {
                        user->mental -= 20;
                        if (user->mental < 0) {
                            user->mental = 0;
                        }
                    }
                    updateTextBox("식량을 먹으니 한결 든든해진 기분이다.");
                    printstat(user);
                }
                else {
                    updateTextBox("먹을 수 있는 식량이 없다...");
                }
            }
            else if (key == '2') { // 아이템 사용
                if (user->medicine > 0) {
                    user->medicine--;
                    if (user->mode == 3) {
                        user->heart += 2;
                        if (user->heart > user->maxh) {
                            user->heart = user->maxh;
                        }
                    }
                    else {
                        user->heart++;
                        if (user->heart > user->maxh) {
                            user->heart = user->maxh;
                        }
                    }
                    printstat(user);
                    updateTextBox("치료제를 사용하니 몸이 회복되는 것이 느껴진다.");
                }
                else {
                    updateTextBox("사용할 수 있는 치료제가 없다...");
                }
            }
        }

        if (user->heart <=0) {
            stop_timer_running();
            zombie_moving = false;
            zombie_spawning = false;
            bullet_moving = false;
            if (timerThread.joinable()) { timerThread.join(); }
            if (zombieSpawnThread.joinable()) zombieSpawnThread.join();
            if (zombieMoveThread.joinable()) zombieMoveThread.join();
            if (bulletMoveThread.joinable()) bulletMoveThread.join();
            bad_ending_zombie();
        }
        map[user->player_y][user->player_x] = 'P';
        draw_map(map);
    }
    stop_timer_running();
    zombie_moving = false;
    zombie_spawning = false;
    bullet_moving = false;
    if (timerThread.joinable()) { timerThread.join(); }
    if (zombieSpawnThread.joinable()) zombieSpawnThread.join();
    if (zombieMoveThread.joinable()) zombieMoveThread.join();
    if (bulletMoveThread.joinable()) bulletMoveThread.join();
    if (user->mental < 50 && user->heart>3) {
        hidden_ending();
    }
    else {
        normal_ending();
    }
}