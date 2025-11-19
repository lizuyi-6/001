#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10
void InitBoard(char board[][COLS], int r, int c, char set);  // 支持变长数组列数
void DisplayBoard(char board[][COLS], int r, int c);
void SetMine(char mine[][COLS], int r, int c, int de);
void FindMine(char mine[][COLS], char show[][COLS], int r, int c, int mine_count);  // 新增地雷数量参数