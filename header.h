#define MAZE_UP (1)
#define MAZE_RIGHT (1 << 1)
#define MAZE_DOWN (1 << 2)
#define MAZE_LEFT (1 << 3)
#define MAZE_MAX_WIDTH 150
#define MAZE_MAX_HEIGHT 150
#define TRUE 1
#define FALSE 0
#define INVALID -1

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void Draw_SetWidthAndHeight(int width, int height);
void DRAW_DrawPoint(int x, int y);
void DRAW_DrawLine(int x1, int y1, int x2, int y2);
void DRAW_DrawCircle(int x, int y, int r);
void DRAW_EndDraw();
void DRAW_BeginDraw();
void DRAW_SetTitle(char* title);
void DRAW_SetColor(int R, int G, int B);
void Draw_SetIconColor(int R, int G, int B);
void DRAW_SetDrawIconInBackground(int drawIcon);

int MAZE_GetFullBoundFlag(void);
int MAZE_HasViewed(int content);
int MAZE_GetRandomDirection(int y, int x);
int MAZE_CanBreakBound(int y, int x, int direction);
int MAZE_GetWidth();
int MAZE_GetHeight();
void MAZE_BreakBound(int y, int x, int direction);
int MAZE_GetNextX(int x, int direction);
int MAZE_GetNextY(int y, int direction);
int MAZE_GetOppositeDirection(int direction);
void MAZE_CreateNewMaze(int width, int height);
void MAZE_Search(int y, int x);
int MAZE_GetMazeData(int y, int x);

int SOLVE_IfMove(int y, int x, int direction);
void SOLVE_Mark(int y,int x);
void SOLVE_FindWay(int y,int x);
int SOLVE_GetSolvedMazeData(int y, int x);
void SOLVE_CopyMaze();

int MAIN_GetRandomNumber(int min, int max);
void MAIN_PrintResult();

#include "draw.h"
#include "maze.h"
#include "mazeSolver.h"
