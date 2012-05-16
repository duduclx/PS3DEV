float camposx;
float camposy;
float camposz;
float camangy;

float playerposx=0.f;
float playerposy=0.f;
float playermovx=0.f;
float playermovy=0.f;
float playerangy=0.f;
bool playergrounded=0;

float playeranimation=0.f;
float *playervertexmeshframe[5];

#include "projectspecific/meshes/mario.h"
#include "projectspecific/meshes/mario0.h"
#include "projectspecific/meshes/mario1.h"
#include "projectspecific/meshes/mario2.h"
#include "projectspecific/meshes/goomba.h"

#include "projectspecific/textures.h"
#include "projectspecific/entity.h"
#include "projectspecific/loadlevel.h"
#include "projectspecific/bumpintoworld.h"
#include "projectspecific/play.h"
#include "projectspecific/genworld.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Gambol");
	dash_bars_gameversion=0.2;

	//load and prep everything else
	setuptextures();

	//player animation prep
	playervertexmeshframe[0]=&mario0vertexarray[0];
	playervertexmeshframe[1]=&mario1vertexarray[0];
	playervertexmeshframe[2]=&mario0vertexarray[0];
	playervertexmeshframe[3]=&mario2vertexarray[0];
	playervertexmeshframe[4]=&mario0vertexarray[0];

	loadlevel(1);
	genworld();

	camposx=playerposx;
	camposy=playerposy;
	camposz=5.f;
	camangy=0.f;

}
