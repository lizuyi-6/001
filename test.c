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

void game()
{
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	SetMine(mine, ROW, COL,10 );

	DisplayBoard(show, ROW, COL);
	FindMine(mine, show, ROW, COL);
}
void game_2()
{
	char mine[ROWS+7][COLS+7] = { 0 };
	char show[ROWS+7][COLS+7] = { 0 };

	InitBoard(mine, ROWS+7, COLS+7, '0');
	InitBoard(show, ROWS+7, COLS+7, '*');

	SetMine(mine, ROW+7, COL+7,40);

	DisplayBoard(show, ROW+7, COL+7);
	FindMine(mine, show, ROW+7, COL+7);
}
void game_3()
{
	char mine[ROWS + 7][COLS + 21] = { 0 };
	char show[ROWS + 7][COLS + 21] = { 0 };

	InitBoard(mine, ROWS + 7, COLS + 21, '0');
	InitBoard(show, ROWS + 7, COLS + 21, '*');

	SetMine(mine, ROW + 7, COL + 21, 99);

	DisplayBoard(show, ROW + 7, COL + 21);
	FindMine(mine, show, ROW + 7, COL + 21);
}
//void game_4()
//{
//	int row_1, col_1, mineCount;
//	// 提示用户输入自定义参数
//	printf("请输入自定义棋盘的行数：");
//	scanf("%d", &row_1);
//	printf("请输入自定义棋盘的列数：");
//	scanf("%d", &col_1);
//	printf("请输入地雷数量：");
//	scanf("%d", &mineCount);
//
//	// 合法性验证：行数、列数至少为5（避免棋盘过小），地雷数不超过总格子数且不小于1
//	if (row_1 < 5 || col_1 < 5 || mineCount < 1 || mineCount > row_1 * col_1)
//	{
//		printf("输入不合法！行数/列数至少为5，地雷数需在1~%d之间\n", row_1 * col_1);
//		return;
//	}
//
//	// 定义可变长度数组（VLA），存储地雷分布和显示面板
//	char mine[row_1][col_1] = { 0 };
//	char show[row_1][col] = { 0 };
//
//	// 初始化棋盘
//	InitBoard(mine, row, col, '0');
//	InitBoard(show, row, col, '*');
//
//	// 设置地雷
//	SetMine(mine, row, col, mineCount);
//
//	// 显示棋盘
//	DisplayBoard(show, row, col);
//
//	// 开始扫雷逻辑
//	FindMine(mine, show, row, col);
//}
int main()
{
	int input = 0;
	int input_2 = 0;
	srand((unsigned int)time(NULL));
	do
	{
		system("color");
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		system("cls");
		switch (input)
		{
		case 1:
		{
			choice();
			scanf("%d", &input_2);
			system("cls");
			switch (input_2)
			{
			case 1:
				game();
				input = 0;
				break;
			case 2:
				game_2();
					input = 0;
				break;
			case 3:
				game_3();
				input = 0;
				break;
			case 4:
				printf("暂时弃用");
				//game_4();
				return 0;
				break;
			default:
				printf("选择错误\n");
				break;
			}
			break;
		}
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误\n");
			break;
		}
	} while (input);

	return 0;
}