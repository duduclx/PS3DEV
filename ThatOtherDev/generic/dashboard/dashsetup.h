#ifdef PS3

	#include "dashps3.h"

#else

	#ifdef SDL
	SDL_Surface *dash_sprite = NULL;
	#endif
	#ifdef OPENGL
	GLuint dash_texture = NULL;
	#endif
	#ifdef GX
	GXTexObj dashboardtexture_GXTexObj;
	TPLFile dashboardtextureTPL;
	#include "dashboardtexture_tpl.h"
	#include "dashboardtexture.h"
	#endif

	#if defined(OPENGL) || defined(GX) || defined(RSX)
	void dashgentexturecoords(float* texturecoords,float x,float y,float w,float h){
		texturecoords[0]=x;
		texturecoords[1]=y+h;
		texturecoords[2]=x+w;
		texturecoords[3]=y+h;
		texturecoords[4]=x+w;
		texturecoords[5]=y;
		texturecoords[6]=x;
		texturecoords[7]=y;
		for(int a=0; a<4; a++){
			texturecoords[a*2+0]/=1024.f;
			texturecoords[a*2+1]/=256.f;
		}
	}
	#endif

	void dashprepdraw(){
		#ifdef OPENGL
		set2dcamera(0,screenh,0,screenw);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D,dash_texture);
		#endif
		#ifdef GX
		set2dcamera(0,screenh,0,screenw);
		GX_LoadTexObj(&dashboardtexture_GXTexObj, GX_TEXMAP0);
		GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
		GX_SetAlphaUpdate(GX_TRUE);
		#endif
	}

	void dashdonedraw(){
		#ifdef OPENGL
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		#endif
		#ifdef GX
		GX_SetAlphaUpdate(GX_FALSE);
		#endif
	}

	#include "dashtime.h"
	#include "dashcursor.h"
	#include "dashtext.h"
	#include "dashbutton.h"
	#include "dashonoff.h"
	#include "dashbars.h"
	#include "dashmenu.h"

#endif

void dashsetup(){
#ifdef PS3
	dashps3setup();
#else
	if(useopengl){
		#ifdef SDL
		#ifdef OPENGL
		SDL_Surface *tempsurface = IMG_LoadOptimizeAlpha("Media/dashboard.png");
		dash_sprite = SDL_CreateRGBSurface(
			tempsurface->flags,
			1024,256,
			tempsurface->format->BitsPerPixel,
			tempsurface->format->Rmask,
			tempsurface->format->Gmask,
			tempsurface->format->Bmask,
			tempsurface->format->Amask);
		SDL_SetAlpha(tempsurface,SDL_RLEACCEL,0);
		SDL_SetAlpha(dash_sprite,SDL_RLEACCEL,0);
		apply_surface(0,0,tempsurface,dash_sprite,NULL);
		SDL_FreeSurface(tempsurface);
		dash_texture=maketexturefromsurface(dash_sprite,0);
		SDL_FreeSurface(dash_sprite);
		#endif
		#endif
	}else if(usegx){
		#ifdef GX
		TPL_OpenTPLFromMemory(&dashboardtextureTPL,(void *)dashboardtexture_tpl,dashboardtexture_tpl_size);
		TPL_GetTexture(&dashboardtextureTPL,dashboardtexture,&dashboardtexture_GXTexObj);
		#endif
	}else if(usesdl){
		#ifdef SDL
		dash_sprite = IMG_LoadOptimizeAlpha("Media/dashboard.png");
		#endif
	}

	setupdashtime();
	setupdashcursor();
	setupdashtext();
	setupdashbutton();
	setupdashonoff();
	setupdashbars();
	setupdashmenu();
#endif
}
