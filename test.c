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

// 简单模式(9x9 10雷)
void game()
{
    // 使用最大尺寸数组，按实际尺寸操作
    char mine[MAX_ROWS][MAX_COLS];
    char show[MAX_ROWS][MAX_COLS];

    InitBoard(mine, MAX_ROWS, MAX_COLS, '0');
    InitBoard(show, MAX_ROWS, MAX_COLS, '*');

    SetMine(mine, EASY_ROW, EASY_COL, EASY_COUNT);
    DisplayBoard(show, EASY_ROW, EASY_COL);
    FindMine(mine, show, EASY_ROW, EASY_COL, EASY_COUNT);
}

// 中等模式(16x16 40雷)
void game_2()
{
    char mine[MAX_ROWS][MAX_COLS];
    char show[MAX_ROWS][MAX_COLS];

    InitBoard(mine, MAX_ROWS, MAX_COLS, '0');
    InitBoard(show, MAX_ROWS, MAX_COLS, '*');

    SetMine(mine, MID_ROW, MID_COL, MID_COUNT);
    DisplayBoard(show, MID_ROW, MID_COL);
    FindMine(mine, show, MID_ROW, MID_COL, MID_COUNT);
}

// 困难模式(16x30 99雷)
void game_3()
{
    char mine[MAX_ROWS][MAX_COLS];
    char show[MAX_ROWS][MAX_COLS];

    InitBoard(mine, MAX_ROWS, MAX_COLS, '0');
    InitBoard(show, MAX_ROWS, MAX_COLS, '*');

    SetMine(mine, HARD_ROW, HARD_COL, HARD_COUNT);
    DisplayBoard(show, HARD_ROW, HARD_COL);
    FindMine(mine, show, HARD_ROW, HARD_COL, HARD_COUNT);
}

// 自定义模式（使用固定最大尺寸数组）
void game_4()
{
    int row, col, mineCount;
    printf("请输入自定义棋盘的行数:");
    scanf("%d", &row);
    printf("请输入自定义棋盘的列数:");
    scanf("%d", &col);
    printf("请输入地雷数量:");
    scanf("%d", &mineCount);

    // 有效性验证（不超过最大尺寸）
    if (row < 5 || row > MAX_ROW ||
        col < 5 || col > MAX_COL ||
        mineCount < 1 || mineCount >= row * col)
    {
        printf("无效输入! 行数范围5~%d, 列数范围5~%d, 地雷数在1~%d之间\n",
            MAX_ROW, MAX_COL, row * col - 1);
        return;
    }

    // 使用固定最大尺寸数组
    char mine[MAX_ROWS][MAX_COLS];
    char show[MAX_ROWS][MAX_COLS];

    InitBoard(mine, MAX_ROWS, MAX_COLS, '0');
    InitBoard(show, MAX_ROWS, MAX_COLS, '*');

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
            system("color 07");  // 恢复默认颜色
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