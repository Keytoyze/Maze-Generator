int m_asTrackMaze [MAZE_MAX_HEIGHT][MAZE_MAX_WIDTH];

int SOLVE_IfMove(int y, int x, int direction)//判断（y，x）点是否可以向direction方向移动
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

void SOLVE_Mark(int y,int x)//标记最终路径，以第7位二进制作为标志 
{
	m_asTrackMaze[y][x]+=64;
}


void SOLVE_FindWay(int y,int x) //递归寻找路径
{
	int i,x1,y2;
	for (i=0; i<=3; i++)//向四个方向都进行尝试
	{
		if (SOLVE_IfMove(y, x, 1 << i))//判断向其中一个方向是否可以移动 
		{
			y2 = MAZE_GetNextY(y, 1<<i);//得出移动后的坐标
			x1 = MAZE_GetNextX(x, 1<<i);
			if (MAZE_GetMazeData(y2, x1) >= 64) continue; //如果移动后的坐标已经被最终路径标识，则不移动并且进行下一方向的探索   
			m_asTrackMaze[y][x] += 1<<i;//成功移动后，在路径上建墙，防止在探索失败前原路返回   
			m_asTrackMaze[y2][x1] += MAZE_GetOppositeDirection(1<<i);//相邻格子的属性也要发生改变
			if ((x1!=MAZE_GetWidth()-1) || (y2!=MAZE_GetHeight()-1))
			{      
				SOLVE_FindWay(y2,x1);  //没到达终点前持续探索 
			}
			else  
			{
				SOLVE_Mark(y2,x1);//到达终点后开始标记
			}
			if (m_asTrackMaze[y2][x1] >= 64) SOLVE_Mark(y,x);	//原路返回的路上持续标记 
			m_asTrackMaze[y2][x1] -= MAZE_GetOppositeDirection(1 << i);//撤墙 原路返回 
			m_asTrackMaze[y][x] -= 1 << i;	     
		}
	}
}

void SOLVE_CopyMaze()//将生成后的迷宫备份
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

int SOLVE_GetSolvedMazeData(int y, int x) //获取生成迷宫
{
	return m_asTrackMaze[y][x];
}
