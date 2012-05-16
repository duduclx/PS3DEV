void plot4points(SDL_Surface *dest,int cx,int cy,int x,int y,Uint32 color){
	if(x!=0 && y!=0)if(cy-y>=0 && cy-y<dest->h)
		for(int a=highint(0,cx-x);a<lowint(dest->w,cx+x);a++)
			putpixel(dest,a,cy-y,color);
	if(x!=0)if(cy+y>=0 && cy+y<dest->h)
		for(int a=highint(0,cx-x);a<lowint(dest->w,cx+x);a++)
			putpixel(dest,a,cy+y,color);
}

void drawcircle(SDL_Surface *dest,int cx,int cy,int radius,Uint32 color){
	int error = -radius;
	int x = radius;
	int y = 0;
	while(x >= y){
		plot4points(dest,cx,cy,x,y,color);
		if(x!=y)plot4points(dest,cx,cy,y,x,color);
		error += y;
		++y;
		error += y;
		if (error >= 0){
			--x;
			error -= x;
			error -= x;
		}
	}
}
