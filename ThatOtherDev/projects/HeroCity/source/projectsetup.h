int gamestate=0;

int score=0;
int highscore=0;
int experience=0;

#include "projectspecific/meshes/sky.h"
#include "projectspecific/meshes/car.h"

#include "projectspecific/meshes/hero_default.h"
#include "projectspecific/meshes/hero_standing.h"
#include "projectspecific/meshes/hero_walking1.h"
#include "projectspecific/meshes/hero_walking2.h"
#include "projectspecific/meshes/hero_jumping.h"
#include "projectspecific/meshes/hero_flying.h"
#include "projectspecific/meshes/hero_attackl.h"
#include "projectspecific/meshes/hero_attackr.h"
float *herovertexarray[8];

#define aniframes	(20)
#include "projectspecific/meshes/zombie_default.h"
#include "projectspecific/meshes/zombie_standing.h"
#include "projectspecific/meshes/zombie_walking1.h"
#include "projectspecific/meshes/zombie_walking2.h"
float *zombievertexarray[5*aniframes];
#include "projectspecific/meshes/bigmonster_default.h"
#include "projectspecific/meshes/bigmonster_standing.h"
#include "projectspecific/meshes/bigmonster_walking1.h"
#include "projectspecific/meshes/bigmonster_walking2.h"
float *bigmonstervertexarray[5*aniframes];
#include "projectspecific/meshes/robot_default.h"
#include "projectspecific/meshes/robot_standing.h"
#include "projectspecific/meshes/robot_walking1.h"
#include "projectspecific/meshes/robot_walking2.h"
float *robotvertexarray[5*aniframes];

#ifdef WII
	int worldviewrange=40;
	int peopleviewrange=20;
#endif
#ifdef WIN
	int worldviewrange=40;
	int peopleviewrange=20;
#endif
#ifdef PS3
	int worldviewrange=30;
	int peopleviewrange=20;
#endif

int playerxgridpos=0;
int playerygridpos=0;
int playerzgridpos=0;

float playerxpos=0,playerypos=0,playerzpos=0;
float playerxang=0,playeryang=0,playerzang=0;
float camxpos=0,camypos=0,camzpos=0;
float camxang=0,camyang=0,camzang=0;

float playerxposmov=0,playeryposmov=0,playerzposmov=0;
float playerxangmov=0,playeryangmov=0,playerzangmov=0;
float camxposmov=0,camyposmov=0,camzposmov=0;
float camxangmov=0,camyangmov=0,camzangmov=0;

bool playergrounded=0;
bool playerjumping=0;
bool playerflying=0;
bool playerattackingl=0;
bool playerattackingr=0;

float playerframeprogress=0;
int playerlastframe=0;
int playernextframe=0;

float playerhealth=0;
float playerhealthregenwait=0;
float playerenergy=0;
float playerenergyregenwait=0;

#define playerradius	(2.5)

#ifdef OPENGL
GLuint hudtexture = NULL;
GLuint worldtexture = NULL;
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
GXTexObj worldtexture_GXTexObj;
TPLFile worldtextureTPL;
#include "worldtexture_tpl.h"
#include "worldtexture.h"
#endif

#ifdef RSX
#include "hudtexture.bin.h"
Image hudtexture_image;
#include "worldtexture.bin.h"
Image worldtexture_image;
#endif

#include "projectspecific/music.h"
#include "projectspecific/text.h"

#include "projectspecific/tiles.h"
#include "projectspecific/genworldgrid.h"
#include "projectspecific/bumpintoworld.h"

#include "projectspecific/people.h"

#include "projectspecific/drawsplashscreen.h"
#include "projectspecific/titlescreen.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"
#include "projectspecific/drawhud.h"

void resetgame(){

	char filename[256];

	#ifdef WIN
	sprintf(filename,"%s","herocity.score");
	#endif
	#ifdef PS3
	sprintf(filename,"%s","/dev_hdd0/game/HEROCITY1/USRDIR/herocity.score");
	#endif
	#ifdef WII
	sprintf(filename,"%s","herocity.score");
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

	#ifdef WIN
	sprintf(filename,"%s","herocity.exp");
	#endif
	#ifdef PS3
	sprintf(filename,"%s","/dev_hdd0/game/HEROCITY1/USRDIR/herocity.exp");
	#endif
	#ifdef WII
	sprintf(filename,"%s","herocity.exp");
	#endif
	if(experience!=0){
		FILE * pFile = fopen(filename,"wb");
		if(pFile != NULL){
			int data=experience;
			fwrite(&data,sizeof(int),1,pFile);
			fclose(pFile);
		}
	}else{
		FILE * pFile = fopen(filename,"rb");
		if(pFile != NULL){
			int data=0;
			fread(&data,sizeof(int),1,pFile);
			fclose(pFile);
			experience=data;
		}
	}

	//clear the people lists
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(personcount[x][z]>0)removepersonfromlist(x,z,0);

	//clean up
	genworldgrid_part0();
	//water and streets
	genworldgrid_part1();
	//sidewalks allyways and street correction
	genworldgrid_part2();
	//buildings
	genworldgrid_part3();
	//doors
	genworldgrid_part4();
	//multi colour buildings
	genworldgrid_part5();
	//street lines and sided sidewalks
	genworldgrid_part6();
	
	genworldbumpgrid();	
	
	int x=worldgridsizex/2;
	int y=streetlevel+4;
	int z=worldgridsizez/2;
	while(bumpgrid[x][z]==1){
		x=rand()%worldgridsizex;
		z=rand()%worldgridsizez;
	}
	playerxpos=x*worldtilesize;
	playerypos=y*worldtilesize;
	playerzpos=z*worldtilesize;
	
	playerframeprogress=0.5;
	playerlastframe=1;
	playernextframe=2;

	playerhealth=100;
	playerhealthregenwait=0;
	playerenergy=100;
	playerenergyregenwait=0;

	camxpos=playerxpos;
	camypos=playerypos;
	camzpos=playerzpos;

	playerxgridpos=(int)((playerxpos+worldtilesize*0.5f)/worldtilesize);
	playerygridpos=(int)((playerypos+worldtilesize*0.5f)/worldtilesize);
	playerzgridpos=(int)((playerzpos+worldtilesize*0.5f)/worldtilesize);

	while(totalpersoncount<500){
		int x=rand()%worldgridsizex;
		int z=rand()%worldgridsizez;
		if(bumpgrid[x][z]==0 && personcount[x][z]==0)
		if(x<playerxgridpos-peopleviewrange || x>playerxgridpos+peopleviewrange
		|| z<playerzgridpos-peopleviewrange || z>playerzgridpos+peopleviewrange)
			makeperson(
				rand()%persontypecount,
				x*worldtilesize,
				0-worldtilesize,
				z*worldtilesize);
	}

}

void projectsetup(){
	
	sprintf(dash_bars_gamename,"%s","Hero City");
	dash_bars_gameversion=0.5;

	float scalex=worldgridsizex*worldtilesize;
	float scaley=(worldgridsizex+worldgridsizez)*worldtilesize*0.5f;
	float scalez=worldgridsizez*worldtilesize;
	for(int a=0;a<skyvertexcount;a++){
		skyvertexarray[a*3+0]*=scalex;
		skyvertexarray[a*3+1]*=scaley;
		skyvertexarray[a*3+2]*=scalez;
	}

	herovertexarray[0]=hero_standingvertexarray;
	herovertexarray[1]=hero_walking1vertexarray;
	herovertexarray[2]=hero_standingvertexarray;
	herovertexarray[3]=hero_walking2vertexarray;
	herovertexarray[4]=hero_jumpingvertexarray;
	herovertexarray[5]=hero_flyingvertexarray;
	herovertexarray[6]=hero_attacklvertexarray;
	herovertexarray[7]=hero_attackrvertexarray;

	zombievertexarray[0*aniframes]=zombie_standingvertexarray;
	zombievertexarray[1*aniframes]=zombie_walking1vertexarray;
	zombievertexarray[2*aniframes]=zombie_standingvertexarray;
	zombievertexarray[3*aniframes]=zombie_walking2vertexarray;
	zombievertexarray[4*aniframes]=zombie_standingvertexarray;
	for(int a=0;a<4;a++)for(int b=1;b<aniframes;b++){
		zombievertexarray[a*aniframes+b]=(float*)malloc(zombie_defaultvertexcount*3*sizeof(float));
		for(int c=0; c<zombie_defaultvertexcount*3; c++)
			zombievertexarray[a*aniframes+b][c]=
				zombievertexarray[(a+0)*aniframes][c]*(1.f-((float)b/(float)aniframes))+
				zombievertexarray[(a+1)*aniframes][c]*((float)b/(float)aniframes);
	}

	bigmonstervertexarray[0*aniframes]=bigmonster_standingvertexarray;
	bigmonstervertexarray[1*aniframes]=bigmonster_walking1vertexarray;
	bigmonstervertexarray[2*aniframes]=bigmonster_standingvertexarray;
	bigmonstervertexarray[3*aniframes]=bigmonster_walking2vertexarray;
	bigmonstervertexarray[4*aniframes]=bigmonster_standingvertexarray;
	for(int a=0;a<4;a++)for(int b=1;b<aniframes;b++){
		bigmonstervertexarray[a*aniframes+b]=(float*)malloc(bigmonster_defaultvertexcount*3*sizeof(float));
		for(int c=0; c<bigmonster_defaultvertexcount*3; c++)
			bigmonstervertexarray[a*aniframes+b][c]=
				bigmonstervertexarray[(a+0)*aniframes][c]*(1.f-((float)b/(float)aniframes))+
				bigmonstervertexarray[(a+1)*aniframes][c]*((float)b/(float)aniframes);
	}

	robotvertexarray[0*aniframes]=robot_standingvertexarray;
	robotvertexarray[1*aniframes]=robot_walking1vertexarray;
	robotvertexarray[2*aniframes]=robot_standingvertexarray;
	robotvertexarray[3*aniframes]=robot_walking2vertexarray;
	robotvertexarray[4*aniframes]=robot_standingvertexarray;
	for(int a=0;a<4;a++)for(int b=1;b<aniframes;b++){
		robotvertexarray[a*aniframes+b]=(float*)malloc(robot_defaultvertexcount*3*sizeof(float));
		for(int c=0; c<robot_defaultvertexcount*3; c++)
			robotvertexarray[a*aniframes+b][c]=
				robotvertexarray[(a+0)*aniframes][c]*(1.f-((float)b/(float)aniframes))+
				robotvertexarray[(a+1)*aniframes][c]*((float)b/(float)aniframes);
	}

	//load the texture
	#ifdef OPENGL
	hudtexture=loadtexture((char*)"Media/hudtexture.png",0);
	worldtexture=loadtexture((char*)"Media/worldtexture.png",mipmapping);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&splashscreenTPL,(void *)splashscreen_tpl,splashscreen_tpl_size);
	TPL_GetTexture(&splashscreenTPL,splashscreen,&splashscreen_GXTexObj);
	TPL_OpenTPLFromMemory(&hudtextureTPL,(void *)hudtexture_tpl,hudtexture_tpl_size);
	TPL_GetTexture(&hudtextureTPL,hudtexture,&hudtexture_GXTexObj);
	TPL_OpenTPLFromMemory(&worldtextureTPL,(void *)worldtexture_tpl,worldtexture_tpl_size);
	TPL_GetTexture(&worldtextureTPL,worldtexture,&worldtexture_GXTexObj);
	#endif
	#ifdef RSX
	hudtexture_image = loadPng(hudtexture_bin);
	worldtexture_image = loadPng(worldtexture_bin);
	#endif

	//set up the text
	setuptext();

	//setup the world tiles
	setuptiles();

	//adjust texture coordinates
	for(int a=0; a<skyvertexcount; a++)
		skytexturearray[a*2+1]*=-1.f;
	for(int a=0; a<hero_defaultvertexcount; a++)
		hero_defaulttexturearray[a*2+1]*=-1.f;
	for(int a=0; a<zombie_defaultvertexcount; a++)
		zombie_defaulttexturearray[a*2+1]*=-1.f;
	for(int a=0; a<bigmonster_defaultvertexcount; a++)
		bigmonster_defaulttexturearray[a*2+1]*=-1.f;
	for(int a=0; a<robot_defaultvertexcount; a++)
		robot_defaulttexturearray[a*2+1]*=-1.f;
	for(int a=0; a<hero_defaultvertexcount; a++){
		hero_defaulttexturearray[a*2+0]*=0.25f;
		hero_defaulttexturearray[a*2+1]*=0.25f;
		hero_defaulttexturearray[a*2+0]+=0.5f;
		hero_defaulttexturearray[a*2+1]+=0.5f+0.25f;
	}
	for(int a=0; a<zombie_defaultvertexcount; a++){
		zombie_defaulttexturearray[a*2+0]*=0.25f;
		zombie_defaulttexturearray[a*2+1]*=0.25f;
		zombie_defaulttexturearray[a*2+0]+=0.5f;
		zombie_defaulttexturearray[a*2+1]+=0.75f+0.25f;
	}
	for(int a=0; a<bigmonster_defaultvertexcount; a++){
		bigmonster_defaulttexturearray[a*2+0]*=0.25f;
		bigmonster_defaulttexturearray[a*2+1]*=0.25f;
		bigmonster_defaulttexturearray[a*2+0]+=0.75f;
		bigmonster_defaulttexturearray[a*2+1]+=0.75f+0.25f;
	}
	for(int a=0; a<robot_defaultvertexcount; a++){
		robot_defaulttexturearray[a*2+0]*=0.25f;
		robot_defaulttexturearray[a*2+1]*=0.25f;
		robot_defaulttexturearray[a*2+0]+=0.75f;
		robot_defaulttexturearray[a*2+1]+=0.5f+0.25f;
	}

	musicsetup();

	resetgame();

}
