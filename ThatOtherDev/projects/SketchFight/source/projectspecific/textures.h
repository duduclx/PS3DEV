#ifdef OPENGL
GLuint fighter1texture = NULL;
GLuint fighter2texture = NULL;
GLuint othertexture = NULL;
GLuint splashscreentexture = NULL;
#endif

#ifdef RSX
#include "fighter1texture.bin.h"
Image fighter1texture_image;
#include "fighter2texture.bin.h"
Image fighter2texture_image;
#include "othertexture.bin.h"
Image othertexture_image;
#include "splashscreentexture.bin.h"
Image splashscreentexture_image;
#endif

float backgroundtexturecoords[8];
float fightertexturecoords[2][16][8];

void setuptextures(){

	//load textures
	#ifdef OPENGL
	fighter1texture=loadtexture((char*)"Media/fighter1texture.png",mipmapping);
	fighter2texture=loadtexture((char*)"Media/fighter2texture.png",mipmapping);
	othertexture=loadtexture((char*)"Media/othertexture.png",mipmapping);
	splashscreentexture=loadtexture((char*)"Media/splashscreentexture.png",mipmapping);
	#endif
	#ifdef RSX
	fighter1texture_image = loadPng(fighter1texture_bin);
	fighter2texture_image = loadPng(fighter2texture_bin);
	othertexture_image = loadPng(othertexture_bin);
	splashscreentexture_image = loadPng(splashscreentexture_bin);
	#endif

	//texture coordinates for the background
	if(1){
		float xsize=1024.f;
		float ysize=1024.f-242.f;
		float xoffset=0.f;
		float yoffset=242.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		backgroundtexturecoords[0]=xoffset;
		backgroundtexturecoords[1]=yoffset+ysize;
		backgroundtexturecoords[2]=xoffset+xsize;
		backgroundtexturecoords[3]=yoffset+ysize;
		backgroundtexturecoords[4]=xoffset+xsize;
		backgroundtexturecoords[5]=yoffset;
		backgroundtexturecoords[6]=xoffset;
		backgroundtexturecoords[7]=yoffset;
	}
	//set the texture coordinates for the player
	for(int y=0;y<4;y++)for(int x=0;x<4;x++){
		int a=y*4+x;
		float xsize=256.f;
		float ysize=256.f;
		float xoffset=(float)x*xsize;
		float yoffset=(float)y*ysize;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		fightertexturecoords[0][a][0]=xoffset;
		fightertexturecoords[0][a][1]=yoffset+ysize;
		fightertexturecoords[0][a][2]=xoffset+xsize;
		fightertexturecoords[0][a][3]=yoffset+ysize;
		fightertexturecoords[0][a][4]=xoffset+xsize;
		fightertexturecoords[0][a][5]=yoffset;
		fightertexturecoords[0][a][6]=xoffset;
		fightertexturecoords[0][a][7]=yoffset;
	}
	for(int y=0;y<4;y++)for(int x=0;x<4;x++){
		int a=y*4+x;
		float xsize=256.f;
		float ysize=256.f;
		float xoffset=(float)x*xsize;
		float yoffset=(float)y*ysize;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		fightertexturecoords[1][a][0]=xoffset+xsize;
		fightertexturecoords[1][a][1]=yoffset+ysize;
		fightertexturecoords[1][a][2]=xoffset;
		fightertexturecoords[1][a][3]=yoffset+ysize;
		fightertexturecoords[1][a][4]=xoffset;
		fightertexturecoords[1][a][5]=yoffset;
		fightertexturecoords[1][a][6]=xoffset+xsize;
		fightertexturecoords[1][a][7]=yoffset;
	}

}
