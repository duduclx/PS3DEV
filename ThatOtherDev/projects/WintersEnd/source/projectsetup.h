#include "projectspecific/meshes/ground.h"
#include "projectspecific/meshes/snow.h"
#include "projectspecific/meshes/snowpeoplesmall.h"
#include "projectspecific/meshes/snowpeoplebig.h"
#include "projectspecific/meshes/tree.h"

const float worldtilesize=5;
const int streetlevel=1;

#define worldgridsizex	(25)
#define worldgridsizez	(25)
bool treegrid[worldgridsizex][worldgridsizez];
bool snowgrid[worldgridsizex*2][worldgridsizez*2];
float treegridheight[worldgridsizex][worldgridsizez];
float snowgridheight[worldgridsizex*2][worldgridsizez*2];

int currentlevel=1;

int totalsnow=0;
int snowcollected=0;

int playerxgridpos=0;
int playerzgridpos=0;

float playerxpos=0,playerzpos=0;
float playeryang=0;

float playerxposmov=0,playerzposmov=0;
float playeryangmov=0;

float playersize=0;

float camxpos=0,camypos=0,camzpos=0;
float camxang=0,camyang=0,camzang=0;

float goalcamxang=0,goalcamyang=0,goalcamzang=0;

#include "projectspecific/textures.h"
#include "projectspecific/genworldgrid.h"

void setupgame(){
	
	totalsnow=0;
	snowcollected=0;
	playersize=0.f;
	
	genworldgrid();

	int x=worldgridsizex/2;
	int z=worldgridsizez/2;
	playerxpos=x*worldtilesize;
	playerzpos=z*worldtilesize;	
	
	camxpos=playerxpos;
	camypos=0;
	camzpos=playerzpos;

	camxang=-25*radiansindegree;
	camyang=0;
	camzang=0;
	
	goalcamxang=-25*radiansindegree;
	goalcamyang=0;
	goalcamzang=0;
	
}

#include "projectspecific/bumpintoworld.h"
#include "projectspecific/play.h"
#include "projectspecific/text.h"
#include "projectspecific/drawworld.h"

void projectsetup(){

	//feed info to the dashboard
	sprintf(dash_bars_gamename,"%s","Winters End");
	dash_bars_gameversion=1.0;

	//load textures
	setuptextures();

	//setup text
	setuptext();

	//scale the meshes
	for(int a=0;a<groundvertexcount*3;a++)groundvertexarray[a]*=0.1;
	for(int a=0;a<snowvertexcount*3;a++)snowvertexarray[a]*=0.15;
	for(int a=0;a<snowpeoplesmallvertexcount*3;a++)snowpeoplesmallvertexarray[a]*=0.1;
	for(int a=0;a<snowpeoplebigvertexcount*3;a++)snowpeoplebigvertexarray[a]*=0.1;
	for(int a=0;a<treevertexcount*3;a++)treevertexarray[a]*=0.1;

	//scale and adjust the texture coordintes
	for(int a=0; a<groundvertexcount; a++){
		groundtexturearray[a*2+0]+=0.f;//x
		groundtexturearray[a*2+0]/=4.f;//x
		groundtexturearray[a*2+1]+=0.f;//y
		groundtexturearray[a*2+1]/=4.f;//y
	}
	for(int a=0; a<snowvertexcount; a++){
		snowtexturearray[a*2+0]+=1.f;//x
		snowtexturearray[a*2+0]/=4.f;//x
		snowtexturearray[a*2+1]+=0.f;//y
		snowtexturearray[a*2+1]/=4.f;//y
	}
	for(int a=0; a<snowpeoplesmallvertexcount; a++){
		snowpeoplesmalltexturearray[a*2+0]+=2.f;//x
		snowpeoplesmalltexturearray[a*2+0]/=4.f;//x
		snowpeoplesmalltexturearray[a*2+1]+=0.f;//y
		snowpeoplesmalltexturearray[a*2+1]/=4.f;//y
	}
	for(int a=0; a<snowpeoplebigvertexcount; a++){
		snowpeoplebigtexturearray[a*2+0]+=2.f;//x
		snowpeoplebigtexturearray[a*2+0]/=4.f;//x
		snowpeoplebigtexturearray[a*2+1]+=0.f;//y
		snowpeoplebigtexturearray[a*2+1]/=4.f;//y
	}
	for(int a=0; a<treevertexcount; a++){
		treetexturearray[a*2+0]+=3.f;//x
		treetexturearray[a*2+0]/=4.f;//x
		treetexturearray[a*2+1]+=0.f;//y
		treetexturearray[a*2+1]/=4.f;//y
	}

	//rig the normals for the snow mesh
	/*for(int a=0; a<snowvertexcount/3; a++){
		CVector3 g_vTriangle[3];
		g_vTriangle[0]=CVector3(
			snowvertexarray[a*9+0],
			snowvertexarray[a*9+1],
			snowvertexarray[a*9+2]);
		g_vTriangle[1]=CVector3(
			snowvertexarray[a*9+3],
			snowvertexarray[a*9+4],
			snowvertexarray[a*9+5]);
		g_vTriangle[2]=CVector3(
			snowvertexarray[a*9+6],
			snowvertexarray[a*9+7],
			snowvertexarray[a*9+8]);
		CVector3 vNormal = Normal(g_vTriangle);
		snownormalarray[a*9+0]=-vNormal.x;//vert1
		snownormalarray[a*9+1]=-vNormal.y;
		snownormalarray[a*9+2]=-vNormal.z;
		snownormalarray[a*9+3]=-vNormal.x;//vert2
		snownormalarray[a*9+4]=-vNormal.y;
		snownormalarray[a*9+5]=-vNormal.z;
		snownormalarray[a*9+6]=-vNormal.x;//vert3
		snownormalarray[a*9+7]=-vNormal.y;
		snownormalarray[a*9+8]=-vNormal.z;
	}*/

	//start the game
	setupgame();

}
