#ifdef OPENGL
GLuint mazetexture = NULL;
#endif

#ifdef RSX
#include "mazetexture.bin.h"
Image mazetexture_image;
#endif

#ifdef GX
GXTexObj mazetexture_GXTexObj;
TPLFile mazetextureTPL;
#include "mazetexture_tpl.h"
#include "mazetexture.h"
#endif

float colorpalettetexturecoords[5][8];
float playertexturecoords[8];
float backgroundtexturecoords[8];
float titletexturecoords[8];
float infotexturecoords[8];
float size1texturecoords[8];
float size2texturecoords[8];
float size3texturecoords[8];

void gentexturecoords(float (*coords),
					  float xsize,float ysize,
					  float xoffset,float yoffset,
					  float fullsizex,float fullsizey){
		xsize-=2.f;
		ysize-=2.f;
		xoffset+=1.f;
		yoffset+=1.f;
		xsize/=fullsizex;
		ysize/=fullsizey;
		xoffset/=fullsizex;
		yoffset/=fullsizey;
		coords[0]=xoffset;
		coords[1]=yoffset+ysize;
		coords[2]=xoffset+xsize;
		coords[3]=yoffset+ysize;
		coords[4]=xoffset+xsize;
		coords[5]=yoffset;
		coords[6]=xoffset;
		coords[7]=yoffset;
}

void setuptextures(){

	//load textures
	#ifdef OPENGL
	mazetexture=loadtexture((char*)"Media/mazetexture.png",mipmapping);
	#endif
	#ifdef RSX	
	mazetexture_image = loadPng(mazetexture_bin);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&mazetextureTPL,(void *)mazetexture_tpl,mazetexture_tpl_size);
	TPL_GetTexture(&mazetextureTPL,mazetexture,&mazetexture_GXTexObj);
	#endif

	//set the texture coordinates

	for(int x=0;x<5;x++){
		gentexturecoords(&colorpalettetexturecoords[x][0],
			0.f,0.f,
			32.f+(float)x*64.f,32.f,
			1024.f,1024.f);
	}
	gentexturecoords(&playertexturecoords[0],
		128.f,128.f,
		0.f,64.f,
		1024.f,1024.f);
	gentexturecoords(&backgroundtexturecoords[0],
		640.f,480.f,
		0.f,544.f,
		1024.f,1024.f);
	gentexturecoords(&titletexturecoords[0],
		640.f,128.f,
		0.f,256.f,
		1024.f,1024.f);
	gentexturecoords(&infotexturecoords[0],
		640.f,64.f,
		0.f,384.f,
		1024.f,1024.f);
	gentexturecoords(&size1texturecoords[0],
		640.f,32.f,
		0.f,448.f,
		1024.f,1024.f);
	gentexturecoords(&size2texturecoords[0],
		640.f,32.f,
		0.f,480.f,
		1024.f,1024.f);
	gentexturecoords(&size3texturecoords[0],
		640.f,32.f,
		0.f,512.f,
		1024.f,1024.f);

}

