#ifndef EXPIRE_TOOL_H
#define EXPIRE_TOOL_H
#include "player.h"
#include<string>
#include <atomic>
#include<iostream>
//////////////////// �⺻ ��� �Լ�///////////////////////////
// �ܼ� Ŀ�� ��ġ ����
void setCursorPosition(int x, int y);

// �ܼ� �ؽ�Ʈ ���� ����
void setColor(int color);

//////////////////// ��ȭâ ///////////////////////////

// �ؽ�Ʈ â �ʱ�ȭ �� �޽��� ��� �Լ�  -> ª�� ��ȭ�� ���
void updateTextBox(const char* message);
// �� ��ȭ�� ���
void updateDialogue(std::string& message);
//��ȭâ û��
void dialogue_clear();
//////////////////// ����â ///////////////////////////


void printstat(player* user);

//////////////////// Ÿ�̸� ///////////////////////////
int is_mission_failed();
void draw_clock(int time);
void stop_timer_running();
void timer();
void start_timer_running();
#endif