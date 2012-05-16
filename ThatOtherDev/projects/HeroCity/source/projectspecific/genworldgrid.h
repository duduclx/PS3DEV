#define worldgridsizex	(40*5)
#define worldgridsizey	(8)
#define worldgridsizez	(40*5)
char worldgrid[worldgridsizex][worldgridsizey][worldgridsizez][2];

#define worldtilesize	(10)
#define streetlevel		(0)

bool watergrid[worldgridsizex/5][worldgridsizez/5];
bool streetgrid[worldgridsizex/5][worldgridsizez/5];
int buildingdata[worldgridsizex][worldgridsizez];
bool buildinggrid[worldgridsizex][worldgridsizez];

float worldgridcolor[worldgridsizex][worldgridsizez][3];

void genworldgrid_part0(){

	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	for(int a=0; a<3; a++){
		worldgridcolor[x][z][a]=1;
	}

	//clean the world grid
	for(int x=0; x<worldgridsizex; x++)
	for(int y=0; y<worldgridsizey; y++)
	for(int z=0; z<worldgridsizez; z++){
		worldgrid[x][y][z][0]=0;
		worldgrid[x][y][z][1]=0;
	}

}
void genworldgrid_part1(){

	//setup water grid
	for(int x=0; x<worldgridsizex/5; x++)
	for(int z=0; z<worldgridsizez/5; z++){
		watergrid[x][z]=1;
	}
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.00075; n++){
		int middlex=rand()%(worldgridsizex/5-20)+10;
		int middlez=rand()%(worldgridsizez/5-20)+10;
		int sizex=rand()%4+2;
		int sizez=rand()%4+2;
		bool overlap=0;
		for(int x=middlex-sizex; x<middlex+sizex+1; x++)
		for(int z=middlez-sizez; z<middlez+sizez+1; z++)
			if(watergrid[x][z]==1)overlap=1;
		if(n==0 || overlap==1)
		for(int x=middlex-sizex; x<middlex+sizex+1; x++)
		for(int z=middlez-sizez; z<middlez+sizez+1; z++){
			watergrid[x][z]=0;
		}
	}

	//setup street grid
	for(int x=0; x<worldgridsizex/5; x++)
	for(int z=0; z<worldgridsizez/5; z++){
		streetgrid[x][z]=0;
		if(watergrid[x][z]==1)streetgrid[x][z]=1;
	}
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.004; n++){
		int startx,startz;
		int x,z;
		//horizontal line
		startx=rand()%(worldgridsizex/5-2)+1;
		startz=rand()%(worldgridsizez/5-2)+1;
		if(!streetgrid[startx][startz]
		&& !streetgrid[startx][startz-1]
		&& !streetgrid[startx][startz+1]){
			streetgrid[startx][startz]=1;
			x=startx;z=startz;
			while(!streetgrid[x-1][z]){
				x--;streetgrid[x][z]=1;}
			x=startx;z=startz;
			while(!streetgrid[x+1][z]){
				x++;streetgrid[x][z]=1;}
		}
		//verticle line
		startx=rand()%(worldgridsizex/5-2)+1;
		startz=rand()%(worldgridsizez/5-2)+1;
		if(!streetgrid[startx][startz]
		&& !streetgrid[startx-1][startz]
		&& !streetgrid[startx+1][startz]){
			streetgrid[startx][startz]=1;
			x=startx;z=startz;
			while(!streetgrid[x][z-1]){
				z--;streetgrid[x][z]=1;}
			x=startx;z=startz;
			while(!streetgrid[x][z+1]){
				z++;streetgrid[x][z]=1;}
		}
	}
	
	//actually place the water and the streets
	for(int x=0; x<worldgridsizex; x++)for(int z=0; z<worldgridsizez; z++){
		if(streetgrid[(int)floor((float)x/5)][(int)floor((float)z/5)])
			worldgrid[x][streetlevel][z][0]=14;
		if(watergrid[(int)floor((float)x/5)][(int)floor((float)z/5)])
			worldgrid[x][streetlevel][z][0]=16;
	}

}
void genworldgrid_part2(){

	//place street sidewalks
	for(int x=1; x<worldgridsizex-1; x++)for(int z=1; z<worldgridsizez-1; z++){
		if(worldgrid[x][streetlevel][z][0]==14)
			if(worldgrid[x-1][streetlevel][z+0][0]==0
			|| worldgrid[x+1][streetlevel][z+0][0]==0
			|| worldgrid[x+0][streetlevel][z-1][0]==0
			|| worldgrid[x+0][streetlevel][z+1][0]==0			
			|| worldgrid[x-1][streetlevel][z+1][0]==0
			|| worldgrid[x-1][streetlevel][z-1][0]==0
			|| worldgrid[x+1][streetlevel][z+1][0]==0
			|| worldgrid[x+1][streetlevel][z-1][0]==0
			|| worldgrid[x-1][streetlevel][z+0][0]==16
			|| worldgrid[x+1][streetlevel][z+0][0]==16
			|| worldgrid[x+0][streetlevel][z-1][0]==16
			|| worldgrid[x+0][streetlevel][z+1][0]==16		
			|| worldgrid[x-1][streetlevel][z+1][0]==16
			|| worldgrid[x-1][streetlevel][z-1][0]==16
			|| worldgrid[x+1][streetlevel][z+1][0]==16
			|| worldgrid[x+1][streetlevel][z-1][0]==16)
				worldgrid[x][streetlevel][z][0]=11;
	}
	
	//place water sidewalks
	for(int x=1; x<worldgridsizex-1; x++)for(int z=1; z<worldgridsizez-1; z++)
	if(worldgrid[x][streetlevel][z][0]==16){
		if(worldgrid[x+1][streetlevel][z][0]!=16
		&& worldgrid[x+1][streetlevel][z][0]!=11)
			worldgrid[x][streetlevel][z][0]=11;
		if(worldgrid[x-1][streetlevel][z][0]!=16
		&& worldgrid[x-1][streetlevel][z][0]!=11)
			worldgrid[x][streetlevel][z][0]=11;
		if(worldgrid[x][streetlevel][z+1][0]!=16
		&& worldgrid[x][streetlevel][z+1][0]!=11)
			worldgrid[x][streetlevel][z][0]=11;
		if(worldgrid[x][streetlevel][z-1][0]!=16
		&& worldgrid[x][streetlevel][z-1][0]!=11)
			worldgrid[x][streetlevel][z][0]=11;
		if(worldgrid[x+1][streetlevel][z+1][0]!=16
		&& worldgrid[x+1][streetlevel][z+1][0]!=11)
			worldgrid[x][streetlevel][z][0]=11;
		if(worldgrid[x+1][streetlevel][z-1][0]!=16
		&& worldgrid[x+1][streetlevel][z-1][0]!=11)
			worldgrid[x][streetlevel][z][0]=11;
		if(worldgrid[x-1][streetlevel][z+1][0]!=16
		&& worldgrid[x-1][streetlevel][z+1][0]!=11)
			worldgrid[x][streetlevel][z][0]=11;
		if(worldgrid[x-1][streetlevel][z-1][0]!=16
		&& worldgrid[x-1][streetlevel][z-1][0]!=11)
			worldgrid[x][streetlevel][z][0]=11;
	}
	
	//L shaped buildings caused by water be gone
	for(int x=1; x<worldgridsizex/5-1; x++)
	for(int z=1; z<worldgridsizez/5-1; z++)
	if(watergrid[x][z]==1){
		int newx,newz;
		if(watergrid[x-1][z]==0 && watergrid[x][z-1]==0){
			//horizontal line
			newx=x*5;
			newz=z*5;
			while(!worldgrid[newx-1][streetlevel][newz][0]
			&& worldgrid[newx-1][streetlevel][newz-1][0]!=11
			&& worldgrid[newx-1][streetlevel][newz+1][0]!=11){
				newx--;worldgrid[newx][streetlevel][newz][0]=11;}
			//verticle line
			newx=x*5;
			newz=z*5;
			while(!worldgrid[newx][streetlevel][newz-1][0]
			&& worldgrid[newx-1][streetlevel][newz-1][0]!=11
			&& worldgrid[newx+1][streetlevel][newz-1][0]!=11){
				newz--;worldgrid[newx][streetlevel][newz][0]=11;}
		}
		if(watergrid[x+1][z]==0 && watergrid[x][z+1]==0){
			//horizontal line
			newx=x*5+5-1;
			newz=z*5+5-1;
			while(!worldgrid[newx+1][streetlevel][newz][0]
			&& worldgrid[newx+1][streetlevel][newz-1][0]!=11
			&& worldgrid[newx+1][streetlevel][newz+1][0]!=11){
				newx++;worldgrid[newx][streetlevel][newz][0]=11;}
			//verticle line
			newx=x*5+5-1;
			newz=z*5+5-1;
			while(!worldgrid[newx][streetlevel][newz+1][0]
			&& worldgrid[newx-1][streetlevel][newz+1][0]!=11
			&& worldgrid[newx+1][streetlevel][newz+1][0]!=11){
				newz++;worldgrid[newx][streetlevel][newz][0]=11;}
		}
		if(watergrid[x+1][z]==0 && watergrid[x][z-1]==0){
			//horizontal line
			newx=x*5+5-1;
			newz=z*5;
			while(!worldgrid[newx+1][streetlevel][newz][0]
			&& worldgrid[newx+1][streetlevel][newz-1][0]!=11
			&& worldgrid[newx+1][streetlevel][newz+1][0]!=11){
				newx++;worldgrid[newx][streetlevel][newz][0]=11;}
			//verticle line
			newx=x*5+5-1;
			newz=z*5;
			while(!worldgrid[newx][streetlevel][newz-1][0]
			&& worldgrid[newx-1][streetlevel][newz-1][0]!=11
			&& worldgrid[newx+1][streetlevel][newz-1][0]!=11){
				newz--;worldgrid[newx][streetlevel][newz][0]=11;}
		}
		if(watergrid[x-1][z]==0 && watergrid[x][z+1]==0){
			//horizontal line
			newx=x*5;
			newz=z*5+5-1;
			while(!worldgrid[newx-1][streetlevel][newz][0]
			&& worldgrid[newx-1][streetlevel][newz-1][0]!=11
			&& worldgrid[newx-1][streetlevel][newz+1][0]!=11){
				newx--;worldgrid[newx][streetlevel][newz][0]=11;}
			//verticle line
			newx=x*5;
			newz=z*5+5-1;
			while(!worldgrid[newx][streetlevel][newz+1][0]
			&& worldgrid[newx-1][streetlevel][newz+1][0]!=11
			&& worldgrid[newx+1][streetlevel][newz+1][0]!=11){
				newz++;worldgrid[newx][streetlevel][newz][0]=11;}
		}
	}
	
	//some ally ways
	for(int n=0; n<(float)worldgridsizex*(float)worldgridsizez*0.15; n++){
		int x,z;
		//verticle line
		x=rand()%worldgridsizex;
		z=rand()%worldgridsizez;
		if(worldgrid[x][streetlevel][z][0]==0
		&& worldgrid[x+1][streetlevel][z][0]==0
		&& worldgrid[x-1][streetlevel][z][0]==0
		&& worldgrid[x+2][streetlevel][z][0]==0
		&& worldgrid[x-2][streetlevel][z][0]==0
		&& worldgrid[x+3][streetlevel][z][0]==0
		&& worldgrid[x-3][streetlevel][z][0]==0){
			worldgrid[x][streetlevel][z][0]=11;
			int startz=z;
			while(z>0 && !worldgrid[x][streetlevel][z-1][0]){
				z--;worldgrid[x][streetlevel][z][0]=11;}
			z=startz;
			while(z<worldgridsizez && !worldgrid[x][streetlevel][z+1][0]){
				z++;worldgrid[x][streetlevel][z][0]=11;}
		}
		//horizontal line
		x=rand()%worldgridsizex;
		z=rand()%worldgridsizez;
		if(worldgrid[x][streetlevel][z][0]==0
		&& worldgrid[x][streetlevel][z+1][0]==0
		&& worldgrid[x][streetlevel][z-1][0]==0
		&& worldgrid[x][streetlevel][z+2][0]==0
		&& worldgrid[x][streetlevel][z-2][0]==0
		&& worldgrid[x][streetlevel][z+3][0]==0
		&& worldgrid[x][streetlevel][z-3][0]==0){
			worldgrid[x][streetlevel][z][0]=11;
			int startx=x;
			while(x>0 && !worldgrid[x-1][streetlevel][z][0]){
				x--;worldgrid[x][streetlevel][z][0]=11;}
			x=startx;
			while(x<worldgridsizex && !worldgrid[x+1][streetlevel][z][0]){
				x++;worldgrid[x][streetlevel][z][0]=11;}
		}
	}
	
}
void genworldgrid_part3(){
	
	//prep for multi floor buildings
	for(int x=0; x<worldgridsizex; x++)for(int z=0; z<worldgridsizez; z++){
		if(worldgrid[x][streetlevel][z][0]==0){
			buildingdata[x][z]=1;
		}else{
			buildingdata[x][z]=0;
		}
	}
	for(int x=1; x<worldgridsizex-1; x++)
	for(int z=1; z<worldgridsizez-1; z++)
	if(buildingdata[x][z]==1){
		int startx=x;
		int startz=z;
		int height=2+rand()%5;
		while(x<worldgridsizex-1 && buildingdata[x][z]==1){
			buildingdata[x][z]=height;
			while(z<worldgridsizez-1 && buildingdata[x][z+1]==1){
				z++;
				buildingdata[x][z]=height;
			}
			z=startz;
			x++;
		}
		x=startx;
	}
	
	//place buildings
	for(int x=1; x<worldgridsizex-1; x++)for(int z=1; z<worldgridsizez-1; z++)
	if(worldgrid[x][streetlevel][z][0]==0){
		//normal walls
		if(worldgrid[x][streetlevel][z+1][0]==11){
			worldgrid[x][streetlevel][z][0]=9;
			worldgrid[x][streetlevel][z][1]=0;
		}
		if(worldgrid[x+1][streetlevel][z][0]==11){
			worldgrid[x][streetlevel][z][0]=9;
			worldgrid[x][streetlevel][z][1]=1;
		}
		if(worldgrid[x][streetlevel][z-1][0]==11){
			worldgrid[x][streetlevel][z][0]=9;
			worldgrid[x][streetlevel][z][1]=2;
		}
		if(worldgrid[x-1][streetlevel][z][0]==11){
			worldgrid[x][streetlevel][z][0]=9;
			worldgrid[x][streetlevel][z][1]=3;
		}
		//windows
		if(worldgrid[x][streetlevel][z+1][0]==11
		&& worldgrid[x][streetlevel][z+2][0]==14){
			worldgrid[x][streetlevel][z][0]=17;
			worldgrid[x][streetlevel][z][1]=0;
		}
		if(worldgrid[x+1][streetlevel][z][0]==11
		&& worldgrid[x+2][streetlevel][z][0]==14){
			worldgrid[x][streetlevel][z][0]=17;
			worldgrid[x][streetlevel][z][1]=1;
		}
		if(worldgrid[x][streetlevel][z-1][0]==11
		&& worldgrid[x][streetlevel][z-2][0]==14){
			worldgrid[x][streetlevel][z][0]=17;
			worldgrid[x][streetlevel][z][1]=2;
		}
		if(worldgrid[x-1][streetlevel][z][0]==11
		&& worldgrid[x-2][streetlevel][z][0]==14){
			worldgrid[x][streetlevel][z][0]=17;
			worldgrid[x][streetlevel][z][1]=3;
		}
		//corners
		if(worldgrid[x-1][streetlevel][z+0][0]==11
		&& worldgrid[x+0][streetlevel][z+1][0]==11){
			worldgrid[x][streetlevel][z][0]=8;
			worldgrid[x][streetlevel][z][1]=0;
		}
		if(worldgrid[x+1][streetlevel][z+0][0]==11
		&& worldgrid[x+0][streetlevel][z+1][0]==11){
			worldgrid[x][streetlevel][z][0]=8;
			worldgrid[x][streetlevel][z][1]=1;
		}
		if(worldgrid[x+1][streetlevel][z+0][0]==11
		&& worldgrid[x+0][streetlevel][z-1][0]==11){
			worldgrid[x][streetlevel][z][0]=8;
			worldgrid[x][streetlevel][z][1]=2;
		}
		if(worldgrid[x-1][streetlevel][z-0][0]==11
		&& worldgrid[x-0][streetlevel][z-1][0]==11){
			worldgrid[x][streetlevel][z][0]=8;
			worldgrid[x][streetlevel][z][1]=3;
		}		
	}
	
	//multi floor buildings
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	for(int a=1; a<buildingdata[x][z]; a++){
		if(a!=buildingdata[x][z]-1){
			if(worldgrid[x][streetlevel][z][0]==8)worldgrid[x][streetlevel+a][z][0]=5;
			if(worldgrid[x][streetlevel][z][0]==9)worldgrid[x][streetlevel+a][z][0]=6;
			if(worldgrid[x][streetlevel][z][0]==10)worldgrid[x][streetlevel+a][z][0]=6;
			if(worldgrid[x][streetlevel][z][0]==17)worldgrid[x][streetlevel+a][z][0]=7;
			worldgrid[x][streetlevel+a][z][1]=worldgrid[x][streetlevel][z][1];
		}else{
			if(worldgrid[x][streetlevel][z][0]==0)worldgrid[x][streetlevel+a][z][0]=1;
			if(worldgrid[x][streetlevel][z][0]==8)worldgrid[x][streetlevel+a][z][0]=2;
			if(worldgrid[x][streetlevel][z][0]==9)worldgrid[x][streetlevel+a][z][0]=3;
			if(worldgrid[x][streetlevel][z][0]==10)worldgrid[x][streetlevel+a][z][0]=3;
			if(worldgrid[x][streetlevel][z][0]==17)worldgrid[x][streetlevel+a][z][0]=4;
			worldgrid[x][streetlevel+a][z][1]=worldgrid[x][streetlevel][z][1];
		}
	}
	
}
void genworldgrid_part4(){
	
	//doors
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(worldgrid[x][streetlevel][z][0]==0){
			buildinggrid[x][z]=1;
		}else{
			buildinggrid[x][z]=0;
		}
	}
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(buildinggrid[x][z]){
			//remember the starting position
			int startx=x;
			int startz=z;
			//get the size of the building
			int buildingxsize=0;
			int buildingzsize=0;
			while(worldgrid[x][streetlevel][z][0]==0){
				x++;buildingxsize++;}
			x=startx;
			while(worldgrid[x][streetlevel][z][0]==0){
				z++;buildingzsize++;}
			//clear out the building from the grid
			for(x=startx; x<startx+buildingxsize+1; x++)
			for(z=startz; z<startz+buildingzsize+1; z++)buildinggrid[x][z]=0;
			//choose a random position inside the building
			int middlex=startx+rand()%buildingxsize;
			int middlez=startz+rand()%buildingzsize;
			//place the door(s) facing the street
			int doorcount=0;
			if(worldgrid[startx-3][streetlevel][middlez][0]==14){
				worldgrid[startx-1][streetlevel][middlez][0]=10;
				doorcount++;}
			if(worldgrid[startx+buildingxsize+2][streetlevel][middlez][0]==14){
				worldgrid[startx+buildingxsize][streetlevel][middlez][0]=10;
				doorcount++;}
			if(worldgrid[middlex][streetlevel][startz-3][0]==14){
				worldgrid[middlex][streetlevel][startz-1][0]=10;
				doorcount++;}
			if(worldgrid[middlex][streetlevel][startz+buildingzsize+2][0]==14){
				worldgrid[middlex][streetlevel][startz+buildingzsize][0]=10;
				doorcount++;}
			//choose a random position inside the building
			middlex=startx+rand()%buildingxsize;
			middlez=startz+rand()%buildingzsize;
			//place the door(s) facing anywhere
			if(doorcount==0 || rand()%5==0){
				worldgrid[startx-1][streetlevel][middlez][0]=10;
				doorcount++;}
			if(doorcount==0 || rand()%5==0){
				worldgrid[startx+buildingxsize][streetlevel][middlez][0]=10;
				doorcount++;}
			if(doorcount==0 || rand()%5==0){
				worldgrid[middlex][streetlevel][startz-1][0]=10;
				doorcount++;}
			if(doorcount==0 || rand()%5==0){
				worldgrid[middlex][streetlevel][startz+buildingzsize][0]=10;
				doorcount++;}
			//reset the position
			x=startx;
			z=startz;
		}
	}
	
}
void genworldgrid_part5(){
	
	//find buildings
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(worldgrid[x][streetlevel][z][0]==0
		|| worldgrid[x][streetlevel][z][0]==8
		|| worldgrid[x][streetlevel][z][0]==9
		|| worldgrid[x][streetlevel][z][0]==10
		|| worldgrid[x][streetlevel][z][0]==17){
			buildingdata[x][z]=1;
		}else{
			buildingdata[x][z]=0;
		}
	}
	
	//decide what colour to make them
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(buildingdata[x][z]==1){
			//remember the starting position
			int startx=x;
			int startz=z;
			//get the size of the building
			int buildingxsize=0;
			int buildingzsize=0;
			while(buildingdata[x][z]==1){
				x++;
				buildingxsize++;
			}
			x=startx;
			while(buildingdata[x][z]==1){
				z++;
				buildingzsize++;
			}
			//pick a colour
			float r=0.855f;
			float g=0.786f;
			float b=0.742f;
			if(rand()%4!=0){
				r=(float)(rand()%100+900)*0.001f;
				g=(float)(rand()%100+900)*0.001f;
				b=(float)(rand()%100+900)*0.001f;
				/*float avg=(r+g+b)/3;
				r=(r+avg*20)/21;
				g=(g+avg*20)/21;
				b=(b+avg*20)/21;*/
			}
			//set that colour
			for(x=startx; x<startx+buildingxsize; x++)
			for(z=startz; z<startz+buildingzsize; z++){
				buildingdata[x][z]=0;
				worldgridcolor[x][z][0]=r;
				worldgridcolor[x][z][1]=g;
				worldgridcolor[x][z][2]=b;
			}
			//reset the position
			x=startx;
			z=startz;
		}
	}

}
void genworldgrid_part6(){
	
	//street lines
	for(int x=2; x<worldgridsizex-2; x++)for(int z=2; z<worldgridsizez-2; z++)
	if(worldgrid[x][streetlevel][z][0]==14){
		if(worldgrid[x-2][streetlevel][z][0]==11
		&& worldgrid[x+2][streetlevel][z][0]==11){
			worldgrid[x][streetlevel][z][0]=15;
			worldgrid[x][streetlevel][z][1]=0;
		}
		if(worldgrid[x][streetlevel][z-2][0]==11
		&& worldgrid[x][streetlevel][z+2][0]==11){
			worldgrid[x][streetlevel][z][0]=15;
			worldgrid[x][streetlevel][z][1]=1;
		}
	}	
	
	//sided sidewalks
	for(int x=1; x<worldgridsizex-1; x++)for(int z=1; z<worldgridsizez-1; z++)
	if(worldgrid[x][streetlevel][z][0]==11){
		bool up=0;
		bool down=0;
		bool left=0;
		bool right=0;		
		if(worldgrid[x][streetlevel][z-1][0]==14
		|| worldgrid[x][streetlevel][z-1][0]==15
		|| worldgrid[x][streetlevel][z-1][0]==16)up=1;		
		if(worldgrid[x][streetlevel][z+1][0]==14
		|| worldgrid[x][streetlevel][z+1][0]==15
		|| worldgrid[x][streetlevel][z+1][0]==16)down=1;		
		if(worldgrid[x-1][streetlevel][z][0]==14
		|| worldgrid[x-1][streetlevel][z][0]==15
		|| worldgrid[x-1][streetlevel][z][0]==16)left=1;
		if(worldgrid[x+1][streetlevel][z][0]==14
		|| worldgrid[x+1][streetlevel][z][0]==15
		|| worldgrid[x+1][streetlevel][z][0]==16)right=1;
		if(up==1){
			worldgrid[x][streetlevel][z][0]=12;
			worldgrid[x][streetlevel][z][1]=3;
		}
		if(down==1){
			worldgrid[x][streetlevel][z][0]=12;
			worldgrid[x][streetlevel][z][1]=1;
		}
		if(left==1){
			worldgrid[x][streetlevel][z][0]=12;
			worldgrid[x][streetlevel][z][1]=0;
		}
		if(right==1){
			worldgrid[x][streetlevel][z][0]=12;
			worldgrid[x][streetlevel][z][1]=2;
		}
		if(up==1 && left==1){
			worldgrid[x][streetlevel][z][0]=13;
			worldgrid[x][streetlevel][z][1]=3;
		}
		if(down==1 && right==1){
			worldgrid[x][streetlevel][z][0]=13;
			worldgrid[x][streetlevel][z][1]=1;
		}
		if(down==1 && left==1){
			worldgrid[x][streetlevel][z][0]=13;
			worldgrid[x][streetlevel][z][1]=0;
		}
		if(up==1 && right==1){
			worldgrid[x][streetlevel][z][0]=13;
			worldgrid[x][streetlevel][z][1]=2;
		}
		if(left==1 && right==1){
			worldgrid[x][streetlevel][z][0]=18;
			worldgrid[x][streetlevel][z][1]=0;
		}
		if(up==1 && down==1){
			worldgrid[x][streetlevel][z][0]=18;
			worldgrid[x][streetlevel][z][1]=1;
		}
	}

}
