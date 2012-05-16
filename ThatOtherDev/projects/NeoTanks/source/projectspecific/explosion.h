//struct info
typedef struct explosion{
	float x,y,z,s,a;
	int target;
}explosion;

//keep a list of every one
#define maxexplosioncount (100)
struct explosion explosionlist[maxexplosioncount];
int explosioncount=0;

//helpfull function for removing one from the list
void removeexplosionfromlist(int num){
	if(num!=explosioncount)
		for(int b=num;b<explosioncount;b++)
			explosionlist[b]=explosionlist[b+1];
	explosioncount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeexplosion(float xpos,float ypos,float zpos,float size){
	if(explosioncount<maxexplosioncount){
		explosionlist[explosioncount].x=xpos;
		explosionlist[explosioncount].y=ypos;
		explosionlist[explosioncount].z=zpos;
		explosionlist[explosioncount].s=size;
		explosionlist[explosioncount].a=1.f;
		explosionlist[explosioncount].target=0;
		explosioncount+=1;
	}
}
