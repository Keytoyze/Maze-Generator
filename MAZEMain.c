#include "MAZEHeader.h"

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

		printf("��������Թ�...");//�����Թ�ʱ����ʾ��ע���Թ��������
		
		MAZE_CreateNewMaze(sWidth, sHeight);
		
		printf("    �ɹ���\n�����Թ�·��...");
		SOLVE_CopyMaze();//�����Թ��ĳ�·   
		SOLVE_Mark(0,0);
		SOLVE_FindWay(0,0);
		
		printf("    �ɹ���\n�����Թ�����...\n\n");
		MAIN_PrintResult();//������ɵõ����Թ� 
		printf("���������ȥ�Ĳ�����\n[1]��������\n[2]��������\n");
		scanf("%d", &sC);
		if (sC != 1) {
			break;
		}
	}
}

int MAIN_GetRandomNumber(int min, int max)//�Զ����һ���������������max��min�м�������
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
	
	DRAW_BeginDraw();//��ʼ�����Թ�
	DRAW_SetTitle(acMazeTitle);
	DRAW_SetColor(200, 200, 0);
	DRAW_SetWidthAndHeight(sLeft * 2 + sWidthCell * MAZE_GetWidth(), sTop * 2 + sHeightCell * MAZE_GetHeight());
	DRAW_SetDrawIconInBackground(TRUE);
	DRAW_SetIconColor(0, 255, 255);
	int i, j;
	for(i = 0; i < MAZE_GetHeight(); i++) //����Թ��ĳ�·���Թ����ǵ�7λ�����Ƶĵ������������������Թ���ͨ·   
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
	DRAW_EndDraw();//�����Թ��Ļ���
}



