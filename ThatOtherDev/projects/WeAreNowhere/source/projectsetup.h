#ifdef OPENGL
GLuint fonttexture = NULL;
#endif

#ifdef RSX
#include "fonttexture.bin.h"
Image fonttexture_image;
#endif

#include "projectspecific/text.h"

float textyscroll;
int optionscount;
int conversationstate;
int canusaythat[100];
int selectionnum;

bool holdingUp=0;
bool pressedUp=0;
bool holdingDown=0;
bool pressedDown=0;
bool holdingX=0;
bool pressedX=0;

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","We Are Nowhere");
	dash_bars_gameversion=0.2;

	//load textures
	#ifdef OPENGL
	fonttexture=loadtexture((char*)"Media/fonttexture.png",mipmapping);
	#endif
	#ifdef RSX	
	fonttexture_image = loadPng(fonttexture_bin);
	#endif

	conversationstate=0;
	for(int a=0;a<100;a++)canusaythat[a]=1;
	selectionnum=1;

	setuptext();

}
