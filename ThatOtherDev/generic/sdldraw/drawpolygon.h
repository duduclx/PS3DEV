//#define SWAP(x,y,temp) temp=x;x=y;y=temp
void SWAP(Sint16 &x,Sint16 &y,Sint16 &temp){
	temp=x;
	x=y;
	y=temp;
}

void _HLine(SDL_Surface *Surface, Sint16 x1, Sint16 x2, Sint16 y, Uint32 Color){
	if(x1>x2){Sint16 tmp=x1; x1=x2; x2=tmp;}
	//Do the clipping
	#if SDL_VERSIONNUM(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL) < \
    SDL_VERSIONNUM(1, 1, 5)
	if(y<Surface->clip_miny || y>Surface->clip_maxy || x1>Surface->clip_maxx || x2<Surface->clip_minx)
		return;
	if(x1<Surface->clip_minx)
		x1=Surface->clip_minx;
	if(x2>Surface->clip_maxx)
		x2=Surface->clip_maxx;
	#endif
	SDL_Rect line = {x1,y,x2-x1+1,1};
	SDL_FillRect(Surface, &line, Color);
	//SDL_Rect l;
	//l.x=x1; l.y=y; l.w=x2-x1+1; l.h=1;
	//SDL_FillRect(Surface, &l, Color);
	//for(int x=x1; x<x2+1; x++)renderedscreen[x][y]=Color;
}

void drawpolygon(SDL_Surface *dest,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2,Sint16 x3,Sint16 y3,Uint32 color){
	Sint16 y;
	if( y1==y3 )
		return;
	/* Sort coords */
	if ( y1 > y2 ) {
		SWAP(y1,y2,y);
		SWAP(x1,x2,y);
	}
	if ( y2 > y3 ) {
		SWAP(y2,y3,y);
		SWAP(x2,x3,y);
	}
	if ( y1 > y2 ) {
		SWAP(y1,y2,y);
		SWAP(x1,x2,y);
	}
	/*
	 * How do we calculate the starting and ending x coordinate of the horizontal line
	 * on each y coordinate?  We can do this by using a standard line algorithm but
	 * instead of plotting pixels, use the x coordinates as start and stop
	 * coordinates for the horizontal line.
	 * So we will simply trace the outlining of the triangle; this will require 3 lines.
	 * Line 1 is the line between (x1,y1) and (x2,y2)
	 * Line 2 is the line between (x1,y1) and (x3,y3)
	 * Line 3 is the line between (x2,y2) and (x3,y3)
	 *
	 * We can divide the triangle into 2 halfs. The upper half will be outlined by line
	 * 1 and 2. The lower half will be outlined by line line 2 and 3.
	*/
	/* Starting coords for the three lines */
	Sint32 xa = Sint32(x1<<16);
	Sint32 xb = xa;
	Sint32 xc = Sint32(x2<<16);
	/* Lines step values */
	Sint32 m1 = 0;
	Sint32 m2 = Sint32((x3 - x1)<<16)/Sint32(y3 - y1);
	Sint32 m3 = 0;
	/* Upper half of the triangle */
	if( y1==y2 )
		_HLine(dest, x1, x2, y1, color);
	else{
		m1 = Sint32((x2 - x1)<<16)/Sint32(y2 - y1);
		
		for ( y = y1; y <= y2; y++) {
			_HLine(dest, xa>>16, xb>>16, y, color);
				
			xa += m1;
			xb += m2;
		}
	}
	/* Lower half of the triangle */
	if( y2==y3 )
		_HLine(dest, x2, x3, y2, color);
	else{
		m3 = Sint32((x3 - x2)<<16)/Sint32(y3 - y2);
		
		for ( y = y2+1; y <= y3; y++) {
			_HLine(dest, xb>>16, xc>>16, y, color);

			xb += m2;
			xc += m3;
		}
	}
	//if(_sge_update!=1){return;}
	Sint16 xmax=x1, xmin=x1;
	xmax= (xmax>x2)? xmax : x2;
	xmin= (xmin<x2)? xmin : x2;
	xmax= (xmax>x3)? xmax : x3;
	xmin= (xmin<x3)? xmin : x3;
	//sge_UpdateRect(dest, xmin, y1, xmax-xmin+1, y3-y1+1);
}
