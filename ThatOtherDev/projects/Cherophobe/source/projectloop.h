int gamestate=0;

void projectloop(){

	//adjust the speed of the game based on the frame rate
	#ifndef PS3
	float gamespeed=60.f/dash_framerate;
	#else
	float gamespeed=1.f;
	#endif
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;

	//controller rumble
	if(playerhurt){
		playerhurt=0;
		#ifdef WII
		WPAD_Rumble(WPAD_CHAN_0,1);
		#endif
	}else{
		#ifdef WII
		WPAD_Rumble(WPAD_CHAN_0,0);
		#endif
	}

	if(gamestate==0){
		//tile screen
		titlescreen();
		//start the game
		#ifdef WIN
		if((mousestate[SDL_BUTTON_LEFT]==2)||(keystate[SDLK_a]==2))
		#endif
		#ifdef WII
		if(WiiButtonsDown[0] & WPAD_BUTTON_A)
		#endif
		#ifdef PS3
		if(BTN_CROSS[0]==2)
		#endif
			gamestate=1;
	}else if(gamestate==1){
		//play
		play(gamespeed);
		//draw
		drawworld();
		drawhud();
		//game over when die
		if(health<=0){
			resetgame();
			gamestate=0;
		}
	}
	
	//keep the music playing
	musicplay();

}
