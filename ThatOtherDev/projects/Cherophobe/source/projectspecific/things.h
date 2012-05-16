//types
#define thingtypecount			(3)

#define thingtype_ammo			(0)
#define thingtype_medkit		(1)
#define thingtype_blast			(2)

//struct info
typedef struct thing{
	int type;
	float xpos,ypos,zpos,yang;
	float xposmov,yposmov,zposmov;
}thing;

//keep a list of every one
#define maxthingcount (10)
struct thing thinglist[worldgridsizex][worldgridsizez][maxthingcount];
int thingcount[worldgridsizex][worldgridsizez];
int totalthingcount=0;
int totalthingtypecount[] = {0,0,0,};

//helpfull function for removing one from the list
void removethingfromlist(int x,int z,int num){
	totalthingtypecount[thinglist[x][z][num].type]-=1;
	if(num!=thingcount[x][z])
		for(int b=num;b<thingcount[x][z];b++)
			thinglist[x][z][b]=thinglist[x][z][b+1];
	thingcount[x][z]-=1;
	totalthingcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makething(int type,float xpos,float ypos,float zpos,float yang, float xposmov,float yposmov,float zposmov){
	int x=(int)floor(xpos/worldtilesize);
	int z=(int)floor(zpos/worldtilesize);
	//make one if there is room on the list
	if(thingcount[x][z]<maxthingcount){
		totalthingtypecount[type]+=1;
		thinglist[x][z][thingcount[x][z]].type=type;
		thinglist[x][z][thingcount[x][z]].xpos=xpos;
		thinglist[x][z][thingcount[x][z]].ypos=ypos;
		thinglist[x][z][thingcount[x][z]].zpos=zpos;
		thinglist[x][z][thingcount[x][z]].yang=yang;
		thinglist[x][z][thingcount[x][z]].xposmov=xposmov;
		thinglist[x][z][thingcount[x][z]].yposmov=yposmov;
		thinglist[x][z][thingcount[x][z]].zposmov=zposmov;
		thingcount[x][z]+=1;
		totalthingcount+=1;
	}
}
