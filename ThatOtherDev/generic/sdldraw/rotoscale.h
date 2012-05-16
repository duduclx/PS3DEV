void fastrotoscale(
	SDL_Surface *source,SDL_Surface *destination,float angle,float scale){
	
	int sourcew=source->w;
	int sourceh=source->h;
	int destinationw=destination->w;
	int destinationh=destination->h;
	
	float x1=	dist2d(0,0,(float)sourcew/2,(float)sourcew/2)				*scale	*cos(atan2((float)sourcew*0.5f,(float)sourcew*0.5f)+angle);
	float y1=	dist2d(0,0,(float)sourcew/2,(float)sourcew/2)				*scale	*sin(atan2((float)sourcew*0.5f,(float)sourcew*0.5f)+angle);
	float x2=	dist2d((float)sourcew,0,(float)sourcew/2,(float)sourcew/2)	*scale	*cos(atan2((float)sourcew*0.5f,(float)sourcew*0.5f-(float)sourcew)+angle);
	float y2=	dist2d((float)sourcew,0,(float)sourcew/2,(float)sourcew/2)	*scale	*sin(atan2((float)sourcew*0.5f,(float)sourcew*0.5f-(float)sourcew)+angle);
	float x3=	dist2d(0,(float)sourcew,(float)sourcew/2,(float)sourcew/2)	*scale	*cos(atan2((float)sourcew*0.5f-(float)sourcew,(float)sourcew*0.5f)+angle);
	float y3=	dist2d(0,(float)sourcew,(float)sourcew/2,(float)sourcew/2)	*scale	*sin(atan2((float)sourcew*0.5f-(float)sourcew,(float)sourcew*0.5f)+angle);

	float xdifx=(x1-x2)/(float)sourcew;
	float xdify=(y1-y2)/(float)sourcew;
	float ydifx=(x1-x3)/(float)sourcew;
	float ydify=(y1-y3)/(float)sourcew;

	float offsetx=(float)sourcew*0.5f-(float)destinationw*0.5f*xdifx-(float)destinationh*0.5f*ydifx;
	float offsety=(float)sourceh*0.5f-(float)destinationw*0.5f*xdify-(float)destinationh*0.5f*ydify;
	float xuse=0;
	float yuse=0;
	
	if(source->format->BitsPerPixel==16 && destination->format->BitsPerPixel==16){
		if(angle==0){
			Uint16* pixelposition=(Uint16*)destination->pixels;
			Uint16* pixelpositiony=0;
			for(int y=0;y<destinationh;y++){
				xuse=offsetx;
				yuse=offsety+y*ydify;
				pixelpositiony=(Uint16*)source->pixels+(int)yuse*sourcew;
				for(int x=0;x<destinationw;x++){
					xuse+=xdifx;
					if(xuse>0 && xuse<sourcew && yuse>0 && yuse<sourceh)
						*pixelposition=*(pixelpositiony+(int)xuse);
					pixelposition++;
				}
			}
		}else{
			Uint16* pixelposition=(Uint16*)destination->pixels;
			for(int y=0;y<destinationh;y++){
				xuse=offsetx+y*ydifx;
				yuse=offsety+y*ydify;
				for(int x=0;x<destinationw;x++){
					xuse+=xdifx;
					yuse+=xdify;
					if(xuse>0 && xuse<sourcew && yuse>0 && yuse<sourceh)
						*pixelposition=*((Uint16*)source->pixels+(int)xuse+(int)yuse*sourcew);
					pixelposition++;
				}
			}
		}
	}else if(source->format->BitsPerPixel==32 && destination->format->BitsPerPixel==32){
		if(angle==0){
			Uint32* pixelposition=(Uint32*)destination->pixels;
			Uint32* pixelpositiony=0;
			for(int y=0;y<destinationh;y++){
				xuse=offsetx;
				yuse=offsety+y*ydify;
				pixelpositiony=(Uint32*)source->pixels+(int)yuse*sourcew;
				for(int x=0;x<destinationw;x++){
					xuse+=xdifx;
					if(xuse>0 && xuse<sourcew && yuse>0 && yuse<sourceh)
						*pixelposition=*(pixelpositiony+(int)xuse);
					pixelposition++;
				}
			}
		}else{
			Uint32* pixelposition=(Uint32*)destination->pixels;
			for(int y=0;y<destinationh;y++){
				xuse=offsetx+y*ydifx;
				yuse=offsety+y*ydify;
				for(int x=0;x<destinationw;x++){
					xuse+=xdifx;
					yuse+=xdify;
					if(xuse>0 && xuse<sourcew && yuse>0 && yuse<sourceh)
						*pixelposition=*((Uint32*)source->pixels+(int)xuse+(int)yuse*sourcew);
					pixelposition++;
				}
			}
		}
	}else{
		if(angle==0){
			for(int y=0;y<destinationh;y++){
				xuse=offsetx;
				yuse=offsety+y*ydify;
				for(int x=0;x<destinationw;x++){
					xuse+=xdifx;
					if(xuse>0 && xuse<sourcew && yuse>0 && yuse<sourceh)
						putpixel(destination,x,y,getpixel(source,(int)xuse,(int)yuse));
				}
			}
		}else{
			for(int y=0;y<destinationh;y++){
				xuse=offsetx+y*ydifx;
				yuse=offsety+y*ydify;
				for(int x=0;x<destinationw;x++){
					xuse+=xdifx;
					yuse+=xdify;
					if(xuse>0 && xuse<sourcew && yuse>0 && yuse<sourceh)
						putpixel(destination,x,y,getpixel(source,(int)xuse,(int)yuse));
				}
			}
		}
	}

}

void rotoscale(
	SDL_Surface *source,SDL_Surface *destination,
	float angle,float scale,
	int dx,int dy,int dw,int dh){
	
	float x1=	dist2d(0,0,(float)source->w/2,(float)source->w/2)					*scale	*cos(atan2((float)source->w*0.5f,(float)source->w*0.5f)+angle);
	float y1=	dist2d(0,0,(float)source->w/2,(float)source->w/2)					*scale	*sin(atan2((float)source->w*0.5f,(float)source->w*0.5f)+angle);
	float x2=	dist2d((float)source->w,0,(float)source->w/2,(float)source->w/2)	*scale	*cos(atan2((float)source->w*0.5f,(float)source->w*0.5f-(float)source->w)+angle);
	float y2=	dist2d((float)source->w,0,(float)source->w/2,(float)source->w/2)	*scale	*sin(atan2((float)source->w*0.5f,(float)source->w*0.5f-(float)source->w)+angle);
	float x3=	dist2d(0,(float)source->w,(float)source->w/2,(float)source->w/2)	*scale	*cos(atan2((float)source->w*0.5f-(float)source->w,(float)source->w*0.5f)+angle);
	float y3=	dist2d(0,(float)source->w,(float)source->w/2,(float)source->w/2)	*scale	*sin(atan2((float)source->w*0.5f-(float)source->w,(float)source->w*0.5f)+angle);

	float xdifx=(x1-x2)/(float)source->w;
	float xdify=(y1-y2)/(float)source->w;
	float ydifx=(x1-x3)/(float)source->w;
	float ydify=(y1-y3)/(float)source->w;

	float offsetx=(float)source->w/2;
	float offsety=(float)source->w/2;
	float xuse=0;
	float yuse=0;

	for(int y=0;y<dh;y++){
		xuse=offsetx+y*ydifx-dw/2*xdifx-dh/2*ydifx;
		yuse=offsety+y*ydify-dw/2*xdify-dh/2*ydify;
		for(int x=0;x<dw;x++){
			xuse+=xdifx;
			yuse+=xdify;
			if(xuse>0 && xuse<source->w && yuse>0 && yuse<source->h){
				putpixel(destination,x+dx,y+dy,getpixel(source,(int)xuse,(int)yuse));
			}
		}
	}

}

void scalesurface(
	SDL_Surface *source,SDL_Surface *destination,
	float sourcex1,float sourcex2,float sourcey1,float sourcey2,
	float destx1,float destx2,float desty1,float desty2){
	
	float xdif=(sourcex1-sourcex2)/(destx1-destx2);
	float ydif=(sourcey1-sourcey2)/(desty1-desty2);
	
	float xuse=sourcex1;
	float yuse=sourcey1;
	
	for(int y=desty1;y<desty2+1;y++){
		xuse=sourcex1;
		for(int x=destx1;x<destx2+1;x++){
			xuse+=xdif;
			if(x>=0 && x<destination->w
			&& y>=0 && y<destination->h
			&& (int)xuse>=0 && (int)xuse<source->w
			&& (int)yuse>=0 && (int)yuse<source->h)
				putpixel(destination,x,y,getpixel(source,(int)xuse,(int)yuse));
		}
		yuse+=ydif;
	}

}
