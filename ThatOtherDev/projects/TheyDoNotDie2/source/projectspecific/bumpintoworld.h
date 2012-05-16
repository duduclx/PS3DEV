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

bool touchblock(float posx,float posy,float radius,
				float blockx,float blockw,
				float blocky,float blockh){
	bool touched=0;
	if(radius==0.f){
		if(posx>=blockx && posx<=blockx+blockw
		&& posy>=blocky && posy<=blocky+blockh)touched=1;
	}else{
		if(posx+radius>blockx && posx-radius<blockx+blockw
		&& posy+radius>blocky && posy-radius<blocky+blockh){
			if(posx<blockx || posx>blockx+blockw
			|| posy<blocky || posy>blocky+blockh){
				float impactx=0,impacty=0;
				if(posx>blockx+blockw){impactx=blockx+blockw;}
				else if(posx<blockx){impactx=blockx;}
				else{impactx=posx;}
				if(posy>blocky+blockh){impacty=blocky+blockh;}
				else if(posy<blocky){impacty=blocky;}
				else{impacty=posy;}
				if(dist2d(posx,posy,impactx,impacty)<radius){
					touched=1;
				}
			}else{
				touched=1;
			}
		}
	}
	return touched;
}

void bumpintoworld(float *posx,float *posy,float radius,bool touchwater){
	//some variables that will be needed
	int xgridpos=(int)floor(*posx);
	int ygridpos=(int)floor(*posy);
	int range=(int)floor(radius)+1;
	float objcos=0,objsin=0,oldposx=0,oldposy=0;
	//bump into sides of walls and water
	for(int x=highint(xgridpos-range,0); x<lowint(xgridpos+range+1,mapsizex); x++)
	for(int y=highint(ygridpos-range,0); y<lowint(ygridpos+range+1,mapsizey); y++){
		if(touchwater && map[x][y]<4)
			bumpintosideofblock(posx,posy,radius,(float)x,1.f,(float)y,1.f);
		for(int a=0;a<wallcount[x][y];a++)
			bumpintosideofblock(posx,posy,radius,
				walllist[x][y][a].posx,walllist[x][y][a].sizex,
				walllist[x][y][a].posy,walllist[x][y][a].sizey);
	}
	//bump into corners of walls and water
	for(int x=highint(xgridpos-range,0); x<lowint(xgridpos+range+1,mapsizex); x++)
	for(int y=highint(ygridpos-range,0); y<lowint(ygridpos+range+1,mapsizey); y++){
		if(touchwater && map[x][y]<4)
			bumpintocornerofblock(posx,posy,radius,(float)x,1.f,(float)y,1.f);
		for(int a=0;a<wallcount[x][y];a++)
			bumpintocornerofblock(posx,posy,radius,
				walllist[x][y][a].posx,walllist[x][y][a].sizex,
				walllist[x][y][a].posy,walllist[x][y][a].sizey);
	}
	//bump into objects
	for(int x=highint(xgridpos-range,0); x<lowint(xgridpos+range+1,mapsizex); x++)
	for(int y=highint(ygridpos-range,0); y<lowint(ygridpos+range+1,mapsizey); y++)
	for(int a=0;a<objectcount[x][y];a++){
		oldposx=*posx-objectlist[x][y][a].posx;
		oldposy=*posy-objectlist[x][y][a].posy;
		objcos=cos(objectlist[x][y][a].angle);
		objsin=sin(objectlist[x][y][a].angle);
		*posx=oldposy*objsin+oldposx*objcos;
		*posy=oldposy*objcos-oldposx*objsin;
		if(objectlist[x][y][a].type==objecttype_crate
		|| objectlist[x][y][a].type==objecttype_crateexplosive
		|| objectlist[x][y][a].type==objecttype_cratemedical
		|| objectlist[x][y][a].type==objecttype_crateammo)
			bumpintocornerofblock(posx,posy,radius,-0.4f,0.8f,-0.4f,0.8f);
		if(objectlist[x][y][a].type==objecttype_car)
			bumpintocornerofblock(posx,posy,radius,-0.9f,1.8f,-0.4f,0.8f);
		oldposx=*posx;
		oldposy=*posy;
		objcos=cos(-objectlist[x][y][a].angle);
		objsin=sin(-objectlist[x][y][a].angle);
		*posx=oldposy*objsin+oldposx*objcos+objectlist[x][y][a].posx;
		*posy=oldposy*objcos-oldposx*objsin+objectlist[x][y][a].posy;
	}
}

bool touchworld(float posx,float posy,float radius,bool touchwater){
	//float startingx=posx;
	//float startingy=posy;	
	//bumpintoworld(&posx,&posy,radius,touchwater);
	//if(posx==startingx && posy==startingy){return 0;}else{return 1;}
	//some variables that will be needed
	bool touched=0;
	int xgridpos=(int)floor(posx);
	int ygridpos=(int)floor(posy);
	int range=(int)floor(radius)+1;
	float objcos=0,objsin=0,oldposx=0,oldposy=0;
	//touch walls and water
	for(int x=highint(xgridpos-range,0); x<lowint(xgridpos+range+1,mapsizex); x++)
	for(int y=highint(ygridpos-range,0); y<lowint(ygridpos+range+1,mapsizey); y++){
		if(touchwater && map[x][y]<4)
			if(touchblock(posx,posy,radius,(float)x,1.f,(float)y,1.f))touched=1;
		for(int a=0;a<wallcount[x][y];a++)
			if(touchblock(posx,posy,radius,
				walllist[x][y][a].posx,walllist[x][y][a].sizex,
				walllist[x][y][a].posy,walllist[x][y][a].sizey))touched=1;
	}
	//touch objects
	for(int x=highint(xgridpos-range,0); x<lowint(xgridpos+range+1,mapsizex); x++)
	for(int y=highint(ygridpos-range,0); y<lowint(ygridpos+range+1,mapsizey); y++)
	for(int a=0;a<objectcount[x][y];a++){
		oldposx=posx-objectlist[x][y][a].posx;
		oldposy=posy-objectlist[x][y][a].posy;
		objcos=cos(objectlist[x][y][a].angle);
		objsin=sin(objectlist[x][y][a].angle);
		posx=oldposy*objsin+oldposx*objcos;
		posy=oldposy*objcos-oldposx*objsin;
		if(objectlist[x][y][a].type==objecttype_crate
		|| objectlist[x][y][a].type==objecttype_crateexplosive
		|| objectlist[x][y][a].type==objecttype_cratemedical
		|| objectlist[x][y][a].type==objecttype_crateammo)
			if(touchblock(posx,posy,radius,-0.4f,0.8f,-0.4f,0.8f))touched=1;
		if(objectlist[x][y][a].type==objecttype_car)
			if(touchblock(posx,posy,radius,-0.9f,1.8f,-0.4f,0.8f))touched=1;
		oldposx=posx;
		oldposy=posy;
		objcos=cos(-objectlist[x][y][a].angle);
		objsin=sin(-objectlist[x][y][a].angle);
		posx=oldposy*objsin+oldposx*objcos+objectlist[x][y][a].posx;
		posy=oldposy*objcos-oldposx*objsin+objectlist[x][y][a].posy;
	}
	return touched;
}
