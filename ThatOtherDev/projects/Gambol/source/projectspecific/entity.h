//types
#define entitytype_player		(0)
#define entitytype_enemy		(1)

//struct info
typedef struct entity{
	int type;
	float posx,posy,movx,movy;
	bool grounded,direction;
}entity;

//keep a list of every one
#define maxentitycount (500)
struct entity entitylist[maxentitycount];
int entitycount=0;
int entitytypecount[] = {0,0,};

//helpfull function for removing one from the list
void removeentityfromlist(int num){
	entitytypecount[entitylist[num].type]-=1;
	if(num!=entitycount)
		for(int b=num;b<entitycount;b++)
			entitylist[b]=entitylist[b+1];
	entitycount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeentity(int type,float posx,float posy,float movx,float movy){
	//make one if there is room on the list
	if(entitycount<maxentitycount){
		entitytypecount[type]+=1;
		entitylist[entitycount].type=type;
		entitylist[entitycount].posx=posx;
		entitylist[entitycount].posy=posy;
		entitylist[entitycount].movx=movx;
		entitylist[entitycount].movy=movy;
		entitylist[entitycount].grounded=0;
		entitylist[entitycount].direction=0;
		entitycount+=1;
	}
}
