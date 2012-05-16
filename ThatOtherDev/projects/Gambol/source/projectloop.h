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
	play(gamespeed);
	drawworld();

}
