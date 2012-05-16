#include "dashboardtexture.bin.h"
Image dashboardtexture_image;

float dashonpercent=0.f;
bool dashon=0;

char dash_bars_credits[2][256];

char dash_bars_gamename[256];
float dash_bars_gameversion=0;

float dash_logo_texturecoords[8];
float dash_font_texturecoords[2][96][8];

float dash_textxsize=0;
float dash_textysize=0;

void dashps3setup(){
	//load the texture
	dashboardtexture_image = loadPng(dashboardtexture_bin);
	//setup logo coords
	if(1){
		float x=0;
		float y=384;
		float w=512;
		float h=128;
		dash_logo_texturecoords[0]=x;
		dash_logo_texturecoords[1]=y+h;
		dash_logo_texturecoords[2]=x+w;
		dash_logo_texturecoords[3]=y+h;
		dash_logo_texturecoords[4]=x+w;
		dash_logo_texturecoords[5]=y;
		dash_logo_texturecoords[6]=x;
		dash_logo_texturecoords[7]=y;
		for(int a=0; a<4; a++){
			dash_logo_texturecoords[a*2+0]/=512.f;
			dash_logo_texturecoords[a*2+1]/=512.f;
		}
	}
	//setup font coords
	float textxsize=32;
	float textysize=32;
	float textxborder=1;
	float textyborder=1;
	for(int a=0; a<2; a++){
		float xoffset=0;
		float yoffset=192.f*(float)a;
		for(int y=0; y<6; y++)for(int x=0; x<16; x++){//setup the pixel positions
			dash_font_texturecoords[a][16*y+x][0]=xoffset+x*textxsize+textxborder;
			dash_font_texturecoords[a][16*y+x][1]=yoffset+y*textysize-textyborder+textysize;
			dash_font_texturecoords[a][16*y+x][2]=xoffset+x*textxsize-textxborder+textxsize;
			dash_font_texturecoords[a][16*y+x][3]=yoffset+y*textysize-textyborder+textysize;
			dash_font_texturecoords[a][16*y+x][4]=xoffset+x*textxsize-textxborder+textxsize;
			dash_font_texturecoords[a][16*y+x][5]=yoffset+y*textysize+textyborder;
			dash_font_texturecoords[a][16*y+x][6]=xoffset+x*textxsize+textxborder;
			dash_font_texturecoords[a][16*y+x][7]=yoffset+y*textysize+textyborder;
		}
		for(int b=0; b<96; b++){//scale it for the texture
			for(int c=0; c<4; c++){
				dash_font_texturecoords[a][b][c*2+0]/=512;
				dash_font_texturecoords[a][b][c*2+1]/=512;
			}
		}
	}
	textxsize-=textxborder*2;
	textysize-=textyborder*2;
	dash_textxsize=textxsize;
	dash_textysize=textysize;
}

void dash_drawtext(float posx,float posy,char* text,float size){
	int length=strlen(text);
	float xsize=dash_textxsize*size;
	float ysize=dash_textysize*size;
	posx-=(float)length*xsize*0.3f;
	float startx=posx;
	for(int a=0;a<length;a++){
		draw2dquad(
			posx,posy,
			xsize,ysize,
			dash_font_texturecoords[0][text[a]-' '],
			0,0.f);
		posx+=xsize*0.3f;
	}
	posx=startx;
	for(int a=0;a<length;a++){
		draw2dquad(
			posx,posy,
			xsize,ysize,
			dash_font_texturecoords[1][text[a]-' '],
			0,0.f);
		posx+=xsize*0.3f;
	}

}

void dashps3loop(){
	if(dashon==1){
		usetexture(dashboardtexture_image);
		float viewsizex=900.f*screena;
		float viewsizey=900.f;
		set2dcamera(0.f,viewsizey,0.f,viewsizex);
		//draw the game name
		//dash_drawtext(viewsizex-100.f,viewsizey-128.f-90.f,dash_bars_gamename,1.8f);
		//draw the version number
		char temptext[256];
		sprintf(temptext,"%s%f","version ",dash_bars_gameversion);
		while(strlen(temptext)>9
		&& temptext[strlen(temptext)-2]!='.'
		&& temptext[strlen(temptext)-1]=='0'){
			temptext[strlen(temptext)-1]='\0';
		}
		dash_drawtext(viewsizex-100.f,viewsizey-128.f-40.f,temptext,1.8f);
		//draw the logo
		draw2dquad(viewsizex-512.f-40.f,viewsizey-128.f-10.f,512.f,128.f,dash_logo_texturecoords,0,0);
	}
	//xmb comes on and off
	if(xmbup==1){
		dashonpercent=100;
		dashon=1;
	}else{
		dashonpercent=0;
		dashon=0;
	}
}

