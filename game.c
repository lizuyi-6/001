#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

// 初始化棋盘
void InitBoard(char board[ROWS][COLS], int r, int c, char set)
{
    int i = 0;
    for (i = 0; i < r; i++)
    {
        int j = 0;
        for (j = 0; j < c; j++)
        {
            board[i][j] = set;
        }
    }
}

// 显示棋盘
void DisplayBoard(char board[ROWS][COLS], int r, int c)
{
    int i = 0;
    printf("--------扫雷--------\n");
    // 打印列号
    for (i = 0; i <= c; i++)
    {
        printf("%3d ", i);
    }
    printf("\n");
    // 打印行号和棋盘内容
    for (i = 1; i <= r; i++)
    {
        int j = 0;
        printf("%3d ", i);  // 打印行号
        for (j = 1; j <= c; j++)
        {
            printf("%3c ", board[i][j]);
        }
        printf("\n");
    }
}

// 设置地雷
void SetMine(char mine[ROWS][COLS], int r, int c,int de)
{
    int count = de;
    while (count)
    {
        // 生成1~r和1~c范围内的随机坐标
        int x = rand() % r + 1;
        int y = rand() % c + 1;
        // 确保该位置未设置过地雷
        if (mine[x][y] == '0')
        {
            mine[x][y] = '1';
            count--;
        }
    }
}

// 计算(x,y)周围8个方向的地雷数量
static int GetMineCount(char mine[ROWS][COLS], int x, int y)
{
    // 利用ROWS和COLS的额外行/列（0和r+1行，0和c+1列）避免越界判断
    return (mine[x - 1][y - 1] - '0') +
        (mine[x - 1][y] - '0') +
        (mine[x - 1][y + 1] - '0') +
        (mine[x][y - 1] - '0') +
        (mine[x][y + 1] - '0') +
        (mine[x + 1][y - 1] - '0') +
        (mine[x + 1][y] - '0') +
        (mine[x + 1][y + 1] - '0');
}

// 递归展开周围无雷的格子
static void Expand(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y, int r, int c)
{
    // 1. 坐标合法性检查（仅处理游戏区1~r行，1~c列）
    if (x < 1 || x > r || y < 1 || y > c)
        return;

    // 2. 如果已经展开过，直接返回（避免重复处理）
    if (show[x][y] != '*')
        return;

    // 3. 计算当前格子周围的地雷数
    int count = GetMineCount(mine, x, y);

    if (count > 0)
    {
        // 周围有地雷：显示地雷数量，不继续展开
        show[x][y] = count + '0';
    }
    else
    {
        // 周围无地雷：显示空格，并递归展开8个方向的格子
        show[x][y] = ' ';  // 用空格表示周围无雷

        // 遍历8个方向（上/下/左/右/四个对角线）
        Expand(mine, show, x - 1, y - 1, r, c);  // 左上
        Expand(mine, show, x - 1, y, r, c);    // 上
        Expand(mine, show, x - 1, y + 1, r, c);  // 右上
        Expand(mine, show, x, y - 1, r, c);    // 左
        Expand(mine, show, x, y + 1, r, c);    // 右
        Expand(mine, show, x + 1, y - 1, r, c);  // 左下
        Expand(mine, show, x + 1, y, r, c);    // 下
        Expand(mine, show, x + 1, y + 1, r, c);  // 右下
    }
}

// 排查地雷逻辑
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c)
{
    int x = 0;
    int y = 0;
    int win = 0;  // 已排查的非雷格子数量

    while (win < r * c - EASY_COUNT)  // 总格子数 - 地雷数 = 需排查的非雷格子数
    {
        printf("请输入要排查的坐标:");
        scanf("%d %d", &x, &y);

        // 坐标合法性检查
        if (x >= 1 && x <= r && y >= 1 && y <= c)
        {
            if (mine[x][y] == '1')
            {
                // 踩中地雷，游戏结束
                system("cls");
                system("color 04");
                printf("很遗憾，你被炸死了\n");
                DisplayBoard(mine, r, c);  // 显示所有地雷位置
                break;
            }
            else
            {
                // 未踩中地雷，且该位置未排查过
                if (show[x][y] == '*')
                {
                    // 调用展开函数，处理当前格子及周围可展开的格子
                    Expand(mine, show, x, y, r, c);
                    // 显示更新后的棋盘
                    system("cls");
                    DisplayBoard(show, r, c);
                    // 重新计算已排查的非雷格子数量（因为一次可能展开多个）
                    win = 0;
                    for (int i = 1; i <= r; i++)
                    {
                        for (int j = 1; j <= c; j++)
                        {
                            if (show[i][j] != '*')  // 已展开的格子（非'*'）
                                win++;
                        }
                    }
                }
                else
                {
                    printf("该坐标已经被排查过，重新输入坐标\n");
                }
            }
        }
        else
        {
            printf("输入的坐标非法，请重新输入\n");
        }
    }

    // 判断是否胜利
    if (win == r * c - EASY_COUNT)
    {
        system("color 0A");
        printf("恭喜你，排雷成功\n");
        DisplayBoard(mine, r, c);
    }
}