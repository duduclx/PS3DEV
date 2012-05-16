void cleanoutpeopleandthings(){

	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	while(thingcount[x][z]>0)removethingfromlist(x,z,0);

	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	while(personcount[x][z]>0)removepersonfromlist(x,z,0);

}

void genpeopleandthings(){

	if(totalthingtypecount[thingtype_ammo]<20){
		int x=rand()%worldgridsizex;
		int z=rand()%worldgridsizez;
		if(x<camxgridpos-viewrange || x>camxgridpos+viewrange
		|| z<camzgridpos-viewrange || z>camzgridpos+viewrange)
		if(worldgrid[x][z]==0 && thingcount[x][z]==0){
			makething(
				thingtype_ammo,
				x*worldtilesize,
				-15.f,
				z*worldtilesize,
				0.f,0.f,0.f,0.f);
		}
	}

	if(totalthingtypecount[thingtype_medkit]<10){
		int x=rand()%worldgridsizex;
		int z=rand()%worldgridsizez;
		if(x<camxgridpos-viewrange || x>camxgridpos+viewrange
		|| z<camzgridpos-viewrange || z>camzgridpos+viewrange)
		if(worldgrid[x][z]==0 && thingcount[x][z]==0){
			makething(
				thingtype_medkit,
				x*worldtilesize,
				-15.f,
				z*worldtilesize,
				0.f,0.f,0.f,0.f);
		}
	}

	if(totalpersoncount<50){
		int x=rand()%worldgridsizex;
		int z=rand()%worldgridsizez;
		if(x<camxgridpos-viewrange || x>camxgridpos+viewrange
		|| z<camzgridpos-viewrange || z>camzgridpos+viewrange)
		if(worldgrid[x][z]==0 &&personcount[x][z]==0){
			makeperson(x*worldtilesize,0,z*worldtilesize);
		}
	}

}
