void drawworld(){

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	//setup the camera
	set3dcamera(
		camxpos,camypos,camzpos,
		-camxang,camyang+90*radiansindegree,camzang,
		50,screena,0.1f,1000.f);

	//draw the game world
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,meshtexture);
	#endif
	#ifdef GX
	GX_LoadTexObj(&meshtexture_GXTexObj,GX_TEXMAP0);
	#endif
	#ifdef RSX
	usetexture(meshtexture_image);
	#endif

	//draw cylinders
	for(int a=0;a<cylindercount;a++){
		savecammatrix();
		translatecam(cylinderlist[a].xpos,cylinderlist[a].ypos,cylinderlist[a].zpos);
		draw3dtrianglemesh(
			cylindervertexcount,&cylindervertexarray[0],&cylindertexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//draw the player
	savecammatrix();
	translatecam(plrxpos,plrypos,plrzpos);
	draw3dtrianglemesh(
		spherevertexcount,&spherevertexarray[0],&spheretexturearray[0],NULL,NULL);
	loadcammatrix();

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
