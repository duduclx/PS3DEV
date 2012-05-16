//constant info
#define wallbordersize (0.03f)

//struct info
typedef struct wall{
	float posx,posy,sizex,sizey;
}wall;

//keep a list of every one
#define maxwallcount (7)
struct wall walllist[mapsizex][mapsizey][maxwallcount];
int wallcount[mapsizex][mapsizey];

//helpfull function for removing one from the list
void removewallfromlist(int x,int y,int num){
	if(num!=wallcount[x][y])
		for(int b=num;b<wallcount[x][y];b++)
			walllist[x][y][b]=walllist[x][y][b+1];
	wallcount[x][y]-=1;
}

//helpfull function for spawning one and adding it to the list
void makewall(int x,int y,float posx,float posy,float sizex,float sizey){
	//dont make crazy thin walls
	if(sizex>0.025f && sizey>0.025f)
	//make one if there is room on the list
	if(wallcount[x][y]<maxwallcount){
		walllist[x][y][wallcount[x][y]].posx=posx;
		walllist[x][y][wallcount[x][y]].posy=posy;
		walllist[x][y][wallcount[x][y]].sizex=sizex;
		walllist[x][y][wallcount[x][y]].sizey=sizey;
		wallcount[x][y]+=1;
	}
}

void makewalladvanced(int xgridpos,int ygridpos,int rotation,
					  int pixelx1,int pixely1,int pixelx2,int pixely2){
	float offsetx=(float)xgridpos+0.5f;
	float offsety=(float)ygridpos+0.5f;
	float x1=(float)pixelx1/100.f-0.5f;
	float y1=(float)pixely1/100.f-0.5f;
	float x2=(float)pixelx2/100.f-0.5f;
	float y2=(float)pixely2/100.f-0.5f;
	float angle=-(float)rotation*90.f*radiansindegree;
	float rotatedx1=y1*sin(angle)+x1*cos(angle);
	float rotatedy1=y1*cos(angle)-x1*sin(angle);
	float rotatedx2=y2*sin(angle)+x2*cos(angle);
	float rotatedy2=y2*cos(angle)-x2*sin(angle);
	if(rotatedx1>rotatedx2){
		float temp=rotatedx1;
		rotatedx1=rotatedx2;
		rotatedx2=temp;
	}
	if(rotatedy1>rotatedy2){
		float temp=rotatedy1;
		rotatedy1=rotatedy2;
		rotatedy2=temp;
	}
	makewall(
		xgridpos,ygridpos,
		offsetx+rotatedx1,
		offsety+rotatedy1,
		rotatedx2-rotatedx1,
		rotatedy2-rotatedy1);
}

void genwalls(){
	//place new walls
	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++){
		if(map[x][y]==tiletype_buildingwall){
			makewalladvanced(x,y,maprotation[x][y],1,0,13,100);
		}
		if(map[x][y]==tiletype_buildingdoor){
			makewalladvanced(x,y,maprotation[x][y],1,0,13,5);
			makewalladvanced(x,y,maprotation[x][y],1,95,13,100);
		}
		if(map[x][y]==tiletype_buildingcorner){
			makewalladvanced(x,y,maprotation[x][y],1,0,13,99);
			makewalladvanced(x,y,maprotation[x][y],1,87,100,99);
		}
		if(map[x][y]==tiletype_buildinginnerwallconnectedtoouterwall){
			makewalladvanced(x,y,maprotation[x][y],1,0,13,100);
			makewalladvanced(x,y,maprotation[x][y],1,44,100,56);
		}
		if(map[x][y]==tiletype_buildinginnerdoor){
			makewalladvanced(x,y,maprotation[x][y],0,44,5,56);
			makewalladvanced(x,y,maprotation[x][y],95,44,100,56);
		}
		if(map[x][y]==tiletype_buildinginnerwall){
			makewalladvanced(x,y,maprotation[x][y],0,44,100,56);
		}
	}
}

//distructable walls
void digintowalls(float x,float y,float w,float h){
	for(int gridx=highint(0,(int)floor(x));gridx<lowint(1000,(int)ceil(x+w)+1);gridx++)
	for(int gridy=highint(0,(int)floor(y));gridy<lowint(1000,(int)ceil(y+h)+1);gridy++){
		int wallstocheck=wallcount[gridx][gridy];
		//loop threw every preexisting wall
		for(int a=0; a<wallstocheck; a++)
		//find one that overlaps the area we are clearing out
		if(walllist[gridx][gridy][a].posx+walllist[gridx][gridy][a].sizex>x
		&& walllist[gridx][gridy][a].posx<x+w
		&& walllist[gridx][gridy][a].posy+walllist[gridx][gridy][a].sizey>y
		&& walllist[gridx][gridy][a].posy<y+h){
			//subdivide it into smaller walls that arent in that area
			//see if we can make a devide left from the clear area
			if(walllist[gridx][gridy][a].posx<x){
				makewall(gridx,gridy,
					walllist[gridx][gridy][a].posx,
					walllist[gridx][gridy][a].posy,
					(x)-(walllist[gridx][gridy][a].posx),
					walllist[gridx][gridy][a].sizey);
				walllist[gridx][gridy][a].sizex=(walllist[gridx][gridy][a].posx+walllist[gridx][gridy][a].sizex)-(x);
				walllist[gridx][gridy][a].posx=x;
			}
			//see if we can make a devide right from the clear area
			if(walllist[gridx][gridy][a].posx+walllist[gridx][gridy][a].sizex>x+w){
				makewall(gridx,gridy,
					x+w,
					walllist[gridx][gridy][a].posy,
					(walllist[gridx][gridy][a].posx+walllist[gridx][gridy][a].sizex)-(x+w),
					walllist[gridx][gridy][a].sizey);
				walllist[gridx][gridy][a].sizex=(x+w)-(walllist[gridx][gridy][a].posx);
			}
			//see if we can make a devide down from the clear area
			if(walllist[gridx][gridy][a].posy<y){
				makewall(gridx,gridy,
					walllist[gridx][gridy][a].posx,
					walllist[gridx][gridy][a].posy,
					walllist[gridx][gridy][a].sizex,
					(y)-(walllist[gridx][gridy][a].posy));
				walllist[gridx][gridy][a].sizey=(walllist[gridx][gridy][a].posy+walllist[gridx][gridy][a].sizey)-(y);
				walllist[gridx][gridy][a].posy=y;
			}
			//see if we can make a devide up from the clear area
			if(walllist[gridx][gridy][a].posy+walllist[gridx][gridy][a].sizey>y+h){
				makewall(gridx,gridy,
					walllist[gridx][gridy][a].posx,
					y+h,
					walllist[gridx][gridy][a].sizex,
					(walllist[gridx][gridy][a].posy+walllist[gridx][gridy][a].sizey)-(y+h));
				walllist[gridx][gridy][a].sizey=(y+h)-(walllist[gridx][gridy][a].posy);
			}
			//then delete the original undevided wall
			removewallfromlist(gridx,gridy,a);
			//we don't want/need to check the walls we just created
			wallstocheck--;
			//but we dont want to skip the next wall on the list
			//which has just been lowered to the current position in the array
			a--;
		}
	}
}
