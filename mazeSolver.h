#ifndef WIDTH_MAX
#define WIDTH_MAX 150
#endif
#ifndef HEIGHT_MAX
#define HEIGHT_MAX 150
#endif
int maze1 [HEIGHT_MAX][WIDTH_MAX];

int ifmove(int y, int x, int direction)
{
	switch(direction)
	{
		case UP:
			if(((maze1[y][x]) & UP)==0)
			{
				if((y==0) && (x==0)) return 0;
				return 1;
			}
			break;
		case DOWN:
			if(((maze1[y][x]) & DOWN)==0)
			{
				return 1;
			}
			break;
		case RIGHT:
			if(((maze1[y][x]) & RIGHT)==0)
			{
				return 1;
			}
			break;
		case LEFT:
			if(((maze1[y][x]) & LEFT) == 0)
			{
				if((y==0) && (x==0)) return 0;
				return 1;
			}
			break;
	}
	return 0;
}

void mark(int y,int x)
{
	maze1[y][x]+=64;
}


void findway(int y,int x)
{
	int i,x1,y2;
	for (i=0; i<=3; i++)
	{
		if (ifmove(y, x, 1 << i))
		{
			y2 = getNextY(y, 1<<i);
			x1 = getNextX(x, 1<<i);
			if (maze[y2][x1]>=64) continue;
			maze1[y][x] += 1<<i;
			maze1[y2][x1] += getOppositeDirection(1<<i);
			if ((x1!=WIDTH-1) || (y2!=HEIGHT-1))
			{      
				findway(y2,x1);  
			}
			else  
			{
				mark(y2,x1);
			}
			if (maze1[y2][x1] >= 64) mark(y,x);	
			maze1[y2][x1] -= getOppositeDirection(1 << i);
			maze1[y][x] -= 1 << i;	     
		}
	}
}

void copyMaze()
{
	int i, j;
	for(i = 0; i < HEIGHT; i++)
	{
		for(j = 0; j < WIDTH; j++)
		{
			maze1[i][j]=getMazeData(i, j);
		}
	}
}

int getSolvedMazeData(int y, int x)
{
	return maze1[y][x];
}
