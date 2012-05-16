int gameworldvertexcount=0;
float* gameworldvertexarray=NULL;
float* gameworldtexturearray=NULL;

void genworld(){
	gameworldvertexcount=0;
	for(int x=0;x<worldsizex;x++)for(int y=0;y<worldsizey;y++)
		if(worldgrid[x][y]==1)gameworldvertexcount+=4*5;
	free(gameworldvertexarray);
	free(gameworldtexturearray);
	gameworldvertexarray=(float*)malloc(gameworldvertexcount*3*sizeof(float));
	gameworldtexturearray=(float*)malloc(gameworldvertexcount*2*sizeof(float));
	int arraposy3=0,arraposy2=0;
	for(int x=0;x<worldsizex;x++)for(int y=0;y<worldsizey;y++)
	if(worldgrid[x][y]==1){
		float posx=(float)x;
		float posy=(float)y;
		float posz=-0.5f;
		if(1){//side 1
			float verts[]={
				posx+1.f,	posy,		posz+1.f,
				posx+1.f,	posy,		posz,
				posx+1.f,	posy+1.f,	posz,
				posx+1.f,	posy+1.f,	posz+1.f,};
			for(int a=0;a<4*3;a++)gameworldvertexarray[arraposy3+a]=verts[a];
			for(int a=0;a<4*2;a++)gameworldtexturearray[arraposy2+a]=blocksidetexturecoords[1][0][a];
			arraposy3+=4*3;
			arraposy2+=4*2;
		}
		if(1){//side 2
			float verts[]={
				posx,		posy,		posz,
				posx,		posy,		posz+1.f,
				posx,		posy+1.f,	posz+1.f,
				posx,		posy+1.f,	posz,};
			for(int a=0;a<4*3;a++)gameworldvertexarray[arraposy3+a]=verts[a];
			for(int a=0;a<4*2;a++)gameworldtexturearray[arraposy2+a]=blocksidetexturecoords[2][0][a];
			arraposy3+=4*3;
			arraposy2+=4*2;
		}
		if(1){//top
			float verts[]={
				posx,		posy+1.f,	posz+1.f,
				posx+1.f,	posy+1.f,	posz+1.f,
				posx+1.f,	posy+1.f,	posz,
				posx,		posy+1.f,	posz,};
			for(int a=0;a<4*3;a++)gameworldvertexarray[arraposy3+a]=verts[a];
			for(int a=0;a<4*2;a++)gameworldtexturearray[arraposy2+a]=grasstoptexturecoords[a];
			arraposy3+=4*3;
			arraposy2+=4*2;
		}
		if(1){//bottom
			float verts[]={
				posx,		posy,		posz,
				posx+1.f,	posy,		posz,
				posx+1.f,	posy,		posz+1.f,
				posx,		posy,		posz+1.f,};
			for(int a=0;a<4*3;a++)gameworldvertexarray[arraposy3+a]=verts[a];
			for(int a=0;a<4*2;a++)gameworldtexturearray[arraposy2+a]=blockbottomtexturecoords[a];
			arraposy3+=4*3;
			arraposy2+=4*2;
		}
		if(1){//side 3
			float verts[]={
				posx,		posy,		posz+1.f,
				posx+1.f,	posy,		posz+1.f,
				posx+1.f,	posy+1.f,	posz+1.f,
				posx,		posy+1.f,	posz+1.f,};
			for(int a=0;a<4*3;a++)gameworldvertexarray[arraposy3+a]=verts[a];
			for(int a=0;a<4*2;a++)gameworldtexturearray[arraposy2+a]=blocksidetexturecoords[0][0][a];
			arraposy3+=4*3;
			arraposy2+=4*2;
		}
	}
}
