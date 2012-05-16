void play(float gamespeed){

	//get input
	float inputspeed=0;
	float inputangle=0;
	#ifdef WIN
		bool up=0,down=0,left=0,right=0;
		if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
		if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
		if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
		if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
		inputangle=atan2((float)right-(float)left,(float)up-(float)down)-90.f*radiansindegree;
		inputspeed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
		if(inputspeed>1.f)inputspeed=1.f;
	#endif
	#ifdef PS3
		inputspeed=dist2d(0,0,(float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))/128.f;
		if(inputspeed>0.2f){
			if(inputspeed>1.f)inputspeed=1.f;
			inputangle=atan2((float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128));
		}else{
			inputspeed=0;
		}
	#endif

	if(mazecomplete==0){
		for(int a=0;a<2;a++)genmaze_work();
		if(mazecomplete==1)genmaze_finish();
	}else{
		playerposx+=cos(inputangle)*inputspeed*0.15f*gamespeed;
		playerposy+=sin(inputangle)*inputspeed*0.15f*gamespeed;
		bumpintoworld(&playerposx,&playerposy,0.5f);
		if(playerposx>=(float)(mazesizex-2)
		&& playerposy>=(float)(mazesizey-2)){
			solvecount+=1;
			FILE * pFile = NULL;
			#ifdef WIN
			pFile = fopen ("solvecount.dat" , "w");
			#endif
			#ifdef PS3
			pFile = fopen ("/dev_hdd0/game/MAZEGENRT/USRDIR/solvecount.dat" , "w");
			#endif
			#ifdef WII
			pFile = fopen ("solvecount.dat" , "w");
			#endif
			if(pFile != NULL){
				char temptext[100];
				sprintf(temptext,"%i%c",solvecount,'\n');
				fputs(temptext,pFile);
				fclose (pFile);
			}
			gamestate=gamestate_menu;
		}
	}

}
