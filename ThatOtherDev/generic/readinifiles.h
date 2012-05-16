#ifndef PS3
int inilinecount=0;
char inidata[100][256];

void loadinifile(char* filename){
	inilinecount=0;
	//load the data
	ifstream indata;
	indata.open(filename);
	if(!indata.fail()){
		while(/*!indata.eof() && */inilinecount<100){
			//sprintf(inidata[inilinecount],"%s","");
			//inidata[inilinecount][1]=';';
			indata.getline(inidata[inilinecount],256,'\n');
			inilinecount+=1;
			//indata.eof();
		}
		indata.close();
		//remove spaces
		for(int a=0;a<inilinecount;a++){
			int textlength=strlen(inidata[a]);
			for(int b=0;b<textlength;b++){
				if(inidata[a][b]==' '){
					for(int c=b;c<textlength+1;c++)inidata[a][c]=inidata[a][c+1];
					textlength-=1;
					b-=1;
				}
			}
		}
	}
}

float readfloatfromini(char* varname){
	float var=0;
	if(inilinecount>0){
		char text[256];
		sprintf(text,"%s%s",varname,"=");
		for(int a=0;a<inilinecount;a++){
			if(strncmp(inidata[a],text,(signed)strlen(text))==0){
				char value[256];
				for(int b=0;b<(signed)strlen(inidata[a])-(signed)strlen(text);b++){
					value[b]=inidata[a][strlen(text)+b];
				}
				var=atof(value);
			}
		}
	}
	return var;
}
#endif
