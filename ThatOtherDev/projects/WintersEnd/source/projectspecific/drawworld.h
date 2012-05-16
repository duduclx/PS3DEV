void drawworld(){

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	//set the camera
	set3dcamera(
		camxpos,camypos,camzpos,-camxang,camyang+90.f*radiansindegree,camzang,
		45.f,screena,0.1f,1000.f);

	//load the texture
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,worldtexture);
	#endif
	#ifdef GX
	GX_LoadTexObj(&worldtexture_GXTexObj,GX_TEXMAP0);
	#endif
	#ifdef RSX
	usetexture(worldtexture_image);
	#endif

	//draw the ground
	for(int x=0; x<worldgridsizex; x++)for(int z=0; z<worldgridsizez; z++){
		savecammatrix();
		translatecam(x*worldtilesize,0,z*worldtilesize);
		draw3dtrianglemesh(
			groundvertexcount,&groundvertexarray[0],&groundtexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//draw the trees
	for(int x=0; x<worldgridsizex; x++)for(int z=0; z<worldgridsizez; z++)
	if(treegrid[x][z]==1){
		savecammatrix();
		translatecam(x*worldtilesize,treegridheight[x][z],z*worldtilesize);
		draw3dtrianglemesh(
			treevertexcount,&treevertexarray[0],&treetexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//draw the snow
	for(int x=0; x<worldgridsizex*2; x++)for(int z=0; z<worldgridsizez*2; z++)
	if(snowgrid[x][z]==1){
		savecammatrix();
		translatecam(x*worldtilesize*0.5f,snowgridheight[x][z],z*worldtilesize*0.5f);
		draw3dtrianglemesh(
			snowvertexcount,&snowvertexarray[0],&snowtexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//draw the player
	int snowpeoplevertexcount=snowpeoplesmallvertexcount;
	float *snowpeoplevertexarray=(float*)malloc(snowpeoplevertexcount*3*sizeof(float));
	for(int a=0; a<snowpeoplevertexcount*3; a++)
		snowpeoplevertexarray[a]=
			snowpeoplesmallvertexarray[a]*(1.f-playersize)+
			snowpeoplebigvertexarray[a]*(playersize);
	float *snowpeopletexturearray=snowpeoplesmalltexturearray;
	//float *snowpeoplenormalarray=snowpeoplesmallnormalarray;
	savecammatrix();
	translatecam(playerxpos,0.f,playerzpos);
	rotatecam(-playeryang*degreesinradian,0,1,0);
	draw3dtrianglemesh(
		snowpeoplevertexcount,&snowpeoplevertexarray[0],&snowpeopletexturearray[0],NULL,NULL);
	loadcammatrix();
	free(snowpeoplevertexarray);

	//draw hud
	float viewsizex=480.f*screena;
	float viewsizey=480.f;

	#ifdef PS3
	viewsizex=550.f*screena;
	viewsizey=550.f;
	#endif

	set2dcamera(0.f,viewsizey,0.f,viewsizex);

	//set2dcamera(1,-1,-1,1);

	char temptext[100];
	int x=0;
	int y=20;
	#ifdef PS3
	y+=5;
	#endif
	for(int a=0;a<3;a++){
		sprintf(temptext,"%s","                             ");
		drawtext(x,y,(char*)temptext,0.5f);
		y+=22;
	}
	y-=22*3;
	sprintf(temptext,"%s%i"," level: ",currentlevel);
	drawtext(x,y,(char*)temptext,1.0f);
	y+=44;
	sprintf(temptext,"%s%f%s","  snow collected: ",((float)snowcollected/(float)totalsnow*100),"%");
	drawtext(x,y,(char*)temptext,0.5f);
	y+=22;

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
