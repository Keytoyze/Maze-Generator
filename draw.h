FILE* file;
void drawPoint(int x, int y){
	fprintf(file, "point %d %d\n", x, y);
}
void drawLine(int x1, int y1, int x2, int y2){
	fprintf(file, "line %d %d %d %d\n", x1, y1, x2, y2);
} 
void setWidthAndHeight(int width, int height){
	fprintf(file, "setWidthAndHeight %d %d\n", width, height);
}
void setTitle(char* title){
	fprintf(file, "title %s\n", title);
}
void setColor(int R, int G, int B){
	fprintf(file, "color %d %d %d\n", R, G, B);
}
void setIconColor(int R, int G, int B){
	fprintf(file, "iconColor %d %d %d\n", R, G, B);
}
void setDrawIconInBackground(int drawIcon) {
	fprintf(file, "drawIcon %d\n", drawIcon);
}
void beginDraw(){
	file = fopen("drawData.dat", "w"); 
}
void endDraw(){
	fclose(file);
	system("win.exe");
}

