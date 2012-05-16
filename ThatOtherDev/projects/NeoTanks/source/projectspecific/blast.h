//struct info
typedef struct blast{
	float x,y,z,xm,ym,zm;
	int target;
}blast;

//keep a list of every one
#define maxblastcount (500)
struct blast blastlist[maxblastcount];
int blastcount=0;

//helpfull function for removing one from the list
void removeblastfromlist(int num){
	if(num!=blastcount)
		for(int b=num;b<blastcount;b++)
			blastlist[b]=blastlist[b+1];
	blastcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeblast(float xpos,float ypos,float zpos,float xmove,float ymove,float zmove){
	if(blastcount<maxblastcount){
		blastlist[blastcount].x=xpos;
		blastlist[blastcount].y=ypos;
		blastlist[blastcount].z=zpos;
		blastlist[blastcount].xm=xmove;
		blastlist[blastcount].ym=ymove;
		blastlist[blastcount].zm=zmove;
		blastlist[blastcount].target=0;
		blastcount+=1;
	}
}
