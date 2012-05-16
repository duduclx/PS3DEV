int gamestate=0;
#define gamestate_titlescreen	(0)
#define gamestate_menutoplay	(1)
#define gamestate_menutoedit	(2)
#define gamestate_play			(3)
#define gamestate_edit			(4)

int menustate=0;
int menuscroll=0;

float camx=0;
float camy=0;
float camz=0;

float aimx;
float aimy;
float aiminworldx;
float aiminworldy;
float swingaimangle;
int gravitydirection;
float glowspawnwait;

float score;

#include "projectspecific/entities/ball.h"

ball player;

#include "projectspecific/loadlevel.h"

void startnewgame(int levelnum){

	while(ballcount>0)removeballfromlist(0);

	player.type=0;
	player.swinging=0;
	player.grounded=0;
	player.posx=0.f;
	player.posy=0.f;
	player.movx=0.f;
	player.movy=0.f;
	player.swingendx=0.f;
	player.swingendy=0.f;
	player.swinglength=0.f;

	aimx=0.f;
	aimy=0.f;
	swingaimangle=0.f;
	gravitydirection=0;
	glowspawnwait=0.f;

	loadlevel(levelnum);

	aiminworldx=player.posx;
	aiminworldy=player.posy;

	camx=player.posx;
	camy=player.posy;
	camz=1.f;

	score=300.f;
	currentlevelnumber=levelnum;

}

#include "projectspecific/textures.h"
#include "projectspecific/text.h"
#include "projectspecific/menu.h"
#include "projectspecific/bumpintoworld.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"
#include "projectspecific/edit.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","SwingBall 2");
	dash_bars_gameversion=0.4;

	//load and prep everything else
	loadlevellist();
	setuptextures();
	setuptext();

}
