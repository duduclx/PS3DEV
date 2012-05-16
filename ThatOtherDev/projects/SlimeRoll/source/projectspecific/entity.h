//types
const int entitytype_wall										= 0;
const int entitytype_slime										= 1;
const int entitytype_goal										= 2;

//struct info
typedef struct entity{
	int type;
	float posx,posy,movx,movy,size;
}entity;

//keep a list of every one
struct entity entitylist[9001];
int entitycount=0;

//keep a count of each type
int entitytypecount[] = {0,0,0,};

//helpfull function for removing one from the list
void removeentityfromlist(int num){
	entitytypecount[entitylist[num].type]-=1;
	if(num!=entitycount)
		for(int b=num;b<entitycount;b++)
			entitylist[b]=entitylist[b+1];
	entitycount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeentity(int type,float posx,float posy,float movx,float movy,float size){
	//make one if there is room on the list
	if(entitycount<9000){
		entitylist[entitycount].type=type;
		entitylist[entitycount].posx=posx;
		entitylist[entitycount].posy=posy;
		entitylist[entitycount].size=size;
		entitycount+=1;
		entitytypecount[type]+=1;
	}
}
