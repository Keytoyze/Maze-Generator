#define WIDTH_MAX 150
#define HEIGHT_MAX 150
#include "header.h"

int main(void)
{
	int c;
	printf("===========�Թ�===========\n\n�������볤�����100�Ի��������顣\n"); 
	while(true)
	{
		printf("\n==========================\n");
		do {
			printf("�������Թ��Ŀ�� ��������%d�񣩣�", WIDTH_MAX);
			scanf("%d", &WIDTH);
		} while (WIDTH < 2 || WIDTH > WIDTH_MAX);

		do {
			printf("�������Թ��ĳ��� ��������%d�񣩣�", HEIGHT_MAX);
			scanf("%d", &HEIGHT);
		} while (HEIGHT < 2 || HEIGHT > HEIGHT_MAX);

		printf("��ʼ��������Թ�...\n");
		
		createMaze(WIDTH, HEIGHT);
		copyMaze();
		mark(0,0);
		findway(0,0);
		
		printf("���ɳɹ������ڻ����Թ�����...\n\n");
		printResult();
		printf("���������ȥ�Ĳ�����\n[1]��������\n[2]��������\n");
		scanf("%d", &c);
		if (c != 1) {
			break;
		}
	}
}

int random(int min, int max)
{
	return min + rand() % (max - min + 1);
}

void printResult()
{
	int left = 20;
	int top = 20;
	int heightCell = 900/HEIGHT;
	int widthCell = heightCell;
	char mazeTitle[] = "maze";
	
	beginDraw();
	setTitle(mazeTitle);
	setColor(200, 200, 0);
	setWidthAndHeight(left * 2 + widthCell * WIDTH, top * 2 + heightCell * HEIGHT);
	setDrawIconInBackground(1);
	setIconColor(0, 255, 255);
	int i, j;
	for(i = 0; i < HEIGHT; i++) 
	{
		for(j = 0; j < WIDTH; j++)
		{
			if (getMazeData(i, j) & UP)
			{
				drawLine(left + j * widthCell, top + i * heightCell, left + (j + 1) * widthCell, top + i * heightCell);
			}
			if (getMazeData(i, j) & DOWN)
			{
				drawLine(left + j * widthCell, top + (i + 1) * heightCell, left + (j + 1) * widthCell, top + (i + 1) * heightCell);
			}
			if (getMazeData(i, j) & LEFT)
			{
				drawLine(left + j * widthCell, top + i * heightCell, left + j * widthCell, top + (i + 1) * heightCell);
			}
			if (getMazeData(i, j) & RIGHT)
			{
				drawLine(left + (j + 1) * widthCell, top + i * heightCell, left + (j + 1) * widthCell, top + (i + 1) * heightCell);
			}
		}
	}
	setDrawIconInBackground(0); 
	setColor(255, 0, 0);
	for(i = 0; i < HEIGHT; i++)
	{
		for(j = 0; j < WIDTH; j++)
		{
			if (getSolvedMazeData(i, j) >=64)
			{
				//drawLine(left + j* widthCell, top + (i+0.5) * heightCell, left + (j+0.5) * widthCell, top + (i+1)* heightCell);
				//drawLine(left + j * widthCell, top + i * heightCell, left + (j+ 1) * widthCell, top + (i+1) * heightCell);
				//drawLine(left + (j+0.5) * widthCell, top + i * heightCell, left + (j + 1) * widthCell, top + (i+0.5) * heightCell);
				//drawLine(left + (j+0.75) * widthCell, top + i * heightCell, left + (j + 1) * widthCell, top + (i+0.25) * heightCell);
				//drawLine(left + (j+0.25) * widthCell, top + i * heightCell, left + (j + 1) * widthCell, top + (i+0.75) * heightCell);
				//drawLine(left + j* widthCell, top + (i+0.75) * heightCell, left + (j+0.25) * widthCell, top + (i+1)* heightCell);
				//drawLine(left + j* widthCell, top + (i+0.25) * heightCell, left + (j+0.75) * widthCell, top + (i+1)* heightCell);
				drawCircle(left+(j+0.5)*heightCell, top+(i+0.5)*widthCell, heightCell/3);
			}
		}
	}
	endDraw();
}



