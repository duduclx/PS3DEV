void menu(){

	//get input
	bool left=0,right=0,justplay=0,watchmazegen=0;
	#ifdef WIN
		if(keystate[SDLK_a]==2|keystate[SDLK_LEFT]==2)left=1;
		if(keystate[SDLK_d]==2|keystate[SDLK_RIGHT]==2)right=1;
		if(keystate[SDLK_q]==2)justplay=1;
		if(keystate[SDLK_e]==2)watchmazegen=1;
	#endif
	#ifdef PS3
		if(BTN_LEFT[0]==2)left=1;
		if(BTN_RIGHT[0]==2)right=1;
		if(BTN_CROSS[0]==2)justplay=1;
		if(BTN_CIRCLE[0]==2)watchmazegen=1;
	#endif

	if(left)menustate-=1;
	if(right)menustate+=1;
	if(menustate<0)menustate=0;
	if(menustate>2)menustate=2;

	if(menustate==0){
		mazesizex=25;
		mazesizey=15;
	}
	if(menustate==1){
		mazesizex=55;
		mazesizey=35;
	}
	if(menustate==2){
		mazesizex=135;
		mazesizey=85;
	}

	if(justplay){
		genmaze();
		gamestate=gamestate_play;
	}else if(watchmazegen){
		genmaze_start();
		gamestate=gamestate_play;
	}

}
