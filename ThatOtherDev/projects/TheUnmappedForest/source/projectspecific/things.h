//struct info
typedef struct thing{
	int type;
	float spawnx,spawny,posx,posy,movx,movy;
	int health;
	int frame;
	float frametime;
	int direction;
	bool drawn;
}thing;

const int thingtype_monster1	= 0;
const int thingtype_monster2	= 1;
const int thingtype_monster3	= 2;
const int thingtype_monster4	= 3;
const int thingtype_monster5	= 4;
const int thingtype_chest		= 5;

//keep a list of every one
struct thing thinglist[500];
int thingcount=0;

//helpfull function for removing one from the list
void removethingfromlist(int num){
	if(num!=thingcount)
		for(int b=num;b<thingcount;b++)
			thinglist[b]=thinglist[b+1];
	thingcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makething(int type,float posx,float posy,
			   float movx,float movy,float angle,
			   int frame,float frametime,int direction){
	//make one if there is room on the list
	if(thingcount<500){
		thinglist[thingcount].type=type;
		thinglist[thingcount].spawnx=posx;
		thinglist[thingcount].spawny=posy;
		thinglist[thingcount].posx=posx;
		thinglist[thingcount].posy=posy;
		thinglist[thingcount].movx=movx;
		thinglist[thingcount].movy=movy;
		thinglist[thingcount].health=100;
		thinglist[thingcount].frame=frame;
		thinglist[thingcount].frametime=frametime;
		thinglist[thingcount].direction=direction;
		thingcount+=1;
	}
}

