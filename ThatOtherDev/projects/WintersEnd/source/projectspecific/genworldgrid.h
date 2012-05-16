void genworldgrid(){

	//clean up
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)treegrid[x][z]=0;

	//load the tree placement
	char filename[256];
	char temptext[256];
	#ifdef WIN
	sprintf(filename,"%s%i%s","Media/level",currentlevel,".txt");
	#endif
	#ifdef WII
	sprintf(filename,"%s%i%s","Media/level",currentlevel,".txt");
	#endif
	#ifdef PS3
	sprintf(filename,"%s%i%s","/dev_hdd0/game/WINTERSEN/USRDIR/level",currentlevel,".txt");
	#endif
	FILE *pFile=fopen(filename,"r");
	if(pFile != NULL){
		for(int a=0; a<25; a++){
			fgets(temptext,1000,pFile);
			for(int b=0; b<25; b++){
				if(temptext[b]=='1')treegrid[b][a]=1;
			}
		}
		fclose (pFile);
	}

	//set snow everywhere
	for(int x=0; x<worldgridsizex*2; x++)
	for(int z=0; z<worldgridsizez*2; z++)snowgrid[x][z]=1;

	//get rid of snow near trees
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)if(treegrid[x][z]){
		for(int x2=highint(0,x*2-1); x2<lowint(worldgridsizex*2,x*2+2); x2++)
		for(int z2=highint(0,z*2-1); z2<lowint(worldgridsizez*2,z*2+2); z2++)
			snowgrid[x2][z2]=0;
	}

	//get rid of snow near the player
	for(int x=worldgridsizex-2; x<worldgridsizex+1; x++)
	for(int z=worldgridsizez-2; z<worldgridsizez+1; z++)snowgrid[x][z]=0;

	//set tree height
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
		treegridheight[x][z]=0.f-(float)(rand()%100)*0.010f;

	//set snow height
	for(int x=0; x<worldgridsizex*2; x++)
	for(int z=0; z<worldgridsizez*2; z++)
		snowgridheight[x][z]=0.f-(float)(rand()%100)*0.005f;

	//count the blocks of snow
	totalsnow=0;
	for(int x=0; x<worldgridsizex*2; x++)
	for(int z=0; z<worldgridsizez*2; z++)if(snowgrid[x][z])totalsnow+=1;;

}
