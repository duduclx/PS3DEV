#define maxmapcount (15)
#define maxmapsizex (1000)
#define maxmapsizey (1000)
int map[maxmapsizex][maxmapsizey];

char mapname[maxmapcount][256];
bool mapfound[maxmapcount];
int maphighscore[maxmapcount];
int mapfoundcount;

int currentlevelnumber;

int mapsizex=0;
int mapsizey=0;

#define maptype_nothing			(0)

#define maptype_blocknormal		(1)
#define maptype_blockharmful	(2)
#define maptype_blocknoswing	(3)
#define maptype_blockghost		(4)

#define maptype_gravitydown		(5)
#define maptype_gravityleft		(6)
#define maptype_gravityup		(7)
#define maptype_gravityright	(8)

#define maptype_playerspawn		(9)

#define maptype_extratime		(10)
#define maptype_finish			(11)

void loadlevellist(){
	mapfoundcount=0;
	for(int a=0;a<maxmapcount;a++){
		int levelnum=a+1;
		FILE * pFile;
		char address[256];
		#ifdef WIN
		sprintf(address,"%s%i%s","Levels/level",levelnum,".dat");
		#endif
		#ifdef PS3
		sprintf(address,"%s%i%s","/dev_hdd0/game/SWINGBAL2/USRDIR/Levels/level",levelnum,".dat");
		#endif
		#ifdef WII
		sprintf(address,"%s%i%s","Levels/level",levelnum,".dat");
		#endif
		pFile=fopen(address,"r");
		if(pFile != NULL){
			char line[maxmapsizex];
			fgets(line,maxmapsizex,pFile);
			sprintf(mapname[a],"%s",line);
			fclose (pFile);
			mapfound[a]=1;
			//mapfoundcount+=1;
			mapfoundcount=a+1;
		}else{
			mapfound[a]=0;
		}
	}
	for(int a=0;a<maxmapcount;a++){
		int levelnum=a+1;
		FILE * pFile;
		char address[256];
		#ifdef WIN
		sprintf(address,"%s%i%s","Levels/level",levelnum,".score");
		#endif
		#ifdef PS3
		sprintf(address,"%s%i%s","/dev_hdd0/game/SWINGBAL2/USRDIR/Levels/level",levelnum,".score");
		#endif
		#ifdef WII
		sprintf(address,"%s%i%s","Levels/level",levelnum,".score");
		#endif
		pFile=fopen(address,"rb");
		if(pFile != NULL){
			int data=0;
			fread(&data,sizeof(int),1,pFile);
			fclose(pFile);
			maphighscore[a]=data;
		}else{
			maphighscore[a]=0;
		}
	}
}

void loadlevel(int levelnum){

	FILE * pFile;
	char address[256];
	#ifdef WIN
	sprintf(address,"%s%i%s","Levels/level",levelnum,".dat");
	#endif
	#ifdef PS3
	sprintf(address,"%s%i%s","/dev_hdd0/game/SWINGBAL2/USRDIR/Levels/level",levelnum,".dat");
	#endif
	#ifdef WII
	sprintf(address,"%s%i%s","Levels/level",levelnum,".dat");
	#endif
	pFile=fopen(address,"r");
	if(pFile != NULL){
		char line[maxmapsizex];
		//title
		fgets(line,maxmapsizex,pFile);
		//map size x
		fgets(line,maxmapsizex,pFile);
		mapsizex=(int)atof(line);
		//map size y
		fgets(line,maxmapsizex,pFile);
		mapsizey=(int)atof(line);
		//map contents
		for(int y=0;y<mapsizey;y++){
			fgets(line,maxmapsizex,pFile);
			for(int x=0;x<mapsizex;x++)map[x][y]=(int)line[x]-'a';
		}
		fclose (pFile);
	}

	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++){
		if(map[x][y]==maptype_playerspawn){
			player.posx=(float)x+0.5f;
			player.posy=(float)y+0.5f;
		}
		if(map[x][y]==maptype_extratime){
			makeball(balltype_extratime,(float)x+0.5f,(float)y+0.5f);
		}
		if(map[x][y]==maptype_finish){
			makeball(balltype_finish,(float)x+0.5f,(float)y+0.5f);
		}
	}

}

void savescore(int levelnum,int score){
	FILE * pFile = NULL;
	char address[256];
	#ifdef WIN
	sprintf(address,"%s%i%s","Levels/level",levelnum,".score");
	#endif
	#ifdef PS3
	sprintf(address,"%s%i%s","/dev_hdd0/game/SWINGBAL2/USRDIR/Levels/level",levelnum,".score");
	#endif
	#ifdef WII
	sprintf(address,"%s%i%s","Levels/level",levelnum,".score");
	#endif
	pFile = fopen(address,"wb");
	if(pFile != NULL){
		fwrite(&score,sizeof(int),1,pFile);
	}
	fclose(pFile);
}

void savelevel(int levelnum){

	FILE * pFile;
	char address[256];
	#ifdef WIN
	sprintf(address,"%s%i%s","Levels/level",levelnum,".dat");
	#endif
	#ifdef PS3
	sprintf(address,"%s%i%s","/dev_hdd0/game/SWINGBAL2/USRDIR/Levels/level",levelnum,".dat");
	#endif
	#ifdef WII
	sprintf(address,"%s%i%s","Levels/level",levelnum,".dat");
	#endif
	pFile=fopen(address,"w");
	if(pFile != NULL){
		char line[maxmapsizex];
		//title
		sprintf(line,"%s",mapname[levelnum-1]);
		fputs(line,pFile);
		//map size x
		sprintf(line,"%i%s",mapsizex,"\n");
		fputs(line,pFile);
		//map size y
		sprintf(line,"%i%s",mapsizey,"\n");
		fputs(line,pFile);
		//map contents
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				char data=map[x][y]+'a';
				fwrite(&data,sizeof(char),1,pFile);
			}
			char data='\n';
			fwrite(&data,sizeof(char),1,pFile);
		}
		fclose (pFile);
	}

}
