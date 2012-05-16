void projectloop(){
	
	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,slimetexture);
	#endif
	#ifdef RSX
	usetexture(slimetexture_image);
	#endif

	//adjust the speed of the game based on the frame rate
	#ifndef PS3
	float gamespeed=60.f/dash_framerate;
	#else
	float gamespeed=1.f;
	#endif
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;

	if(gamestate==0){
		menu();
	}else if(gamestate==1){
		//for(int a=0;a<4;a++)play(gamespeed*0.25f);
		play(gamespeed);
		drawworld();
	}else if(gamestate==2){
		edit(gamespeed);
		drawworld();
	}

	#ifndef PS3
	dashusecursors=0;
	#endif

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	#endif

}
