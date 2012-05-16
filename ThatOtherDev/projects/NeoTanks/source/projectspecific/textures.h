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
