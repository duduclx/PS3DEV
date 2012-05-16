float fonttexturecoords[2][96][8];

float textxsize=32;
float textysize=32;

void setuptext(){
	float textxborder=4;
	float textyborder=4;
	for(int a=0; a<2; a++){
		float xoffset=768.f;
		float yoffset=256.f+(float)a*384.f;
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
		posx+=xsize*0.7f;
	}

}

void drawtextrightaligned(int font,float posx,float posy,char* text,float size){
	posx-=textxsize*size*0.7f*(float)strlen(text);
	drawtext(font,posx,posy,text,size);
}

void drawtextcenteraligned(int font,float posx,float posy,char* text,float size){
	posx-=textxsize*size*0.7f*(float)strlen(text)*0.5f;
	drawtext(font,posx,posy,text,size);
}
