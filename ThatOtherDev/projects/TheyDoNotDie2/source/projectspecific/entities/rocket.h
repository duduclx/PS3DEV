//struct info
typedef struct rocket{
	int shotby;
	float posx,posy,movx,movy,angle,health;
}rocket;

//keep a list of every one
#define maxrocketcount (50)
struct rocket rocketlist[maxrocketcount];
int rocketcount=0;

//helpfull function for removing one from the list
void removerocketfromlist(int num){
	if(num!=rocketcount)
		for(int b=num;b<rocketcount;b++)
			rocketlist[b]=rocketlist[b+1];
	rocketcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makerocket(int shotby,float posx,float posy,float movx,float movy,float angle){
	//make one if there is room on the list
	if(rocketcount<maxrocketcount){
		rocketlist[rocketcount].shotby=shotby;
		rocketlist[rocketcount].posx=posx;
		rocketlist[rocketcount].posy=posy;
		rocketlist[rocketcount].movx=movx;
		rocketlist[rocketcount].movy=movy;
		rocketlist[rocketcount].angle=angle;
		rocketlist[rocketcount].health=100.f;
		rocketcount+=1;
	}
}
