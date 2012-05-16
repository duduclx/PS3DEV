//types
#define tiletype_water									(0)
#define tiletype_wateredge								(1)
#define tiletype_watercorner1							(2)
#define tiletype_watercorner2							(3)
#define tiletype_streetline								(4)
#define tiletype_street									(5)
#define tiletype_sidewalkcorner							(6)
#define tiletype_sidewalk								(7)
#define tiletype_grass									(8)
#define tiletype_buildinginside							(9)
#define tiletype_buildingwall							(10)
#define tiletype_buildingdoor							(11)
#define tiletype_buildingcorner							(12)
#define tiletype_buildinginnerwallconnectedtoouterwall	(13)
#define tiletype_buildinginnerdoor						(14)
#define tiletype_buildinginnerwall						(15)

#define tiletype_placeholder							(16)

void genworldgrid(){

	//clean the map
	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++)map[x][y]=tiletype_water;
	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++)maprotation[x][y]=0;

	//create a water grid
	for(int x=0; x<smallmapsizex; x++)for(int y=0; y<smallmapsizey; y++){
		watergrid[x][y]=1;
	}
	for(int n=0; n<(int)((float)smallmapsizex*(float)smallmapsizey*0.02); n++){
		int middlex=rand()%(smallmapsizex-20)+10;
		int middley=rand()%(smallmapsizey-20)+10;
		int sizex=rand()%4+2;
		int sizey=rand()%4+2;
		bool overlap=0;
		for(int x=middlex-sizex+1; x<middlex+sizex+1-1; x++)
		for(int y=middley-sizey+1; y<middley+sizey+1-1; y++)
			if(watergrid[x][y]==1)overlap=1;
		if(n==0 || overlap==1)
		for(int x=middlex-sizex; x<middlex+sizex+1; x++)
		for(int y=middley-sizey; y<middley+sizey+1; y++){
			watergrid[x][y]=0;
		}
	}

	//create a street grid
	for(int x=0; x<smallmapsizex; x++)for(int y=0; y<smallmapsizey; y++){
		streetgrid[x][y]=0;
		if(watergrid[x][y]==1)streetgrid[x][y]=1;
	}
	for(int n=0; n<(int)((float)smallmapsizex*(float)smallmapsizey*0.1); n++){
		int startx,starty;
		int x,y;
		//horiyontal line
		startx=rand()%(smallmapsizex-2)+1;
		starty=rand()%(smallmapsizey-2)+1;
		if(!streetgrid[startx][starty]
		&& !streetgrid[startx][starty-1]
		&& !streetgrid[startx][starty+1]){
			streetgrid[startx][starty]=1;
			x=startx;y=starty;
			while(!streetgrid[x-1][y]){
				x--;streetgrid[x][y]=1;}
			x=startx;y=starty;
			while(!streetgrid[x+1][y]){
				x++;streetgrid[x][y]=1;}
		}
		//verticle line
		startx=rand()%(smallmapsizex-2)+1;
		starty=rand()%(smallmapsizey-2)+1;
		if(!streetgrid[startx][starty]
		&& !streetgrid[startx-1][starty]
		&& !streetgrid[startx+1][starty]){
			streetgrid[startx][starty]=1;
			x=startx;y=starty;
			while(!streetgrid[x][y-1]){
				y--;streetgrid[x][y]=1;}
			x=startx;y=starty;
			while(!streetgrid[x][y+1]){
				y++;streetgrid[x][y]=1;}
		}
	}

	//apply the water and street grids to the map
	int offsetx=(int)floor((float)(mapsizex-smallmapsizex*5)*0.5f);
	int offsety=(int)floor((float)(mapsizey-smallmapsizey*5)*0.5f);
	for(int x=0; x<smallmapsizex; x++)for(int y=0; y<smallmapsizey; y++)
	if(watergrid[x][y]==0)for(int x2=0;x2<5;x2++)for(int y2=0;y2<5;y2++)
		map[x*5+x2+offsetx][y*5+y2+offsety]=tiletype_grass;
	for(int x=0; x<smallmapsizex; x++)for(int y=0; y<smallmapsizey; y++)
	if(streetgrid[x][y]==1)for(int x2=0;x2<5;x2++)for(int y2=0;y2<5;y2++)
		map[x*5+x2+offsetx][y*5+y2+offsety]=tiletype_street;
	for(int x=0; x<smallmapsizex; x++)for(int y=0; y<smallmapsizey; y++)
	if(watergrid[x][y]==1)for(int x2=0;x2<5;x2++)for(int y2=0;y2<5;y2++)
		map[x*5+x2+offsetx][y*5+y2+offsety]=tiletype_water;

	//setup sidewalks
	for(int x=1; x<mapsizex-1; x++)for(int y=1; y<mapsizey-1; y++)
	if(map[x][y]==tiletype_street)
	if(map[x-1][y]==tiletype_grass || map[x][y-1]==tiletype_grass	|| map[x-1][y-1]==tiletype_grass	|| map[x-1][y+1]==tiletype_grass
	|| map[x+1][y]==tiletype_grass || map[x][y+1]==tiletype_grass || map[x+1][y+1]==tiletype_grass	|| map[x+1][y-1]==tiletype_grass
	|| map[x-1][y]==tiletype_water || map[x][y-1]==tiletype_water	|| map[x-1][y-1]==tiletype_water	|| map[x-1][y+1]==tiletype_water
	|| map[x+1][y]==tiletype_water || map[x][y+1]==tiletype_water || map[x+1][y+1]==tiletype_water	|| map[x+1][y-1]==tiletype_water)
		map[x][y]=tiletype_sidewalk;

	//L shaped buildings caused by water be gone
	for(int x=0; x<mapsizex/5; x++)for(int y=0; y<mapsizey/5; y++)
	if(watergrid[x][y]==1){
		int newx,newy;
		if(watergrid[x-1][y]==tiletype_water
		&& watergrid[x][y-1]==tiletype_water){
			//horiyontal line
			newx=x*5+offsetx;
			newy=y*5+offsety;
			while(map[newx-1][newy]==tiletype_grass
			&& map[newx-1][newy-1]!=tiletype_sidewalk
			&& map[newx-1][newy+1]!=tiletype_sidewalk){
				newx--;
				map[newx][newy]=tiletype_sidewalk;
			}
			//verticle line
			newx=x*5+offsetx;
			newy=y*5+offsety;
			while(map[newx][newy-1]==tiletype_grass
			&& map[newx-1][newy-1]!=tiletype_sidewalk
			&& map[newx+1][newy-1]!=tiletype_sidewalk){
				newy--;
				map[newx][newy]=tiletype_sidewalk;
			}
		}
		if(watergrid[x+1][y]==tiletype_water && watergrid[x][y+1]==tiletype_water){
			//horiyontal line
			newx=x*5+5-1+offsetx;
			newy=y*5+5-1+offsety;
			while(map[newx+1][newy]==tiletype_grass
			&& map[newx+1][newy-1]!=tiletype_sidewalk
			&& map[newx+1][newy+1]!=tiletype_sidewalk){
				newx++;
				map[newx][newy]=tiletype_sidewalk;
			}
			//verticle line
			newx=x*5+5-1+offsetx;
			newy=y*5+5-1+offsety;
			while(map[newx][newy+1]==tiletype_grass
			&& map[newx-1][newy+1]!=tiletype_sidewalk
			&& map[newx+1][newy+1]!=tiletype_sidewalk){
				newy++;
				map[newx][newy]=tiletype_sidewalk;
			}
		}
		if(watergrid[x+1][y]==tiletype_water && watergrid[x][y-1]==tiletype_water){
			//horiyontal line
			newx=x*5+5-1+offsetx;
			newy=y*5+offsety;
			while(map[newx+1][newy]==tiletype_grass
			&& map[newx+1][newy-1]!=tiletype_sidewalk
			&& map[newx+1][newy+1]!=tiletype_sidewalk){
				newx++;
				map[newx][newy]=tiletype_sidewalk;
			}
			//verticle line
			newx=x*5+5-1+offsetx;
			newy=y*5+offsety;
			while(map[newx][newy-1]==tiletype_grass
			&& map[newx-1][newy-1]!=tiletype_sidewalk
			&& map[newx+1][newy-1]!=tiletype_sidewalk){
				newy--;
				map[newx][newy]=tiletype_sidewalk;
			}
		}
		if(watergrid[x-1][y]==tiletype_water && watergrid[x][y+1]==tiletype_water){
			//horiyontal line
			newx=x*5+offsetx;
			newy=y*5+5-1+offsety;
			while(map[newx-1][newy]==tiletype_grass
			&& map[newx-1][newy-1]!=tiletype_sidewalk
			&& map[newx-1][newy+1]!=tiletype_sidewalk){
				newx--;
				map[newx][newy]=tiletype_sidewalk;
			}
			//verticle line
			newx=x*5+offsetx;
			newy=y*5+5-1+offsety;
			while(map[newx][newy+1]==tiletype_grass
			&& map[newx-1][newy+1]!=tiletype_sidewalk
			&& map[newx+1][newy+1]!=tiletype_sidewalk){
				newy++;
				map[newx][newy]=tiletype_sidewalk;
			}
		}
	}

	//some ally ways
	for(int n=0; n<(int)((float)mapsizex*(float)mapsizey*0.085f); n++){
		int x,y;
		//verticle line
		x=rand()%mapsizex;
		y=rand()%mapsizey;
		if(map[x][y]==tiletype_grass
		&& map[x+1][y]==tiletype_grass
		&& map[x-1][y]==tiletype_grass
		&& map[x+2][y]==tiletype_grass
		&& map[x-2][y]==tiletype_grass
		&& map[x+3][y]==tiletype_grass
		&& map[x-3][y]==tiletype_grass){
			map[x][y]=tiletype_sidewalk;
			int starty=y;
			while(map[x][y-1]==tiletype_grass){
				y--;map[x][y]=tiletype_sidewalk;}
			y=starty;
			while(map[x][y+1]==tiletype_grass){
				y++;map[x][y]=tiletype_sidewalk;}
		}
		//horiyontal line
		x=rand()%mapsizex;
		y=rand()%mapsizey;
		if(map[x][y]==tiletype_grass
		&& map[x][y+1]==tiletype_grass
		&& map[x][y-1]==tiletype_grass
		&& map[x][y+2]==tiletype_grass
		&& map[x][y-2]==tiletype_grass
		&& map[x][y+3]==tiletype_grass
		&& map[x][y-3]==tiletype_grass){
			map[x][y]=tiletype_sidewalk;
			int startx=x;
			while(map[x-1][y]==tiletype_grass){
				x--;map[x][y]=tiletype_sidewalk;}
			x=startx;
			while(map[x+1][y]==tiletype_grass){
				x++;map[x][y]=tiletype_sidewalk;}
		}
	}

	//lines in the middle of streets
	for(int x=2; x<mapsizex-2; x++)for(int y=2; y<mapsizey-2; y++)
	if(map[x][y]==tiletype_street){
		if(map[x-2][y]==tiletype_sidewalk
		&& map[x+2][y]==tiletype_sidewalk){
			map[x][y]=tiletype_streetline;
			maprotation[x][y]=1;
		}
		if(map[x][y-2]==tiletype_sidewalk
		&& map[x][y+2]==tiletype_sidewalk){
			map[x][y]=tiletype_streetline;
		}
	}

	//water touches nothing but water and sidewalk
	for(int x=1; x<mapsizex-1; x++)for(int y=1; y<mapsizey-1; y++)
	if(map[x][y]==tiletype_water){
		if((map[x-1][y]!=tiletype_water && map[x-1][y]!=tiletype_sidewalk)
		|| (map[x+1][y]!=tiletype_water && map[x+1][y]!=tiletype_sidewalk)
		|| (map[x][y-1]!=tiletype_water && map[x][y-1]!=tiletype_sidewalk)
		|| (map[x][y+1]!=tiletype_water && map[x][y+1]!=tiletype_sidewalk)
		|| (map[x-1][y-1]!=tiletype_water && map[x-1][y-1]!=tiletype_sidewalk)
		|| (map[x+1][y-1]!=tiletype_water && map[x+1][y-1]!=tiletype_sidewalk)
		|| (map[x-1][y+1]!=tiletype_water && map[x-1][y+1]!=tiletype_sidewalk)
		|| (map[x+1][y+1]!=tiletype_water && map[x+1][y+1]!=tiletype_sidewalk))
			map[x][y]=tiletype_sidewalk;
	}

	//the shoreline
	for(int x=1; x<mapsizex-1; x++)for(int y=1; y<mapsizey-1; y++)
	if(map[x][y]==tiletype_water){
		if(map[x-1][y+1]==tiletype_sidewalk){
			map[x][y]=tiletype_watercorner2;
			maprotation[x][y]=0;
		}
		if(map[x-1][y-1]==tiletype_sidewalk){
			map[x][y]=tiletype_watercorner2;
			maprotation[x][y]=1;
		}
		if(map[x+1][y-1]==tiletype_sidewalk){
			map[x][y]=tiletype_watercorner2;
			maprotation[x][y]=2;
		}
		if(map[x+1][y+1]==tiletype_sidewalk){
			map[x][y]=tiletype_watercorner2;
			maprotation[x][y]=3;
		}
		if(map[x+1][y]==tiletype_sidewalk){
			map[x][y]=tiletype_wateredge;
			maprotation[x][y]=0;
		}
		if(map[x][y+1]==tiletype_sidewalk){
			map[x][y]=tiletype_wateredge;
			maprotation[x][y]=1;
		}
		if(map[x-1][y]==tiletype_sidewalk){
			map[x][y]=tiletype_wateredge;
			maprotation[x][y]=2;
		}
		if(map[x][y-1]==tiletype_sidewalk){
			map[x][y]=tiletype_wateredge;
			maprotation[x][y]=3;
		}
		if(map[x-1][y]==tiletype_sidewalk
		&& map[x][y+1]==tiletype_sidewalk){
			map[x][y]=tiletype_watercorner1;
			maprotation[x][y]=0;
		}
		if(map[x-1][y]==tiletype_sidewalk
		&& map[x][y-1]==tiletype_sidewalk){
			map[x][y]=tiletype_watercorner1;
			maprotation[x][y]=1;
		}
		if(map[x+1][y]==tiletype_sidewalk
		&& map[x][y-1]==tiletype_sidewalk){
			map[x][y]=tiletype_watercorner1;
			maprotation[x][y]=2;
		}
		if(map[x+1][y]==tiletype_sidewalk
		&& map[x][y+1]==tiletype_sidewalk){
			map[x][y]=tiletype_watercorner1;
			maprotation[x][y]=3;
		}
	}

	//sidewalk corners
	for(int x=1; x<mapsizex-1; x++)for(int y=1; y<mapsizey-1; y++)
	if(map[x][y]==tiletype_sidewalk){
		if(map[x+1][y]==tiletype_sidewalk && map[x-1][y]==tiletype_street
		&& map[x][y-1]==tiletype_sidewalk && map[x][y+1]==tiletype_street){
			map[x][y]=tiletype_sidewalkcorner;
			maprotation[x][y]=0;
		}
		if(map[x+1][y]==tiletype_sidewalk && map[x-1][y]==tiletype_street
		&& map[x][y+1]==tiletype_sidewalk && map[x][y-1]==tiletype_street){
			map[x][y]=tiletype_sidewalkcorner;
			maprotation[x][y]=1;
		}
		if(map[x-1][y]==tiletype_sidewalk && map[x+1][y]==tiletype_street
		&& map[x][y+1]==tiletype_sidewalk && map[x][y-1]==tiletype_street){
			map[x][y]=tiletype_sidewalkcorner;
			maprotation[x][y]=2;
		}
		if(map[x-1][y]==tiletype_sidewalk && map[x+1][y]==tiletype_street
		&& map[x][y-1]==tiletype_sidewalk && map[x][y+1]==tiletype_street){
			map[x][y]=tiletype_sidewalkcorner;
			maprotation[x][y]=3;
		}
	}

	//decide where to place buildings and then place them
	for(int x=0; x<mapsizex; x++)for(int y=0; y<mapsizey; y++){
		if(map[x][y]==tiletype_grass)map[x][y]=tiletype_placeholder;
	}
	for(int x=0; x<mapsizex; x++)for(int y=0; y<mapsizey; y++)
	if(map[x][y]==tiletype_placeholder){
		int startx=x;
		int starty=y;
		int tobuildornottobuild=rand()%100;
		bool build=0;
		if(tobuildornottobuild>10)build=1;
		while(map[x][y]==tiletype_placeholder){
			map[x][y]=tiletype_grass;
			if(build)map[x][y]=tiletype_buildinginside;
			while(map[x][y+1]==tiletype_placeholder && y<mapsizey){
				y++;
				map[x][y]=tiletype_grass;
				if(build)map[x][y]=tiletype_buildinginside;
			}
			y=starty;
			x++;
		}
		x=startx;
	}

	//building walls
	for(int x=0; x<mapsizex; x++)for(int y=0; y<mapsizey; y++)
	if(map[x][y]==tiletype_buildinginside){
		if(map[x-1][y]==tiletype_sidewalk){
			map[x][y]=tiletype_buildingwall;
			maprotation[x][y]=0;
		}
		if(map[x][y-1]==tiletype_sidewalk){
			map[x][y]=tiletype_buildingwall;
			maprotation[x][y]=1;
		}
		if(map[x+1][y]==tiletype_sidewalk){
			map[x][y]=tiletype_buildingwall;
			maprotation[x][y]=2;
		}
		if(map[x][y+1]==tiletype_sidewalk){
			map[x][y]=tiletype_buildingwall;
			maprotation[x][y]=3;
		}
		if(map[x-1][y]==tiletype_sidewalk
		&& map[x][y+1]==tiletype_sidewalk){
			map[x][y]=tiletype_buildingcorner;
			maprotation[x][y]=0;
		}
		if(map[x-1][y]==tiletype_sidewalk
		&& map[x][y-1]==tiletype_sidewalk){
			map[x][y]=tiletype_buildingcorner;
			maprotation[x][y]=1;
		}
		if(map[x+1][y]==tiletype_sidewalk
		&& map[x][y-1]==tiletype_sidewalk){
			map[x][y]=tiletype_buildingcorner;
			maprotation[x][y]=2;
		}
		if(map[x+1][y]==tiletype_sidewalk
		&& map[x][y+1]==tiletype_sidewalk){
			map[x][y]=tiletype_buildingcorner;
			maprotation[x][y]=3;
		}
	}

	//add doors to the buildings
	for(int x=0; x<mapsizex; x++)for(int y=0; y<mapsizey; y++){
		if(map[x][y]==tiletype_buildinginside)map[x][y]=tiletype_placeholder;
	}
	for(int x=0; x<mapsizex; x++)for(int y=0; y<mapsizey; y++)
	if(map[x][y]==tiletype_placeholder){
		//remember the starting position
		int startx=x;
		int starty=y;
		//get the size of the building
		int buildingxsize=0;
		int buildingysize=0;
		while(map[x][y]==tiletype_placeholder){
			x++;buildingxsize++;}
		x=startx;
		while(map[x][y]==tiletype_placeholder){
			y++;buildingysize++;}
		y=starty;
		//clear out the building from the grid
		for(x=startx; x<startx+buildingxsize; x++)
		for(y=starty; y<starty+buildingysize; y++)
			map[x][y]=tiletype_buildinginside;
		//choose a random position inside the building
		int middlex=startx+rand()%buildingxsize;
		int middley=starty+rand()%buildingysize;
		//place the door(s) facing the street
		int doorcount=0;
		if(map[startx-3][middley]==tiletype_street){
			map[startx-1][middley]=tiletype_buildingdoor;
			doorcount++;}
		if(map[startx+buildingxsize+2][middley]==tiletype_street){
			map[startx+buildingxsize][middley]=tiletype_buildingdoor;
			doorcount++;}
		if(map[middlex][starty-3]==tiletype_street){
			map[middlex][starty-1]=tiletype_buildingdoor;
			doorcount++;}
		if(map[middlex][starty+buildingysize+2]==tiletype_street){
			map[middlex][starty+buildingysize]=tiletype_buildingdoor;
			doorcount++;}
		//choose a random position inside the building
		middlex=startx+rand()%buildingxsize;
		middley=starty+rand()%buildingysize;
		//place the door(s) facing anywhere
		if(doorcount==0 || rand()%10==0)
			map[startx-1][middley]=tiletype_buildingdoor;
		if(doorcount==0 || rand()%10==0)
			map[startx+buildingxsize][middley]=tiletype_buildingdoor;
		if(doorcount==0 || rand()%10==0)
			map[middlex][starty-1]=tiletype_buildingdoor;
		if(doorcount==0 || rand()%10==0)
			map[middlex][starty+buildingysize]=tiletype_buildingdoor;
		//reset the position
		x=startx;
		y=starty;
	}

	//subdevide buildings into rooms
	for(int n=0; n<(int)((float)mapsizex*(float)mapsizey*0.05f); n++){
		int x=rand()%mapsizex;
		int y=rand()%mapsizey;
		if(map[x][y]==tiletype_buildinginside){
			bool doit=1;
			if(rand()%2==0){
				int startx=x;
				while(map[x][y]==tiletype_buildinginside)x+=1;
					if(map[x][y]!=tiletype_buildingwall)doit=0;
				x=startx;
				while(map[x][y]==tiletype_buildinginside)x-=1;
					if(map[x][y]!=tiletype_buildingwall)doit=0;
				if(doit==1){
					x=startx;
					map[x][y]=tiletype_buildinginnerdoor;
					x+=1;
					while(map[x][y]==tiletype_buildinginside){
						map[x][y]=tiletype_buildinginnerwall;
						x+=1;
					}
					map[x][y]=tiletype_buildinginnerwallconnectedtoouterwall;
					x=startx;
					x-=1;
					while(map[x][y]==tiletype_buildinginside){
						map[x][y]=tiletype_buildinginnerwall;
						x-=1;
					}
					map[x][y]=tiletype_buildinginnerwallconnectedtoouterwall;
				}
			}else{
				int starty=y;
				while(map[x][y]==tiletype_buildinginside)y+=1;
					if(map[x][y]!=tiletype_buildingwall)doit=0;
				y=starty;
				while(map[x][y]==tiletype_buildinginside)y-=1;
					if(map[x][y]!=tiletype_buildingwall)doit=0;
				if(doit==1){
					y=starty;
					map[x][y]=tiletype_buildinginnerdoor;
					maprotation[x][y]=1;
					y+=1;
					while(map[x][y]==tiletype_buildinginside){
						map[x][y]=tiletype_buildinginnerwall;
						maprotation[x][y]=1;
						y+=1;
					}
					map[x][y]=tiletype_buildinginnerwallconnectedtoouterwall;
					y=starty;
					y-=1;
					while(map[x][y]==tiletype_buildinginside){
						map[x][y]=tiletype_buildinginnerwall;
						maprotation[x][y]=1;
						y-=1;
					}
					map[x][y]=tiletype_buildinginnerwallconnectedtoouterwall;
				}
			}
		}
	}

}
