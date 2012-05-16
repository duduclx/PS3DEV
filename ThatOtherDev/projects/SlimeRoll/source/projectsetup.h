int gamestate=0;

float camx=0;
float camy=0;
float cama=0;
float camz=0;

float camxmov=0;
float camymov=0;
float camamov=0;
float camzmov=0;

float aimx=0;
float aimy=0;
float aiminworldx=0;
float aiminworldy=0;

bool spawning=0;
float spawnposx=0;
float spawnposy=0;
float spawnsize=0;

#include "projectspecific/textures.h"
#include "projectspecific/text.h"
#include "projectspecific/entity.h"
#include "projectspecific/saveandload.h"
#include "projectspecific/menu.h"
#include "projectspecific/play.h"
#include "projectspecific/edit.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Slime Roll");
	dash_bars_gameversion=0.3;

	setuptextures();

	setuptext();
	
}
