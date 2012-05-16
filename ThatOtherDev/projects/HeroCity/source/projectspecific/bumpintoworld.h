bool bumpgrid[worldgridsizex][worldgridsizez];

void genworldbumpgrid(){
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++){
		if(worldgrid[x][streetlevel][z][0]==11
		|| worldgrid[x][streetlevel][z][0]==12
		|| worldgrid[x][streetlevel][z][0]==13
		|| worldgrid[x][streetlevel][z][0]==14
		|| worldgrid[x][streetlevel][z][0]==15
		|| worldgrid[x][streetlevel][z][0]==18){
			bumpgrid[x][z]=0;
		}else{
			bumpgrid[x][z]=1;
		}
	}
}

void bumpintoworld(float *posxpointer,float *posypointer,float *poszpointer,float radius){
	//some variables that will be needed
	float posx=*posxpointer;
	float posy=*posypointer;
	float posz=*poszpointer;
	float dist,impactx,impactz,groundheight;
	int xgridpos=(int)((posx+worldtilesize*0.5)/worldtilesize);
	int zgridpos=(int)((posz+worldtilesize*0.5)/worldtilesize);
	//loop through each grid section and check if its a wall
	for(int x=xgridpos-1; x<xgridpos+2; x++)
	for(int z=zgridpos-1; z<zgridpos+2; z++)
	if(bumpgrid[x][z]==1){
		//get the walls info
		float wallx1=worldtilesize*x-worldtilesize*0.5;
		float wallx2=worldtilesize*x+worldtilesize*0.5;
		float wallz1=worldtilesize*z-worldtilesize*0.5;
		float wallz2=worldtilesize*z+worldtilesize*0.5;
		//check if you are close enough for a collission to be possible
		if(posx+radius>wallx1 && posx-radius<wallx2
		&& posz+radius>wallz1 && posz-radius<wallz2){
			//you are already inside it so just give up and do nothing
			if(posx>wallx1 && posx<wallx2 && posz>wallz1 && posz<wallz2){}
			//hit the front or back side
			else if(posx>wallx1 && posx<wallx2){
				if(posz<worldtilesize*z){
					posz=wallz1-radius;
				}else{
					posz=wallz2+radius;
				}
			}
			//hit the left or right side
			else if(posz>wallz1 && posz<wallz2){
				if(posx<worldtilesize*x){
					posx=wallx1-radius;
				}else{
					posx=wallx2+radius;
				}
			}
			//potentially hit a corner
			else{
				if(posx>wallx2){impactx=wallx2;}else{impactx=wallx1;}
				if(posz>wallz2){impactz=wallz2;}else{impactz=wallz1;}
				//check if its actually colliding
				dist=dist2d(posx,posz,impactx,impactz);
				if(dist<radius){
					//and push back if it is
					float percentx=(posx-impactx)/dist;
					float percentz=(posz-impactz)/dist;
					posx=impactx+percentx*radius;
					posz=impactz+percentz*radius;
				}
			}
		}
	}
	//dont fall past the floor
	//sidewalk -5
	//street -6
	//roof +5
	if(worldgrid[xgridpos][streetlevel][zgridpos][0]==11
	|| worldgrid[xgridpos][streetlevel][zgridpos][0]==12
	|| worldgrid[xgridpos][streetlevel][zgridpos][0]==13
	|| worldgrid[xgridpos][streetlevel][zgridpos][0]==18)
		groundheight=streetlevel*worldtilesize-5;//sidewalk
	if(worldgrid[xgridpos][streetlevel][zgridpos][0]==14
	|| worldgrid[xgridpos][streetlevel][zgridpos][0]==15)
		groundheight=streetlevel*worldtilesize-6;//street
	if(posy<groundheight)posy=groundheight;
	//return the values
	*posxpointer=posx;
	*posypointer=posy;
	*poszpointer=posz;
}

void bumpintoworldcorrect(float *posxpointer,float *posypointer,float *poszpointer,float radius){
	#ifdef PS3
	bumpintoworld(posxpointer,posypointer,poszpointer,radius);
	#else
	//some variables that will be needed
	float posx=*posxpointer;
	float posy=*posypointer;
	float posz=*poszpointer;
	posy+=radius;
	int xgridpos=(int)((posx+worldtilesize*0.5)/worldtilesize);
	int ygridpos=(int)((posy+worldtilesize*0.5)/worldtilesize);
	int zgridpos=(int)((posz+worldtilesize*0.5)/worldtilesize);
	int lowx=highint(xgridpos-2,0);
	int lowy=highint(ygridpos-2,0);
	int lowz=highint(zgridpos-2,0);
	int highx=lowint(xgridpos+2+1,worldgridsizex);
	int highy=lowint(ygridpos+2+1,worldgridsizey);
	int highz=lowint(zgridpos+2+1,worldgridsizez);
	//check if you bump into polygons
	for(int x=lowx; x<highx; x++)for(int y=lowy; y<highy; y++)for(int z=lowz; z<highz; z++)
	if(worldgrid[x][y][z][0]!=0){
		posx-=x*worldtilesize;
		posy-=y*worldtilesize;
		posz-=z*worldtilesize;
		spherebumppolygoncollisionmesh(
			posx,posy,posz,radius,
			tilecollisionmesh[(int)worldgrid[x][y][z][0]][(int)worldgrid[x][y][z][1]],
			1,0);
		posx+=x*worldtilesize;
		posy+=y*worldtilesize;
		posz+=z*worldtilesize;
	}
	//check if you bump into the edges of polygons
	for(int x=lowx; x<highx; x++)for(int y=lowy; y<highy; y++)for(int z=lowz; z<highz; z++)
	if(worldgrid[x][y][z][0]!=0){
		posx-=x*worldtilesize;
		posy-=y*worldtilesize;
		posz-=z*worldtilesize;
		spherebumppolygoncollisionmesh(
			posx,posy,posz,radius,
			tilecollisionmesh[(int)worldgrid[x][y][z][0]][(int)worldgrid[x][y][z][1]],
			0,1);
		posx+=x*worldtilesize;
		posy+=y*worldtilesize;
		posz+=z*worldtilesize;
	}
	posy-=radius;
	//return the values
	*posxpointer=posx;
	*posypointer=posy;
	*poszpointer=posz;
	#endif
}
