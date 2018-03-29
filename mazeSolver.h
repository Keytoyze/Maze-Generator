int m_asTrackMaze [MAZE_MAX_HEIGHT][MAZE_MAX_WIDTH];

int SOLVE_IfMove(int y, int x, int direction)
{
	switch(direction)
	{
		case MAZE_UP:
			if(((m_asTrackMaze[y][x]) & MAZE_UP)==0)
			{
				if((y==0) && (x==0)) return 0;
				return 1;
			}
			break;
		case MAZE_DOWN:
			if(((m_asTrackMaze[y][x]) & MAZE_DOWN)==0)
			{
				return 1;
			}
			break;
		case MAZE_RIGHT:
			if(((m_asTrackMaze[y][x]) & MAZE_RIGHT)==0)
			{
				return 1;
			}
			break;
		case MAZE_LEFT:
			if(((m_asTrackMaze[y][x]) & MAZE_LEFT) == 0)
			{
				if((y==0) && (x==0)) return 0;
				return 1;
			}
			break;
	}
	return 0;
}

void SOLVE_Mark(int y,int x)
{
	m_asTrackMaze[y][x]+=64;
}


void SOLVE_FindWay(int y,int x)
{
	int i,x1,y2;
	for (i=0; i<=3; i++)
	{
		if (SOLVE_IfMove(y, x, 1 << i))
		{
			y2 = MAZE_GetNextY(y, 1<<i);
			x1 = MAZE_GetNextX(x, 1<<i);
			if (MAZE_GetMazeData(y2, x1) >= 64) continue;
			m_asTrackMaze[y][x] += 1<<i;
			m_asTrackMaze[y2][x1] += MAZE_GetOppositeDirection(1<<i);
			if ((x1!=MAZE_GetWidth()-1) || (y2!=MAZE_GetHeight()-1))
			{      
				SOLVE_FindWay(y2,x1);  
			}
			else  
			{
				SOLVE_Mark(y2,x1);
			}
			if (m_asTrackMaze[y2][x1] >= 64) SOLVE_Mark(y,x);	
			m_asTrackMaze[y2][x1] -= MAZE_GetOppositeDirection(1 << i);
			m_asTrackMaze[y][x] -= 1 << i;	     
		}
	}
}

void SOLVE_CopyMaze()
{
	int i, j;
	for(i = 0; i < MAZE_GetHeight(); i++)
	{
		for(j = 0; j < MAZE_GetWidth(); j++)
		{
			m_asTrackMaze[i][j] = MAZE_GetMazeData(i, j);
		}
	}
}

int SOLVE_GetSolvedMazeData(int y, int x)
{
	return m_asTrackMaze[y][x];
}
