//types
#define balltype_player		(0)
#define balltype_extratime	(1)
#define balltype_finish		(2)
#define balltype_glow		(3)

//struct info
typedef struct ball{
	int type;
	bool swinging;
	bool grounded;
	float posx,posy,movx,movy,swingendx,swingendy,swinglength;
}ball;

//keep a list of every one
#define maxballcount (5000)
struct ball balllist[maxballcount];
int ballcount=0;
int balltypecount[] = {0,0,0,0,};

//helpfull function for removing one from the list
void removeballfromlist(int num){
	balltypecount[balllist[num].type]-=1;
	if(num!=ballcount)
		for(int b=num;b<ballcount;b++)
			balllist[b]=balllist[b+1];
	ballcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeball(int type,float posx,float posy){
	//make one if there is room on the list
	if(ballcount<maxballcount){
		balltypecount[type]+=1;
		balllist[ballcount].type=type;
		balllist[ballcount].posx=posx;
		balllist[ballcount].posy=posy;
		balllist[ballcount].movx=0.f;
		balllist[ballcount].movy=0.f;
		ballcount+=1;
	}
}
