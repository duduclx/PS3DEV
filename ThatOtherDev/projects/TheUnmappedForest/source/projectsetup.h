int gamestate=0;

float camx=0;
float camy=0;

const int maxmapsizex=1000;
const int maxmapsizey=1000;
#ifndef PS3
char map[maxmapsizex][maxmapsizey];
#endif
#ifdef PS3
int map[1000][1000];
#endif
int mapsizex=50;
int mapsizey=25;

#include "projectspecific/textures.h"
#include "projectspecific/things.h"
#include "projectspecific/text.h"

struct thing player;
int playerexp;
int playerexplastlevel;
int playerexpnextlevel;
int playerlevel;
int playermaxhealth;
int playerattacking;

void startnewgame(){
	//clean the map
	for(int x=0;x<maxmapsizex;x++)for(int y=0;y<maxmapsizey;y++)map[x][y]='g';
	//clean out old things
	while(thingcount>0)removethingfromlist(0);
	//load the map
	FILE *pFile=NULL;
	char lineread[1000];
	#ifdef WIN
	pFile=fopen("Media/world.dat","r");
	#endif
	#ifdef WII
	pFile=fopen("world.dat","r");
	#endif
	#ifdef PS3
	pFile=fopen("/dev_hdd0/game/UNMAPPEDF/USRDIR/world.dat","r");
	#endif
	if(pFile != NULL){
		fgets(lineread,1000,pFile);
		mapsizex=(int)atof(lineread);
		fgets(lineread,1000,pFile);
		mapsizey=(int)atof(lineread);
		for(int y=0;y<mapsizey;y++){
			fgets(lineread,1000,pFile);
			for(int x=0;x<mapsizex;x++)map[x][y]=lineread[x];
		}
		fclose (pFile);
	}
	//place things on the map
	for(int x=0;x<maxmapsizex;x++)for(int y=0;y<maxmapsizey;y++){
		if(map[x][y]=='s'){
			player.posx=(float)x;
			player.posy=(float)y;
			camx=player.posx;
			camy=player.posy;
		}
		if(map[x][y]=='1')makething(thingtype_monster1,(float)x,(float)y,0,0,0,0,0,0);
		if(map[x][y]=='2')makething(thingtype_monster2,(float)x,(float)y,0,0,0,0,0,0);
		if(map[x][y]=='3')makething(thingtype_monster3,(float)x,(float)y,0,0,0,0,0,0);
		if(map[x][y]=='4')makething(thingtype_monster4,(float)x,(float)y,0,0,0,0,0,0);
		if(map[x][y]=='5')makething(thingtype_monster5,(float)x,(float)y,0,0,0,0,0,0);
		if(map[x][y]=='c')makething(thingtype_chest,(float)x,(float)y,0,0,0,0,0,0);
	}
	//reset player info
	playerexp=0;
	playerexplastlevel=0;
	playerexpnextlevel=5;
	playerlevel=1;
	playermaxhealth=25;
	playerattacking=0;
	//reset remaining player info
	//player.type;
	//player.spawnx;
	//player.spawny;
	//player.posx;
	//player.posy;
	player.movx=0.f;
	player.movy=0.f;
	player.health=playermaxhealth;
	player.frame=0;
	player.frametime=0;
	player.direction=0;
	player.drawn=0;
}

#include "projectspecific/bumpintoworld.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"
#include "projectspecific/drawhud.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","The Unmapped Forest");
	dash_bars_gameversion=0.3;

	setuptextures();
	setuptext();
	startnewgame();

}
