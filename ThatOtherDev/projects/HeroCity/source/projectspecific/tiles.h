#define tilecount	(19)
float *tilevertexarray[tilecount][4];
float *tiletexturearray[tilecount];
float *tilenormalarray[tilecount][4];
int tilevertexcount[tilecount];
#ifndef PS3
polygoncollisionmesh *tilecollisionmesh[tilecount][4];
#endif

#include "meshes/tile0.h"
#include "meshes/tile1.h"
#include "meshes/tile2.h"
#include "meshes/tile3.h"
#include "meshes/tile4.h"
#include "meshes/tile5.h"
#include "meshes/tile6.h"
#include "meshes/tile7.h"
#include "meshes/tile8.h"
#include "meshes/tile9.h"
#include "meshes/tile10.h"
#include "meshes/tile11.h"
#include "meshes/tile12.h"
#include "meshes/tile13.h"
#include "meshes/tile14.h"
#include "meshes/tile15.h"
#include "meshes/tile16.h"
#include "meshes/tile17.h"
#include "meshes/tile18.h"

const int tiletype_nothing					=0;
const int tiletype_buildingtoproofcenter	=1;
const int tiletype_buildingtopcorner		=2;
const int tiletype_buildingtopblankwall		=3;
const int tiletype_buildingtopwindow		=4;
const int tiletype_buildingmiddlecorner		=5;
const int tiletype_buildingmiddleblankwall	=6;
const int tiletype_buildingmiddlewindow		=7;
const int tiletype_buildingbottomcorner		=8;
const int tiletype_buildingbottomblankwall	=9;
const int tiletype_buildingbottomdoor		=10;
const int tiletype_sidewalk0sided			=11;
const int tiletype_sidewalk1sided			=12;
const int tiletype_sidewalk2sidedcorner		=13;
const int tiletype_street					=14;
const int tiletype_streetwithline			=15;
const int tiletype_water					=16;
const int tiletype_buildingbottomwindow		=17;
const int tiletype_sidewalk2sidedboth		=18;

void setuptiles(){

	//get the data from the included headers into more usable arrays
	//vertex positions
	tilevertexarray[0][0]=tile0vertexarray;
	tilevertexarray[1][0]=tile1vertexarray;
	tilevertexarray[2][0]=tile2vertexarray;
	tilevertexarray[3][0]=tile3vertexarray;
	tilevertexarray[4][0]=tile4vertexarray;
	tilevertexarray[5][0]=tile5vertexarray;
	tilevertexarray[6][0]=tile6vertexarray;
	tilevertexarray[7][0]=tile7vertexarray;
	tilevertexarray[8][0]=tile8vertexarray;
	tilevertexarray[9][0]=tile9vertexarray;
	tilevertexarray[10][0]=tile10vertexarray;
	tilevertexarray[11][0]=tile11vertexarray;
	tilevertexarray[12][0]=tile12vertexarray;
	tilevertexarray[13][0]=tile13vertexarray;
	tilevertexarray[14][0]=tile14vertexarray;
	tilevertexarray[15][0]=tile15vertexarray;
	tilevertexarray[16][0]=tile16vertexarray;
	tilevertexarray[17][0]=tile17vertexarray;
	tilevertexarray[18][0]=tile18vertexarray;
	//texture coordinates
	tiletexturearray[0]=tile0texturearray;
	tiletexturearray[1]=tile1texturearray;
	tiletexturearray[2]=tile2texturearray;
	tiletexturearray[3]=tile3texturearray;
	tiletexturearray[4]=tile4texturearray;
	tiletexturearray[5]=tile5texturearray;
	tiletexturearray[6]=tile6texturearray;
	tiletexturearray[7]=tile7texturearray;
	tiletexturearray[8]=tile8texturearray;
	tiletexturearray[9]=tile9texturearray;
	tiletexturearray[10]=tile10texturearray;
	tiletexturearray[11]=tile11texturearray;
	tiletexturearray[12]=tile12texturearray;
	tiletexturearray[13]=tile13texturearray;
	tiletexturearray[14]=tile14texturearray;
	tiletexturearray[15]=tile15texturearray;
	tiletexturearray[16]=tile16texturearray;
	tiletexturearray[17]=tile17texturearray;
	tiletexturearray[18]=tile18texturearray;
	//normals
	tilenormalarray[0][0]=tile0normalarray;
	tilenormalarray[1][0]=tile1normalarray;
	tilenormalarray[2][0]=tile2normalarray;
	tilenormalarray[3][0]=tile3normalarray;
	tilenormalarray[4][0]=tile4normalarray;
	tilenormalarray[5][0]=tile5normalarray;
	tilenormalarray[6][0]=tile6normalarray;
	tilenormalarray[7][0]=tile7normalarray;
	tilenormalarray[8][0]=tile8normalarray;
	tilenormalarray[9][0]=tile9normalarray;
	tilenormalarray[10][0]=tile10normalarray;
	tilenormalarray[11][0]=tile11normalarray;
	tilenormalarray[12][0]=tile12normalarray;
	tilenormalarray[13][0]=tile13normalarray;
	tilenormalarray[14][0]=tile14normalarray;
	tilenormalarray[15][0]=tile15normalarray;
	tilenormalarray[16][0]=tile16normalarray;
	tilenormalarray[17][0]=tile17normalarray;
	tilenormalarray[18][0]=tile18normalarray;
	//vertex count
	tilevertexcount[0]=tile0vertexcount;
	tilevertexcount[1]=tile1vertexcount;
	tilevertexcount[2]=tile2vertexcount;
	tilevertexcount[3]=tile3vertexcount;
	tilevertexcount[4]=tile4vertexcount;
	tilevertexcount[5]=tile5vertexcount;
	tilevertexcount[6]=tile6vertexcount;
	tilevertexcount[7]=tile7vertexcount;
	tilevertexcount[8]=tile8vertexcount;
	tilevertexcount[9]=tile9vertexcount;
	tilevertexcount[10]=tile10vertexcount;
	tilevertexcount[11]=tile11vertexcount;
	tilevertexcount[12]=tile12vertexcount;
	tilevertexcount[13]=tile13vertexcount;
	tilevertexcount[14]=tile14vertexcount;
	tilevertexcount[15]=tile15vertexcount;
	tilevertexcount[16]=tile16vertexcount;
	tilevertexcount[17]=tile17vertexcount;
	tilevertexcount[18]=tile18vertexcount;
	
	//create the alternate rotations
	for(int a=0; a<tilecount; a++)
	for(int b=1; b<4; b++){
		tilevertexarray[a][b]=(float*)malloc(tilevertexcount[a]*3*sizeof(float));
		for(int c=0; c<tilevertexcount[a]; c++){
			float angle = (float)(b*90)*radiansindegree;
			float tempposx=tilevertexarray[a][0][c*3+0];
			float tempposy=tilevertexarray[a][0][c*3+1];
			float tempposz=tilevertexarray[a][0][c*3+2];
			tilevertexarray[a][b][c*3+0] = tempposz*sin(angle)+tempposx*cos(angle);
			tilevertexarray[a][b][c*3+1] = tempposy;
			tilevertexarray[a][b][c*3+2] = tempposz*cos(angle)-tempposx*sin(angle);
		}
	}

	//move in the the texture coordinates to hide things bleeding into the edges
	for(int a=0; a<tilecount; a++)
	for(int b=0; b<tilevertexcount[a]/3; b++)
	for(int c=0; c<3; c++){
		float amount=0.001f;
		if(mipmapping==1)amount=0.002f;
		bool increase=0;
		for(int d=0; d<3; d++)if(d!=c)
			if(tiletexturearray[a][(b*3+c)*2+0]<tiletexturearray[a][(b*3+d)*2+0]-amount*1.5)
				increase=1;
		if(increase==0){
			tiletexturearray[a][(b*3+c)*2+0]-=amount;
		}else{
			tiletexturearray[a][(b*3+c)*2+0]+=amount;
		}
		increase=0;
		for(int d=0; d<3; d++)if(d!=c)
			if(tiletexturearray[a][(b*3+c)*2+1]<tiletexturearray[a][(b*3+d)*2+1]-amount*1.5)
				increase=1;
		if(increase==0){
			tiletexturearray[a][(b*3+c)*2+1]-=amount;
		}else{
			tiletexturearray[a][(b*3+c)*2+1]+=amount;
		}
	}

	//texture coordinates are upside down
	for(int a=0; a<tilecount; a++)
	for(int b=0; b<tilevertexcount[a]; b++){
		tiletexturearray[a][b*2+1]*=-1;
		tiletexturearray[a][b*2+1]+=1;
	}

	//lower the mesh for the water so the collission mesh will be lower
	for(int a=0; a<tilevertexcount[16]; a++)for(int b=0; b<4; b++){
		tilevertexarray[16][b][a*3+1]-=3.5;
	}

	#ifndef PS3
	//create the collision meshes
	for(int a=0; a<tilecount; a++)for(int b=0; b<4; b++)
		tilecollisionmesh[a][b]=maketrianglepolygoncollisionmesh(
			tilevertexcount[a],
			tilevertexarray[a][b],
			NULL);
	#endif

	//lower the mesh for the water back up
	for(int a=0; a<tilevertexcount[16]; a++)for(int b=0; b<4; b++){
		tilevertexarray[16][b][a*3+1]+=3.5;
	}

}
