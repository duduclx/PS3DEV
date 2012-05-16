float fonttexturecoords[2][96][8];

float textxsize=32;
float textysize=32;

void setuptext(){
	float xoffset=0;
	float yoffset=0;
	float textxborder=3;
	float textyborder=2;
	for(int font=0;font<2;font++){
		for(int y=0; y<12; y++)for(int x=0; x<8; x++){//setup the pixel positions
			fonttexturecoords[font][8*y+x][0]=xoffset+x*textxsize+textxborder;
			fonttexturecoords[font][8*y+x][1]=yoffset+y*textysize-textyborder+textysize;
			fonttexturecoords[font][8*y+x][2]=xoffset+x*textxsize-textxborder+textxsize;
			fonttexturecoords[font][8*y+x][3]=yoffset+y*textysize-textyborder+textysize;
			fonttexturecoords[font][8*y+x][4]=xoffset+x*textxsize-textxborder+textxsize;
			fonttexturecoords[font][8*y+x][5]=yoffset+y*textysize+textyborder;
			fonttexturecoords[font][8*y+x][6]=xoffset+x*textxsize+textxborder;
			fonttexturecoords[font][8*y+x][7]=yoffset+y*textysize+textyborder;
		}
		for(int a=0; a<96; a++){//scale it for the texture
			for(int b=0; b<4; b++){
				fonttexturecoords[font][a][b*2+0]/=256.f;
				fonttexturecoords[font][a][b*2+1]+=(float)font*384.f;
				fonttexturecoords[font][a][b*2+1]/=1024.f;
			}
		}
	}
	textxsize-=textxborder*2;
	textysize-=textyborder*2;
}

int counttextwrappedlines(char* text,int maxlinelength){
	int length=strlen(text);
	int linecount=0;
	int a=0;
	while(a<length){
		int b=maxlinelength+a;
		if(maxlinelength+a<length){
			for(int c=a;c<maxlinelength+a;c++)
				if(text[c]==' ')b=c+1;
		}else{
			b=length;
		}
		while(a<b && a<length){
			a++;
		}
		linecount+=1;
	}
	return linecount;
}

void drawtextwrapped(float posx,float posy,char* text,float size,int maxlinelength,int font){
	float startposx=posx;
	float xsize=textxsize*size;
	float ysize=textysize*size;
	int length=strlen(text);
	int a=0;
	while(a<length){
		int b=maxlinelength+a;
		if(maxlinelength+a<length){
			for(int c=a;c<maxlinelength+a;c++)
				if(text[c]==' ')b=c+1;
		}else{
			b=length;
		}
		while(a<b && a<length){
			draw2dquad(
				posx,posy,
				xsize,ysize,
				fonttexturecoords[font][text[a]-' '],
				0,0.f);
			posx+=xsize*0.575f;
			a++;
		}
		posx=startposx;
		posy+=ysize*0.8f;
	}
}
