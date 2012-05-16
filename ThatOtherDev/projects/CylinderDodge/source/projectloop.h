#ifndef PS3
int starttime=0;
#endif

void projectloop(){
	
	//adjust the speed of the game based on the frame rate
	#ifndef PS3
	float gamespeed=60.f/dash_framerate;
	#else
	float gamespeed=1.f;
	#endif
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;
	
	#ifndef PS3
	if(starttime==0)starttime=dash_gametime;
	#endif
	
	if(gamestate==0){
		#ifdef PS3
		gamestate=1;
		#else
		drawsplashscreen();
		if(dash_gametime>5000+starttime){
			resetgame();
			gamestate=1;
		}else{
			#ifdef WIN
			if((mousestate[SDL_BUTTON_LEFT]==2)||(keystate[SDLK_a]==2)){
			#endif
			#ifdef WII
			if(WiiButtonsDown[0] & WPAD_BUTTON_A){
			#endif
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
			for(int a=0;a<125;a++)play(1);
			score=0;
		}
		drawhud();
	}else if(gamestate==2){
		play(gamespeed);	
		drawworld();
		drawhud();
	}
	if(gamestate==3){
		resetgame();
		gamestate=1;
	}
	
	musicplay();

}
