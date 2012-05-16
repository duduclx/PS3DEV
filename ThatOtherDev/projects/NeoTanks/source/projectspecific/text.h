float fonttexturecoords[2][96][8];

float textxsize=0,textysize=0;

void setuptext(){
	textxsize=64;
	textysize=64;
	float textxborder=1;
	float textyborder=1;
	for(int a=0; a<2; a++){
		float xoffset=1024.f+512.f*(float)a;
		float yoffset=256;
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
			for(int c=0; c<4; c++){
				fonttexturecoords[a][b][c*2+0]/=2048.f;
				fonttexturecoords[a][b][c*2+1]/=1024.f;
			}
		}
	}
	textxsize-=textxborder*2;
	textysize-=textyborder*2;
}

void drawtext(int font,float posx,float posy,char* text,float size){
	float xsize=textxsize*size;
	float ysize=textysize*size;
	int length=strlen(text);
	for(int a=0;a<length;a++){
		draw2dquad(
			posx,posy,
			xsize,ysize,
			fonttexturecoords[font][text[a]-' '],
			0,0.f);
		posx+=xsize*0.45f;
	}
}

void drawtextrightaligned(int font,float posx,float posy,char* text,float size){
	posx-=textxsize*size*0.45f*(float)strlen(text);
	drawtext(font,posx,posy,text,size);
}

void drawtextcenteraligned(int font,float posx,float posy,char* text,float size){
	posx-=textxsize*size*0.45f*(float)(strlen(text)+1)*0.5f;
	drawtext(font,posx,posy,text,size);
}

void drawblackbox(float x,float y,float w,float h){
	float texturecoords[]={
		1736.f/2048.f,	118.f/1024.f,
		1736.f/2048.f,	118.f/1024.f,
		1736.f/2048.f,	118.f/1024.f,
		1736.f/2048.f,	118.f/1024.f,};
	draw2dquad(x,y,w,h,texturecoords,0,0);
}
