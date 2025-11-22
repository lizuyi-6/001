#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

// 初始化棋盘（按实际尺寸初始化）
void InitBoard(char board[][MAX_COLS], int r, int c, char set)
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

// 显示棋盘（按实际尺寸显示）
void DisplayBoard(char board[][MAX_COLS], int r, int c)
{
    int i = 0;
    printf("--------扫雷游戏--------\n");
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

// 设置地雷（按实际尺寸设置）
void SetMine(char mine[][MAX_COLS], int r, int c, int count)
{
    while (count > 0)
    {
        // 生成1~r和1~c范围内的随机坐标
        int x = rand() % r + 1;
        int y = rand() % c + 1;
        // 确保该位置未设置地雷
        if (mine[x][y] == '0')
        {
            mine[x][y] = '1';
            count--;
        }
    }
}

// 计算(x,y)周围8个位置的地雷数量
static int GetMineCount(char mine[][MAX_COLS], int x, int y)
{
    return (mine[x - 1][y - 1] - '0') +
        (mine[x - 1][y] - '0') +
        (mine[x - 1][y + 1] - '0') +
        (mine[x][y - 1] - '0') +
        (mine[x][y + 1] - '0') +
        (mine[x + 1][y - 1] - '0') +
        (mine[x + 1][y] - '0') +
        (mine[x + 1][y + 1] - '0');
}

// 递归展开无雷区域
static void Expand(char mine[][MAX_COLS], char show[][MAX_COLS], int x, int y, int r, int c)
{
    // 检查坐标是否在有效范围1~r，1~c内
    if (x < 1 || x > r || y < 1 || y > c)
        return;

    // 已展开的位置直接返回，避免重复处理
    if (show[x][y] != '*')
        return;

    // 计算当前位置周围地雷数
    int count = GetMineCount(mine, x, y);

    if (count > 0)
    {
        // 有地雷，显示数量不展开
        show[x][y] = count + '0';
    }
    else
    {
        // 无地雷，显示空格并递归展开8个方向
        show[x][y] = ' ';
        Expand(mine, show, x - 1, y - 1, r, c);
        Expand(mine, show, x - 1, y, r, c);
        Expand(mine, show, x - 1, y + 1, r, c);
        Expand(mine, show, x, y - 1, r, c);
        Expand(mine, show, x, y + 1, r, c);
        Expand(mine, show, x + 1, y - 1, r, c);
        Expand(mine, show, x + 1, y, r, c);
        Expand(mine, show, x + 1, y + 1, r, c);
    }
}

// 扫雷核心逻辑
void FindMine(char mine[][MAX_COLS], char show[][MAX_COLS], int r, int c, int mine_count)
{
    int x = 0;
    int y = 0;
    int win = 0;  // 已扫雷的格子数量

    // 循环条件：已扫格子数 < 总格子数 - 地雷数
    while (win < r * c - mine_count)
    {
        printf("请输入要排查的坐标:");
        scanf("%d %d", &x, &y);

        // 检查坐标有效性
        if (x >= 1 && x <= r && y >= 1 && y <= c)
        {
            if (mine[x][y] == '1')
            {
                // 踩雷，游戏结束
                system("cls");
                system("color 04");  // 红色显示
                printf("很遗憾，你被炸死了!\n");
                DisplayBoard(mine, r, c);  // 显示所有地雷位置
                exit(0);
            }
            else
            {
                // 未踩雷且未排查过
                if (show[x][y] == '*')
                {
                    Expand(mine, show, x, y, r, c);  // 展开无雷区域
                    system("cls");
                    DisplayBoard(show, r, c);

                    // 统计已排查的格子数
                    win = 0;
                    for (int i = 1; i <= r; i++)
                    {
                        for (int j = 1; j <= c; j++)
                        {
                            if (show[i][j] != '*')
                                win++;
                        }
                    }
                }
                else
                {
                    printf("该位置已排查，请重新输入!\n");
                }
            }
        }
        else
        {
            printf("坐标无效，请输入1~%d和1~%d之间的坐标!\n", r, c);
        }
    }

    // 判断是否胜利
    if (win == r * c - mine_count)
    {
        system("color 0A");  // 绿色显示
        printf("恭喜你，排雷成功!\n");
        DisplayBoard(mine, r, c);
    }
}