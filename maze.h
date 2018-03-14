#define UP (1)
#define RIGHT (1 << 1)
#define DOWN (1 << 2)
#define LEFT (1 << 3)
extern int maze[WIDTH_MAX][HEIGHT_MAX];

int getFullBoundFlag(void){
	return (UP | RIGHT | DOWN | LEFT);
}

int hasViewed(int content){
	return content >> 4 & 1;
}

int getRandomDirection(int y, int x){
	int count = 0, k, direction[4];
	for(k = 0; k < 4; k++){
		if(canBreak(y, x, 1 << k)){
			direction[count++] = 1 << k;
		}
	}
	if(count == 0){
		return 0;
	}
	return direction[random(0, count - 1)];
}

int canBreak(int y, int x, int direction){
	switch(direction){
		case UP:
			if(y == 0 || hasViewed(maze[y-1][x])){
				return 0;
			}
			return 1;
		case RIGHT:
			if(x == WIDTH - 1 || hasViewed(maze[y][x+1])){
				return 0;
			}
			return 1;
		case LEFT:
			if(x == 0 || hasViewed(maze[y][x-1])){
				return 0;
			}
			return 1;
		case DOWN:
			if(y == HEIGHT - 1 || hasViewed(maze[y+1][x])){
				return 0;
			}
			return 1;
	}
	return 0;
}

void breakBound(int y, int x, int direction){
	maze[y][x] -= direction;
	if(canBreak(y, x, direction)){
		int y1 = getNextY(y, direction);
		int x1 = getNextX(x, direction);
		maze[y1][x1] -= getOppositeDirection(direction);
	}
}

int getNextX(int x, int direction){
	switch(direction){
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

int getNextY(int y, int direction){
	switch(direction){
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

int getOppositeDirection(int direction){
	switch(direction){
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


