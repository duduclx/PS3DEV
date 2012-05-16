//struct info
typedef struct person{
	float xpos,ypos,zpos,yang;
	float xposmov,yposmov,zposmov;
	int health;
}person;

//keep a list of every one
#define maxpersoncount (5)
struct person personlist[worldgridsizex][worldgridsizez][maxpersoncount];
int personcount[worldgridsizex][worldgridsizez];
int totalpersoncount=0;

//helpfull function for removing one from the list
void removepersonfromlist(int x,int z,int num){
	if(num!=personcount[x][z])
		for(int b=num;b<personcount[x][z];b++)
			personlist[x][z][b]=personlist[x][z][b+1];
	personcount[x][z]-=1;
	totalpersoncount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeperson(float xpos,float ypos,float zpos){
	int x=(int)floor(xpos/worldtilesize);
	int z=(int)floor(zpos/worldtilesize);
	//make one if there is room on the list
	if(personcount[x][z]<maxpersoncount){
		personlist[x][z][personcount[x][z]].xpos=xpos;
		personlist[x][z][personcount[x][z]].ypos=ypos;
		personlist[x][z][personcount[x][z]].zpos=zpos;
		personlist[x][z][personcount[x][z]].yang=0.f;
		personlist[x][z][personcount[x][z]].xposmov=0.f;
		personlist[x][z][personcount[x][z]].yposmov=0.f;
		personlist[x][z][personcount[x][z]].zposmov=0.f;
		personlist[x][z][personcount[x][z]].health=5;
		personcount[x][z]+=1;
		totalpersoncount+=1;
	}
}
