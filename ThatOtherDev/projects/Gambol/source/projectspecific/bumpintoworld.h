void bumpintosideofblock(float *posx,float *posy,float radius,
						 float blockx,float blockw,
						 float blocky,float blockh){
	//check if you are close enough for a collission to be possible
	if(*posx+radius>blockx && *posx-radius<blockx+blockw
	&& *posy+radius>blocky && *posy-radius<blocky+blockh)
	//just give up and do nothing if you are already inside it
	if(*posx<blockx || *posx>blockx+blockw
	|| *posy<blocky || *posy>blocky+blockh){
		//hit the left or right side
		if(*posy>blocky && *posy<blocky+blockh){
			if(*posx<blockx+blockw*0.5f){
				*posx=blockx-radius;
			}else{
				*posx=blockx+blockw+radius;
			}
		}
		//hit the top or bottom side
		else if(*posx>blockx && *posx<blockx+blockw){
			if(*posy<blocky+blockh*0.5f){
				*posy=blocky-radius;
			}else{
				*posy=blocky+blockh+radius;
			}
		}
	}
}

void bumpintocornerofblock(float *posx,float *posy,float radius,
						   float blockx,float blockw,
						   float blocky,float blockh){
	//check if you are close enough for a collission to be possible
	if(*posx+radius>blockx && *posx-radius<blockx+blockw
	&& *posy+radius>blocky && *posy-radius<blocky+blockh)
	//just give up and do nothing if you are already inside it
	if(*posx<blockx || *posx>blockx+blockw
	|| *posy<blocky || *posy>blocky+blockh){
		//usefull variables
		float impactx=0,impacty=0;
		//get where the collission would occure
		if(*posx>blockx+blockw){impactx=blockx+blockw;}
		else if(*posx<blockx){impactx=blockx;}
		else{impactx=*posx;}
		if(*posy>blocky+blockh){impacty=blocky+blockh;}
		else if(*posy<blocky){impacty=blocky;}
		else{impacty=*posy;}
		//check if its actually colliding
		float distance=dist2d(*posx,*posy,impactx,impacty);
		if(distance<radius){
			//and push back if it is
			float percentx=(*posx-impactx)/distance;
			float percenty=(*posy-impacty)/distance;
			*posx=impactx+percentx*radius;
			*posy=impacty+percenty*radius;
		}
	}
}

void bumpintoworld(float *posx,float *posy,float radius){
	//some variables that will be needed
	int xgridpos=(int)floor(*posx);
	int ygridpos=(int)floor(*posy);
	int range=(int)floor(radius)+1;
	//bump into sides of walls and water
	for(int x=highint(xgridpos-range,0); x<lowint(xgridpos+range+1,worldsizex); x++)
	for(int y=highint(ygridpos-range,0); y<lowint(ygridpos+range+1,worldsizey); y++){
		if(worldgrid[x][y]==1)
			bumpintosideofblock(posx,posy,radius,(float)x,1.f,(float)y,1.f);
	}
	//bump into corners of walls and water
	for(int x=highint(xgridpos-range,0); x<lowint(xgridpos+range+1,worldsizex); x++)
	for(int y=highint(ygridpos-range,0); y<lowint(ygridpos+range+1,worldsizey); y++){
		if(worldgrid[x][y]==1)
			bumpintocornerofblock(posx,posy,radius,(float)x,1.f,(float)y,1.f);
	}
}
