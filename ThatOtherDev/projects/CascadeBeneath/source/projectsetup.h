const float yousize=0.075;
float youx=0;
float youy=0;
float youxmov=0;
float youymov=0;
float wallspawntime=0;
float score=0;
float highscore=0;

#include "projectspecific/walls.h"
#include "projectspecific/saveandload.h"

void resetgame(){
	while(wallcount>0)
		removewallfromlist(0);
	youx=0;
	youy=0;
	youxmov=0;
	youymov=0;
	wallspawntime=0;
	if(score>highscore){
		highscore=score;
		save();
	}else{
		load();
	}
	score=0;
}

#include "projectspecific/textures.h"
#include "projectspecific/text.h"
#include "projectspecific/spherebumpworld.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Cascade Beneath");
	dash_bars_gameversion=1.1;

	setuptextures();
	setuptext();
	resetgame();

}
