#ifndef WIDTH_MAX
#define WIDTH_MAX 150
#endif
#ifndef HEIGHT_MAX
#define HEIGHT_MAX 150
#endif
#define UP (1)
#define RIGHT (1 << 1)
#define DOWN (1 << 2)
#define LEFT (1 << 3)

int maze[WIDTH_MAX][HEIGHT_MAX];
int WIDTH;
int HEIGHT;
int viewedCount = 0;

int getFullBoundFlag(void)
{
	return (UP | RIGHT | DOWN | LEFT);
}

int hasViewed(int content)
{
	return content >> 4 & 1;
}

int getRandomDirection(int y, int x)
{
	int count = 0, k, direction[4];
	for(k = 0; k < 4; k++)
	{
		if (canBreak(y, x, 1 << k))
		{
			direction[count++] = 1 << k;
		}
	}
	if (count == 0){
		return 0;
	}
	return direction[random(0, count - 1)];
}

int canBreak(int y, int x, int direction)
{
	switch (direction)
	{
		case UP:
			if (y == 0 || hasViewed(maze[y-1][x]))
			{
				return 0;
			}
			return 1;
		case RIGHT:
			if (x == WIDTH - 1 || hasViewed(maze[y][x+1]))
			{
				return 0;
			}
			return 1;
		case LEFT:
			if (x == 0 || hasViewed(maze[y][x-1]))
			{
				return 0;
			}
			return 1;
		case DOWN:
			if (y == HEIGHT - 1 || hasViewed(maze[y+1][x]))
			{
				return 0;
			}
			return 1;
	}
	return 0;
}

void breakBound(int y, int x, int direction)
{
	maze[y][x] -= direction;
	if (canBreak(y, x, direction))
	{
		int y1 = getNextY(y, direction);
		int x1 = getNextX(x, direction);
		maze[y1][x1] -= getOppositeDirection(direction);
	}
}

int getNextX(int x, int direction)
{
	switch (direction)
	{
		case UP:
		case DOWN:
			return x;
		case LEFT:
			return x - 1;
		case RIGHT:
			return x + 1;
	}
	return -1;
}

int getNextY(int y, int direction)
{
	switch (direction)
	{
		case LEFT:
		case RIGHT:
			return y;
		case UP:
			return y - 1;
		case DOWN:
			return y + 1;
	}
	return -1;
}

int getOppositeDirection(int direction)
{
	switch (direction)
	{
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		case UP:
			return DOWN;
		case DOWN:
			return UP;
	}
	return -1;
}

void createMaze(int width, int height)
{
	srand((unsigned) time(NULL));
	
	WIDTH = width;
	HEIGHT = height;
	int i, j, k;
	viewedCount = 0;
	
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			maze[i][j] = getFullBoundFlag(); 
		}
	}
	
	breakBound(0, 0, random(0, 1)? UP: LEFT);
	breakBound(HEIGHT - 1, WIDTH - 1, random(0, 1)? RIGHT: DOWN);
	maze[0][0] += 1 << 4;
	viewedCount += 1; 

	int count = 2;
	
	int x = 0, y = 0, scanCount;
	int xx[WIDTH * HEIGHT], yy[WIDTH * HEIGHT];
	search(y, x);

	while (viewedCount < WIDTH * HEIGHT)
	{
		scanCount = 0;
		
		for (i = 0; i < HEIGHT; i++)
		{
			for (j = 0; j < WIDTH; j++)
			{
				if (getRandomDirection(i, j) && hasViewed(maze[i][j]))
				{
					yy[scanCount] = i;
					xx[scanCount] = j;
					scanCount++;
				}
			}
		}
		k = random(0, scanCount - 1);
		x = xx[k]; y = yy[k];

		search(y, x);
	}
}

int getMazeData(int y, int x)
{
	return maze[y][x];
}

void search(int y, int x)
{
	int direction = getRandomDirection(y, x);
	if (direction == 0)
	{
		return;
	}
	breakBound(y, x, direction); 
	int y1 = getNextY(y, direction);
	int x1 = getNextX(x, direction);
	viewedCount++;
	maze[y1][x1] += 1 << 4;
	search(y1, x1);
}


