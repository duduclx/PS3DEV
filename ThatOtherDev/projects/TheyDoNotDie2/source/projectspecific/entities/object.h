//types
#define objecttype_crate			(0)
#define objecttype_crateexplosive	(1)
#define objecttype_cratemedical		(2)
#define objecttype_crateammo		(3)
#define objecttype_car				(4)

//struct info
typedef struct object{
	int type;
	float posx,posy,movx,movy,angle,health;
}object;

//keep a list of every one
#define maxobjectcount (2)
struct object objectlist[mapsizex][mapsizey][maxobjectcount];
int objectcount[mapsizex][mapsizey];

//helpfull function for removing one from the list
void removeobjectfromlist(int x,int y,int num){
	if(num!=objectcount[x][y])
		for(int b=num;b<objectcount[x][y];b++)
			objectlist[x][y][b]=objectlist[x][y][b+1];
	objectcount[x][y]-=1;
}

//helpfull function for spawning one and adding it to the list
void makeobject(int x,int y,int type,float posx,float posy,float movx,float movy,float angle){
	//make one if there is room on the list
	if(objectcount[x][y]<maxobjectcount){
		objectlist[x][y][objectcount[x][y]].type=type;
		objectlist[x][y][objectcount[x][y]].posx=posx;
		objectlist[x][y][objectcount[x][y]].posy=posy;
		objectlist[x][y][objectcount[x][y]].movx=movx;
		objectlist[x][y][objectcount[x][y]].movy=movy;
		objectlist[x][y][objectcount[x][y]].angle=angle;
		objectlist[x][y][objectcount[x][y]].health=100.f;
		objectcount[x][y]+=1;
	}
}

void genobjects(){
	//place cars
	for(int n=0; n<(int)((float)mapsizex*(float)mapsizey*0.1f); n++){
		int x=rand()%(mapsizex-4)+2;
		int y=rand()%(mapsizey-4)+2;
		bool doit=1;
		for(int x2=x-2;x2<x+3;x2++)for(int y2=y-2;y2<y+3;y2++)
			if(objectcount[x2][y2]>0)doit=0;
		if(doit==1)
		if(map[x][y]==tiletype_streetline){
			if(maprotation[x][y]==0)
			if(map[x-1][y]==tiletype_streetline || map[x-1][y]==tiletype_street)
			if(map[x+1][y]==tiletype_streetline || map[x+1][y]==tiletype_street){
				if(rand()%2==0){
					makeobject(
						x,y,objecttype_car,
						(float)x+0.5f,(float)y+0.5f-0.8f,
						0.f,0.f,0.f*radiansindegree);
				}else{
					makeobject(
						x,y,objecttype_car,
						(float)x+0.5f,(float)y+0.5f+0.8f,
						0.f,0.f,180.f*radiansindegree);
				}
			}
			if(maprotation[x][y]==1)
			if(map[x][y-1]==tiletype_streetline || map[x][y-1]==tiletype_street)
			if(map[x][y+1]==tiletype_streetline || map[x][y+1]==tiletype_street){
				if(rand()%2==0){
					makeobject(
						x,y,objecttype_car,
						(float)x+0.5f+0.8f,(float)y+0.5f,
						0.f,0.f,90.f*radiansindegree);
				}else{
					makeobject(
						x,y,objecttype_car,
						(float)x+0.5f-0.8f,(float)y+0.5f,
						0.f,0.f,270.f*radiansindegree);
				}
			}
		}
	}
	//place crates
	for(int n=0; n<(int)((float)mapsizex*(float)mapsizey*0.025f); n++){
		float posx=(float)(rand()%(mapsizex*10-40)+20)*0.1f;
		float posy=(float)(rand()%(mapsizey*10-40)+20)*0.1f;
		if(touchworld(posx,posy,0.9f,1)==0){
			int x=(int)floor(posx);
			int y=(int)floor(posy);
			makeobject(x,y,objecttype_crate+rand()%4,posx,posy,0.f,0.f,randangle());
		}
	}
}