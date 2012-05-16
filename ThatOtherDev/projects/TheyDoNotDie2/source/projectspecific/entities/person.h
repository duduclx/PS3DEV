//types
#define persontype_player		(0)
#define persontype_zombie		(1)
#define persontype_survivor		(2)
#define persontype_other		(3)

//struct info
typedef struct person{
	int type,havetarget,targetnum,updateturn;
	float posx,posy,movx,movy,angle,health,bleedwait;
}person;

//keep a list of every one
#define maxpersoncount (1000)
struct person personlist[maxpersoncount];
int personcount=0;
int persontypecount[] = {0,0,0,0,0,0,};

//helpfull function for removing one from the list
void removepersonfromlist(int num){
	persontypecount[personlist[num].type]-=1;
	if(num!=personcount)
		for(int b=num;b<personcount;b++)
			personlist[b]=personlist[b+1];
	personcount-=1;
	for(int a=0;a<personcount;a++)if(personlist[a].havetarget==1){
		if(personlist[a].targetnum>num){
			personlist[a].targetnum-=1;
		}else if(personlist[a].targetnum==num){
			personlist[a].havetarget=0;
		}
	}
}

//helpfull function for spawning one and adding it to the list
void makeperson(int type,float posx,float posy,float movx,float movy,float angle){
	//make one if there is room on the list
	if(personcount<maxpersoncount){
		persontypecount[type]+=1;
		personlist[personcount].type=type;
		personlist[personcount].havetarget=0;
		personlist[personcount].targetnum=0;
		personlist[personcount].updateturn=rand()%10;
		personlist[personcount].posx=posx;
		personlist[personcount].posy=posy;
		personlist[personcount].movx=movx;
		personlist[personcount].movy=movy;
		personlist[personcount].angle=angle;
		personlist[personcount].health=100.f;
		personlist[personcount].bleedwait=0.f;
		personcount+=1;
	}
}

//find a target for one of them
float findnearesttarget(int personnum,int targettype,float maxdistance){
	for(int a=0;a<personcount;a++)if(personlist[a].type==targettype)if(a!=personnum)
	if(personlist[personnum].posx<personlist[a].posx+maxdistance
	&& personlist[personnum].posx>personlist[a].posx-maxdistance
	&& personlist[personnum].posy<personlist[a].posy+maxdistance
	&& personlist[personnum].posy>personlist[a].posy-maxdistance){
		float distance=dist2d(personlist[personnum].posx,personlist[personnum].posy,personlist[a].posx,personlist[a].posy);
		if(distance<maxdistance){
			personlist[personnum].havetarget=1;
			personlist[personnum].targetnum=a;
			maxdistance=distance;
		}
	}
	return maxdistance;
}
