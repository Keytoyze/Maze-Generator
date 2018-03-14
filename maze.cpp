#define WIDTH_MAX 150
#define HEIGHT_MAX 150

int maze [HEIGHT_MAX][WIDTH_MAX];
	/*共有五个二进制位。
	其中，第一个二进制位表示该格是否被遍历，是表示1， 否表示0 
	后四个二进制位表示一个格子的边界（上右下左）， 如1010表示上、下有边界，左右没有。*/ 
	
int WIDTH = 120, HEIGHT = 120;
	
#include "header.h"

int viewedCount = 0;   /*表示已遍历个数*/ 

int maxDepth = 10;



int main(void){
	while(true){
		
		viewedCount = 0;
		
		srand((unsigned) time(NULL));
		printf("请输入迷宫的宽度 （不超过%d格）：", WIDTH_MAX);
		scanf("%d", &WIDTH);
		printf("请输入迷宫的长度 （不超过%d格）：", HEIGHT_MAX);
		scanf("%d", &HEIGHT);
		printf("开始随机生成迷宫...\n");
		
		int i, j, k;
		for(i = 0; i < HEIGHT; i++){
			for(j = 0; j < WIDTH; j++){
				maze[i][j] = getFullBoundFlag(); // = 1111，初始时每面都有边界 
			}
		}
		
		breakBound(0, 0, random(0, 1)? UP: LEFT);
		breakBound(HEIGHT - 1, WIDTH - 1, random(0, 1)? RIGHT: DOWN);
		maze[0][0] += 1 << 4;
		viewedCount++; 
	
		int count = 2;
		
		int x = 0, y = 0, scanCount;
		int xx[WIDTH * HEIGHT], yy[WIDTH * HEIGHT];
		search(y, x, maxDepth);
	
		while(viewedCount < WIDTH * HEIGHT){
			scanCount = 0;
			
			for(i = 0; i < HEIGHT; i++){
				for(j = 0; j < WIDTH; j++){
					if(getRandomDirection(i, j) && hasViewed(maze[i][j])){
						yy[scanCount] = i;
						xx[scanCount] = j;
						scanCount++;
					}
				}
			}
			k = random(0, scanCount - 1);
			x = xx[k]; y = yy[k];
	
			search(y, x, maxDepth);
			
		}
		
		printf("生成成功！正在绘制迷宫界面...\n\n");
		printResult();
	}
}

int random(int min, int max){
	return min + rand() % (max - min + 1);
}

void search(int y, int x, int maxDepth){
	int direction = getRandomDirection(y, x);
	if(direction == 0){
		return;
	}
	if(random(1, maxDepth) == 1){
		return;
	}
	breakBound(y, x, direction); 
	int y1 = getNextY(y, direction);
	int x1 = getNextX(x, direction);
	viewedCount++;
	maze[y1][x1] += 1 << 4;
	search(y1, x1, maxDepth);
}

void printResult(){
	int left = 20;
	int top = 20;
	int heightCell = 900/HEIGHT;
	int widthCell = heightCell;
	
	
	beginDraw();
	setTitle("迷宫");
	setColor(0, 255, 255);
	setWidthAndHeight(left * 2 + widthCell * WIDTH, top * 2 + heightCell * HEIGHT);
	int i, j;
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
			if (maze[i][j] & UP){
				drawLine(left + j * widthCell, top + i * heightCell, left + (j + 1) * widthCell, top + i * heightCell);
			}
			if (maze[i][j] & DOWN){
				drawLine(left + j * widthCell, top + (i + 1) * heightCell, left + (j + 1) * widthCell, top + (i + 1) * heightCell);
			}
			if (maze[i][j] & LEFT){
				drawLine(left + j * widthCell, top + i * heightCell, left + j * widthCell, top + (i + 1) * heightCell);
			}
			if (maze[i][j] & RIGHT){
				drawLine(left + (j + 1) * widthCell, top + i * heightCell, left + (j + 1) * widthCell, top + (i + 1) * heightCell);
			}
		}
	}
	endDraw();
}



