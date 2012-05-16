Uint8 dashrgb1[640][480][3];
Uint8 dashrgb2[640][480][3];

void filtersurface(
	SDL_Surface* &source,
	SDL_Surface* &dest,
	int blurdist1,int blurstrength1,
	int blurdist2,int blurstrength2,
	bool grayscale,
	int rdiff,int gdiff,int bdiff){

	if(source->format->BitsPerPixel==16){
		Uint32 color;
		Uint16* pPosition=(Uint16*)screen->pixels;
		for(int y=0;y<480;y++)for(int x=0;x<640;x++){
			color=*pPosition;
			dashrgb1[x][y][0]=(((color&63488)>>11)<<3);
			dashrgb1[x][y][1]=(((color&2016)>>5)<<2);
			dashrgb1[x][y][2]=(((color&31)>>0)<<3);
			pPosition++;}
	}else{
		for(int x=0;x<640;x++)for(int y=0;y<480;y++)
			SDL_GetRGB(getpixel(screen,x,y),
			screen->format,&dashrgb1[x][y][0],&dashrgb1[x][y][1],&dashrgb1[x][y][2]);
	}

	if(grayscale){
		for(int y=0;y<480;y++)for(int x=0;x<640;x++)
			dashrgb1[x][y][0]=(dashrgb1[x][y][0]+dashrgb1[x][y][1]+dashrgb1[x][y][2])/3;
		memcpy(dashrgb2,dashrgb1,640*480*1*sizeof(Uint8));
		for(int a=0;a<blurstrength1;a++){
			for(int x=blurdist1;x<640-blurdist1;x++)for(int y=blurdist1;y<480-blurdist1;y++)
				dashrgb2[x][y][0]=(dashrgb1[x][y-blurdist1][0]+dashrgb1[x][y+blurdist1][0]+dashrgb1[x-blurdist1][y][0]+dashrgb1[x+blurdist1][y][0])/4;
			for(int x=blurdist1;x<640-blurdist1;x++)for(int y=blurdist1;y<480-blurdist1;y++)
				dashrgb1[x][y][0]=(dashrgb2[x][y-blurdist1][0]+dashrgb2[x][y+blurdist1][0]+dashrgb2[x-blurdist1][y][0]+dashrgb2[x+blurdist1][y][0]+1)/4;
		}
		for(int a=0;a<blurstrength2;a++){
			for(int x=blurdist2;x<640-blurdist2;x++)for(int y=blurdist2;y<480-blurdist2;y++)
				dashrgb2[x][y][0]=(dashrgb1[x][y-blurdist2][0]+dashrgb1[x][y+blurdist2][0]+dashrgb1[x-blurdist2][y][0]+dashrgb1[x+blurdist2][y][0])/4;
			for(int x=blurdist2;x<640-blurdist2;x++)for(int y=blurdist2;y<480-blurdist2;y++)
				dashrgb1[x][y][0]=(dashrgb2[x][y-blurdist2][0]+dashrgb2[x][y+blurdist2][0]+dashrgb2[x-blurdist2][y][0]+dashrgb2[x+blurdist2][y][0])/4;
		}
		for(int y=0;y<480;y++)for(int x=0;x<640;x++){
			dashrgb1[x][y][1]=dashrgb1[x][y][0];
			dashrgb1[x][y][2]=dashrgb1[x][y][0];
		}
	}else{
		memcpy(dashrgb2,dashrgb1,640*480*3*sizeof(Uint8));
		for(int a=0;a<blurstrength1;a++){
			for(int x=blurdist1;x<640-blurdist1;x++)for(int y=blurdist1;y<480-blurdist1;y++){
				dashrgb2[x][y][0]=(dashrgb1[x][y-blurdist1][0]+dashrgb1[x][y+blurdist1][0]+dashrgb1[x-blurdist1][y][0]+dashrgb1[x+blurdist1][y][0])/4;
				dashrgb2[x][y][1]=(dashrgb1[x][y-blurdist1][1]+dashrgb1[x][y+blurdist1][1]+dashrgb1[x-blurdist1][y][1]+dashrgb1[x+blurdist1][y][1])/4;
				dashrgb2[x][y][2]=(dashrgb1[x][y-blurdist1][2]+dashrgb1[x][y+blurdist1][2]+dashrgb1[x-blurdist1][y][2]+dashrgb1[x+blurdist1][y][2])/4;
			}for(int x=blurdist1;x<640-blurdist1;x++)for(int y=blurdist1;y<480-blurdist1;y++){
				dashrgb1[x][y][0]=(dashrgb2[x][y-blurdist1][0]+dashrgb2[x][y+blurdist1][0]+dashrgb2[x-blurdist1][y][0]+dashrgb2[x+blurdist1][y][0]+1)/4;
				dashrgb1[x][y][1]=(dashrgb2[x][y-blurdist1][1]+dashrgb2[x][y+blurdist1][1]+dashrgb2[x-blurdist1][y][1]+dashrgb2[x+blurdist1][y][1]+1)/4;
				dashrgb1[x][y][2]=(dashrgb2[x][y-blurdist1][2]+dashrgb2[x][y+blurdist1][2]+dashrgb2[x-blurdist1][y][2]+dashrgb2[x+blurdist1][y][2]+1)/4;
			}
		}
		for(int a=0;a<blurstrength2;a++){
			for(int x=blurdist2;x<640-blurdist2;x++)for(int y=blurdist2;y<480-blurdist2;y++){
				dashrgb2[x][y][0]=(dashrgb1[x][y-blurdist2][0]+dashrgb1[x][y+blurdist2][0]+dashrgb1[x-blurdist2][y][0]+dashrgb1[x+blurdist2][y][0])/4;
				dashrgb2[x][y][1]=(dashrgb1[x][y-blurdist2][1]+dashrgb1[x][y+blurdist2][1]+dashrgb1[x-blurdist2][y][1]+dashrgb1[x+blurdist2][y][1])/4;
				dashrgb2[x][y][2]=(dashrgb1[x][y-blurdist2][2]+dashrgb1[x][y+blurdist2][2]+dashrgb1[x-blurdist2][y][2]+dashrgb1[x+blurdist2][y][2])/4;
			}for(int x=blurdist2;x<640-blurdist2;x++)for(int y=blurdist2;y<480-blurdist2;y++){
				dashrgb1[x][y][0]=(dashrgb2[x][y-blurdist2][0]+dashrgb2[x][y+blurdist2][0]+dashrgb2[x-blurdist2][y][0]+dashrgb2[x+blurdist2][y][0])/4;
				dashrgb1[x][y][1]=(dashrgb2[x][y-blurdist2][1]+dashrgb2[x][y+blurdist2][1]+dashrgb2[x-blurdist2][y][1]+dashrgb2[x+blurdist2][y][1])/4;
				dashrgb1[x][y][2]=(dashrgb2[x][y-blurdist2][2]+dashrgb2[x][y+blurdist2][2]+dashrgb2[x-blurdist2][y][2]+dashrgb2[x+blurdist2][y][2])/4;
			}
		}
	}
	if(rdiff||gdiff||bdiff)for(int y=0;y<480;y++)for(int x=0;x<640;x++){
		dashrgb1[x][y][0]=in8bitrange(dashrgb1[x][y][0]+rdiff);
		dashrgb1[x][y][1]=in8bitrange(dashrgb1[x][y][1]+gdiff);
		dashrgb1[x][y][2]=in8bitrange(dashrgb1[x][y][2]+bdiff);
	}

	if(dest->format->BitsPerPixel==16){
		Uint16* pPosition=(Uint16*)dest->pixels;
		for(int y=0;y<480;y++)for(int x=0;x<640;x++){
			*pPosition=
				(dashrgb1[x][y][0]>>3<<11)|
				(dashrgb1[x][y][1]>>2<<5)|
				(dashrgb1[x][y][2]>>3<<0);
			pPosition++;
		}
	}else{
		for(int y=0;y<480;y++)for(int x=0;x<640;x++)
			putpixel(dest,x,y,
				SDL_MapRGB(dest->format,
				dashrgb1[x][y][0],dashrgb1[x][y][1],dashrgb1[x][y][2]));
	}

}
