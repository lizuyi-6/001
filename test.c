#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void menu()
{
    printf("****************************\n");
    printf("*******    1. play   *******\n");
    printf("*******    0. exit   *******\n");
    printf("****************************\n");
}

void choice()
{
    printf("Please choice level\n\t");
    printf("1.easy\n\t");
    printf("2.middle\n\t");
    printf("3.difficult\n\t");
    printf("4.customer\n\t");
}

// 简单模式（9x9，10雷）
void game()
{
    char mine[ROWS][COLS];  // 静态数组可以初始化，但这里统一用InitBoard
    char show[ROWS][COLS];

    InitBoard(mine, ROWS, COLS, '0');  // 用函数初始化
    InitBoard(show, ROWS, COLS, '*');

    SetMine(mine, ROW, COL, 10);
    DisplayBoard(show, ROW, COL);
    FindMine(mine, show, ROW, COL, 10);
}

// 中等模式（16x16，40雷）
void game_2()
{
#define MID_ROW 16
#define MID_COL 16
#define MID_ROWS MID_ROW+2
#define MID_COLS MID_COL+2

    char mine[MID_ROWS][MID_COLS];  // 移除初始化
    char show[MID_ROWS][MID_COLS];

    InitBoard(mine, MID_ROWS, MID_COLS, '0');
    InitBoard(show, MID_ROWS, MID_COLS, '*');

    SetMine(mine, MID_ROW, MID_COL, 40);
    DisplayBoard(show, MID_ROW, MID_COL);
    FindMine(mine, show, MID_ROW, MID_COL, 40);
}

// 困难模式（16x30，99雷）
void game_3()
{
#define HARD_ROW 16
#define HARD_COL 30
#define HARD_ROWS HARD_ROW+2
#define HARD_COLS HARD_COL+2

    char mine[HARD_ROWS][HARD_COLS];  // 移除初始化
    char show[HARD_ROWS][HARD_COLS];

    InitBoard(mine, HARD_ROWS, HARD_COLS, '0');
    InitBoard(show, HARD_ROWS, HARD_COLS, '*');

    SetMine(mine, HARD_ROW, HARD_COL, 99);
    DisplayBoard(show, HARD_ROW, HARD_COL);
    FindMine(mine, show, HARD_ROW, HARD_COL, 99);
}

// 自定义模式（核心：移除VLA的初始化）
void game_4()
{
    int row, col, mineCount;
    printf("请输入自定义棋盘的行数:");
    scanf("%d", &row);
    printf("请输入自定义棋盘的列数:");
    scanf("%d", &col);
    printf("请输入地雷数量:");
    scanf("%d", &mineCount);

    // 输入验证
    if (row < 5 || col < 5 || mineCount < 1 || mineCount >= row * col)
    {
        printf("输入无效！行数/列数至少为5，地雷数需在1~%d之间\n", row * col - 1);
        return;
    }

    // 变长数组（VLA）不允许初始化，只定义不赋值
    char mine[row + 2][col + 2];  // 移除 = {0}
    char show[row + 2][col + 2];  // 移除 = {0}

    // 用InitBoard函数初始化（替代定义时的初始化）
    InitBoard(mine, row + 2, col + 2, '0');
    InitBoard(show, row + 2, col + 2, '*');

    SetMine(mine, row, col, mineCount);
    system("cls");
    DisplayBoard(show, row, col);
    FindMine(mine, show, row, col, mineCount);
}

int main()
{
    int input = 0;
    int input_2 = 0;
    srand((unsigned int)time(NULL));
    do
    {
        menu();
        printf("请选择:>");
        scanf("%d", &input);
        system("cls");
        switch (input)
        {
        case 1:
            choice();
            scanf("%d", &input_2);
            system("cls");
            switch (input_2)
            {
            case 1: game(); break;
            case 2: game_2(); break;
            case 3: game_3(); break;
            case 4: game_4(); break;
            default: printf("选择错误，请重新选择!\n"); break;
            }
            break;
        case 0:
            printf("退出游戏\n");
            break;
        default:
            printf("选择错误，请重新选择!\n");
            break;
        }
    } while (input);

    return 0;
}