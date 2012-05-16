#ifdef OPENGL
GLuint worldtexture = NULL;
#endif

#ifdef GX
GXTexObj worldtexture_GXTexObj;
TPLFile worldtextureTPL;
#include "worldtexture_tpl.h"
#include "worldtexture.h"
#endif

#ifdef RSX
#include "worldtexture.bin.h"
Image worldtexture_image;
#endif

float grasstoptexturecoords[8];
float blocksidetexturecoords[3][2][8];
float blockbottomtexturecoords[8];

void gentexturecoords(float (*coords),
					  float xsize,float ysize,
					  float xoffset,float yoffset,
					  float fullsizex,float fullsizey){
		xsize-=0.f;
		ysize-=0.f;
		xoffset+=0.f;
		yoffset+=0.f;
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
	worldtexture=loadtexture((char*)"Media/worldtexture.png",mipmapping);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&worldtextureTPL,(void *)worldtexture_tpl,worldtexture_tpl_size);
	TPL_GetTexture(&worldtextureTPL,worldtexture,&worldtexture_GXTexObj);
	#endif
	#ifdef RSX	
	worldtexture_image = loadPng(worldtexture_bin);
	#endif

}

