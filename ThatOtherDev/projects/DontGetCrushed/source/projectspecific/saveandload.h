void save(){
	/*ofstream outdata;
	outdata.open("/dev_hdd0/game/CRUS66666/USRDIR/savefile.txt");
	if(outdata.good()){
		outdata << highscore << "\n" ;
		outdata << endl;
	}
	outdata.close();*/
	FILE * pFile;
	pFile = fopen ("/dev_hdd0/game/DGCRUSHED/USRDIR/level.dat" , "w");
	if(pFile != NULL){
		char temptext[100];
		sprintf(temptext,"%f%c",highscore,'\n');
		fputs(temptext,pFile);
		fclose (pFile);
	}
}

void load(){
	/*ifstream indata;
	indata.open("/dev_hdd0/game/CRUS66666/USRDIR/savefile.txt");
	if(indata.good()){
		indata >> highscore;
	}
	indata.close();*/
	FILE * pFile;
	char lineread[1000];
	pFile = fopen ("/dev_hdd0/game/DGCRUSHED/USRDIR/level.dat" , "r");
	if(pFile != NULL){
		fgets(lineread,1000,pFile);
		highscore=(float)atof(lineread);
		fclose (pFile);
	}
}
