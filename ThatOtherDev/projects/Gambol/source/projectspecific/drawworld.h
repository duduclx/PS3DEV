void drawworld(){

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	//set the camera
	set3dcamera(
		camposx,camposy,camposz,0.f,camangy,0.f,
		45.f,screena,0.1f,1000.f);

	//draw the game world
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,worldtexture);
	#endif
	#ifdef GX
	GX_LoadTexObj(&worldtexture_GXTexObj,GX_TEXMAP0);
	#endif
	#ifdef RSX
	usetexture(worldtexture_image);
	#endif
	draw3dquadmesh(
		gameworldvertexcount,&gameworldvertexarray[0],&gameworldtexturearray[0],NULL,NULL);

	//draw the player
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,mariotexture);
	#endif
	#ifdef GX
	GX_LoadTexObj(&mariotexture_GXTexObj,GX_TEXMAP0);
	#endif
	#ifdef RSX
	usetexture(mariotexture_image);
	#endif
	savecammatrix();
	translatecam(playerposx,playerposy-0.45f,0.f);
	rotatecam(playerangy*degreesinradian,0,1,0);
	draw3dtrianglemesh(
		mariovertexcount,&mariovertexarray[0],&mariotexturearray[0],NULL,NULL);
	loadcammatrix();

	//draw enemies
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,goombatexture);
	#endif
	#ifdef GX
	GX_LoadTexObj(&goombatexture_GXTexObj,GX_TEXMAP0);
	#endif
	#ifdef RSX
	usetexture(goombatexture_image);
	#endif
	for(int a=0;a<entitycount;a++){
		if(entitylist[a].type==entitytype_enemy){
			savecammatrix();
			translatecam(entitylist[a].posx,entitylist[a].posy-0.45f,0.f);
			draw3dtrianglemesh(
				goombavertexcount,&goombavertexarray[0],&goombatexturearray[0],NULL,NULL);
			loadcammatrix();
		}
	}

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
