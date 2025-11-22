#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义最大尺寸（适配所有模式，包括自定义）
#define MAX_ROW 30
#define MAX_COL 30
#define MAX_ROWS MAX_ROW + 2
#define MAX_COLS MAX_COL + 2

// 各模式参数
#define EASY_ROW 9
#define EASY_COL 9
#define EASY_COUNT 10

#define MID_ROW 16
#define MID_COL 16
#define MID_COUNT 40

#define HARD_ROW 16
#define HARD_COL 30
#define HARD_COUNT 99

// 函数声明（统一使用最大尺寸数组参数）
void InitBoard(char board[][MAX_COLS], int r, int c, char set);
void DisplayBoard(char board[][MAX_COLS], int r, int c);
void SetMine(char mine[][MAX_COLS], int r, int c, int count);
void FindMine(char mine[][MAX_COLS], char show[][MAX_COLS], int r, int c, int mine_count);