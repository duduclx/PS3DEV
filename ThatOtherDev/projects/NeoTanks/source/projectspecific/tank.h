//struct info
typedef struct tank{
	float x,y,z,ba,ta,xm,ym,zm;
	int target;
	bool player;
}tank;

//keep a list of every one
#define maxtankcount (150)
struct tank redtanklist[maxtankcount];
int redtankcount=0;
struct tank bluetanklist[maxtankcount];
int bluetankcount=0;

tank* playertank=NULL;

//helpfull function for removing one from the list
void removeredtankfromlist(int num){
	if(num!=redtankcount)for(int b=num;b<redtankcount;b++){
		redtanklist[b]=redtanklist[b+1];
		if(redtanklist[b].player==1)playertank=&redtanklist[b];
	}
	redtankcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeredtank(float xpos,float ypos,float zpos,float angle){
	if(redtankcount<maxtankcount){
		redtanklist[redtankcount].x=xpos;
		redtanklist[redtankcount].y=ypos;
		redtanklist[redtankcount].z=zpos;
		redtanklist[redtankcount].ba=angle;
		redtanklist[redtankcount].ta=angle;
		redtanklist[redtankcount].xm=0;
		redtanklist[redtankcount].ym=0;
		redtanklist[redtankcount].zm=0;
		redtanklist[redtankcount].target=0;
		redtanklist[redtankcount].player=0;
		redtankcount+=1;
	}
}

//helpfull function for removing one from the list
void removebluetankfromlist(int num){
	if(num!=bluetankcount)for(int b=num;b<bluetankcount;b++){
		bluetanklist[b]=bluetanklist[b+1];
		if(bluetanklist[b].player==1)playertank=&bluetanklist[b];
	}
	bluetankcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makebluetank(float xpos,float ypos,float zpos,float angle){
	if(bluetankcount<maxtankcount){
		bluetanklist[bluetankcount].x=xpos;
		bluetanklist[bluetankcount].y=ypos;
		bluetanklist[bluetankcount].z=zpos;
		bluetanklist[bluetankcount].ba=angle;
		bluetanklist[bluetankcount].ta=angle;
		bluetanklist[bluetankcount].xm=0;
		bluetanklist[bluetankcount].ym=0;
		bluetanklist[bluetankcount].zm=0;
		bluetanklist[bluetankcount].target=0;
		bluetanklist[bluetankcount].player=0;
		bluetankcount+=1;
	}
}
