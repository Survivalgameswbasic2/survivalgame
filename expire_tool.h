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
void draw_face();
void stop_timer_running();
void timer();
void start_timer_running();
int get_hour();
void set_hour(int h);
void set_isExplore(bool x);
//////�޺��ý���
void draw_sunlight(char map[][35]);
void erase_sunlight(char map[][35]);
#endif