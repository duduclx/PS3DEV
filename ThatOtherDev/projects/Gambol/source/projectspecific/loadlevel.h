#define maxworldsizex	(1000)
#define maxworldsizey	(1000)
int worldsizex=0;
int worldsizey=0;
int worldgrid[maxworldsizex][maxworldsizey];

#define maptype_nothing			(0)
#define maptype_blocknormal		(1)
#define maptype_playerspawn		(2)
#define maptype_enemyspawn		(3)

void loadlevel(int levelnum){

	FILE * pFile;
	char address[256];
	#ifdef WIN
	sprintf(address,"%s%i%s","Levels/level",levelnum,".dat");
	#endif
	#ifdef PS3
	sprintf(address,"%s%i%s","/dev_hdd0/game/GAMBOL123/USRDIR/Levels/level",levelnum,".dat");
	#endif
	#ifdef WII
	sprintf(address,"%s%i%s","Levels/level",levelnum,".dat");
	#endif
	pFile=fopen(address,"r");
	if(pFile != NULL){
		char line[maxworldsizex];
		//title
		fgets(line,maxworldsizex,pFile);
		//map size x
		fgets(line,maxworldsizex,pFile);
		worldsizex=(int)atof(line);
		//map size y
		fgets(line,maxworldsizex,pFile);
		worldsizey=(int)atof(line);
		//map contents
		for(int y=0;y<worldsizey;y++){
			fgets(line,maxworldsizex,pFile);
			for(int x=0;x<worldsizex;x++)worldgrid[x][worldsizey-1-y]=(int)line[x]-'a';
		}
		fclose (pFile);
	}else{
		worldsizex=10;
		worldsizey=10;
		for(int x=0;x<worldsizex;x++)for(int y=0;y<worldsizey;y++){
			if(x==0 || x==worldsizex-1 || y==0 || y==worldsizey-1){
				worldgrid[x][y]=maptype_blocknormal;
			}else if(x==5 && y==5){
				worldgrid[x][y]=maptype_playerspawn;
			}else{
				worldgrid[x][y]=maptype_nothing;
			}
		}
	}

	for(int x=0;x<worldsizex;x++)for(int y=0;y<worldsizey;y++){
		if(worldgrid[x][y]==maptype_playerspawn){
			playerposx=(float)x+0.5f;
			playerposy=(float)y+0.5f;
		}
		if(worldgrid[x][y]==maptype_enemyspawn){
			makeentity(entitytype_enemy,(float)x+0.5f,(float)y+0.5f,0.f,0.f);
		}
	}

}
