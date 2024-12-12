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

//���� �� �ٰ��ͼ� �����Ҷ� ü�� �ȴ�
//���� ����Ʈ �������� ����
std::vector<std::vector<std::string>> dialogue_7 = { {
    "������: �� ��������. ������. ���� ��",
"������: �̰ɷ� ���� ��ġ�� �˷��ָ� �����ַ� ��Ⱑ �ðſ���.",
"�÷��̾�: ��, �ǳ�ó�� �ִ� �����ڵ�� �����ϰ� ������ �Ծ��. �ٰ��� Ż������ ����",
"�����ڵ�: ���� Ż���ϴ±���! �����մϴ�.",
"������: �׷� ���� ���� ��û�� �����Կ�!",
"������: ...���¾��. ���� ��ġ�� Ȯ���ϰ� ���� ���� �� ���ƿ�",
"�÷��̾�: ��ø���. ���⿡ ���� ���̴� �� ���ƿ�!",
"������: ����� ���� ���� ��ô�� �������ڴµ�. ������ �����ϱ���.",
"������: �� ���� ����̸� ū�� �ε���. ���� ��Ⱑ ������ ���� �ɸ� �ٵ�.",
"�÷��̾�: �ϴ� ���� ������ ������������. ���� �ð��� ���� ���Կ�.",
"������: �װ� ����! ���� ��������",
"�÷��̾�: �ƴ�, �����־� ���� ���� ��������� ������ �����ؼ� �и� ��ų �ſ���.",
"�÷��̾�: ���� ���� óġ�ϸ鼭 �������״�. ��Ⱑ ���� ���� Ÿ�鼭 Ż���� �غ� �ϼ���.",
"�÷��̾�: ���� ������ ���� ���� �����ϴٰ� �������� Ż�Կ�!",
"������: ...�ݹ��ϰ� ������ �װ� ���� �ո����ΰ� ���׿�. �Ѿ��� �˳��ϴ� ������ ���Կ�!",
"������: ����� ��¼�� ��������� ������ ���ı���� �����ϰ� �� �����Ͻʼ�! ���� �ż��� �ȵſ�!",
"�÷��̾�: ��������. ����������. ���� ���� ���°� ������ ���� ��������.",
"�÷��̾�: ...�� �̰� �������ΰ� ���� ������ ���... ���� �غ��ڰ�!"
}
};

std::vector<Zombies*> zombies;
std::mutex zombieMutex;
static int bullet_num = 3;
static int playerDirection = 3; // 0: ��, 1: �Ʒ�, 2: ����, 3: ������ (�ʱ� ���� ������)

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
        std::this_thread::sleep_for(std::chrono::seconds(6)); // 3�� ���

        std::lock_guard<std::mutex> lock(zombieMutex); // ���ؽ� ���
        Zombies* newZombie = new Zombies(spawn_x, spawn_y, 1, 0);
        zombies.push_back(newZombie);
        map[spawn_y][spawn_x] = 'x'; // �ʿ� ���� ǥ��
    }
}

static bool zombie_moving = true;
static void move_zombies(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
    while (zombie_moving){
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���

        std::lock_guard<std::mutex> lock(zombieMutex); // ���ؽ� ���
        for (auto it = zombies.begin(); it != zombies.end();) {
            Zombies* z = *it;

            // ���� ���� ��ġ�� ����
            map[z->y][z->x] = ' ';

            // �÷��̾ ���� �̵� ���
            if (z->x < user->player_x && map[z->y][z->x+1]!='x') z->x++;
            else if (z->x > user->player_x && map[z->y][z->x - 1] != 'x') z->x--;
            if (z->y < user->player_y && map[z->y+1][z->x] != 'x') z->y++;
            else if (z->y > user->player_y && map[z->y-1][z->x] != 'x') z->y--;

            // �浹 üũ
            if (z->x == user->player_x && z->y == user->player_y) {
                user->heart--; // �÷��̾� ü�� ����
                PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
                if (user->heart > 0) {
                    printstat(user);
                }
                meet_zombie_change_edge();
                updateTextBox("���񿡰� ���ݴ��߽��ϴ�!");
                delete z;       // ���� ����
                it = zombies.erase(it);
                continue;
            }

            // �ʿ� �� ��ġ ������Ʈ
            map[z->y][z->x] = 'x';
            ++it;
        }
    }
}
static bool bullet_moving = true;
static void move_bullets(char map[MAP_HEIGHT][MAP_WIDTH + 1]) {
    while (bullet_moving) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 0.1�� ���
        std::lock_guard<std::mutex> lock(bulletMutex);

        for (auto it = bullets.begin(); it != bullets.end();) {
            Bullet& b = *it;

            // ���� �Ѿ� ��ġ ����
            map[b.y][b.x] = ' ';

            // ���⿡ ���� �̵�
            switch (b.direction) {
            case 0: b.y--; break;
            case 1: b.y++; break;
            case 2: b.x--; break;
            case 3: b.x++; break;
            }

            b.distanceTraveled++;

            // �浹 ����
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

            // �浹 �Ǵ� ��� �ʰ� ó��
            if (hit || b.x < 0 || b.x >= MAP_WIDTH || b.y < 0 || b.y >= MAP_HEIGHT || b.distanceTraveled > 7) {
                it = bullets.erase(it);
                continue;
            }

            // �ʿ� �Ѿ� ��ġ ǥ��
            map[b.y][b.x] = '*';
            ++it;
        }
    }
}


void start_day7(player* user,BackP*user_back) {
    system("cls");
    char map[MAP_HEIGHT][MAP_WIDTH + 1];
    copy_map(7, map);
    draw_map(map);         // Ž�� ��
    printstat(user); // ������ â 
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
            // ��ȭ ���� ��

            if (_kbhit()) {
                int key = _getch();
                if (key == ' ') { // �����̽��ٷ� ��ȭ ����
                    if (dialogue_line < dialogue_7[dialogue_num].size()) {
                        updateDialogue(dialogue_7[dialogue_num][dialogue_line++]);
                    }
                    else {
                        // ��ȭ ����
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
            continue; // ��ȭ �߿��� �Ʒ� ������ �����ϰ� ���� ������ �̵�
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

            if (key == 224) { // ����Ű �Է� Ȯ��
                key = _getch();
                int newX = user->player_x, newY = user->player_y;
                switch (key) {
                case 72: newY--; playerDirection = 0; break; // ���� ����
                case 80: newY++; playerDirection = 1; break; // �Ʒ��� ����
                case 75: newX--; playerDirection = 2; break; // ���� ����
                case 77: newX++; playerDirection = 3; break; // ������ ����
                }

                // �̵� ���� ���� Ȯ��
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
                    updateTextBox("�޺��� ��Ʈ������ �޾Ҵ�");
                }
                else if (is_zombie_position(newX, newY, map)) {
                    user->heart--;
                    PlaySound(TEXT("hurt.wav"), NULL, SND_ASYNC);
                    if (user->heart > 0) {
                        printstat(user);
                    }
                    updateTextBox("���񿡰� �������� �Ծ���.");
					meet_zombie_change_edge();	
                }
            }
            else if (key == 's' && user->bullet>0&&user->gun>=1) { // 's' Ű�� �Ѿ� �߻�
                PlaySound(TEXT("gun.wav"), NULL, SND_ASYNC);
                std::lock_guard<std::mutex> lock(bulletMutex);
          
                user->bullet--;
                printstat(user);
                bullets.push_back({ user->player_x, user->player_y, playerDirection, 0 });
            }
            else if (key == ' ' && is_player_near_item(user, map, user_back)) { // ����Ű�� ������ ȹ��
                map[user->player_y][user->player_x] = ' ';
            }
            else if (key == '1') { // ������ ���
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
                    updateTextBox("�ķ��� ������ �Ѱ� ������� ����̴�.");
                    printstat(user);
                }
                else {
                    updateTextBox("���� �� �ִ� �ķ��� ����...");
                }
            }
            else if (key == '2') { // ������ ���
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
                    updateTextBox("ġ������ ����ϴ� ���� ȸ���Ǵ� ���� ��������.");
                }
                else {
                    updateTextBox("����� �� �ִ� ġ������ ����...");
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