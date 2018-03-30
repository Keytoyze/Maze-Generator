FILE* file;
void DRAW_DrawPoint(int x, int y)//���ݸ���������Ƶ� 
{
	fprintf(file, "point %d %d\n", x, y);
}
void DRAW_DrawLine(int x1, int y1, int x2, int y2)//���ݸ���ͷβ������������ 
{
	fprintf(file, "line %d %d %d %d\n", x1, y1, x2, y2);
}
void DRAW_DrawCircle(int x, int y, int r)//���ݸ�����Բ������Ͱ뾶����ʵ��Բ 
{
	fprintf(file, "circle %d %d %d\n", x, y, r);
} 
void DRAW_SetWidthAndHeight(int width, int height)//����ͼ�δ��ڵĳ��� 
{
	fprintf(file, "setWidthAndHeight %d %d\n", width, height);
}
void DRAW_SetTitle(char* title)//���ô��ڱ��� 
{
	fprintf(file, "title %s\n", title);
}
void DRAW_SetColor(int R, int G, int B)//���û��Ƶ����ɫ 
{
	fprintf(file, "color %d %d %d\n", R, G, B);
}
void DRAW_SetIconColor(int R, int G, int B)//���ñ���ͼ�����ɫ 
{
	fprintf(file, "iconColor %d %d %d\n", R, G, B);
}
void DRAW_SetDrawIconInBackground(int drawIcon)//�����Ƿ��ڱ�������ͼ�� 
{
	fprintf(file, "drawIcon %d\n", drawIcon);
}
void DRAW_BeginDraw()//��ʼ���ơ��˴���һ���ļ��� ���ڴ������������ͼ�ο� 
{
	file = fopen("lib\\drawData.dat", "w"); 
}
void DRAW_EndDraw()//�������ơ��ر��ļ������ҵ���ͼ�ο���ʾ�Թ� 
{
	fclose(file);
	system("lib\\win.exe");
}

