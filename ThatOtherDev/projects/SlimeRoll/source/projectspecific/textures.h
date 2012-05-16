#ifdef OPENGL
GLuint slimetexture = NULL;
#endif

#ifdef RSX
#include "slimetexture.bin.h"
Image slimetexture_image;
#endif

float texturecoords[4][8];
float logotexturecoords[8];
float backgroundtexturecoords[8];
float reticletexturecoords[8];

void setuptextures(){

	//load textures
	#ifdef OPENGL
	slimetexture=loadtexture((char*)"Media/slimetexture.png",mipmapping);
	#endif
	#ifdef RSX	
	slimetexture_image = loadPng(slimetexture_bin);
	#endif

	//set the texture coordinates
	for(int a=0;a<4;a++){
		float xsize=256.f-4.f;
		float ysize=256.f-4.f;
		float xoffset=256.f*(float)a+2.f;
		float yoffset=1024.f-256.f+2.f;
		xsize/=1024.f;
		ysize/=2048.f;
		xoffset/=1024.f;
		yoffset/=2048.f;
		texturecoords[a][0]=xoffset;
		texturecoords[a][1]=yoffset+ysize;
		texturecoords[a][2]=xoffset+xsize;
		texturecoords[a][3]=yoffset+ysize;
		texturecoords[a][4]=xoffset+xsize;
		texturecoords[a][5]=yoffset;
		texturecoords[a][6]=xoffset;
		texturecoords[a][7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=512.f-4.f;
		float ysize=512.f-4.f;
		float xoffset=0.f+2.f;
		float yoffset=1024.f+2.f;
		xsize/=1024.f;
		ysize/=2048.f;
		xoffset/=1024.f;
		yoffset/=2048.f;
		logotexturecoords[0]=xoffset;
		logotexturecoords[1]=yoffset+ysize;
		logotexturecoords[2]=xoffset+xsize;
		logotexturecoords[3]=yoffset+ysize;
		logotexturecoords[4]=xoffset+xsize;
		logotexturecoords[5]=yoffset;
		logotexturecoords[6]=xoffset;
		logotexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=512.f-4.f;
		float ysize=512.f-4.f;
		float xoffset=0.f+2.f;
		float yoffset=1024.f+512.f+2.f;
		xsize/=1024.f;
		ysize/=2048.f;
		xoffset/=1024.f;
		yoffset/=2048.f;
		backgroundtexturecoords[0]=xoffset;
		backgroundtexturecoords[1]=yoffset+ysize;
		backgroundtexturecoords[2]=xoffset+xsize;
		backgroundtexturecoords[3]=yoffset+ysize;
		backgroundtexturecoords[4]=xoffset+xsize;
		backgroundtexturecoords[5]=yoffset;
		backgroundtexturecoords[6]=xoffset;
		backgroundtexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=256.f-4.f;
		float ysize=256.f-4.f;
		float xoffset=256.f*3.f+2.f;
		float yoffset=1024.f+2.f;
		xsize/=1024.f;
		ysize/=2048.f;
		xoffset/=1024.f;
		yoffset/=2048.f;
		reticletexturecoords[0]=xoffset;
		reticletexturecoords[1]=yoffset+ysize;
		reticletexturecoords[2]=xoffset+xsize;
		reticletexturecoords[3]=yoffset+ysize;
		reticletexturecoords[4]=xoffset+xsize;
		reticletexturecoords[5]=yoffset;
		reticletexturecoords[6]=xoffset;
		reticletexturecoords[7]=yoffset;
	}

}