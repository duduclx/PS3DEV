//struct info
typedef struct shot{
	float angle,startx,starty,endx,endy;
}shot;

//keep a list of every one
#define maxshotcount (250)
struct shot shotlist[maxshotcount];
int shotcount=0;

//helpfull function for removing one from the list
void removeshotfromlist(int num){
	if(num!=shotcount)
		for(int b=num;b<shotcount;b++)
			shotlist[b]=shotlist[b+1];
	shotcount-=1;
}

//helpfull function for spawning one and adding it to the list
void makeshot(float angle,float startx,float starty,float startrange,float endrange,float damage,int shotbynum){
	//make one if there is room on the list
	if(shotcount<maxshotcount){

		shotlist[shotcount].angle=angle;
		shotlist[shotcount].startx=startx+cos(angle)*startrange;
		shotlist[shotcount].starty=starty+sin(angle)*startrange;
		shotlist[shotcount].endx=startx+cos(angle)*endrange;
		shotlist[shotcount].endy=starty+sin(angle)*endrange;

		float xportion=cos(angle)*(endrange-startrange)/100.f;
		float yportion=sin(angle)*(endrange-startrange)/100.f;
		float xpos=shotlist[shotcount].startx;
		float ypos=shotlist[shotcount].starty;
		for(int a=0;a<100;a++){
			for(int b=0;b<personcount;b++)if(b!=shotbynum)
			if(xpos<personlist[b].posx+0.25f
			&& xpos>personlist[b].posx-0.25f
			&& ypos<personlist[b].posy+0.25f
			&& ypos>personlist[b].posy-0.25f)
			if(dist2d(xpos,ypos,personlist[b].posx,personlist[b].posy)<0.25f){
				if(personlist[b].type==persontype_zombie){
					personlist[b].havetarget=1;
					personlist[b].targetnum=0;
					personlist[b].updateturn=-1;
				}
				shotlist[shotcount].endx=xpos;
				shotlist[shotcount].endy=ypos;
				personlist[b].movx+=cos(angle)*0.075f;
				personlist[b].movy+=sin(angle)*0.075f;
				if(personlist[b].type==persontype_player)damage*=0.25f;
				//if(personlist[b].type!=persontype_player){
					personlist[b].health-=damage;
					if(personlist[b].bleedwait<0.f){
						makedecal(
							decaltype_blood,
							personlist[b].posx,
							personlist[b].posy,
							angle+((float)(rand()%200)*0.1f-10.f)*radiansindegree);
						personlist[b].bleedwait=10.f;
					}
				//}
				a=100;
			}
			for(int b=0;b<rocketcount;b++)
			if(xpos<rocketlist[b].posx+0.25f
			&& xpos>rocketlist[b].posx-0.25f
			&& ypos<rocketlist[b].posy+0.25f
			&& ypos>rocketlist[b].posy-0.25f)
			if(dist2d(xpos,ypos,rocketlist[b].posx,rocketlist[b].posy)<0.25f){
				rocketlist[b].health=0.f;
				shotlist[shotcount].endx=xpos;
				shotlist[shotcount].endy=ypos;
				a=100;
			}
			if(touchworld(xpos,ypos,0.f,0)){
				shotlist[shotcount].endx=xpos;
				shotlist[shotcount].endy=ypos;
				a=100;
			}
			xpos+=xportion;
			ypos+=yportion;
		}
		shotcount+=1;

	}
}
