#ifdef OPENGL
GLuint blacktexture = NULL;
GLuint whitetexture = NULL;
GLuint fonttexture = NULL;
#endif

#ifdef RSX
#include "blacktexture.bin.h"
Image blacktexture_image;
#include "whitetexture.bin.h"
Image whitetexture_image;
#include "fonttexture.bin.h"
Image fonttexture_image;
#endif

float blacktexturecoords[8];
float whitetexturecoords[8];

void setuptextures(){

	//load textures
	#ifdef OPENGL
	blacktexture=loadtexture((char*)"Media/blacktexture.png",mipmapping);
	whitetexture=loadtexture((char*)"Media/whitetexture.png",mipmapping);
	fonttexture=loadtexture((char*)"Media/fonttexture.png",mipmapping);
	#endif
	#ifdef RSX
	blacktexture_image = loadPng(blacktexture_bin);
	whitetexture_image = loadPng(whitetexture_bin);
	fonttexture_image = loadPng(fonttexture_bin);
	#endif

	//texture coordinates for black
	if(1){
		float xsize=0.f;
		float ysize=0.f;
		float xoffset=0.5f;
		float yoffset=0.5f;
		blacktexturecoords[0]=xoffset;
		blacktexturecoords[1]=yoffset+ysize;
		blacktexturecoords[2]=xoffset+xsize;
		blacktexturecoords[3]=yoffset+ysize;
		blacktexturecoords[4]=xoffset+xsize;
		blacktexturecoords[5]=yoffset;
		blacktexturecoords[6]=xoffset;
		blacktexturecoords[7]=yoffset;
	}
	//texture coordinates for white
	if(1){
		float xsize=0.f;
		float ysize=0.f;
		float xoffset=0.5f;
		float yoffset=0.5f;
		whitetexturecoords[0]=xoffset;
		whitetexturecoords[1]=yoffset+ysize;
		whitetexturecoords[2]=xoffset+xsize;
		whitetexturecoords[3]=yoffset+ysize;
		whitetexturecoords[4]=xoffset+xsize;
		whitetexturecoords[5]=yoffset;
		whitetexturecoords[6]=xoffset;
		whitetexturecoords[7]=yoffset;
	}

}
