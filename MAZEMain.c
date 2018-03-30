#include "MAZEHeader.h"

int main(void)
{
	int sC;
	int sHeight;
	int sWidth;
	printf("\n=================迷宫=================\n\n  建议输入长宽大于100以获得最佳体验\n"); 
	while(TRUE)
	{
		printf("\n======================================\n\n");
		do {
			printf("请输入迷宫的宽度 （不超过%d格）：", MAZE_MAX_WIDTH);
			scanf("%d", &sWidth);
		} while (sWidth < 2 || sWidth > MAZE_MAX_WIDTH);

		do {
			printf("请输入迷宫的长度 （不超过%d格）：", MAZE_MAX_HEIGHT);
			scanf("%d", &sHeight);
		} while (sHeight < 2 || sHeight > MAZE_MAX_HEIGHT);

		printf("随机生成迷宫...");//建造迷宫时的提示，注意迷宫的最大规格
		
		MAZE_CreateNewMaze(sWidth, sHeight);
		
		printf("    成功！\n生成迷宫路径...");
		SOLVE_CopyMaze();//搜索迷宫的出路   
		SOLVE_Mark(0,0);
		SOLVE_FindWay(0,0);
		
		printf("    成功！\n绘制迷宫界面...\n\n");
		MAIN_PrintResult();//输出生成得到的迷宫 
		printf("请输入接下去的操作：\n[1]继续生成\n[2]结束程序\n");
		scanf("%d", &sC);
		if (sC != 1) {
			break;
		}
	}
}

int MAIN_GetRandomNumber(int min, int max)//自定义的一个随机函数，产生max到min中间的随机数
{
	return min + rand() % (max - min + 1);
}

void MAIN_PrintResult()
{
	int sLeft = 20;
	int sTop = 20;
	int sHeightCell = 800/MAZE_GetHeight();
	int sWidthCell = sHeightCell;
	char acMazeTitle[] = "maze";
	
	DRAW_BeginDraw();//开始绘制迷宫
	DRAW_SetTitle(acMazeTitle);
	DRAW_SetColor(200, 200, 0);
	DRAW_SetWidthAndHeight(sLeft * 2 + sWidthCell * MAZE_GetWidth(), sTop * 2 + sHeightCell * MAZE_GetHeight());
	DRAW_SetDrawIconInBackground(TRUE);
	DRAW_SetIconColor(0, 255, 255);
	int i, j;
	for(i = 0; i < MAZE_GetHeight(); i++) //输出迷宫的出路，迷宫中是第7位二进制的点就输出，连起来就是迷宫的通路   
	{
		for(j = 0; j < MAZE_GetWidth(); j++)
		{
			if (MAZE_GetMazeData(i, j) & MAZE_UP)
			{
				DRAW_DrawLine(sLeft + j * sWidthCell, sTop + i * sHeightCell, sLeft + (j + 1) * sWidthCell, sTop + i * sHeightCell);
			}
			if (MAZE_GetMazeData(i, j) & MAZE_DOWN)
			{
				DRAW_DrawLine(sLeft + j * sWidthCell, sTop + (i + 1) * sHeightCell, sLeft + (j + 1) * sWidthCell, sTop + (i + 1) * sHeightCell);
			}
			if (MAZE_GetMazeData(i, j) & MAZE_LEFT)
			{
				DRAW_DrawLine(sLeft + j * sWidthCell, sTop + i * sHeightCell, sLeft + j * sWidthCell, sTop + (i + 1) * sHeightCell);
			}
			if (MAZE_GetMazeData(i, j) & MAZE_RIGHT)
			{
				DRAW_DrawLine(sLeft + (j + 1) * sWidthCell, sTop + i * sHeightCell, sLeft + (j + 1) * sWidthCell, sTop + (i + 1) * sHeightCell);
			}
		}
	}
	DRAW_SetDrawIconInBackground(FALSE); 
	DRAW_SetColor(255, 0, 0);
	for(i = 0; i < MAZE_GetHeight(); i++)
	{
		for(j = 0; j < MAZE_GetWidth(); j++)
		{
			if (SOLVE_GetSolvedMazeData(i, j) >=64)
			{
				DRAW_DrawCircle(sLeft+(j+0.5)*sHeightCell, sTop+(i+0.5)*sWidthCell, sHeightCell/3);
			}
		}
	}
	DRAW_EndDraw();//结束迷宫的绘制
}



