typedef struct enemy{
	float posx,posy,movex,movey,size;
}enemy;

#define maxenemys (1000)

enemy enemys[maxenemys];
int n_enemys = 0;

void deleteenemy(int num){
	if(num!=n_enemys)for(int b=num;b<n_enemys;b++)enemys[b]=enemys[b+1];
	n_enemys-=1;
}

void makeenemy(float posx,float posy,float movex,float movey,float size){
	if(n_enemys<maxenemys){
		enemys[n_enemys].posx=posx;
		enemys[n_enemys].posy=posy;
		enemys[n_enemys].movex=movex;
		enemys[n_enemys].movey=movey;
		enemys[n_enemys].size=size;
		n_enemys++;
	}
}

float youx=0;
float youmovex=0;
float score=0;
float highscore=0;

#include "projectspecific/saveandload.h"

void resetgame(){
	while(n_enemys)deleteenemy(0);
	youx=0.f;
	youmovex=0.f;
	if(score>highscore){
		highscore=score;
		save();
	}else{
		load();
	}
	score=0;
}

//includes
#include "projectspecific/textures.h"
#include "projectspecific/text.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Dont Get Crushed");
	dash_bars_gameversion=1.2;

	setuptextures();
	setuptext();
	resetgame();

}
