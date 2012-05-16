float fonttexturecoords[2][96][8];

float textxsize=64;
float textysize=64;

void setuptext(){
	float textxborder=2;
	float textyborder=2;
	for(int a=0; a<2; a++){
		float xoffset=512.f*(float)a;
		float yoffset=0;
		for(int y=0; y<12; y++)for(int x=0; x<8; x++){//setup the pixel positions
			fonttexturecoords[a][8*y+x][0]=xoffset+x*textxsize+textxborder;
			fonttexturecoords[a][8*y+x][1]=yoffset+y*textysize-textyborder+textysize;
			fonttexturecoords[a][8*y+x][2]=xoffset+x*textxsize-textxborder+textxsize;
			fonttexturecoords[a][8*y+x][3]=yoffset+y*textysize-textyborder+textysize;
			fonttexturecoords[a][8*y+x][4]=xoffset+x*textxsize-textxborder+textxsize;
			fonttexturecoords[a][8*y+x][5]=yoffset+y*textysize+textyborder;
			fonttexturecoords[a][8*y+x][6]=xoffset+x*textxsize+textxborder;
			fonttexturecoords[a][8*y+x][7]=yoffset+y*textysize+textyborder;
		}
		for(int b=0; b<96; b++){//scale it for the texture
			for(int c=0; c<8; c++)fonttexturecoords[a][b][c]/=1024;
		}
	}
	textxsize-=textxborder*2;
	textysize-=textyborder*2;
}

void drawtext(float posx,float posy,char* text,float size){

	float startx=posx;
	float xsize=textxsize*size;
	float ysize=textysize*size;

	int length=strlen(text);

	for(int a=0;a<length;a++){
		draw2dquad(
			posx,posy,
			xsize,ysize,
			fonttexturecoords[0][text[a]-' '],
			0,0.f);
		posx+=xsize*0.45f;
	}
	posx=startx;
	for(int a=0;a<length;a++){
		draw2dquad(
			posx,posy,
			xsize,ysize,
			fonttexturecoords[1][text[a]-' '],
			0,0.f);
		posx+=xsize*0.45f;
	}

}
