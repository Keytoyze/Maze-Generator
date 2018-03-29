FILE* file;
void DRAW_DrawPoint(int x, int y)
{
	fprintf(file, "point %d %d\n", x, y);
}
void DRAW_DrawLine(int x1, int y1, int x2, int y2)
{
	fprintf(file, "line %d %d %d %d\n", x1, y1, x2, y2);
}
void DRAW_DrawCircle(int x, int y, int r)
{
	fprintf(file, "circle %d %d %d\n", x, y, r);
} 
void DRAW_SetWidthAndHeight(int width, int height)
{
	fprintf(file, "setWidthAndHeight %d %d\n", width, height);
}
void DRAW_SetTitle(char* title)
{
	fprintf(file, "title %s\n", title);
}
void DRAW_SetColor(int R, int G, int B)
{
	fprintf(file, "color %d %d %d\n", R, G, B);
}
void DRAW_SetIconColor(int R, int G, int B)
{
	fprintf(file, "iconColor %d %d %d\n", R, G, B);
}
void DRAW_SetDrawIconInBackground(int drawIcon)
{
	fprintf(file, "drawIcon %d\n", drawIcon);
}
void DRAW_BeginDraw()
{
	file = fopen("drawData.dat", "w"); 
}
void DRAW_EndDraw()
{
	fclose(file);
	system("win.exe");
}

