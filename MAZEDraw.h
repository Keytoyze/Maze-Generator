FILE* file;
void DRAW_DrawPoint(int x, int y)//根据给定坐标绘制点 
{
	fprintf(file, "point %d %d\n", x, y);
}
void DRAW_DrawLine(int x1, int y1, int x2, int y2)//根据给定头尾点的坐标绘制线 
{
	fprintf(file, "line %d %d %d %d\n", x1, y1, x2, y2);
}
void DRAW_DrawCircle(int x, int y, int r)//根据给定的圆心坐标和半径绘制实心圆 
{
	fprintf(file, "circle %d %d %d\n", x, y, r);
} 
void DRAW_SetWidthAndHeight(int width, int height)//设置图形窗口的长宽 
{
	fprintf(file, "setWidthAndHeight %d %d\n", width, height);
}
void DRAW_SetTitle(char* title)//设置窗口标题 
{
	fprintf(file, "title %s\n", title);
}
void DRAW_SetColor(int R, int G, int B)//设置绘制点的颜色 
{
	fprintf(file, "color %d %d %d\n", R, G, B);
}
void DRAW_SetIconColor(int R, int G, int B)//设置背景图标的颜色 
{
	fprintf(file, "iconColor %d %d %d\n", R, G, B);
}
void DRAW_SetDrawIconInBackground(int drawIcon)//设置是否在背景画上图标 
{
	fprintf(file, "drawIcon %d\n", drawIcon);
}
void DRAW_BeginDraw()//开始绘制。此处打开一个文件， 用于传输绘制数据至图形库 
{
	file = fopen("lib\\drawData.dat", "w"); 
}
void DRAW_EndDraw()//结束绘制。关闭文件，并且调用图形库显示迷宫 
{
	fclose(file);
	system("lib\\win.exe");
}

