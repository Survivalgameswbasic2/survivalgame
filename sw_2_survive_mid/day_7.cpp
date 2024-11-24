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
#define MAP_WIDTH 34
#define MAP_HEIGHT 20

std::string dialogue_7[] = {
    "������"
};

std::vector<Zombies*> zombies;
std::mutex zombieMutex;
int bullet_num = 3;
int playerDirection = 3; // 0: ��, 1: �Ʒ�, 2: ����, 3: ������ (�ʱ� ���� ������)

struct Bullet {
    int x;
    int y;
    int direction;
    int distanceTraveled;
};

std::vector<Bullet> bullets;
std::mutex bulletMutex;

void spawn_zombies(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user, int spawn_x, int spawn_y) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5)); // 3�� ���

        std::lock_guard<std::mutex> lock(zombieMutex); // ���ؽ� ���
        Zombies* newZombie = new Zombies(spawn_x, spawn_y, 1, 0);
        zombies.push_back(newZombie);
        map[spawn_y][spawn_x] = 'x'; // �ʿ� ���� ǥ��
    }
}

void move_zombies(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���

        std::lock_guard<std::mutex> lock(zombieMutex); // ���ؽ� ���
        for (auto it = zombies.begin(); it != zombies.end();) {
            Zombies* z = *it;

            // ���� ���� ��ġ�� ����
            map[z->y][z->x] = ' ';

            // �÷��̾ ���� �̵� ���
            if (z->x < user->player_x && map[z->y][z->x + 1] !='*') z->x++;
            else if (z->x > user->player_x && map[z->y][z->x -1] != '*') z->x--;
            if (z->y < user->player_y && map[z->y+1][z->x] != '*') z->y++;
            else if (z->y > user->player_y && map[z->y-1][z->x] != '*') z->y--;

            // �浹 üũ
            if (z->x == user->player_x && z->y == user->player_y) {
                user->heart--; // �÷��̾� ü�� ����
                printstat(user);
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

void move_bullets(char map[MAP_HEIGHT][MAP_WIDTH + 1]) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 0.1�� ���
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
                    if (std::abs(z->x - b.x) <= 0 && std::abs(z->y - b.y) <= 0) {
                        map[z->y][z->x] = ' ';
                        delete z;
                        zIt = zombies.erase(zIt);
                        hit = true;
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
                bullet_num++;
                draw_map(map);
                continue;
            }

            // �ʿ� �Ѿ� ��ġ ǥ��
            map[b.y][b.x] = '*';
            ++it;
        }
    }
}


void start_day7(player* user) {
    system("cls");
    char map[MAP_HEIGHT][MAP_WIDTH + 1];
    copy_map(5, map);
    draw_map(map);         // Ž�� ��
    printstat(user); // ������ â 
    updateTextBox("");

    user->player_x = 5;
    user->player_y = 6;
    draw_face();
    set_hour(9);
    std::thread timerThread(timer);

    int dialogue_line = 0;
    bool in_dialogue = false;
    int flag = 0;
    int dialogue_num = 0;
    std::thread zombieSpawnThread(spawn_zombies, map, user, 2, 4);
    std::thread zombieSpawnThread2(spawn_zombies, map, user, 2, 17);
    std::thread zombieSpawnThread3(spawn_zombies, map, user, 31, 4);
    std::thread zombieSpawnThread4(spawn_zombies, map, user, 31, 17);

    std::thread zombieMoveThread(move_zombies, map, user);
    std::thread bulletMoveThread(move_bullets, map);

    map[user->player_y][user->player_x] = 'P';
    while (true) {
        map[user->player_y][user->player_x] = ' ';
        draw_sunlight(map);
        if (get_hour() == 21) {
            if (timerThread.joinable()) { timerThread.join(); }
            if (zombieSpawnThread.joinable()) zombieSpawnThread.join();
            if (zombieMoveThread.joinable()) zombieMoveThread.join();
            if (bulletMoveThread.joinable()) bulletMoveThread.join();
            break;
        }
        if (in_dialogue) {
            // ��ȭ ���� ��
            if (_kbhit()) {
                int key = _getch();
                if (key == ' ') { // �����̽��ٷ� ��ȭ ����
                    if (dialogue_line < sizeof(dialogue_7) / sizeof(dialogue_7[0])) {
                        updateDialogue(dialogue_7[dialogue_line++]);
                    }
                    else {
                        // ��ȭ ����
                        dialogue_clear();
                        in_dialogue = false;
                        set_isExplore(true);
                    }
                }
                if (dialogue_num == 0) {
                    map[1][11] = ' ';
                    map[5][11] = 'N';
                    dialogue_line = 0;
                    dialogue_num++;
                }
                else if (dialogue_num == 1) {
                    map[5][11] = ' ';
                    dialogue_line = 0;
                    dialogue_num++;
                }
            }
            continue; // ��ȭ �߿��� �Ʒ� ������ �����ϰ� ���� ������ �̵�
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
                    map[newY][newX] == '%' && !is_zombie_position(newX, newY, map)) {
                    user->player_x = newX;
                    user->player_y = newY;
                    user->mental--;
                    updateTextBox("�޺��� ��Ʈ������ �޾Ҵ�");
                }
                else if (is_zombie_position(newX, newY, map)) {
                    user->heart--;
                    printstat(user);
                    setCursorPosition(1, 23);
                    updateTextBox("���񿡰� �������� �Ծ���.");
                }
            }
            else if (key == 's' && bullet_num>0) { // 's' Ű�� �Ѿ� �߻�
                std::lock_guard<std::mutex> lock(bulletMutex);
                bullet_num--;
                bullets.push_back({ user->player_x, user->player_y, playerDirection, 0 });
            }
            else if (key == ' ' && is_player_near_item(user, map)) { // ����Ű�� ������ ȹ��
                map[user->player_y][user->player_x] = ' ';
            }
            else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
                set_isExplore(false);
                dialogue_clear();
                updateDialogue(dialogue_7[dialogue_line++]);
                in_dialogue = true; // ��ȭ ���� ����
            }
        }
        if (user->heart <= 0) {

            if (timerThread.joinable()) { timerThread.join(); }
            if (zombieSpawnThread.joinable()) zombieSpawnThread.join();
            if (zombieMoveThread.joinable()) zombieMoveThread.join();
            if (bulletMoveThread.joinable()) bulletMoveThread.join();
            bad_ending();
        }
        if (user->mental <= 0) {
            if (timerThread.joinable()) { timerThread.join(); }
            if (zombieSpawnThread.joinable()) zombieSpawnThread.join();
            if (zombieMoveThread.joinable()) zombieMoveThread.join();
            if (bulletMoveThread.joinable()) bulletMoveThread.join();
            bad_ending();
        }
        map[user->player_y][user->player_x] = 'P';
        draw_map(map);
    }
}