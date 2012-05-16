int gamestate=0;

#include "projectspecific/meshes/cylinder.h"
#include "projectspecific/meshes/sphere.h"
#include "projectspecific/meshes/floortile.h"

float score=0;
int highscore=0;

float camxpos=0,camypos=0,camzpos=0;
float camxmov=0,camymov=0,camzmov=0;
float camxang=0,camyang=0,camzang=0;

float plrxpos=0,plrypos=0,plrzpos=0;
float plrxmov=0,plrymov=0,plrzmov=0;
float plrxang=0,plryang=0,plrzang=0;

#ifdef OPENGL
GLuint splashscreen = NULL;
GLuint hudtexture = NULL;
GLuint meshtexture = NULL;
#endif

#ifdef GX
GXTexObj splashscreen_GXTexObj;
TPLFile splashscreenTPL;
#include "splashscreen_tpl.h"
#include "splashscreen.h"
GXTexObj hudtexture_GXTexObj;
TPLFile hudtextureTPL;
#include "hudtexture_tpl.h"
#include "hudtexture.h"
GXTexObj meshtexture_GXTexObj;
TPLFile meshtextureTPL;
#include "meshtexture_tpl.h"
#include "meshtexture.h"
#endif

#ifdef RSX
#include "hudtexture.bin.h"
Image hudtexture_image;
#include "meshtexture.bin.h"
Image meshtexture_image;
#endif

#include "projectspecific/music.h"
#include "projectspecific/text.h"
#include "projectspecific/cylinders.h"
#include "projectspecific/splashscreen.h"
#include "projectspecific/titlescreen.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"
#include "projectspecific/drawhud.h"

void resetgame(){

	char filename[256];
	#ifdef WIN
	sprintf(filename,"%s","cylinderdodge.score");
	#endif
	#ifdef PS3
	sprintf(filename,"%s","/dev_hdd0/game/CYLINDERD/USRDIR/cylinderdodge.score");
	#endif
	#ifdef WII
	sprintf(filename,"%s","cylinderdodge.score");
	#endif

	if(score>highscore){
		highscore=(int)ceil(score);
		FILE * pFile = fopen(filename,"wb");
		if(pFile != NULL){
			int data=highscore;
			fwrite(&data,sizeof(int),1,pFile);
			fclose(pFile);
		}
	}else{
		FILE * pFile = fopen(filename,"rb");
		if(pFile != NULL){
			int data=0;
			fread(&data,sizeof(int),1,pFile);
			fclose(pFile);
			highscore=data;
		}
	}

	camxpos=0,camypos=0,camzpos=0;
	camxmov=0,camymov=0,camzmov=0;
	camxang=0,camyang=0,camzang=0;

	plrxpos=0,plrypos=0,plrzpos=0;
	plrxmov=0,plrymov=0,plrzmov=0;
	plrxang=0,plryang=0,plrzang=0;

	cylindercount=0;

}

void projectsetup(){
	
	sprintf(dash_bars_gamename,"%s","Cylinder Dodge");
	dash_bars_gameversion=1.0;

	//load the texture
	#ifdef OPENGL
	splashscreen=loadtexture((char*)"Media/splashscreen.png",0);
	hudtexture=loadtexture((char*)"Media/hudtexture.png",0);
	meshtexture=loadtexture((char*)"Media/meshtexture.png",mipmapping);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&splashscreenTPL,(void *)splashscreen_tpl,splashscreen_tpl_size);
	TPL_GetTexture(&splashscreenTPL,splashscreen,&splashscreen_GXTexObj);
	TPL_OpenTPLFromMemory(&hudtextureTPL,(void *)hudtexture_tpl,hudtexture_tpl_size);
	TPL_GetTexture(&hudtextureTPL,hudtexture,&hudtexture_GXTexObj);
	TPL_OpenTPLFromMemory(&meshtextureTPL,(void *)meshtexture_tpl,meshtexture_tpl_size);
	TPL_GetTexture(&meshtextureTPL,meshtexture,&meshtexture_GXTexObj);
	#endif
	#ifdef RSX	
	hudtexture_image = loadPng(hudtexture_bin);
	meshtexture_image = loadPng(meshtexture_bin);
	#endif

	//rig texture coordinates
	for(int a=0; a<cylindervertexcount/3; a++){
		cylindertexturearray[a*3*2+0]=0.f;
		cylindertexturearray[a*3*2+1]=0.f;
		cylindertexturearray[a*3*2+2]=1.f;
		cylindertexturearray[a*3*2+3]=0.f;
		cylindertexturearray[a*3*2+4]=0.f;
		cylindertexturearray[a*3*2+5]=1.f;
	}
	for(int a=0; a<spherevertexcount/3; a++){
		spheretexturearray[a*3*2+0]=0.f;
		spheretexturearray[a*3*2+1]=0.f;
		spheretexturearray[a*3*2+2]=1.f;
		spheretexturearray[a*3*2+3]=0.f;
		spheretexturearray[a*3*2+4]=0.f;
		spheretexturearray[a*3*2+5]=1.f;
	}
	for(int a=0; a<floortilevertexcount/3; a++){
		floortiletexturearray[a*3*2+0]=0.f;
		floortiletexturearray[a*3*2+1]=0.f;
		floortiletexturearray[a*3*2+2]=1.f;
		floortiletexturearray[a*3*2+3]=0.f;
		floortiletexturearray[a*3*2+4]=0.f;
		floortiletexturearray[a*3*2+5]=1.f;
	}

	//set up the text
	setuptext();

	//start the music
	musicsetup();

	resetgame();

}
