#ifdef OPENGL
GLuint swingball2texture = NULL;
#endif

#ifdef RSX
#include "swingball2texture.bin.h"
Image swingball2texture_image;
#endif

#ifdef GX
GXTexObj swingball2texture_GXTexObj;
TPLFile swingball2textureTPL;
#include "swingball2texture_tpl.h"
#include "swingball2texture.h"
#endif

float logotexturecoords[8];

float balltexturecoords[8];
float glowtexturecoords[8];
float extratimetexturecoords[8];
float finishtexturecoords[8];

float gravitydowntexturecoords[8];
float gravitylefttexturecoords[8];
float gravityuptexturecoords[8];
float gravityrighttexturecoords[8];

float blocknormaltexturecoords[8];
float blockharmfultexturecoords[8];
float blocknoswingtexturecoords[8];
float blockghosttexturecoords[8];

float backgroundtexturecoords[8];

float reticletexturecoords[8];

float backgroundtiletexturecoords[8];

float linestarttexturecoords[8];
float linemiddletexturecoords[8];
float linestoptexturecoords[8];

float buttontexturecoords[2][9][8];

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
	swingball2texture=loadtexture((char*)"Media/swingball2texture.png",mipmapping);
	#endif
	#ifdef RSX	
	swingball2texture_image = loadPng(swingball2texture_bin);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&swingball2textureTPL,(void *)swingball2texture_tpl,swingball2texture_tpl_size);
	TPL_GetTexture(&swingball2textureTPL,swingball2texture,&swingball2texture_GXTexObj);
	#endif

	//set the texture coordinates
	gentexturecoords(&logotexturecoords[0],
		512.f,128.f,
		0.f,0.f,
		1024.f,1024.f);

	gentexturecoords(&balltexturecoords[0],
		128.f,128.f,
		0.f,128.f,
		1024.f,1024.f);
	gentexturecoords(&glowtexturecoords[0],
		128.f,128.f,
		128.f,128.f,
		1024.f,1024.f);
	gentexturecoords(&extratimetexturecoords[0],
		128.f,128.f,
		256.f,128.f,
		1024.f,1024.f);
	gentexturecoords(&finishtexturecoords[0],
		128.f,128.f,
		384.f,128.f,
		1024.f,1024.f);

	gentexturecoords(&gravitydowntexturecoords[0],
		128.f,128.f,
		0.f,256.f,
		1024.f,1024.f);
	gentexturecoords(&gravitylefttexturecoords[0],
		128.f,128.f,
		128.f,256.f,
		1024.f,1024.f);
	gentexturecoords(&gravityuptexturecoords[0],
		128.f,128.f,
		256.f,256.f,
		1024.f,1024.f);
	gentexturecoords(&gravityrighttexturecoords[0],
		128.f,128.f,
		384.f,256.f,
		1024.f,1024.f);

	gentexturecoords(&blocknormaltexturecoords[0],
		128.f,128.f,
		0.f,384.f,
		1024.f,1024.f);
	gentexturecoords(&blockharmfultexturecoords[0],
		128.f,128.f,
		128.f,384.f,
		1024.f,1024.f);
	gentexturecoords(&blocknoswingtexturecoords[0],
		128.f,128.f,
		256.f,384.f,
		1024.f,1024.f);
	gentexturecoords(&blockghosttexturecoords[0],
		128.f,128.f,
		384.f,384.f,
		1024.f,1024.f);

	gentexturecoords(&backgroundtexturecoords[0],
		512.f,512.f,
		0.f,512.f,
		1024.f,1024.f);

	gentexturecoords(&reticletexturecoords[0],
		128.f,128.f,
		896.f,768.f,
		1024.f,1024.f);

	gentexturecoords(&backgroundtiletexturecoords[0],
		128.f,128.f,
		896.f,896.f,
		1024.f,1024.f);

	gentexturecoords(&linestarttexturecoords[0],
		64.f,64.f,
		512.f,768.f,
		1024.f,1024.f);
	gentexturecoords(&linemiddletexturecoords[0],
		256.f,64.f,
		576.f,768.f,
		1024.f,1024.f);
	gentexturecoords(&linestoptexturecoords[0],
		64.f,64.f,
		832.f,768.f,
		1024.f,1024.f);

	for(int y=0;y<3;y++)for(int x=0;x<3;x++){
		gentexturecoords(
			&buttontexturecoords[0][y*3+x][0],
			64.f,64.f,
			512.f+(float)x*64.f,
			832.f+(float)y*64.f,
			1024.f,1024.f);
		gentexturecoords(
			&buttontexturecoords[1][y*3+x][0],
			64.f,64.f,
			704.f+(float)x*64.f,
			832.f+(float)y*64.f,
			1024.f,1024.f);
	}

}

