void drawline(int x1,int y1,int x2,int y2,int thickness,SDL_Surface *surface,Uint32 pixel){

	SDL_Rect drawrect={0,0,thickness,thickness};
	x1-=(int)floor((float)thickness*0.5);
	y1-=(int)floor((float)thickness*0.5);
	x2-=(int)floor((float)thickness*0.5);
	y2-=(int)floor((float)thickness*0.5);

	signed char ix,iy; 
	int delta_x = (x2 > x1?(ix = 1, x2 - x1):(ix = -1, x1 - x2)) << 1;
	int delta_y = (y2 > y1?(iy = 1, y2 - y1):(iy = -1, y1 - y2)) << 1;

	drawrect.x=x1;
	drawrect.y=y1;
	SDL_FillRect(surface,&drawrect,pixel);

	if (delta_x >= delta_y){

		int error = delta_y - (delta_x >> 1);
		while (x1 != x2){
			if (error >= 0){
				if (error || (ix > 0)){
					y1 += iy;
					error -= delta_x;
				}
			}
			x1 += ix;
			error += delta_y;

			drawrect.x=x1;
			drawrect.y=y1;
			SDL_FillRect(surface,&drawrect,pixel);

		}

    }else{

		int error = delta_x - (delta_y >> 1);
		while (y1 != y2){
			if (error >= 0){
				if (error || (iy > 0)){
					x1 += ix;
					error -= delta_y;
				}
			}
			y1 += iy;
			error += delta_x;

			drawrect.x=x1;
			drawrect.y=y1;
			SDL_FillRect(surface,&drawrect,pixel);

		}

	}

}
