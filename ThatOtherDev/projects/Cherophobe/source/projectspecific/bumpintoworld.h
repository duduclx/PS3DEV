void bumpintoworld(float *posxpointer,float *posypointer,float *poszpointer,float radius){
	//some variables that will be needed
	float posx=*posxpointer;
	float posy=*posypointer;
	float posz=*poszpointer;
	float dist,impactx,impactz;
	int xgridpos=(int)floor(posx/worldtilesize+0.5f);
	int zgridpos=(int)floor(posz/worldtilesize+0.5f);
	//loop through each grid section and check if its a wall
	for(int x=xgridpos-1; x<xgridpos+2; x++)
	for(int z=zgridpos-1; z<zgridpos+2; z++)
	if(worldgrid[x][z]==1){
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
	*posxpointer=posx;
	*posypointer=posy;
	*poszpointer=posz;
}
