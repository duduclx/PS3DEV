const int maxvertexcount=10000;
float loadedvertex[maxvertexcount][3];
const int maxnormalcount=10000;
float loadednormal[maxnormalcount][3];
const int maxtexturecount=10000;
float loadedtexture[maxtexturecount][2];
const int maxfacecount=10000;
int loadedface[maxfacecount][9];

void loadobj(char* filename,float*& vertexarray,float*& texturearray,float*& normalarray,int &outputarraysize,float scale){

	int vertexcount=0;
	int texturecount=0;
	int normalcount=0;
	int facecount=0;
	ifstream indata;
	indata.open(filename);
	char temptext[500];
	while(indata.good()){
		indata >> temptext;
		if(strlen(temptext)==2 && temptext[0]=='v' && temptext[1]=='n'){
			indata >> loadednormal[normalcount][0];
			indata >> loadednormal[normalcount][1];
			indata >> loadednormal[normalcount][2];
			normalcount++;
		}else if(strlen(temptext)==2 && temptext[0]=='v' && temptext[1]=='t'){
			indata >> loadedtexture[texturecount][0];
			indata >> loadedtexture[texturecount][1];
			texturecount++;
		}else if(strlen(temptext)==1 && temptext[0]=='v'){
			indata >> loadedvertex[vertexcount][0];
			indata >> loadedvertex[vertexcount][1];
			indata >> loadedvertex[vertexcount][2];
			vertexcount++;
		}else if(strlen(temptext)==1 && temptext[0]=='f'){
			indata >> temptext;
			loadedface[facecount][0] = atoi(strtok(temptext,"/"))-1;
			loadedface[facecount][3] = atoi(strtok(NULL,"/"))-1;
			loadedface[facecount][6] = atoi(strtok(NULL,"/"))-1;
			indata >> temptext;
			loadedface[facecount][1] = atoi(strtok(temptext,"/"))-1;
			loadedface[facecount][4] = atoi(strtok(NULL,"/"))-1;
			loadedface[facecount][7] = atoi(strtok(NULL,"/"))-1;
			indata >> temptext;
			loadedface[facecount][2] = atoi(strtok(temptext,"/"))-1;
			loadedface[facecount][5] = atoi(strtok(NULL,"/"))-1;
			loadedface[facecount][8] = atoi(strtok(NULL,"/"))-1;
			facecount++;
		}
	}
	indata.close();
	vertexarray = new float[facecount*3*3];
	for(int a=0; a<facecount; a++){
		vertexarray[a*3*3+0]=loadedvertex[loadedface[a][0]][0]*scale;//vert1
		vertexarray[a*3*3+1]=loadedvertex[loadedface[a][0]][1]*scale;
		vertexarray[a*3*3+2]=loadedvertex[loadedface[a][0]][2]*scale;
		vertexarray[a*3*3+3]=loadedvertex[loadedface[a][1]][0]*scale;//vert2
		vertexarray[a*3*3+4]=loadedvertex[loadedface[a][1]][1]*scale;
		vertexarray[a*3*3+5]=loadedvertex[loadedface[a][1]][2]*scale;
		vertexarray[a*3*3+6]=loadedvertex[loadedface[a][2]][0]*scale;//vert3
		vertexarray[a*3*3+7]=loadedvertex[loadedface[a][2]][1]*scale;
		vertexarray[a*3*3+8]=loadedvertex[loadedface[a][2]][2]*scale;
	}
	texturearray = new float[facecount*3*2];
	for(int a=0; a<facecount; a++){
		texturearray[a*3*2+0]=loadedtexture[loadedface[a][3]][0];//vert1
		texturearray[a*3*2+1]=loadedtexture[loadedface[a][3]][1];
		texturearray[a*3*2+2]=loadedtexture[loadedface[a][4]][0];//vert2
		texturearray[a*3*2+3]=loadedtexture[loadedface[a][4]][1];
		texturearray[a*3*2+4]=loadedtexture[loadedface[a][5]][0];//vert3
		texturearray[a*3*2+5]=loadedtexture[loadedface[a][5]][1];
	}
	scale=1;
	normalarray = new float[facecount*3*3];
	for(int a=0; a<facecount; a++){
		normalarray[a*3*3+0]=loadednormal[loadedface[a][6]][0]*scale;//vert1
		normalarray[a*3*3+1]=loadednormal[loadedface[a][6]][1]*scale;
		normalarray[a*3*3+2]=loadednormal[loadedface[a][6]][2]*scale;
		normalarray[a*3*3+3]=loadednormal[loadedface[a][7]][0]*scale;//vert2
		normalarray[a*3*3+4]=loadednormal[loadedface[a][7]][1]*scale;
		normalarray[a*3*3+5]=loadednormal[loadedface[a][7]][2]*scale;
		normalarray[a*3*3+6]=loadednormal[loadedface[a][8]][0]*scale;//vert3
		normalarray[a*3*3+7]=loadednormal[loadedface[a][8]][1]*scale;
		normalarray[a*3*3+8]=loadednormal[loadedface[a][8]][2]*scale;
	}
	outputarraysize=facecount*3;
}
