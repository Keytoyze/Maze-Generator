#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void setWidthAndHeight(int width, int height);
void drawPoint(int x, int y);
void drawLine(int x1, int y1, int x2, int y2);
void endDraw();
void beginDraw();
void setTitle(char* title);
void setColor(int R, int G, int B);
int getFullBoundFlag(void);
int canBreak(int y, int x, int direction);
int random(int min, int max);
int canBreak(int y, int x, int direction);
int getNextX(int x, int direction);
int getNextY(int y, int direction);
int getOppositeDirection(int direction);
void search(int y, int x, int maxDepth);
void printResult();
#include "draw.h"
#include "maze.h"
