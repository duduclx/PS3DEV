#ifdef OPENGL
GLuint spritesheettexture = NULL;
GLuint borderdarknesstexture = NULL;
GLuint borderbloodtexture = NULL;
GLuint cloudshadowtexture = NULL;
GLuint tilebrighttexture = NULL;
GLuint tiledarktexture = NULL;
#endif

#ifdef RSX
#include "borderdarknesstexture.bin.h"
Image borderdarknesstexture_image;
#include "borderbloodtexture.bin.h"
Image borderbloodtexture_image;
/*#include "cloudshadowtexture.bin.h"
Image cloudshadowtexture_image;*/
#include "tilebrighttexture.bin.h"
Image tilebrighttexture_image;
#include "tiledarktexture.bin.h"
Image tiledarktexture_image;
#include "spritesheettexture.bin.h"
Image spritesheettexture_image;
#endif

#ifdef GX
GXTexObj spritesheettexture_GXTexObj;
TPLFile spritesheettextureTPL;
#include "spritesheettexture_tpl.h"
#include "spritesheettexture.h"
/*GXTexObj borderdarknesstexture_GXTexObj;
TPLFile borderdarknesstextureTPL;
#include "borderdarknesstexture_tpl.h"
#include "borderdarknesstexture.h"
GXTexObj borderbloodtexture_GXTexObj;
TPLFile borderbloodtextureTPL;
#include "borderbloodtexture_tpl.h"
#include "borderbloodtexture.h"
GXTexObj cloudshadowtexture_GXTexObj;
TPLFile cloudshadowtextureTPL;
#include "cloudshadowtexture_tpl.h"
#include "cloudshadowtexture.h"*/
GXTexObj tilebrighttexture_GXTexObj;
TPLFile tilebrighttextureTPL;
#include "tilebrighttexture_tpl.h"
#include "tilebrighttexture.h"
GXTexObj tiledarktexture_GXTexObj;
TPLFile tiledarktextureTPL;
#include "tiledarktexture_tpl.h"
#include "tiledarktexture.h"
#endif

float logotexturecoords[8];
float tilesettexturecoords[16][8];
float wallbordertexturecoords[8];
float walltexturecoords[8];
float persontexturecoords[4][8];
float decaltexturecoords[2][8];
float rockettexturecoords[8];
float reticletexturecoords[8];
float flashpointtexturecoords[8];
float flashlinetexturecoords[8];
float explosiontexturecoords[8];
float borderdarknesstexturecoords[8];
float borderbloodtexturecoords[8];
float cloudshadowtexturecoords[8];
float cratetexturecoords[4][8];
float cartexturecoords[8];

void setuptextures(){

	//load textures
	#ifdef OPENGL
	spritesheettexture=loadtexture((char*)"Media/spritesheettexture.png",mipmapping);
	borderdarknesstexture=loadtexture((char*)"Media/borderdarknesstexture.png",mipmapping);
	borderbloodtexture=loadtexture((char*)"Media/borderbloodtexture.png",mipmapping);
	cloudshadowtexture=loadtexture((char*)"Media/cloudshadowtexture.png",mipmapping);
	tilebrighttexture=loadtexture((char*)"Media/tilebrighttexture.png",mipmapping);
	tiledarktexture=loadtexture((char*)"Media/tiledarktexture.png",mipmapping);
	#endif
	#ifdef RSX	
	borderdarknesstexture_image = loadPng(borderdarknesstexture_bin);
	borderbloodtexture_image = loadPng(borderbloodtexture_bin);
	/*cloudshadowtexture_image = loadPng(cloudshadowtexture_bin);*/
	tilebrighttexture_image = loadPng(tilebrighttexture_bin);
	tiledarktexture_image = loadPng(tiledarktexture_bin);
	spritesheettexture_image = loadPng(spritesheettexture_bin);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&spritesheettextureTPL,(void *)spritesheettexture_tpl,spritesheettexture_tpl_size);
	TPL_GetTexture(&spritesheettextureTPL,spritesheettexture,&spritesheettexture_GXTexObj);
	/*TPL_OpenTPLFromMemory(&borderdarknesstextureTPL,(void *)borderdarknesstexture_tpl,borderdarknesstexture_tpl_size);
	TPL_GetTexture(&borderdarknesstextureTPL,borderdarknesstexture,&borderdarknesstexture_GXTexObj);
	TPL_OpenTPLFromMemory(&borderbloodtextureTPL,(void *)borderbloodtexture_tpl,borderbloodtexture_tpl_size);
	TPL_GetTexture(&borderbloodtextureTPL,borderbloodtexture,&borderbloodtexture_GXTexObj);
	TPL_OpenTPLFromMemory(&cloudshadowtextureTPL,(void *)cloudshadowtexture_tpl,cloudshadowtexture_tpl_size);
	TPL_GetTexture(&cloudshadowtextureTPL,cloudshadowtexture,&cloudshadowtexture_GXTexObj);*/
	TPL_OpenTPLFromMemory(&tilebrighttextureTPL,(void *)tilebrighttexture_tpl,tilebrighttexture_tpl_size);
	TPL_GetTexture(&tilebrighttextureTPL,tilebrighttexture,&tilebrighttexture_GXTexObj);
	TPL_OpenTPLFromMemory(&tiledarktextureTPL,(void *)tiledarktexture_tpl,tiledarktexture_tpl_size);
	TPL_GetTexture(&tiledarktextureTPL,tiledarktexture,&tiledarktexture_GXTexObj);
	#endif

	//set the texture coordinates
	for(int a=0;a<1;a++){
		float xsize=128.f-2.f;
		float ysize=512.f-2.f;
		float xoffset=256.f+1.f;
		float yoffset=384.f+1.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		logotexturecoords[0]=xoffset;
		logotexturecoords[1]=yoffset;
		logotexturecoords[2]=xoffset;
		logotexturecoords[3]=yoffset+ysize;
		logotexturecoords[4]=xoffset+xsize;
		logotexturecoords[5]=yoffset+ysize;
		logotexturecoords[6]=xoffset+xsize;
		logotexturecoords[7]=yoffset;
	}
	for(int a=0;a<16;a++){
		float xsize=128.f-28.f;
		float ysize=128.f-28.f;
		float xoffset=(float)floor((float)(a-(floor((float)a*0.5f)*2.f)))*128.f+14.f;
		float yoffset=(float)floor((float)a*0.5f)*128.f+14.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		tilesettexturecoords[a][0]=xoffset;
		tilesettexturecoords[a][1]=yoffset+ysize;
		tilesettexturecoords[a][2]=xoffset+xsize;
		tilesettexturecoords[a][3]=yoffset+ysize;
		tilesettexturecoords[a][4]=xoffset+xsize;
		tilesettexturecoords[a][5]=yoffset;
		tilesettexturecoords[a][6]=xoffset;
		tilesettexturecoords[a][7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=0.f;
		float ysize=0.f;
		float xoffset=448.f;
		float yoffset=704.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		wallbordertexturecoords[0]=xoffset;
		wallbordertexturecoords[1]=yoffset+ysize;
		wallbordertexturecoords[2]=xoffset+xsize;
		wallbordertexturecoords[3]=yoffset+ysize;
		wallbordertexturecoords[4]=xoffset+xsize;
		wallbordertexturecoords[5]=yoffset;
		wallbordertexturecoords[6]=xoffset;
		wallbordertexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=0.f;
		float ysize=0.f;
		float xoffset=448.f;
		float yoffset=832.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		walltexturecoords[0]=xoffset;
		walltexturecoords[1]=yoffset+ysize;
		walltexturecoords[2]=xoffset+xsize;
		walltexturecoords[3]=yoffset+ysize;
		walltexturecoords[4]=xoffset+xsize;
		walltexturecoords[5]=yoffset;
		walltexturecoords[6]=xoffset;
		walltexturecoords[7]=yoffset;
	}
	for(int a=0;a<4;a++){
		float xsize=128.f-28.f;
		float ysize=128.f-28.f;
		float xoffset=(float)floor((float)(a-(floor((float)a*0.5f)*2.f)))*128.f+14.f+512.f;
		float yoffset=(float)floor((float)a*0.5f)*128.f+14.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		persontexturecoords[a][0]=xoffset;
		persontexturecoords[a][1]=yoffset+ysize;
		persontexturecoords[a][2]=xoffset+xsize;
		persontexturecoords[a][3]=yoffset+ysize;
		persontexturecoords[a][4]=xoffset+xsize;
		persontexturecoords[a][5]=yoffset;
		persontexturecoords[a][6]=xoffset;
		persontexturecoords[a][7]=yoffset;
	}
	for(int a=0;a<2;a++){
		float xsize=128.f-28.f;
		float ysize=128.f-28.f;
		float xoffset=512.f+(float)floor((float)(a-(floor((float)a*0.5f)*2.f)))*128.f+14.f;
		float yoffset=256.f+(float)floor((float)a*0.5f)*128.f+14.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		decaltexturecoords[a][0]=xoffset;
		decaltexturecoords[a][1]=yoffset+ysize;
		decaltexturecoords[a][2]=xoffset+xsize;
		decaltexturecoords[a][3]=yoffset+ysize;
		decaltexturecoords[a][4]=xoffset+xsize;
		decaltexturecoords[a][5]=yoffset;
		decaltexturecoords[a][6]=xoffset;
		decaltexturecoords[a][7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=128.f-28.f;
		float ysize=128.f-28.f;
		float xoffset=512.f+14.f;
		float yoffset=512.f+14.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		rockettexturecoords[0]=xoffset;
		rockettexturecoords[1]=yoffset+ysize;
		rockettexturecoords[2]=xoffset+xsize;
		rockettexturecoords[3]=yoffset+ysize;
		rockettexturecoords[4]=xoffset+xsize;
		rockettexturecoords[5]=yoffset;
		rockettexturecoords[6]=xoffset;
		rockettexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=128.f-2.f;
		float ysize=128.f-2.f;
		float xoffset=256.f+1.f;
		float yoffset=896.f+1.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		reticletexturecoords[0]=xoffset;
		reticletexturecoords[1]=yoffset+ysize;
		reticletexturecoords[2]=xoffset+xsize;
		reticletexturecoords[3]=yoffset+ysize;
		reticletexturecoords[4]=xoffset+xsize;
		reticletexturecoords[5]=yoffset;
		reticletexturecoords[6]=xoffset;
		reticletexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=128.f-2.f;
		float ysize=128.f-2.f;
		float xoffset=512.f+1.f;
		float yoffset=384.f+1.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		flashpointtexturecoords[0]=xoffset;
		flashpointtexturecoords[1]=yoffset+ysize;
		flashpointtexturecoords[2]=xoffset+xsize;
		flashpointtexturecoords[3]=yoffset+ysize;
		flashpointtexturecoords[4]=xoffset+xsize;
		flashpointtexturecoords[5]=yoffset;
		flashpointtexturecoords[6]=xoffset;
		flashpointtexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=128.f-2.f;
		float ysize=128.f-2.f;
		float xoffset=640.f+1.f;
		float yoffset=384.f+1.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		flashlinetexturecoords[0]=xoffset;
		flashlinetexturecoords[1]=yoffset+ysize;
		flashlinetexturecoords[2]=xoffset+xsize;
		flashlinetexturecoords[3]=yoffset+ysize;
		flashlinetexturecoords[4]=xoffset+xsize;
		flashlinetexturecoords[5]=yoffset;
		flashlinetexturecoords[6]=xoffset;
		flashlinetexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=128.f-2.f;
		float ysize=128.f-2.f;
		float xoffset=512.f+1.f;
		float yoffset=384.f+1.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		explosiontexturecoords[0]=xoffset;
		explosiontexturecoords[1]=yoffset+ysize;
		explosiontexturecoords[2]=xoffset+xsize;
		explosiontexturecoords[3]=yoffset+ysize;
		explosiontexturecoords[4]=xoffset+xsize;
		explosiontexturecoords[5]=yoffset;
		explosiontexturecoords[6]=xoffset;
		explosiontexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=512.f;
		float ysize=512.f;
		float xoffset=0.f;
		float yoffset=0.f;
		xsize/=512.f;
		ysize/=512.f;
		xoffset/=512.f;
		yoffset/=512.f;
		borderdarknesstexturecoords[0]=xoffset;
		borderdarknesstexturecoords[1]=yoffset+ysize;
		borderdarknesstexturecoords[2]=xoffset+xsize;
		borderdarknesstexturecoords[3]=yoffset+ysize;
		borderdarknesstexturecoords[4]=xoffset+xsize;
		borderdarknesstexturecoords[5]=yoffset;
		borderdarknesstexturecoords[6]=xoffset;
		borderdarknesstexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=512.f;
		float ysize=512.f;
		float xoffset=0.f;
		float yoffset=0.f;
		xsize/=512.f;
		ysize/=512.f;
		xoffset/=512.f;
		yoffset/=512.f;
		borderbloodtexturecoords[0]=xoffset;
		borderbloodtexturecoords[1]=yoffset+ysize;
		borderbloodtexturecoords[2]=xoffset+xsize;
		borderbloodtexturecoords[3]=yoffset+ysize;
		borderbloodtexturecoords[4]=xoffset+xsize;
		borderbloodtexturecoords[5]=yoffset;
		borderbloodtexturecoords[6]=xoffset;
		borderbloodtexturecoords[7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=512.f;
		float ysize=512.f;
		float xoffset=0.f;
		float yoffset=0.f;
		xsize/=512.f;
		ysize/=512.f;
		xoffset/=512.f;
		yoffset/=512.f;
		cloudshadowtexturecoords[0]=xoffset;
		cloudshadowtexturecoords[1]=yoffset+ysize;
		cloudshadowtexturecoords[2]=xoffset+xsize;
		cloudshadowtexturecoords[3]=yoffset+ysize;
		cloudshadowtexturecoords[4]=xoffset+xsize;
		cloudshadowtexturecoords[5]=yoffset;
		cloudshadowtexturecoords[6]=xoffset;
		cloudshadowtexturecoords[7]=yoffset;
	}
	for(int a=0;a<4;a++){
		float xsize=128.f-2.f;
		float ysize=128.f-2.f;
		float xoffset=512.f+(float)floor((float)(a-(floor((float)a*0.5f)*2.f)))*128.f+1.f;
		float yoffset=640.f+(float)floor((float)a*0.5f)*128.f+1.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		cratetexturecoords[a][0]=xoffset;
		cratetexturecoords[a][1]=yoffset+ysize;
		cratetexturecoords[a][2]=xoffset+xsize;
		cratetexturecoords[a][3]=yoffset+ysize;
		cratetexturecoords[a][4]=xoffset+xsize;
		cratetexturecoords[a][5]=yoffset;
		cratetexturecoords[a][6]=xoffset;
		cratetexturecoords[a][7]=yoffset;
	}
	for(int a=0;a<1;a++){
		float xsize=256.f-2.f;
		float ysize=128.f-2.f;
		float xoffset=512.f+1.f;
		float yoffset=896.f+1.f;
		xsize/=1024.f;
		ysize/=1024.f;
		xoffset/=1024.f;
		yoffset/=1024.f;
		cartexturecoords[0]=xoffset;
		cartexturecoords[1]=yoffset+ysize;
		cartexturecoords[2]=xoffset+xsize;
		cartexturecoords[3]=yoffset+ysize;
		cartexturecoords[4]=xoffset+xsize;
		cartexturecoords[5]=yoffset;
		cartexturecoords[6]=xoffset;
		cartexturecoords[7]=yoffset;
	}

}

