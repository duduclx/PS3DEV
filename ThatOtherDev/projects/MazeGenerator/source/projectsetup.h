int gamestate=0;
#define gamestate_menu		(0)
#define gamestate_play		(1)

int menustate=0;

float playerposx=0.f;
float playerposy=0.f;

int solvecount=0;

#include "projectspecific/genmaze.h"
#include "projectspecific/bumpintoworld.h"
#include "projectspecific/textures.h"
#include "projectspecific/text.h"
#include "projectspecific/menu.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Maze Generator");
	dash_bars_gameversion=1.3;

	//load and prep everything else
	setuptextures();
	setuptext();

	//start at the menu
	gamestate=gamestate_menu;
	menustate=1;

	//load the number of mazes that have been solved
	FILE * pFile = NULL;
	char lineread[1000];
	#ifdef WIN
	pFile = fopen ("solvecount.dat" , "r");
	#endif
	#ifdef PS3
	pFile = fopen ("/dev_hdd0/game/MAZEGENRT/USRDIR/solvecount.dat" , "r");
	#endif
	#ifdef WII
	pFile = fopen ("solvecount.dat" , "r");
	#endif
	if(pFile != NULL){
		fgets(lineread,1000,pFile);
		solvecount=(int)atof(lineread);
		fclose (pFile);
	}

}
