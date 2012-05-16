float shootwait=0;
int ammo=0;
float health=0;
int score=0;
int highscore=0;

bool playerhurt=0;

#include "projectspecific/meshes/ammo.h"
#include "projectspecific/meshes/medkit.h"
#include "projectspecific/meshes/blast.h"
#include "projectspecific/meshes/happypeople.h"

float camxpos=0,camypos=0,camzpos=0;
float camxang=0,camyang=0,camzang=0;
float camxposmov=0,camyposmov=0,camzposmov=0;
float camxangmov=0,camyangmov=0,camzangmov=0;

#define worldgridsizex	(30)
#define worldgridsizez	(30)
#define worldtilesize	(40)
#define viewrange	(11)
const bool worldgrid[30][30]={
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,},
{1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,},
{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,},
{1,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,1,1,1,1,1,1,},
{1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,},
{1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
};

const float happypeopleradius=worldtilesize*0.3f;

int camxgridpos=0;
int camygridpos=0;
int camzgridpos=0;

#ifdef OPENGL
GLuint texture = NULL;
GLuint hudtexture = NULL;
#endif

#ifdef GX
GXTexObj texture_GXTexObj;
TPLFile textureTPL;
#include "texture_tpl.h"
#include "texture.h"
GXTexObj hudtexture_GXTexObj;
TPLFile hudtextureTPL;
#include "hudtexture_tpl.h"
#include "hudtexture.h"
#endif

#ifdef RSX
#include "worldtexture.bin.h"
Image worldtexture_image;
#include "hudtexture.bin.h"
Image hudtexture_image;
#endif

#include "projectspecific/music.h"
#include "projectspecific/titlescreen.h"
#include "projectspecific/text.h"
#include "projectspecific/people.h"
#include "projectspecific/things.h"
#include "projectspecific/bumpintoworld.h"
#include "projectspecific/genpeopleandthings.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"
#include "projectspecific/drawhud.h"

void resetgame(){

	char filename[256];
	#ifdef WIN
	sprintf(filename,"%s","cherophobe.score");
	#endif
	#ifdef PS3
	sprintf(filename,"%s","/dev_hdd0/game/CHEROPHOB/USRDIR/cherophobe.score");
	#endif
	#ifdef WII
	sprintf(filename,"%s","cherophobe.score");
	#endif

	if(score>highscore){
		highscore=score;
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

	shootwait=0;
	ammo=25;
	health=100;
	score=0;

	cleanoutpeopleandthings();

	camxpos=0.f;
	camypos=0.f;
	camzpos=0.0f;
	camxang=0.f;
	camyang=0.f;
	camzang=0.f;
	camxposmov=0.f;
	camyposmov=0.f;
	camzposmov=0.f;
	camxangmov=0.f;
	camyangmov=0.f;
	camzangmov=0.f;

	camxpos=worldgridsizex*0.5f*worldtilesize-worldtilesize*0.55f;
	camypos=0;
	camzpos=worldgridsizez*0.5f*worldtilesize-worldtilesize*0.5f;

}

void projectsetup(){
	
	sprintf(dash_bars_gamename,"%s","Cherophobe");
	dash_bars_gameversion=1.0;

	//load the texture
	#ifdef OPENGL
	texture=loadtexture((char*)"Media/texture.png",mipmapping);
	hudtexture=loadtexture((char*)"Media/hudtexture.png",mipmapping);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&textureTPL,(void *)texture_tpl,texture_tpl_size);
	TPL_GetTexture(&textureTPL,texture,&texture_GXTexObj);
	TPL_OpenTPLFromMemory(&hudtextureTPL,(void *)hudtexture_tpl,hudtexture_tpl_size);
	TPL_GetTexture(&hudtextureTPL,hudtexture,&hudtexture_GXTexObj);
	#endif
	#ifdef RSX	
	worldtexture_image = loadPng(worldtexture_bin);
	hudtexture_image = loadPng(hudtexture_bin);
	#endif

	//texture coords are upside down... again...
	for(int a=0;a<ammovertexcount;a++)
		ammotexturearray[a*2+1]*=-1;
	for(int a=0;a<medkitvertexcount;a++)
		medkittexturearray[a*2+1]*=-1;
	for(int a=0;a<blastvertexcount;a++)
		blasttexturearray[a*2+1]*=-1;
	for(int a=0;a<happypeoplevertexcount;a++)
		happypeopletexturearray[a*2+1]*=-1;

	//set up the text
	setuptext();
	
	//start a new game
	resetgame();
	
	//start the music
	musicsetup();

}
