void removeallentities(){
	while(shotcount>0)removeshotfromlist(0);
	while(personcount>0)removepersonfromlist(0);
	while(decalcount>0)removedecalfromlist(0);
	while(rocketcount>0)removerocketfromlist(0);
	while(explosioncount>0)removeexplosionfromlist(0);
	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++)
		while(objectcount[x][y]>0)removeobjectfromlist(x,y,0);
	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++)
		while(wallcount[x][y]>0)removewallfromlist(x,y,0);
}

void startnewgame(){

	//remove all the old entities
	removeallentities();

	//gen the world
	genworldgrid();

	//gen walls
	genwalls();

	//gen objects
	genobjects();

	//spawn the player and position the camera
	int x=mapsizex/2;
	int y=mapsizey/2;
	while(touchworld((float)x+0.5f,(float)y+0.5f,0.23f,1)){
		x=rand()%mapsizex;
		y=rand()%mapsizey;
	}
	if(playercount>0){
		makeperson(
			persontype_player,
			(float)x+0.5f,
			(float)y+0.5f,
			0.f,0.f,0.f);
	}
	if(playercount>1){
		makeperson(
			persontype_player,
			(float)x+1.5f,
			(float)y+0.5f,
			0.f,0.f,0.f);
	}
	if(playercount>2){
		makeperson(
			persontype_player,
			(float)x-0.5f,
			(float)y+0.5f,
			0.f,0.f,0.f);
	}
	if(playercount>3){
		makeperson(
			persontype_player,
			(float)x+0.5f,
			(float)y+1.5f,
			0.f,0.f,0.f);
	}
	for(int a=0;a<playercount;a++){
		aimx[a]=0;
		aimy[a]=0;
		aiminworldx[a]=0;
		aiminworldy[a]=0;
		shootwait[a]=0;
		healwait[a]=0;
		energy[a]=100;
		energyregenwait[a]=0;
	}
	camx=(float)x+0.5f;
	camy=(float)y+0.5f;
	camz=1.f;

	zombieskilled=0;

	updateturn=0;

}
