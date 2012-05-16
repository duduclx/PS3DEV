void drawtitlescreen(){

	float viewsizex=480.f*screena;
	float viewsizey=480.f;

	#ifdef PS3
	viewsizex=550.f*screena;
	viewsizey=550.f;
	#endif

	set2dcamera(0.f,viewsizey,0.f,viewsizex);

	#ifdef GX
	GX_LoadTexObj(&hudtexture_GXTexObj, GX_TEXMAP0);
	#endif

	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,hudtexture);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	#ifdef RSX
	usetexture(hudtexture_image);
	#endif

	//white background
	if(1){
		float indent=4;
		float texturecoords[]={
			(0.f+indent)/512.f,		(300.f-indent)/512.f,
			(10.f-indent)/512.f,	(300.f-indent)/512.f,
			(10.f-indent)/512.f,	(288.f+indent)/512.f,
			(0.f+indent)/512.f,		(288.f+indent)/512.f,};
		draw2dquad(0,0,viewsizex,viewsizey,texturecoords,0,0);
	}
	//title
	if(1){
		float indent=4;
		float texturecoords[]={
			(0.f+indent)/512.f,		(459.f-indent)/512.f,
			(512.f-indent)/512.f,	(459.f-indent)/512.f,
			(512.f-indent)/512.f,	(288.f+indent)/512.f,
			(0.f+indent)/512.f,		(288.f+indent)/512.f,};
		draw2dquad(
			(viewsizex-(512-indent*2))/2,
			(viewsizey-(171-indent*2))/2,
			512-indent*2,
			171-indent*2,
			texturecoords,0,0);
	}

	#ifdef PS3
	float indent=4;
	drawtext(viewsizex*0.5f-15.f*textxsize*0.5f,(viewsizey-(171-indent*2))/2+175,(char*)"Press X to play",1);
	#endif

	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
