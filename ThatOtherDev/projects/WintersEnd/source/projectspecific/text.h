float fonttexturecoords[96][8];

float textxsize=32;
float textysize=64;
float textxborder=2;
float textyborder=10;

void setuptext(){
	float xoffset=0;
	float yoffset=256;
	for(int y=0; y<3; y++)for(int x=0; x<32; x++){//setup the pixel positions
		fonttexturecoords[32*y+x][0]=xoffset+x*textxsize+textxborder;
		fonttexturecoords[32*y+x][1]=yoffset+y*textysize-textyborder+textysize;
		fonttexturecoords[32*y+x][2]=xoffset+x*textxsize-textxborder+textxsize;
		fonttexturecoords[32*y+x][3]=yoffset+y*textysize-textyborder+textysize;
		fonttexturecoords[32*y+x][4]=xoffset+x*textxsize-textxborder+textxsize;
		fonttexturecoords[32*y+x][5]=yoffset+y*textysize+textyborder;
		fonttexturecoords[32*y+x][6]=xoffset+x*textxsize+textxborder;
		fonttexturecoords[32*y+x][7]=yoffset+y*textysize+textyborder;
	}
	textxsize-=textxborder*2;
	textysize-=textyborder*2;
	for(int a=0; a<96; a++){//scale it for the texture
		fonttexturecoords[a][0]/=1024;
		fonttexturecoords[a][1]/=1024;
		fonttexturecoords[a][2]/=1024;
		fonttexturecoords[a][3]/=1024;
		fonttexturecoords[a][4]/=1024;
		fonttexturecoords[a][5]/=1024;
		fonttexturecoords[a][6]/=1024;
		fonttexturecoords[a][7]/=1024;
	}
}

void drawtext(float posx,float posy,char* text,float size){
	float xsize=textxsize*size;
	float ysize=textysize*size;
	int length=strlen(text);
	for(int a=0;a<length;a++){
		draw2dquad(
			posx,posy,
			xsize,ysize,
			fonttexturecoords[text[a]-' '],
			0,0.f);
		posx+=xsize;
	}
}
