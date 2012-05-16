#define maxmazesizex		(135)
#define maxmazesizey		(85)
int maze[maxmazesizex][maxmazesizey];

int mazesizex;
int mazesizey;

bool mazecomplete;
int currentx;
int currenty;

void genmaze_start(){
	for(int y=0;y<mazesizey;y++)for(int x=0;x<mazesizex;x++){
		maze[x][y]=0;
		if(x-floor((double)x/2)*2==0)maze[x][y]=2;
		if(y-floor((double)y/2)*2==0)maze[x][y]=2;
		if(x==0)maze[x][y]=1;if(x==mazesizex-1)maze[x][y]=1;
		if(y==0)maze[x][y]=1;if(y==mazesizey-1)maze[x][y]=1;
		if(x-floor((double)x/2)*2==0 && y-floor((double)y/2)*2==0)maze[x][y]=1;
	}
	mazecomplete=0;
	currentx=1;
	currenty=1;
}

void genmaze_work(){
	if(mazecomplete==0){
		int tempint=0;
		if(maze[currentx-1][currenty]==2 && maze[currentx-2][currenty]==0)tempint=1;
		if(maze[currentx+1][currenty]==2 && maze[currentx+2][currenty]==0)tempint=1;
		if(maze[currentx][currenty-1]==2 && maze[currentx][currenty-2]==0)tempint=1;
		if(maze[currentx][currenty+1]==2 && maze[currentx][currenty+2]==0)tempint=1;
		if(tempint>0){
			tempint=rand()%4+1;
			if(tempint==1 && maze[currentx-1][currenty]==2 && maze[currentx-2][currenty]==0){//left
				maze[currentx][currenty]=3;
				maze[currentx-1][currenty]=3;
				maze[currentx-2][currenty]=3;
				currentx=currentx-2;}
			if(tempint==2 && maze[currentx+1][currenty]==2 && maze[currentx+2][currenty]==0){//right
				maze[currentx][currenty]=3;
				maze[currentx+1][currenty]=3;
				maze[currentx+2][currenty]=3;
				currentx=currentx+2;}
			if(tempint==3 && maze[currentx][currenty-1]==2 && maze[currentx][currenty-2]==0){//up
				maze[currentx][currenty]=3;
				maze[currentx][currenty-1]=3;
				maze[currentx][currenty-2]=3;
				currenty=currenty-2;}
			if(tempint==4 && maze[currentx][currenty+1]==2 && maze[currentx][currenty+2]==0){//down
				maze[currentx][currenty]=3;
				maze[currentx][currenty+1]=3;
				maze[currentx][currenty+2]=3;
				currenty=currenty+2;}
		}else{
			tempint=rand()%4+1;
			if(tempint==1 && maze[currentx-1][currenty]==3 && maze[currentx-2][currenty]==3){//left
				maze[currentx][currenty]=4;
				currentx=currentx-2;}
			if(tempint==2 && maze[currentx+1][currenty]==3 && maze[currentx+2][currenty]==3){//right
				maze[currentx][currenty]=4;
				currentx=currentx+2;}
			if(tempint==3 && maze[currentx][currenty-1]==3 && maze[currentx][currenty-2]==3){//up
				maze[currentx][currenty]=4;
				currenty=currenty-2;}
			if(tempint==4 && maze[currentx][currenty+1]==3 && maze[currentx][currenty+2]==3){//down
				maze[currentx][currenty]=4;
				currenty=currenty+2;}
		}
	}
	mazecomplete=1;
	for(int x=0;x<mazesizex;x++)for(int y=0;y<mazesizey;y++)if(maze[x][y]==0)mazecomplete=0;
}

void genmaze_finish(){
	for(int x=0;x<mazesizex;x++)for(int y=0;y<mazesizey;y++){
		if(maze[x][y]==0)maze[x][y]=0;
		if(maze[x][y]==1)maze[x][y]=1;
		if(maze[x][y]==2)maze[x][y]=1;
		if(maze[x][y]==3)maze[x][y]=0;
		if(maze[x][y]==4)maze[x][y]=0;
	}
	playerposx=1.5f;
	playerposy=1.5f;
}

void genmaze(){
	genmaze_start();
	while(mazecomplete==0)genmaze_work();
	genmaze_finish();
}
