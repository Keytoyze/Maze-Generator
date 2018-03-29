#include "header.h"

int main(void)
{
	int sC;
	int sHeight;
	int sWidth;
	printf("\n=================�Թ�=================\n\n  �������볤�����100�Ի���������\n"); 
	while(TRUE)
	{
		printf("\n======================================\n\n");
		do {
			printf("�������Թ��Ŀ�� ��������%d�񣩣�", MAZE_MAX_WIDTH);
			scanf("%d", &sWidth);
		} while (sWidth < 2 || sWidth > MAZE_MAX_WIDTH);

		do {
			printf("�������Թ��ĳ��� ��������%d�񣩣�", MAZE_MAX_HEIGHT);
			scanf("%d", &sHeight);
		} while (sHeight < 2 || sHeight > MAZE_MAX_HEIGHT);

		printf("��������Թ�...");
		
		MAZE_CreateNewMaze(sWidth, sHeight);
		
		printf("    �ɹ���\n�����Թ�·��...");
		SOLVE_CopyMaze();
		SOLVE_Mark(0,0);
		SOLVE_FindWay(0,0);
		
		printf("    �ɹ���\n�����Թ�����...\n\n");
		MAIN_PrintResult();
		printf("���������ȥ�Ĳ�����\n[1]��������\n[2]��������\n");
		scanf("%d", &sC);
		if (sC != 1) {
			break;
		}
	}
}

int MAIN_GetRandomNumber(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void MAIN_PrintResult()
{
	int sLeft = 20;
	int sTop = 20;
	int sHeightCell = 900/MAZE_GetHeight();
	int sWidthCell = sHeightCell;
	char acMazeTitle[] = "maze";
	
	DRAW_BeginDraw();
	DRAW_SetTitle(acMazeTitle);
	DRAW_SetColor(200, 200, 0);
	DRAW_SetWidthAndHeight(sLeft * 2 + sWidthCell * MAZE_GetWidth(), sTop * 2 + sHeightCell * MAZE_GetHeight());
	DRAW_SetDrawIconInBackground(TRUE);
	DRAW_SetIconColor(0, 255, 255);
	int i, j;
	for(i = 0; i < MAZE_GetHeight(); i++) 
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
				//DRAW_DrawLine(sLeft + j* sWidthCell, sTop + (i+0.5) * sHeightCell, sLeft + (j+0.5) * sWidthCell, sTop + (i+1)* sHeightCell);
				//DRAW_DrawLine(sLeft + j * sWidthCell, sTop + i * sHeightCell, sLeft + (j+ 1) * sWidthCell, sTop + (i+1) * sHeightCell);
				//DRAW_DrawLine(sLeft + (j+0.5) * sWidthCell, sTop + i * sHeightCell, sLeft + (j + 1) * sWidthCell, sTop + (i+0.5) * sHeightCell);
				//DRAW_DrawLine(sLeft + (j+0.75) * sWidthCell, sTop + i * sHeightCell, sLeft + (j + 1) * sWidthCell, sTop + (i+0.25) * sHeightCell);
				//DRAW_DrawLine(sLeft + (j+0.25) * sWidthCell, sTop + i * sHeightCell, sLeft + (j + 1) * sWidthCell, sTop + (i+0.75) * sHeightCell);
				//DRAW_DrawLine(sLeft + j* sWidthCell, sTop + (i+0.75) * sHeightCell, sLeft + (j+0.25) * sWidthCell, sTop + (i+1)* sHeightCell);
				//DRAW_DrawLine(sLeft + j* sWidthCell, sTop + (i+0.25) * sHeightCell, sLeft + (j+0.75) * sWidthCell, sTop + (i+1)* sHeightCell);
				DRAW_DrawCircle(sLeft+(j+0.5)*sHeightCell, sTop+(i+0.5)*sWidthCell, sHeightCell/3);
			}
		}
	}
	DRAW_EndDraw();
}



