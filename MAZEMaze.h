int m_asMaze[MAZE_MAX_WIDTH][MAZE_MAX_HEIGHT];
int m_sWidth;
int m_sHeight;
int m_sViewedCount = 0;

int MAZE_GetFullBoundFlag(void)//初始化每个点，所有方向都是墙
{
	return (MAZE_UP | MAZE_RIGHT | MAZE_DOWN | MAZE_LEFT);
}

int MAZE_HasViewed(int content)//判断该点是否已经经过了
{
	return content >> 4 & 1;
}

int MAZE_GetRandomDirection(int y, int x)//随机获取一个有墙的方向 
{
	int sCount = 0, k, asDirection[4];
	for(k = 0; k < 4; k++)
	{
		if (MAZE_CanBreakBound(y, x, 1 << k) == TRUE)
		{
			asDirection[sCount++] = 1 << k;
		}
	}
	if (sCount == 0){
		return 0;
	}
	return asDirection[MAIN_GetRandomNumber(0, sCount - 1)];
}

int MAZE_CanBreakBound(int y, int x, int direction)//用来判断该方向是否可以行进的函数
{
	switch (direction)
	{
		case MAZE_UP:
			if (y == 0 || MAZE_HasViewed(m_asMaze[y-1][x]))//如果到达了边界或者该点已经经过了就判断该方向不能行进 
			{
				return FALSE;
			}
			return TRUE;
		case MAZE_RIGHT:
			if (x == m_sWidth - 1 || MAZE_HasViewed(m_asMaze[y][x+1]))
			{
				return FALSE;
			}
			return TRUE;
		case MAZE_LEFT:
			if (x == 0 || MAZE_HasViewed(m_asMaze[y][x-1]))
			{
				return FALSE;
			}
			return TRUE;
		case MAZE_DOWN:
			if (y == m_sHeight - 1 || MAZE_HasViewed(m_asMaze[y+1][x]))
			{
				return FALSE;
			}
			return TRUE;
	}
	return FALSE;
}

void MAZE_BreakBound(int y, int x, int direction)//将该点的该方判断为可以行进，因此反过来也要判断为可以行进，也就是将两点之间的墙打破   
{
	m_asMaze[y][x] -= direction;
	if (MAZE_CanBreakBound(y, x, direction))
	{
		int y1 = MAZE_GetNextY(y, direction);
		int x1 = MAZE_GetNextX(x, direction);
		m_asMaze[y1][x1] -= MAZE_GetOppositeDirection(direction);
	}
}

int MAZE_GetNextX(int x, int direction)//得到下个点的横坐标 
{
	switch (direction)
	{
		case MAZE_UP:
		case MAZE_DOWN:
			return x;
		case MAZE_LEFT:
			return x - 1;
		case MAZE_RIGHT:
			return x + 1;
	}
	return INVALID;
}

int MAZE_GetNextY(int y, int direction)//得到下个点的纵坐标 
{
	switch (direction)
	{
		case MAZE_LEFT:
		case MAZE_RIGHT:
			return y;
		case MAZE_UP:
			return y - 1;
		case MAZE_DOWN:
			return y + 1;
	}
	return INVALID;
}

int MAZE_GetOppositeDirection(int direction)//得到相反的方向
{
	switch (direction)
	{
		case MAZE_LEFT:
			return MAZE_RIGHT;
		case MAZE_RIGHT:
			return MAZE_LEFT;
		case MAZE_UP:
			return MAZE_DOWN;
		case MAZE_DOWN:
			return MAZE_UP;
	}
	return INVALID;
}

void MAZE_CreateNewMaze(int width, int height)//迷宫生成的主体程序
{
	srand((unsigned) time(NULL));
	
	m_sWidth = width;
	m_sHeight = height;
	m_sViewedCount = 0;//记录已经行进过的点的数目 
	
	int i, j, k;
	
	for (i = 0; i < m_sHeight; i++)
	{
		for (j = 0; j < m_sWidth; j++)
		{
			m_asMaze[i][j] = MAZE_GetFullBoundFlag(); //先规定每个格子的四周都是墙
		}
	}
	
	MAZE_BreakBound(0, 0, MAIN_GetRandomNumber(0, 1)? MAZE_UP: MAZE_LEFT);
	MAZE_BreakBound(m_sHeight - 1, m_sWidth - 1, MAIN_GetRandomNumber(0, 1)? MAZE_RIGHT: MAZE_DOWN);
	//得到从起点出发的方向和到终点进入的方向，并将该方向的墙打破   
	m_asMaze[0][0] += 1 << 4;
	m_sViewedCount += 1; 

	int count = 2;
	
	int x = 0, y = 0, sScanCount;
	int xx[m_sWidth * m_sHeight], yy[m_sWidth * m_sHeight];
	MAZE_Search(y, x);//开始从起点建造迷宫

	while (m_sViewedCount < m_sWidth * m_sHeight)//如果迷宫内还有点没有被判断过，就继续建造迷宫，否则可能造成某点四面都是墙   
	{
		sScanCount = 0;
		
		for (i = 0; i < m_sHeight; i++)
		{
			for (j = 0; j < m_sWidth; j++)
			{
				if (MAZE_GetRandomDirection(i, j) && MAZE_HasViewed(m_asMaze[i][j]))
				{
					yy[sScanCount] = i;
					xx[sScanCount] = j;
					sScanCount++;
				}
			}
		}
		k = MAIN_GetRandomNumber(0, sScanCount - 1);
		x = xx[k]; y = yy[k];

		MAZE_Search(y, x);
	}
}

int MAZE_GetMazeData(int y, int x)
{
	return m_asMaze[y][x];
}

void MAZE_Search(int y, int x)//建造迷宫的主要函数，用于递归 
{
	int direction = MAZE_GetRandomDirection(y, x);
	if (direction == 0)
	{
		return;
	}
	MAZE_BreakBound(y, x, direction); //将该点得到的随机方向判断为可以行进
	int y1 = MAZE_GetNextY(y, direction);
	int x1 = MAZE_GetNextX(x, direction);
	m_sViewedCount++;
	m_asMaze[y1][x1] += 1 << 4;
	MAZE_Search(y1, x1);//递归，搜索下一个点 
}

int MAZE_GetWidth()
{
	return m_sWidth;
}

int MAZE_GetHeight()
{
	return m_sHeight;
}


