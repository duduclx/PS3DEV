//struct info
typedef struct cylinder{
	float xpos,ypos,zpos;
}cylinder;

//keep a list of every one
#define maxcylindercount (10000)
struct cylinder cylinderlist[maxcylindercount];
int cylindercount=0;

//helpfull function for removing one from the list
void removecylinderfromlist(int num){
	if(num!=cylindercount)
		for(int b=num;b<cylindercount;b++)
			cylinderlist[b]=cylinderlist[b+1];
	cylindercount-=1;
}

//helpfull function for spawning one and adding it to the list
void makecylinder(float xpos,float ypos,float zpos){
	//make one if there is room on the list
	if(cylindercount<maxcylindercount){
		cylinderlist[cylindercount].xpos=xpos;
		cylinderlist[cylindercount].ypos=ypos;
		cylinderlist[cylindercount].zpos=zpos;
		cylindercount+=1;
	}
}
