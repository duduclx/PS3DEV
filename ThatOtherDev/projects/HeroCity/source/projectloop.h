#ifdef WII
int starttime=0;
#endif

void projectloop(){
	
	//adjust the speed of the game based on the frame rate
	#ifndef PS3
	float gamespeed=60.f/dash_framerate;
	#else
	float gamespeed=2.f;
	#endif
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;
	
	#ifdef WII
	if(starttime==0)starttime=dash_gametime;
	#endif	

	if(gamestate==0){
		#ifndef WII
		gamestate=1;
		#else
		drawsplashscreen();
		if(dash_gametime>5000+starttime){
			resetgame();
			gamestate=1;
		}else{
			if(WiiButtonsDown[0] & WPAD_BUTTON_A){
				resetgame();
				gamestate=1;
			}
		}
		#endif
	}else if(gamestate==1){
		drawtitlescreen();
		#ifdef WIN
		if((mousestate[SDL_BUTTON_LEFT]==2)||(keystate[SDLK_a]==2)){
		#endif
		#ifdef WII
		if(WiiButtonsDown[0] & WPAD_BUTTON_A){
		#endif
		#ifdef PS3
		if(BTN_CROSS[0]==2){
		#endif
			gamestate=2;
			score=0;
		}
		drawhud();
	}else if(gamestate==2){
		play(gamespeed);	
		drawworld();
		drawhud();
		if(playerhealth==0)gamestate=3;
	}
	if(gamestate==3){
		resetgame();
		gamestate=1;
	}
	
	musicplay();

}

