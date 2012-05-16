#define linelength (1500)

void writefloat(float data,FILE* pFile){
	//char temptext[linelength];
	//sprintf(temptext,"%f%c",data,'\n');
	//fputs(temptext,pFile);
	fwrite(&data,sizeof(float),1,pFile);
}

void readfloat(float *data,FILE* pFile){
	//char temptext[linelength];
	//fgets(temptext,linelength,pFile);
	//data=(float)atof(temptext);
	fread(data,sizeof(float),1,pFile);
}

void writeint(int data,FILE* pFile){
	//char temptext[linelength];
	//sprintf(temptext,"%i%c",data,'\n');
	//fputs(temptext,pFile);
	fwrite(&data,sizeof(int),1,pFile);
}

void readint(int *data,FILE* pFile){
	//char temptext[linelength];
	//fgets(temptext,linelength,pFile);
	//data=(int)atof(temptext);
	fread(data,sizeof(int),1,pFile);
}

void writechar(char data,FILE* pFile){
	//char temptext[linelength];
	//sprintf(temptext,"%c%c",data,'\n');
	//fputs(temptext,pFile);
	fwrite(&data,sizeof(char),1,pFile);
}

void readchar(char *data,FILE* pFile){
	//char temptext[linelength];
	//fgets(temptext,linelength,pFile);
	//data=(char)atof(temptext);
	fread(data,sizeof(char),1,pFile);
}

void save(){
	FILE * pFile = NULL;
	#ifdef WIN
	pFile = fopen("save.dat","wb");
	#endif
	#ifdef PS3
	pFile = fopen("/dev_hdd0/game/DONOTDIE2/USRDIR/save.dat","wb");
	#endif
	#ifdef WII
	pFile = fopen("save.dat","wb");
	#endif
	if(pFile != NULL){
		//save the map
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				writechar((char)map[x][y]+' ',pFile);
			}
			writechar((char)'\n',pFile);
		}
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				writechar((char)maprotation[x][y]+' ',pFile);
			}
			writechar((char)'\n',pFile);
		}
		//save the walls
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				writechar((char)wallcount[x][y]+' ',pFile);
			}
			writechar((char)'\n',pFile);
		}
		for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++)
		for(int a=0; a<wallcount[x][y]; a++){
			writefloat(walllist[x][y][a].posx,pFile);
			writefloat(walllist[x][y][a].posy,pFile);
			writefloat(walllist[x][y][a].sizex,pFile);
			writefloat(walllist[x][y][a].sizey,pFile);
		}
		writechar((char)'\n',pFile);
		//save the objects
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				writechar((char)objectcount[x][y]+' ',pFile);
			}
			writechar((char)'\n',pFile);
		}
		for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++)
		for(int a=0; a<objectcount[x][y]; a++){
			writeint(objectlist[x][y][a].type,pFile);
			writefloat(objectlist[x][y][a].posx,pFile);
			writefloat(objectlist[x][y][a].posy,pFile);
			writefloat(objectlist[x][y][a].movx,pFile);
			writefloat(objectlist[x][y][a].movy,pFile);
			writefloat(objectlist[x][y][a].angle,pFile);
			writefloat(objectlist[x][y][a].health,pFile);
		}
		writechar((char)'\n',pFile);
		//save persons
		writeint(personcount,pFile);
		for(int a=0;a<6;a++){
			writeint(persontypecount[a],pFile);
		}
		for(int a=0;a<personcount;a++){
			writeint(personlist[a].type,pFile);
			writeint(personlist[a].havetarget,pFile);
			writeint(personlist[a].targetnum,pFile);
			writeint(personlist[a].updateturn,pFile);
			writefloat(personlist[a].posx,pFile);
			writefloat(personlist[a].posy,pFile);
			writefloat(personlist[a].movx,pFile);
			writefloat(personlist[a].movy,pFile);
			writefloat(personlist[a].angle,pFile);
			writefloat(personlist[a].health,pFile);
		}
		writechar((char)'\n',pFile);
		//save shots
		writeint(shotcount,pFile);
		for(int a=0;a<shotcount;a++){
			writefloat(shotlist[a].angle,pFile);
			writefloat(shotlist[a].startx,pFile);
			writefloat(shotlist[a].starty,pFile);
			writefloat(shotlist[a].endx,pFile);
			writefloat(shotlist[a].endy,pFile);
		}
		writechar((char)'\n',pFile);
		//save decals
		writeint(decalcount,pFile);
		for(int a=0;a<decalcount;a++){
			writeint(decallist[a].type,pFile);
			writefloat(decallist[a].posx,pFile);
			writefloat(decallist[a].posy,pFile);
			writefloat(decallist[a].angle,pFile);
		}
		writechar((char)'\n',pFile);
		//save rockets
		writeint(rocketcount,pFile);
		for(int a=0;a<rocketcount;a++){
			writeint(rocketlist[a].shotby,pFile);
			writefloat(rocketlist[a].posx,pFile);
			writefloat(rocketlist[a].posy,pFile);
			writefloat(rocketlist[a].movx,pFile);
			writefloat(rocketlist[a].movy,pFile);
			writefloat(rocketlist[a].angle,pFile);
			writefloat(rocketlist[a].health,pFile);
		}
		writechar((char)'\n',pFile);
		//save explosions
		writeint(explosioncount,pFile);
		for(int a=0;a<explosioncount;a++){
			writefloat(explosionlist[a].posx,pFile);
			writefloat(explosionlist[a].posy,pFile);
			writefloat(explosionlist[a].angle,pFile);
			writefloat(explosionlist[a].health,pFile);
		}
		writechar((char)'\n',pFile);
		//save player data
		writeint(playercount,pFile);
		for(int a=0;a<playercount;a++){
			writefloat(aimx[a],pFile);
			writefloat(aimy[a],pFile);
			writefloat(aiminworldx[a],pFile);
			writefloat(aiminworldy[a],pFile);
			writefloat(shootwait[a],pFile);
			writefloat(healwait[a],pFile);
			writefloat(energy[a],pFile);
			writefloat(energyregenwait[a],pFile);
		}
		//save remaining data
		writefloat(camx,pFile);
		writefloat(camy,pFile);
		writefloat(camz,pFile);
		writeint(zombieskilled,pFile);
		writeint(updateturn,pFile);
		fclose(pFile);
	}
}

void load(){
	removeallentities();
	FILE * pFile = NULL;
	#ifdef WIN
	pFile = fopen("save.dat","rb");
	#endif
	#ifdef PS3
	pFile = fopen("/dev_hdd0/game/DONOTDIE2/USRDIR/save.dat","rb");
	#endif
	#ifdef WII
	pFile = fopen("save.dat","rb");
	#endif
	char tempchar=0;
	if(pFile != NULL){
		//load map
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				readchar(&tempchar,pFile);
				map[x][y]=(int)tempchar-' ';
			}
			readchar(&tempchar,pFile);
		}
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				readchar(&tempchar,pFile);
				maprotation[x][y]=(int)tempchar-' ';
			}
			readchar(&tempchar,pFile);
		}
		//load walls
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				readchar(&tempchar,pFile);
				wallcount[x][y]=(int)tempchar-' ';
			}
			readchar(&tempchar,pFile);
		}
		for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++)
		for(int a=0; a<wallcount[x][y]; a++){
			readfloat(&walllist[x][y][a].posx,pFile);
			readfloat(&walllist[x][y][a].posy,pFile);
			readfloat(&walllist[x][y][a].sizex,pFile);
			readfloat(&walllist[x][y][a].sizey,pFile);
		}
		readchar(&tempchar,pFile);
		//load objects
		for(int y=0;y<mapsizey;y++){
			for(int x=0;x<mapsizex;x++){
				readchar(&tempchar,pFile);
				objectcount[x][y]=(int)tempchar-' ';
			}
			readchar(&tempchar,pFile);
		}
		for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++)
		for(int a=0; a<objectcount[x][y]; a++){
			readint(&objectlist[x][y][a].type,pFile);
			readfloat(&objectlist[x][y][a].posx,pFile);
			readfloat(&objectlist[x][y][a].posy,pFile);
			readfloat(&objectlist[x][y][a].movx,pFile);
			readfloat(&objectlist[x][y][a].movy,pFile);
			readfloat(&objectlist[x][y][a].angle,pFile);
			readfloat(&objectlist[x][y][a].health,pFile);
		}
		readchar(&tempchar,pFile);
		//load persons
		readint(&personcount,pFile);
		for(int a=0;a<6;a++){
			readint(&persontypecount[a],pFile);
		}
		for(int a=0;a<personcount;a++){
			readint(&personlist[a].type,pFile);
			readint(&personlist[a].havetarget,pFile);
			readint(&personlist[a].targetnum,pFile);
			readint(&personlist[a].updateturn,pFile);
			readfloat(&personlist[a].posx,pFile);
			readfloat(&personlist[a].posy,pFile);
			readfloat(&personlist[a].movx,pFile);
			readfloat(&personlist[a].movy,pFile);
			readfloat(&personlist[a].angle,pFile);
			readfloat(&personlist[a].health,pFile);
		}
		readchar(&tempchar,pFile);
		//load shots
		readint(&shotcount,pFile);
		for(int a=0;a<shotcount;a++){
			readfloat(&shotlist[a].angle,pFile);
			readfloat(&shotlist[a].startx,pFile);
			readfloat(&shotlist[a].starty,pFile);
			readfloat(&shotlist[a].endx,pFile);
			readfloat(&shotlist[a].endy,pFile);
		}
		readchar(&tempchar,pFile);
		//load decals
		readint(&decalcount,pFile);
		for(int a=0;a<decalcount;a++){
			readint(&decallist[a].type,pFile);
			readfloat(&decallist[a].posx,pFile);
			readfloat(&decallist[a].posy,pFile);
			readfloat(&decallist[a].angle,pFile);
		}
		readchar(&tempchar,pFile);
		//load rockets
		readint(&rocketcount,pFile);
		for(int a=0;a<rocketcount;a++){
			readint(&rocketlist[a].shotby,pFile);
			readfloat(&rocketlist[a].posx,pFile);
			readfloat(&rocketlist[a].posy,pFile);
			readfloat(&rocketlist[a].movx,pFile);
			readfloat(&rocketlist[a].movy,pFile);
			readfloat(&rocketlist[a].angle,pFile);
			readfloat(&rocketlist[a].health,pFile);
		}
		readchar(&tempchar,pFile);
		//load explosions
		readint(&explosioncount,pFile);
		for(int a=0;a<explosioncount;a++){
			readfloat(&explosionlist[a].posx,pFile);
			readfloat(&explosionlist[a].posy,pFile);
			readfloat(&explosionlist[a].angle,pFile);
			readfloat(&explosionlist[a].health,pFile);
		}
		readchar(&tempchar,pFile);
		//save player data
		readint(&playercount,pFile);
		for(int a=0;a<playercount;a++){
			readfloat(&aimx[a],pFile);
			readfloat(&aimy[a],pFile);
			readfloat(&aiminworldx[a],pFile);
			readfloat(&aiminworldy[a],pFile);
			readfloat(&shootwait[a],pFile);
			readfloat(&healwait[a],pFile);
			readfloat(&energy[a],pFile);
			readfloat(&energyregenwait[a],pFile);
		}
		//load remaining data
		readfloat(&camx,pFile);
		readfloat(&camy,pFile);
		readfloat(&camz,pFile);
		readint(&zombieskilled,pFile);
		readint(&updateturn,pFile);
		fclose(pFile);
	}
}

void savestats(){
	FILE * pFile = NULL;
	#ifdef WIN
	pFile = fopen("stats.dat","wb");
	#endif
	#ifdef PS3
	pFile = fopen("/dev_hdd0/game/DONOTDIE2/USRDIR/stats.dat","wb");
	#endif
	#ifdef WII
	pFile = fopen("stats.dat","wb");
	#endif
	if(pFile != NULL){
		writeint(mostzombieskilled,pFile);
		fclose(pFile);
	}
}

void loadstats(){
	removeallentities();
	FILE * pFile = NULL;
	#ifdef WIN
	pFile = fopen("stats.dat","rb");
	#endif
	#ifdef PS3
	pFile = fopen("/dev_hdd0/game/DONOTDIE2/USRDIR/stats.dat","rb");
	#endif
	#ifdef WII
	pFile = fopen("stats.dat","rb");
	#endif
	//char tempchar=0;
	if(pFile != NULL){
		readint(&mostzombieskilled,pFile);
		fclose(pFile);
	}
}