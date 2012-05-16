float splashscreenwait=0.f;

void projectloop(){
	
	//adjust the speed of the game based on the frame rate
	#ifndef PS3
	float gamespeed=60.f/dash_framerate;
	#else
	float gamespeed=1.f;
	#endif
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;

	//splashscreen
	if(gamestate==0){
		splashscreenwait+=gamespeed;
		bool startgame=0;
		#ifdef WII
		#endif
		#ifdef WIN
		if(keystate[SDLK_RETURN]==2)startgame=1;
		#endif
		#ifdef PS3
		if(BTN_START[0]==2)startgame=1;
		if(BTN_START[1]==2)startgame=1;
		if(BTN_CROSS[0]==2)startgame=1;
		if(BTN_CROSS[1]==2)startgame=1;
		#endif
		if(splashscreenwait>60.f*5.f || startgame==1)gamestate=1;
	}

	//title screen
	else if(gamestate==1){
		bool startgame=0;
		#ifdef WII
		#endif
		#ifdef WIN
		if(keystate[SDLK_RETURN]==2)startgame=1;
		#endif
		#ifdef PS3
		if(BTN_START[0]==2)startgame=1;
		if(BTN_START[1]==2)startgame=1;
		#endif
		if(startgame==1){
			startnewgame();
			gamestate=2;
		}
	}

	//play
	else if(gamestate==2){
		play(gamespeed);
		bool gameover=0;
		for(int a=0;a<playercount;a++){
			if(player[a].health<=0.f){
				player[a].health=0.f;
				gameover=1;
			}
		}
		if(gameover==1)gamestate=1;
	}

	//draw
	drawworld();

	#ifndef PS3
	dashusecursors=0;
	#endif

}
