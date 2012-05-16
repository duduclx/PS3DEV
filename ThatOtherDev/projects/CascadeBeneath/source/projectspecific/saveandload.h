void save(){
	FILE * pFile;
	pFile = fopen ("/dev_hdd0/game/CASCADEBE/USRDIR/level.dat" , "w");
	if(pFile != NULL){
		char temptext[100];
		sprintf(temptext,"%f%c",highscore,'\n');
		fputs(temptext,pFile);
		fclose (pFile);
	}
}

void load(){
	FILE * pFile;
	char lineread[1000];
	pFile = fopen ("/dev_hdd0/game/CASCADEBE/USRDIR/level.dat" , "r");
	if(pFile != NULL){
		fgets(lineread,1000,pFile);
		highscore=(float)atof(lineread);
		fclose (pFile);
	}
}
