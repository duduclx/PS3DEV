void projectloop(){
	
	//adjust the speed of the game based on the frame rate
	#ifndef PS3
	float gamespeed=60.f/dash_framerate;
	#else
	float gamespeed=1.f;
	#endif
	if(gamespeed<0.2f)gamespeed=0.2f;
	if(gamespeed>2.0f)gamespeed=2.0f;

	//play the game
	if(gamestate==0){
		for(int a=0;a<500;a++)play(2.5f);
		gamestate=1;
	}else if(gamestate==1){
		play(gamespeed);
		drawworld();
	}else if(gamestate==2){
		play(gamespeed);
		drawworld();
	}

}
