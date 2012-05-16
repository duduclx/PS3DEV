void projectloop(){
	
	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,swingball2texture);
	#endif
	#ifdef RSX
	usetexture(swingball2texture_image);
	#endif
	#ifdef GX
	GX_LoadTexObj(&swingball2texture_GXTexObj, GX_TEXMAP0);
	GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	#endif

	int oldgamestate=gamestate;

	//adjust the speed of the game based on the frame rate
	#ifndef PS3
	float gamespeed=60.f/dash_framerate;
	#else
	float gamespeed=1.f;
	#endif
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;

	if(gamestate==gamestate_titlescreen){
		menu();
	}else if(gamestate==gamestate_menutoplay){
		menu();
	}else if(gamestate==gamestate_menutoedit){
		menu();
	}else if(gamestate==gamestate_play){
		play(gamespeed);
		drawworld();
	}else if(gamestate==gamestate_edit){
		edit(gamespeed);
		drawworldeditor();
	}

	if(oldgamestate!=gamestate){
		menustate=0;
		menuscroll=0;
	}

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	#endif
	#ifdef GX
	GX_SetAlphaUpdate(GX_FALSE);
	#endif

}
