#ifdef OPENGL
GLuint mariotexture = NULL;
GLuint goombatexture = NULL;
GLuint worldtexture = NULL;
#endif

#ifdef GX
GXTexObj mariotexture_GXTexObj;
TPLFile mariotextureTPL;
#include "mariotexture_tpl.h"
#include "mariotexture.h"
GXTexObj worldtexture_GXTexObj;
TPLFile worldtextureTPL;
#include "worldtexture_tpl.h"
#include "worldtexture.h"
#endif

#ifdef RSX
#include "mariotexture.bin.h"
Image mariotexture_image;
#include "goombatexture.bin.h"
Image goombatexture_image;
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
		xsize-=4.f;
		ysize-=4.f;
		xoffset+=2.f;
		yoffset+=2.f;
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
	mariotexture=loadtexture((char*)"Media/mariotexture.png",mipmapping);
	goombatexture=loadtexture((char*)"Media/goombatexture.png",mipmapping);
	worldtexture=loadtexture((char*)"Media/worldtexture.png",mipmapping);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&mariotextureTPL,(void *)mariotexture_tpl,mariotexture_tpl_size);
	TPL_GetTexture(&mariotextureTPL,mariotexture,&mariotexture_GXTexObj);
	TPL_OpenTPLFromMemory(&worldtextureTPL,(void *)worldtexture_tpl,worldtexture_tpl_size);
	TPL_GetTexture(&worldtextureTPL,worldtexture,&worldtexture_GXTexObj);
	#endif
	#ifdef RSX	
	mariotexture_image = loadPng(mariotexture_bin);
	goombatexture_image = loadPng(goombatexture_bin);
	worldtexture_image = loadPng(worldtexture_bin);
	#endif

	//set the texture coordinates
	gentexturecoords(&grasstoptexturecoords[0],
		64.f,64.f,
		0.f,0.f,
		256.f,256.f);
	for(int x=0;x<3;x++)for(int y=0;y<2;y++)
	gentexturecoords(&blocksidetexturecoords[x][y][0],
		64.f,64.f,
		64.f*x,64.f*y+64.f,
		256.f,256.f);
	gentexturecoords(&blockbottomtexturecoords[0],
		64.f,64.f,
		64.f,0.f,
		256.f,256.f);

}

