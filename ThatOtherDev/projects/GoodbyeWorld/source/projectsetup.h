#ifdef OPENGL
GLuint asteroidtexture = NULL;
GLuint dontgotexture = NULL;
GLuint shiptexture = NULL;
GLuint skytexture = NULL;
GLuint worldtexture = NULL;
#endif

#ifdef GX
GXTexObj polygontexture_GXTexObj;
TPLFile polygontextureTPL;
#include "polygontexture_tpl.h"
#include "polygontexture.h"
#endif

#ifdef RSX
#include "asteroid.bin.h"
Image asteroid_image;
#include "dontgo.bin.h"
Image dontgo_image;
#include "ship.bin.h"
Image ship_image;
#include "sky.bin.h"
Image sky_image;
#include "world.bin.h"
Image world_image;
#endif

float worldposx=0;
float worldposy=0;
float worldmovx=0;
float worldmovy=0;
float worldangl=0;

float playerposx=0;
float playerposy=0;
float playermovx=0;
float playermovy=0;
float playerangl=0;

float camx=0;
float camy=0;

#include "projectspecific/asteroids.h"
#include "projectspecific/play.h"
#include "projectspecific/drawworld.h"
#include "projectspecific/drawhud.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Goodby World");
	dash_bars_gameversion=1.1;

	//load textures
	#ifdef OPENGL
	asteroidtexture=loadtexture((char*)"Media/asteroidtexture.png",mipmapping);
	dontgotexture=loadtexture((char*)"Media/dontgotexture.png",mipmapping);
	shiptexture=loadtexture((char*)"Media/shiptexture.png",mipmapping);
	skytexture=loadtexture((char*)"Media/skytexture.png",mipmapping);
	worldtexture=loadtexture((char*)"Media/worldtexture.png",mipmapping);
	#endif
	#ifdef GX
	TPL_OpenTPLFromMemory(&polygontextureTPL,(void *)polygontexture_tpl,polygontexture_tpl_size);
	TPL_GetTexture(&polygontextureTPL,polygontexture,&polygontexture_GXTexObj);
	#endif
	#ifdef RSX	
	asteroid_image = loadPng(asteroid_bin);
	dontgo_image = loadPng(dontgo_bin);
	ship_image = loadPng(ship_bin);
	sky_image = loadPng(sky_bin);
	world_image = loadPng(world_bin);
	#endif

	//spawn some asteroids
	for(int a=0;a<100;a++){
		float sizex=(float)(rand()%250)*0.001f+0.03;
		float sizey=(float)(rand()%250)*0.001f+0.03;
		if(rand()%2==0){
			makeasteroid(
				(float)(rand()%400)*0.01f-2,//posx
				(float)(rand()%400)*0.01f-2,//posy
				(float)(rand()%100)*0.00006f-0.003,//movx
				(float)(rand()%100)*0.00006f-0.003,//movy
				sizex*0.75+sizey*0.25,//sizex
				sizey*0.75+sizex*0.25,//sizey
				randangle(),//angle
				(float)(rand()%100)*0.0003f-0.015);//movangle
		}else{
			makeasteroid(
				(float)(rand()%400)*0.01f-2,//posx
				(float)(rand()%400)*0.01f-2,//posy
				0,//movx
				0,//movy
				sizex*0.75+sizey*0.25,//sizex
				sizey*0.75+sizex*0.25,//sizey
				randangle(),//angle
				0);//movangle
		}
	}

}
