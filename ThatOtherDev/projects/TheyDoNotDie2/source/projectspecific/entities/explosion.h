//struct info
typedef struct explosion{
	float posx,posy,angle,health;
}explosion;

//keep a list of every one
#define maxexplosioncount (50)
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
void makeexplosion(float posx,float posy,float angle){
	//make one if there is room on the list
	if(explosioncount<maxexplosioncount){
		explosionlist[explosioncount].posx=posx;
		explosionlist[explosioncount].posy=posy;
		explosionlist[explosioncount].angle=angle;
		explosionlist[explosioncount].health=100.f;
		explosioncount+=1;
	}
}
