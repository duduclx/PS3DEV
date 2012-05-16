//types and stats
#define persontypecount			(3)

#define persontype_zombie		(0)
#define persontype_bigmonster	(1)
#define persontype_robot		(2)

const float persontype_radius[]		= {2.8f,	5.f,	2.8f,};
const float persontype_height[]		= {7.5f,	15.f,	7.5f,};
const float persontype_movespeed[]	= {0.0075f,	0.008f,	0.0125f,};

//struct info
typedef struct person{
	int type;
	float xpos,ypos,zpos,yang;
	float xmov,zmov;
	float health;
	float frame;
}person;

//keep a list of every one
#define maxpersoncount (5)
struct person personlist[worldgridsizex][worldgridsizez][maxpersoncount];
int personcount[worldgridsizex][worldgridsizez];
int totalpersoncount=0;
int totalpersontypecount[] = {0,0,0,};

//helpfull function for removing one from the list
void removepersonfromlist(int x,int z,int num){
	totalpersontypecount[personlist[x][z][num].type]-=1;
	if(num!=personcount[x][z])
		for(int b=num;b<personcount[x][z];b++)
			personlist[x][z][b]=personlist[x][z][b+1];
	personcount[x][z]-=1;
	totalpersoncount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeperson(int type,float posx,float posy,float posz){
	int x=(int)floor(posx/worldtilesize);
	int z=(int)floor(posz/worldtilesize);
	//make one if there is room on the list
	if(personcount[x][z]<maxpersoncount){
		totalpersontypecount[type]+=1;
		personlist[x][z][personcount[x][z]].type=type;
		personlist[x][z][personcount[x][z]].xpos=posx;
		personlist[x][z][personcount[x][z]].ypos=posy;
		personlist[x][z][personcount[x][z]].zpos=posz;
		personlist[x][z][personcount[x][z]].yang=0;
		personlist[x][z][personcount[x][z]].xmov=0;
		personlist[x][z][personcount[x][z]].zmov=0;
		personlist[x][z][personcount[x][z]].health=100;
		personlist[x][z][personcount[x][z]].frame=0;
		personcount[x][z]+=1;
		totalpersoncount+=1;
	}
}

