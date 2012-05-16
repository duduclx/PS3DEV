void projectloop(){
	
	//adjust the speed of the game based on the frame rate
	#ifndef PS3
	float gamespeed=60.f/dash_framerate;
	#else
	float gamespeed=1.f;
	#endif
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;

	if(gamestate==0){
		drawworld();
		drawtitlescreen();
		#ifdef WII
		if(WiiButtonsDown[0] & WPAD_BUTTON_A)gamestate=1;
		#endif
		#ifdef WIN
		if(keystate[SDLK_SPACE]==2)gamestate=1;
		#endif
		#ifdef PS3
		if(paddata[0].BTN_CROSS)gamestate=1;
		#endif
	}else if(gamestate==1){
		for(int a=0;a<4;a++)play(gamespeed*0.25f);
		drawworld();
		drawhud();
	}

}
