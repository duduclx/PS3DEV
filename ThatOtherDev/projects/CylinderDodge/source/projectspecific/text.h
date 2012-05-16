float fonttexturecoords[3][96][8];

float textxsize=0.f, textysize=0.f;

void setuptext(){
	textxsize=16;
	textysize=32;
	float xoffset=0;
	float yoffset=0;
	float textxborder=2;
	float textyborder=6;
	for(int a=0; a<3; a++){
		for(int y=0; y<3; y++)for(int x=0; x<32; x++){//setup the pixel positions
			fonttexturecoords[a][32*y+x][0]=xoffset+x*textxsize+textxborder;
			fonttexturecoords[a][32*y+x][1]=yoffset+y*textysize-textyborder+textysize;
			fonttexturecoords[a][32*y+x][2]=xoffset+x*textxsize-textxborder+textxsize;
			fonttexturecoords[a][32*y+x][3]=yoffset+y*textysize-textyborder+textysize;
			fonttexturecoords[a][32*y+x][4]=xoffset+x*textxsize-textxborder+textxsize;
			fonttexturecoords[a][32*y+x][5]=yoffset+y*textysize+textyborder;
			fonttexturecoords[a][32*y+x][6]=xoffset+x*textxsize+textxborder;
			fonttexturecoords[a][32*y+x][7]=yoffset+y*textysize+textyborder;
		}
		for(int b=0; b<96; b++){//scale it for the texture
			fonttexturecoords[a][b][0]/=512.f;
			fonttexturecoords[a][b][1]/=512.f;
			fonttexturecoords[a][b][2]/=512.f;
			fonttexturecoords[a][b][3]/=512.f;
			fonttexturecoords[a][b][4]/=512.f;
			fonttexturecoords[a][b][5]/=512.f;
			fonttexturecoords[a][b][6]/=512.f;
			fonttexturecoords[a][b][7]/=512.f;
		}
	}
	textxsize-=textxborder*2.f;
	textysize-=textyborder*2.f;
}

void drawtext(float posx,float posy,char* text,float size){
	int font=0;
	float xsize=textxsize*size;
	float ysize=textysize*size;
	int length=strlen(text);
	for(int a=0;a<length;a++){
		if((text[a]-' ')>0 && (text[a]-' ')<96)draw2dquad(
			posx,posy,
			xsize,ysize,
			fonttexturecoords[font][text[a]-' '],
			0,0.f);
		posx+=xsize;
	}
}

void drawtextrightaligned(float posx,float posy,char* text,float size){
	posx-=textxsize*size*(float)strlen(text);
	drawtext(posx,posy,text,size);
}

void drawcomicframe(float x,float y,float w,float h){
	if(1){
		float texturecoords[]={
			500.f/512.f,	495.f/512.f,
			505.f/512.f,	495.f/512.f,
			505.f/512.f,	490.f/512.f,
			500.f/512.f,	490.f/512.f,};
		draw2dquad(x-2,y-2,w+4,h+4,texturecoords,0,0);
	}
	if(1){
		float texturecoords[]={
			500.f/512.f,	75.f/512.f,
			505.f/512.f,	75.f/512.f,
			505.f/512.f,	70.f/512.f,
			500.f/512.f,	70.f/512.f,};
		draw2dquad(x,y,w,h,texturecoords,0,0);
	}
}

