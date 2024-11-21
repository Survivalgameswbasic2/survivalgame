#include "expire_tool.h"
#include "player.h"
#include <string>
#include <conio.h>
#include <thread>
#include <iostream>
#include "bad_ending.h"
#include "game_map.h"
#include <vector>
#include "zombie_move.h"
#include<mutex>
#define MAP_WIDTH 34
#define MAP_HEIGHT 20

std::string dialogue_7[] = {
    "������"
};
typedef struct Bullet {
    int x, y;
    int direction;
    int distance;

    Bullet(int x, int y, int direction) : x(x), y(y), direction(direction), distance(5) {}
};

std::vector<Zombie*>zombies;
std::vector<Bullet> bullets;
std::mutex zombieMutex;

int playerDirection = 3; // 0: ��, 1: �Ʒ�, 2: ����, 3: ������ (�ʱ� ���� ������)

void spawn_zombies(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3)); // 3�� ���

        std::lock_guard<std::mutex> lock(zombieMutex); // ���ؽ� ���
        Zombie* newZombie = new Zombie(4, 4, 1, 0);
        zombies.push_back(newZombie);
        map[4][4] = 'x'; // �ʿ� ���� ǥ��
    }
}
void move_zombies(char map[MAP_HEIGHT][MAP_WIDTH + 1], player* user) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���

        std::lock_guard<std::mutex> lock(zombieMutex); // ���ؽ� ���
        for (auto it = zombies.begin(); it != zombies.end();) {
            Zombie* z = *it;

            // ���� ���� ��ġ�� ����
            map[z->y][z->x] = ' ';

            // �÷��̾ ���� �̵� ���
            if (z->x < user->player_x) z->x++;
            else if (z->x > user->player_x) z->x--;
            if (z->y < user->player_y) z->y++;
            else if (z->y > user->player_y) z->y--;

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
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 0.2�� ���

        for (auto it = bullets.begin(); it != bullets.end();) {
            Bullet& b = *it;

            // ���� ���� ��ġ ����
            map[b.y][b.x] = ' ';

            // ���� �̵� (�������� �̵�)
            if (b.direction == 0) b.y--;
            else if (b.direction == 1) b.y++;
            else if (b.direction == 2) b.x--;
            else if (b.direction == 3) b.x++;

            b.distance--;

            // ��ġ ��ȿ�� Ȯ�� �� �Ÿ� �ʰ� Ȯ��
            if (b.x < 0 || b.x >= MAP_WIDTH || b.y < 0 || b.y >= MAP_HEIGHT || b.distance <= 0 || map[b.y][b.x] == '#') {
                it = bullets.erase(it);
                continue;
            }

            // ����� �浹 üũ
            bool bulletHit = false;
            {
                std::lock_guard<std::mutex> lock(zombieMutex);
                for (auto zIt = zombies.begin(); zIt != zombies.end(); ++zIt) {
                    Zombie* z = *zIt;
                    if (z->x == b.x && z->y == b.y) {
                        delete z;
                        zombies.erase(zIt);
                        bulletHit = true;
                        break;
                    }
                }
            }

            if (bulletHit) {
                it = bullets.erase(it);
                continue;
            }

            // �ʿ� �� ��ġ ������Ʈ
            map[b.y][b.x] = 'B';
            ++it;
        }
    }
}

void start_day7(player* user) {
    system("cls");
    char map[MAP_HEIGHT][MAP_WIDTH + 1];
    copy_map(4, map);
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
    std::thread zombieSpawnThread(spawn_zombies, map, user);
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
            else if (key == ' ' && is_player_near_item(user, map)) { // ����Ű�� ������ ȹ��
                map[user->player_y][user->player_x] = ' ';
            }
            else if (key == ' ' && is_player_near_npc(user, map)) { // �����̽��ٷ� NPC�� ��ȭ
                set_isExplore(false);
                dialogue_clear();
                updateDialogue(dialogue_7[dialogue_line++]);
                in_dialogue = true; // ��ȭ ���� ����
            }
            else if (key == 'f') { // 'f' Ű�� ���� ���
                bullets.push_back(Bullet(user->player_x, user->player_y, playerDirection)); // �÷��̾��� �ٶ󺸴� �������� ���� �߻�
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
