void save(){
	FILE * pFile;
	#ifdef WIN
	pFile = fopen ("level.dat" , "w");
	#endif
	#ifdef PS3
	pFile = fopen ("/dev_hdd0/game/SLIMEROLL/USRDIR/level.dat" , "w");
	#endif
	if(pFile != NULL){
		char temptext[100];
		sprintf(temptext,"%i%c",entitycount,'\n');
		fputs(temptext,pFile);
		for(int a=0;a<entitycount;a++){
			sprintf(temptext,"%i%c",entitylist[a].type,'\n');
			fputs(temptext,pFile);
			sprintf(temptext,"%f%c",entitylist[a].posx,'\n');
			fputs(temptext,pFile);
			sprintf(temptext,"%f%c",entitylist[a].posy,'\n');
			fputs(temptext,pFile);
			sprintf(temptext,"%f%c",entitylist[a].movx,'\n');
			fputs(temptext,pFile);
			sprintf(temptext,"%f%c",entitylist[a].movy,'\n');
			fputs(temptext,pFile);
			sprintf(temptext,"%f%c",entitylist[a].size,'\n');
			fputs(temptext,pFile);
		}
		fclose (pFile);
	}
}

void load(){
	while(entitycount>0)removeentityfromlist(0);
	FILE * pFile;
	char lineread[1000];
	#ifdef WIN
	pFile = fopen ("level.dat" , "r");
	#endif
	#ifdef PS3
	pFile = fopen ("/dev_hdd0/game/SLIMEROLL/USRDIR/level.dat" , "r");
	#endif
	if(pFile != NULL){
		fgets(lineread,1000,pFile);
		entitycount=(int)atof(lineread);
		for(int a=0;a<entitycount;a++){
			fgets(lineread,1000,pFile);
			entitylist[a].type=(int)atof(lineread);
			fgets(lineread,1000,pFile);
			entitylist[a].posx=(float)atof(lineread);
			fgets(lineread,1000,pFile);
			entitylist[a].posy=(float)atof(lineread);
			fgets(lineread,1000,pFile);
			entitylist[a].movx=(float)atof(lineread);
			fgets(lineread,1000,pFile);
			entitylist[a].movy=(float)atof(lineread);
			fgets(lineread,1000,pFile);
			entitylist[a].size=(float)atof(lineread);
			entitytypecount[entitylist[a].type]+=1;
		}
		fclose (pFile);
	}
}

