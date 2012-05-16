//struct info
typedef struct wall{
	float x,y,w,h;
}wall;

//keep a list of every one
struct wall walllist[1000];
int wallcount;

//helpfull function for removing one from the list
void removewallfromlist(int num){
	if(num!=wallcount)
		for(int b=num;b<wallcount;b++)
			walllist[b]=walllist[b+1];
	wallcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makewall(float x,float y,float w,float h){
	//make one if there is room on the list
	if(wallcount<1000){
		walllist[wallcount].x=x;
		walllist[wallcount].y=y;
		walllist[wallcount].w=w;
		walllist[wallcount].h=h;
		wallcount+=1;
	}
}
