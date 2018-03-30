int m_asMaze[MAZE_MAX_WIDTH][MAZE_MAX_HEIGHT];
int m_sWidth;
int m_sHeight;
int m_sViewedCount = 0;

int MAZE_GetFullBoundFlag(void)//��ʼ��ÿ���㣬���з�����ǽ
{
	return (MAZE_UP | MAZE_RIGHT | MAZE_DOWN | MAZE_LEFT);
}

int MAZE_HasViewed(int content)//�жϸõ��Ƿ��Ѿ�������
{
	return content >> 4 & 1;
}

int MAZE_GetRandomDirection(int y, int x)//�����ȡһ����ǽ�ķ��� 
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

int MAZE_CanBreakBound(int y, int x, int direction)//�����жϸ÷����Ƿ�����н��ĺ���
{
	switch (direction)
	{
		case MAZE_UP:
			if (y == 0 || MAZE_HasViewed(m_asMaze[y-1][x]))//��������˱߽���߸õ��Ѿ������˾��жϸ÷������н� 
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

void MAZE_BreakBound(int y, int x, int direction)//���õ�ĸ÷��ж�Ϊ�����н�����˷�����ҲҪ�ж�Ϊ�����н���Ҳ���ǽ�����֮���ǽ����   
{
	m_asMaze[y][x] -= direction;
	if (MAZE_CanBreakBound(y, x, direction))
	{
		int y1 = MAZE_GetNextY(y, direction);
		int x1 = MAZE_GetNextX(x, direction);
		m_asMaze[y1][x1] -= MAZE_GetOppositeDirection(direction);
	}
}

int MAZE_GetNextX(int x, int direction)//�õ��¸���ĺ����� 
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

int MAZE_GetNextY(int y, int direction)//�õ��¸���������� 
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

int MAZE_GetOppositeDirection(int direction)//�õ��෴�ķ���
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

void MAZE_CreateNewMaze(int width, int height)//�Թ����ɵ��������
{
	srand((unsigned) time(NULL));
	
	m_sWidth = width;
	m_sHeight = height;
	m_sViewedCount = 0;//��¼�Ѿ��н����ĵ����Ŀ 
	
	int i, j, k;
	
	for (i = 0; i < m_sHeight; i++)
	{
		for (j = 0; j < m_sWidth; j++)
		{
			m_asMaze[i][j] = MAZE_GetFullBoundFlag(); //�ȹ涨ÿ�����ӵ����ܶ���ǽ
		}
	}
	
	MAZE_BreakBound(0, 0, MAIN_GetRandomNumber(0, 1)? MAZE_UP: MAZE_LEFT);
	MAZE_BreakBound(m_sHeight - 1, m_sWidth - 1, MAIN_GetRandomNumber(0, 1)? MAZE_RIGHT: MAZE_DOWN);
	//�õ����������ķ���͵��յ����ķ��򣬲����÷����ǽ����   
	m_asMaze[0][0] += 1 << 4;
	m_sViewedCount += 1; 

	int count = 2;
	
	int x = 0, y = 0, sScanCount;
	int xx[m_sWidth * m_sHeight], yy[m_sWidth * m_sHeight];
	MAZE_Search(y, x);//��ʼ����㽨���Թ�

	while (m_sViewedCount < m_sWidth * m_sHeight)//����Թ��ڻ��е�û�б��жϹ����ͼ��������Թ�������������ĳ�����涼��ǽ   
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

void MAZE_Search(int y, int x)//�����Թ�����Ҫ���������ڵݹ� 
{
	int direction = MAZE_GetRandomDirection(y, x);
	if (direction == 0)
	{
		return;
	}
	MAZE_BreakBound(y, x, direction); //���õ�õ�����������ж�Ϊ�����н�
	int y1 = MAZE_GetNextY(y, direction);
	int x1 = MAZE_GetNextX(x, direction);
	m_sViewedCount++;
	m_asMaze[y1][x1] += 1 << 4;
	MAZE_Search(y1, x1);//�ݹ飬������һ���� 
}

int MAZE_GetWidth()
{
	return m_sWidth;
}

int MAZE_GetHeight()
{
	return m_sHeight;
}


