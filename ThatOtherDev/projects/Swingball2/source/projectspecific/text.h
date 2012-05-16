float fonttexturecoords[96][8];

float textxsize=0.f;
float textysize=0.f;

void setuptext(){
	textxsize=64.f;
	textysize=64.f;
	float xoffset=512.f;
	float yoffset=0.f;
	float textxborder=1.f;
	float textyborder=1.f;
	for(int y=0; y<12; y++)for(int x=0; x<8; x++){//setup the pixel positions
		fonttexturecoords[8*y+x][0]=xoffset+x*textxsize+textxborder;
		fonttexturecoords[8*y+x][1]=yoffset+y*textysize-textyborder+textysize;
		fonttexturecoords[8*y+x][2]=xoffset+x*textxsize-textxborder+textxsize;
		fonttexturecoords[8*y+x][3]=yoffset+y*textysize-textyborder+textysize;
		fonttexturecoords[8*y+x][4]=xoffset+x*textxsize-textxborder+textxsize;
		fonttexturecoords[8*y+x][5]=yoffset+y*textysize+textyborder;
		fonttexturecoords[8*y+x][6]=xoffset+x*textxsize+textxborder;
		fonttexturecoords[8*y+x][7]=yoffset+y*textysize+textyborder;
	}
	for(int a=0; a<96; a++){//scale it for the texture
		for(int b=0; b<4; b++){
			fonttexturecoords[a][b*2+0]/=1024.f;
			fonttexturecoords[a][b*2+1]/=1024.f;
		}
	}
	textxsize-=textxborder*2.f;
	textysize-=textyborder*2.f;
}

void drawtext(float posx,float posy,char* text,float size){

	float xsize=textxsize*size;
	float ysize=textysize*size;

	int length=strlen(text);

	for(int a=0;a<length;a++){
		if((text[a]-' ')>0 && (text[a]-' ')<96)draw2dquad(
			posx,posy,
			xsize,ysize,
			fonttexturecoords[text[a]-' '],
			0,0.f);
		posx+=xsize*0.525f;
	}

}

void drawtextrightaligned(float posx,float posy,char* text,float size){
	posx-=textxsize*size*0.525f*((float)strlen(text)+0.5f);
	drawtext(posx,posy,text,size);
}

void drawtextcenteraligned(float posx,float posy,char* text,float size){
	posx-=textxsize*size*0.525f*(float)strlen(text)*0.5f;
	drawtext(posx,posy,text,size);
}
