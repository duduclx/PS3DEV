//person struct
typedef struct person{
	float posx;
	float posy;
	float movx;
	float movy;
	bool grounded;
	int frame;
	int animation;
	float animationtime;
	bool direction;
	float drawingversion;
	float health;
}person;

//animation types
#define playeranimation_none		(0)
#define playeranimation_punching	(1)
#define playeranimation_kicking		(2)
#define playeranimation_hurt		(3)
#define playeranimation_crouching	(4)
#define playeranimation_walking		(5)

//camera data
float camx=0;
float camy=0;
float camz=0;

//remember this
int gamestate=0;

//player info
#define maxplayercount				(2)
person player[maxplayercount];
int playercount;

//setup a new game
void startnewgame(){
	//setup players
	playercount=2;
	player[0].posx=0.f-2.f;
	player[0].posy=0.f;
	player[0].movx=0.f;
	player[0].movy=0.f;
	player[0].grounded=0;
	player[0].frame=0;
	player[0].animation=0;
	player[0].animationtime=0.f;
	player[0].direction=0;
	player[0].drawingversion=0.f;
	player[0].health=1.f;
	player[1].posx=0.f+2.f;
	player[1].posy=0.f;
	player[1].movx=0.f;
	player[1].movy=0.f;
	player[1].grounded=0;
	player[1].frame=0;
	player[1].animation=0;
	player[1].animationtime=0.f;
	player[1].direction=1;
	player[1].drawingversion=0.f;
	player[1].health=1.f;
	camx=0;
	camy=0;
	camz=5;
}

//includes
#include "projectspecific/textures.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Sketch Fight");
	dash_bars_gameversion=0.3;

	//load textures and texture coordinates
	setuptextures();

	startnewgame();

}
