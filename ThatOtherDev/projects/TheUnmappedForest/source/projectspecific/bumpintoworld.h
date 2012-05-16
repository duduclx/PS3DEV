void bumpintosideofblock_monster(int thingnum,float radius,
						 float blockx,float blockw,
						 float blocky,float blockh){
	//check if you are close enough for a collission to be possible
	if(thinglist[thingnum].posx+radius>blockx && thinglist[thingnum].posx-radius<blockx+blockw
	&& thinglist[thingnum].posy+radius>blocky && thinglist[thingnum].posy-radius<blocky+blockh)
	//just give up and do nothing if you are already inside it
	if(thinglist[thingnum].posx<blockx || thinglist[thingnum].posx>blockx+blockw
	|| thinglist[thingnum].posy<blocky || thinglist[thingnum].posy>blocky+blockh){
		//hit the left or right side
		if(thinglist[thingnum].posy>blocky && thinglist[thingnum].posy<blocky+blockh){
			if(thinglist[thingnum].posx<blockx+blockw*0.5f){
				thinglist[thingnum].posx=blockx-radius;
			}else{
				thinglist[thingnum].posx=blockx+blockw+radius;
			}
		}
		//hit the top or bottom side
		else if(thinglist[thingnum].posx>blockx && thinglist[thingnum].posx<blockx+blockw){
			if(thinglist[thingnum].posy<blocky+blockh*0.5f){
				thinglist[thingnum].posy=blocky-radius;
			}else{
				thinglist[thingnum].posy=blocky+blockh+radius;
			}
		}
	}
}

void bumpintocornerofblock_monster(int thingnum,float radius,
						   float blockx,float blockw,
						   float blocky,float blockh){
	//check if you are close enough for a collission to be possible
	if(thinglist[thingnum].posx+radius>blockx && thinglist[thingnum].posx-radius<blockx+blockw
	&& thinglist[thingnum].posy+radius>blocky && thinglist[thingnum].posy-radius<blocky+blockh)
	//just give up and do nothing if you are already inside it
	if(thinglist[thingnum].posx<blockx || thinglist[thingnum].posx>blockx+blockw
	|| thinglist[thingnum].posy<blocky || thinglist[thingnum].posy>blocky+blockh){
		//usefull variables
		float impactx=0,impacty=0;
		//get where the collission would occure
		if(thinglist[thingnum].posx>blockx+blockw){impactx=blockx+blockw;}
		else if(thinglist[thingnum].posx<blockx){impactx=blockx;}
		else{impactx=thinglist[thingnum].posx;}
		if(thinglist[thingnum].posy>blocky+blockh){impacty=blocky+blockh;}
		else if(thinglist[thingnum].posy<blocky){impacty=blocky;}
		else{impacty=thinglist[thingnum].posy;}
		//check if its actually colliding
		float distance=dist2d(thinglist[thingnum].posx,thinglist[thingnum].posy,impactx,impacty);
		if(distance<radius){
			//and push back if it is
			float percentx=(thinglist[thingnum].posx-impactx)/distance;
			float percenty=(thinglist[thingnum].posy-impacty)/distance;
			thinglist[thingnum].posx=impactx+percentx*radius;
			thinglist[thingnum].posy=impacty+percenty*radius;
		}
	}
}

void bumpintosideofblock_player(int thingnum,float radius,
						 float blockx,float blockw,
						 float blocky,float blockh){
	//check if you are close enough for a collission to be possible
	if(player.posx+radius>blockx && player.posx-radius<blockx+blockw
	&& player.posy+radius>blocky && player.posy-radius<blocky+blockh)
	//just give up and do nothing if you are already inside it
	if(player.posx<blockx || player.posx>blockx+blockw
	|| player.posy<blocky || player.posy>blocky+blockh){
		//hit the left or right side
		if(player.posy>blocky && player.posy<blocky+blockh){
			if(player.posx<blockx+blockw*0.5f){
				player.posx=blockx-radius;
			}else{
				player.posx=blockx+blockw+radius;
			}
		}
		//hit the top or bottom side
		else if(player.posx>blockx && player.posx<blockx+blockw){
			if(player.posy<blocky+blockh*0.5f){
				player.posy=blocky-radius;
			}else{
				player.posy=blocky+blockh+radius;
			}
		}
	}
}

void bumpintocornerofblock_player(int thingnum,float radius,
						   float blockx,float blockw,
						   float blocky,float blockh){
	//check if you are close enough for a collission to be possible
	if(player.posx+radius>blockx && player.posx-radius<blockx+blockw
	&& player.posy+radius>blocky && player.posy-radius<blocky+blockh)
	//just give up and do nothing if you are already inside it
	if(player.posx<blockx || player.posx>blockx+blockw
	|| player.posy<blocky || player.posy>blocky+blockh){
		//usefull variables
		float impactx=0,impacty=0;
		//get where the collission would occure
		if(player.posx>blockx+blockw){impactx=blockx+blockw;}
		else if(player.posx<blockx){impactx=blockx;}
		else{impactx=player.posx;}
		if(player.posy>blocky+blockh){impacty=blocky+blockh;}
		else if(player.posy<blocky){impacty=blocky;}
		else{impacty=player.posy;}
		//check if its actually colliding
		float distance=dist2d(player.posx,player.posy,impactx,impacty);
		if(distance<radius){
			//and push back if it is
			float percentx=(player.posx-impactx)/distance;
			float percenty=(player.posy-impacty)/distance;
			player.posx=impactx+percentx*radius;
			player.posy=impacty+percenty*radius;
		}
	}
}

const float monsterradius=40.f/2.f/64.f;
void bumpintoworld_monster(int thingnum){
	int xgridpos=(int)floor(thinglist[thingnum].posx+0.5f);
	int ygridpos=(int)floor(thinglist[thingnum].posy+0.5f);
	int bumprange=(int)ceil(monsterradius);
	for(int x=highint(0,xgridpos-bumprange); x<lowint(mapsizex,xgridpos+bumprange+1); x++)
	for(int y=highint(0,ygridpos-bumprange); y<lowint(mapsizey,ygridpos+bumprange+1); y++){
		if(map[x][y]=='t')bumpintosideofblock_monster(
			thingnum,monsterradius,
			(float)x-0.5,1.f,
			(float)y-0.75f,1.f);
		if(map[x][y]=='c')bumpintosideofblock_monster(
			thingnum,monsterradius,
			(float)x-50.f/64.f/2.f,50.f/64.f,
			(float)y-19.f/64.f,38.f/64.f/2);
	}
	for(int x=highint(0,xgridpos-bumprange); x<lowint(mapsizex,xgridpos+bumprange+1); x++)
	for(int y=highint(0,ygridpos-bumprange); y<lowint(mapsizey,ygridpos+bumprange+1); y++){
		if(map[x][y]=='t')bumpintocornerofblock_monster(
			thingnum,monsterradius,
			(float)x-0.5,1.f,
			(float)y-0.75f,1.f);
		if(map[x][y]=='c')bumpintocornerofblock_monster(
			thingnum,monsterradius,
			(float)x-50.f/64.f/2.f,50.f/64.f,
			(float)y-19.f/64.f,38.f/64.f/2);
	}
}

const float playerradius=50.f/2.f/64.f;
void bumpintoworld_player(int thingnum){
	int xgridpos=(int)floor(player.posx+0.5f);
	int ygridpos=(int)floor(player.posy+0.5f);
	int bumprange=(int)ceil(playerradius);
	for(int x=highint(0,xgridpos-bumprange); x<lowint(mapsizex,xgridpos+bumprange+1); x++)
	for(int y=highint(0,ygridpos-bumprange); y<lowint(mapsizey,ygridpos+bumprange+1); y++){
		if(map[x][y]=='t')bumpintosideofblock_player(
			thingnum,playerradius,
			(float)x-0.5,1.f,
			(float)y-0.75f,1.f);
		if(map[x][y]=='c')bumpintosideofblock_player(
			thingnum,playerradius,
			(float)x-50.f/64.f/2.f,50.f/64.f,
			(float)y-13.f/64.f/2.f,38.f/64.f/2);
	}
	for(int x=highint(0,xgridpos-bumprange); x<lowint(mapsizex,xgridpos+bumprange+1); x++)
	for(int y=highint(0,ygridpos-bumprange); y<lowint(mapsizey,ygridpos+bumprange+1); y++){
		if(map[x][y]=='t')bumpintocornerofblock_player(
			thingnum,playerradius,
			(float)x-0.5,1.f,
			(float)y-0.75f,1.f);
		if(map[x][y]=='c')bumpintocornerofblock_player(
			thingnum,playerradius,
			(float)x-50.f/64.f/2.f,50.f/64.f,
			(float)y-13.f/64.f/2.f,38.f/64.f/2);
	}
}
