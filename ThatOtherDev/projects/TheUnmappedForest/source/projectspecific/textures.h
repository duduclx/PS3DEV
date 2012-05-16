#ifdef OPENGL
GLuint spritesheettexture = NULL;
#endif

#ifdef GX
GXTexObj spritesheettexture_GXTexObj;
TPLFile spritesheettextureTPL;
#include "spritesheettexture_tpl.h"
#include "spritesheettexture.h"
#endif

#ifdef RSX
#include "spritesheettexture.bin.h"
Image spritesheettexture_image;
#endif

float playertexture[8][4][8];
float monstertexture[5][7][8];
float logotexture[8];

void gentexturecoords(float (*coords),
					  float xsize,float ysize,
					  float xoffset,float yoffset,
					  float fullsizex,float fullsizey){
		xsize-=3.f;
		ysize-=3.f;
		xoffset+=1.5f;
		yoffset+=1.5f;
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
	spritesheettexture=loadtexture((char*)"Media/spritesheettexture.png",0);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&spritesheettextureTPL,(void *)spritesheettexture_tpl,spritesheettexture_tpl_size);
	TPL_GetTexture(&spritesheettextureTPL,spritesheettexture,&spritesheettexture_GXTexObj);
	#endif
	#ifdef RSX	
	spritesheettexture_image = loadPng(spritesheettexture_bin);
	#endif

	//set the texture coordinates
	for(int direction=0;direction<8;direction++)
	for(int frame=0;frame<4;frame++){
		float xsize=64;
		float ysize=128;
		float xoffset=xsize*frame;
		float yoffset=ysize*direction;
		if(frame==3)xsize=128;
		gentexturecoords(&playertexture[direction][frame][0],xsize,ysize,xoffset,yoffset,1024.f,1024.f);
	}
	for(int type=0;type<5;type++)
	for(int frame=0;frame<7;frame++){
		float xsize=1;
		float ysize=2;
		float xoffset=5.f+xsize*frame;
		float yoffset=3.f+ysize*type;
		monstertexture[type][frame][0]=(xoffset)/16.f			+(1.f/1024);
		monstertexture[type][frame][1]=(yoffset+ysize)/16.f		-(1.f/1024);
		monstertexture[type][frame][2]=(xoffset+xsize)/16.f		-(1.f/1024);
		monstertexture[type][frame][3]=(yoffset+ysize)/16.f		-(1.f/1024);
		monstertexture[type][frame][4]=(xoffset+xsize)/16.f		-(1.f/1024);
		monstertexture[type][frame][5]=(yoffset)/16.f			+(1.f/1024);
		monstertexture[type][frame][6]=(xoffset)/16.f			+(1.f/1024);
		monstertexture[type][frame][7]=(yoffset)/16.f			+(1.f/1024);
	}
	gentexturecoords(&logotexture[0],384,192,448,0,1024.f,1024.f);

}

