int gamestate=0;

#include "projectspecific/meshes/sphere.h"
#include "projectspecific/meshes/tanktop.h"
#include "projectspecific/meshes/tankbottom.h"
#include "projectspecific/meshes/floorgridtile.h"

//float* redtanktoptexturearray = new float[tanktopvertexcount*2];
//float* redtankbottomtexturearray = new float[tankbottomvertexcount*2];
float redtanktoptexturearray[90*2];
float redtankbottomtexturearray[36*2];

//player variables
float playerxpos=0,playerypos=0,playerzpos=0;
float playerxang=0,playeryang=0,playerzang=0;
float playerxposmov=0,playeryposmov=0,playerzposmov=0;
float playerxangmov=0,playeryangmov=0,playerzangmov=0;
float playershootwait=0;

//camera variables
float camxpos=0,camypos=0,camzpos=0;
float camxang=0,camyang=0,camzang=0;
float camxposmov=0,camyposmov=0,camzposmov=0;
float camxangmov=0,camyangmov=0,camzangmov=0;

#include "projectspecific/textures.h"
#include "projectspecific/tank.h"
#include "projectspecific/blast.h"
#include "projectspecific/explosion.h"
#include "projectspecific/play.h"
#include "projectspecific/text.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Neo Tanks");
	dash_bars_gameversion=0.2;

	//load and prep everything else
	setuptextures();
	setuptext();

	//scale the floorgridtile vertex array
	for(int a=0;a<floorgridtilevertexcount*3;a++){
		floorgridtilevertexarray[a]*=0.05f;
	}
	//scale the tankbottom vertex array
	for(int a=0;a<tankbottomvertexcount*3;a++){
		tankbottomvertexarray[a]*=0.01f;
	}
	//scale the tanktop vertex array
	for(int a=0;a<tanktopvertexcount*3;a++){
		tanktopvertexarray[a]*=0.01f;
	}

	//adjust the blast/explosion texture coordinates
	for(int a=0; a<spherevertexcount; a++){
		spheretexturearray[a*2+0]+=5.f;//x
		spheretexturearray[a*2+0]/=8.f;//x
		spheretexturearray[a*2+1]+=0.f;//y
		spheretexturearray[a*2+1]/=4.f;//y
	}
	//adjust the tank top texture coordinates
	for(int a=0; a<tanktopvertexcount; a++){
		tanktoptexturearray[a*2+0]+=1.f;//x
		tanktoptexturearray[a*2+0]/=4.f;//x
		tanktoptexturearray[a*2+1]+=1.f;//y
		tanktoptexturearray[a*2+1]/=-2.f;//y
	}
	//adjust the tank bottom texture coordinates
	for(int a=0; a<tankbottomvertexcount; a++){
		tankbottomtexturearray[a*2+0]+=0.f;//x
		tankbottomtexturearray[a*2+0]/=4.f;//x
		tankbottomtexturearray[a*2+1]+=1.f;//y
		tankbottomtexturearray[a*2+1]/=-2.f;//y
	}
	//adjust the floor grid tile texture coordinates
	for(int a=0; a<floorgridtilevertexcount; a++){
		floorgridtiletexturearray[a*2+0]+=4.f;//x
		floorgridtiletexturearray[a*2+0]/=8.f;//x
		floorgridtiletexturearray[a*2+1]+=0.f;//y
		floorgridtiletexturearray[a*2+1]/=4.f;//y
	}

	//create the red tank top texture coordinates
	for(int a=0; a<tanktopvertexcount; a++){
		redtanktoptexturearray[a*2+0]=tanktoptexturearray[a*2+0];//x
		redtanktoptexturearray[a*2+1]=tanktoptexturearray[a*2+1]+0.5;//y
	}
	//create the red tank bottom texture coordinates
	for(int a=0; a<tankbottomvertexcount; a++){
		redtankbottomtexturearray[a*2+0]=tankbottomtexturearray[a*2+0];//x
		redtankbottomtexturearray[a*2+1]=tankbottomtexturearray[a*2+1]+0.5;//y
	}

	//setup camera
	camxang=-30/degreesinradian;
	camyang=0/degreesinradian;
	camzang=0/degreesinradian;
	camxpos=playerxpos;
	camypos=playerypos+1.5;
	camzpos=playerzpos;

}
