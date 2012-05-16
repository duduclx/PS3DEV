//struct info
typedef struct asteroid{
	float posx,posy,movx,movy,sizex,sizey,angle,movangle;
} asteroid;

//keep a list of every one
struct asteroid asteroids[100];
int n_asteroids=0;

//helpfull function for removing one from the list
void removeasteroidfromlist(int num){
	if(num!=n_asteroids)
		for(int b=num;b<n_asteroids;b++)
			asteroids[b]=asteroids[b+1];
	n_asteroids-=1;
}

//helpfull function for spawning one and adding it to the list
void makeasteroid(float posx,float posy,float movx,float movy,float sizex,float sizey,float angle,float movangle){
	//make the one if there is room on the list
	if(n_asteroids<100){
		asteroids[n_asteroids].posx=posx;
		asteroids[n_asteroids].posy=posy;
		asteroids[n_asteroids].movx=movx;
		asteroids[n_asteroids].movy=movy;
		asteroids[n_asteroids].sizex=sizex;
		asteroids[n_asteroids].sizey=sizey;
		asteroids[n_asteroids].angle=angle;
		asteroids[n_asteroids].movangle=movangle;
		n_asteroids+=1;
	}
}

