void play(float gamespeed){

	//get input
	float inputspeed=0.f;
	float inputangle=0.f;
	bool jump=0;
	#ifdef WIN
	bool up=0,down=0,left=0,right=0;
	if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
	if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
	if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
	if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
	inputangle=atan2((float)right-(float)left,(float)up-(float)down)-90.f*radiansindegree;
	inputspeed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
	if(inputspeed>1.f)inputspeed=1.f;
	if(keystate[SDLK_SPACE])jump=1;
	#endif
	#ifdef PS3
	inputspeed=dist2d(0,0,(float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))/128.f;
	if(inputspeed>0.2f){
		if(inputspeed>1.f)inputspeed=1.f;
		inputangle=atan2((float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128));
	}else{
		inputspeed=0.f;
	}
	if(BTN_CROSS[0])jump=1;
	#endif
	#ifdef WII
	inputspeed=expans[0].nunchuk.js.mag;
	if(inputspeed>0.1f){
		if(inputspeed>1.f)inputspeed=1.f;
		inputangle=(expans[0].nunchuk.js.ang)*radiansindegree-90.f*radiansindegree;
	}else{inputspeed=0.f;}
	#endif
	
	//update the player
	if(1){
		//keep track of the old position
		float oldx=playerposx;
		float oldy=playerposy;
		//get input
		playermovx+=cos(inputangle)*inputspeed*0.0125f*gamespeed;
		if(playergrounded==1 && jump==1)playermovy=0.5f;
		//motion takes effect
		playerposx+=playermovx*gamespeed;
		playerposy+=playermovy*gamespeed;
		//bump into world
		playerposy+=1.f;
		bumpintoworld(&playerposx,&playerposy,0.45f);
		playerposy-=1.f;
		bumpintoworld(&playerposx,&playerposy,0.45f);
		//check if grounded
		if(playerposy>(float)(oldy+(float)(playermovy*gamespeed))+0.001f){
			playergrounded=1;}else{playergrounded=0;}
		//adjust movement speed
		playermovx=(playerposx-oldx)/gamespeed*(1.f-0.125f*gamespeed);
		playermovy=(playerposy-oldy)/gamespeed*(1.f-0.1f*gamespeed)-0.0125f*gamespeed;
		float idealplayerangy=atan2(0,playermovx);
		playerangy+=(idealplayerangy-playerangy)*0.1f*gamespeed;
	}

	//position camera
	camposx+=(playerposx-camposx)*0.05f*gamespeed;
	camposy+=(playerposy+1.5f-camposy)*0.025f*gamespeed;
	camposz=15.f;
	camangy+=(-atan2(camposx-playerposx,camposz-0.f)*1.75f-camangy)*0.05f*gamespeed;

	//animate the player
	playeranimation+=playermovx*1.75f*gamespeed;
	while(playeranimation<0.f)playeranimation+=4.f;
	while(playeranimation>=4.f)playeranimation-=4.f;
	int frame1=(int)floor(playeranimation);
	int frame2=frame1+1;
	float progress=playeranimation-(float)frame1;
	for(int a=0;a<mariovertexcount*3;a++){
		mariovertexarray[a]=
			playervertexmeshframe[frame1][a]*(1.f-progress)+
			playervertexmeshframe[frame2][a]*(progress);
	}

	//update enemies
	bool gameover=0;
	for(int a=0;a<entitycount;a++){
		if(entitylist[a].type==entitytype_enemy){
			//keep track of the old position
			float oldx=entitylist[a].posx;
			float oldy=entitylist[a].posy;
			//get input
			if(entitylist[a].direction==0)entitylist[a].movx-=0.005f*gamespeed;
			if(entitylist[a].direction==1)entitylist[a].movx+=0.005f*gamespeed;
			//motion takes effect
			entitylist[a].posx+=entitylist[a].movx*gamespeed;
			entitylist[a].posy+=entitylist[a].movy*gamespeed;
			//bump into world
			bumpintoworld(&entitylist[a].posx,&entitylist[a].posy,0.45f);
			//check if grounded
			if(entitylist[a].posy>(float)(oldy+(float)(entitylist[a].movy*gamespeed))+0.001f){
				entitylist[a].grounded=1;}else{entitylist[a].grounded=0;}
			//check if bumping into a wall
			if(entitylist[a].posx>(float)(oldx+(float)(entitylist[a].movx*gamespeed))+0.001f)
				entitylist[a].direction=1;
			if(entitylist[a].posx<(float)(oldx+(float)(entitylist[a].movx*gamespeed))-0.001f)
				entitylist[a].direction=0;
			//adjust movement speed
			entitylist[a].movx=(entitylist[a].posx-oldx)/gamespeed*(1.f-0.125f*gamespeed);
			entitylist[a].movy=(entitylist[a].posy-oldy)/gamespeed*(1.f-0.1f*gamespeed)-0.0125f*gamespeed;
			//bump into player
			if(dist2d(entitylist[a].posx,0.f,playerposx,0.4)<=0.9f
			&& entitylist[a].posy>=playerposy-0.45f
			&& entitylist[a].posy<=playerposy+0.45f){
				if(entitylist[a].posy>=playerposy-0.05f){
					gameover=1;
				}else{
					if(playergrounded==0 && entitylist[a].posy<playerposy && playermovy<=0.f){
						removeentityfromlist(a);
						a-=1;
						playermovy=0.35f;
					}
				}
			}
		}
	}
	if(playerposx>worldsizex-10)gameover=1;
	if(gameover==1){
		while(entitycount>0)removeentityfromlist(0);
		loadlevel(1);
	}

}
