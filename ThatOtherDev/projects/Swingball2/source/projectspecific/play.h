void play(float gamespeed){

	//the clock ticks down
	score-=gamespeed/60.f*10.f;
	if(score<0.f)score=0.f;

	//keep track of the starting position
	float oldposx=player.posx;
	float oldposy=player.posy;
	//get input
	float inputspeed=0;
	float inputangle=0;
	bool jump=0;
	bool swing=0;
	#ifdef WIN
		bool up=0,down=0,left=0,right=0;
		if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
		if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
		if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
		if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
		if(keystate[SDLK_SPACE])jump=1;
		inputangle=atan2((float)right-(float)left,(float)up-(float)down)-90.f*radiansindegree;
		inputspeed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
		if(inputspeed>1)inputspeed=1;
		aimx=((float)(cursorx[0])/screenw)*2.f-1.f;
		aimy=((float)(cursory[0])/screenh)*2.f-1.f;
		if(aimx<-1)aimx=-1;if(aimx>1)aimx=1;
		if(aimy<-1)aimy=-1;if(aimy>1)aimy=1;
		aiminworldx=camx+aimx*camz*0.5f*screena;
		aiminworldy=camy+aimy*camz*0.5f;
		if(mousestate[SDL_BUTTON_LEFT])swing=1;
	#endif
	#ifdef PS3
		inputspeed=dist2d(0,0,(float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))/128.f;
		if(inputspeed>0.2f){
			if(inputspeed>1.f)inputspeed=1.f;
			inputangle=atan2((float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128));
		}else{
			inputspeed=0;
		}
		float rightinputspeed=dist2d(0,0,(float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128))/128.f;
		float rightinputangle=0;
		if(rightinputspeed>0.2f){
			if(rightinputspeed>1.f)rightinputspeed=1.f;
			rightinputangle=atan2((float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128));
		}else{
			rightinputspeed=0;
		}
		aimx=aimx*0.75f+rightinputspeed*cos(rightinputangle)*0.25f;
		aimy=aimy*0.75f+rightinputspeed*sin(rightinputangle)*0.25f;
		aiminworldx=aiminworldx*0.75f+(player.posx+aimx*5.75f)*0.25f;
		aiminworldy=aiminworldy*0.75f+(player.posy+aimy*5.75f)*0.25f;
		if(BTN_L1[0])jump=1;
		if(BTN_R1[0])swing=1;
	#endif
	#ifdef WII
		inputspeed=expans[0].nunchuk.js.mag;
		if(inputspeed>0.1f){
			if(inputspeed>1.f)inputspeed=1.f;
			inputangle=(expans[0].nunchuk.js.ang-90.f)*radiansindegree;
		}else{
			inputspeed=0.f;
		}
		aimx=((float)(cursorx[0])/screenw)*2.f-1.f;
		aimy=((float)(cursory[0])/screenh)*2.f-1.f;
		if(aimx<-1)aimx=-1;if(aimx>1)aimx=1;
		if(aimy<-1)aimy=-1;if(aimy>1)aimy=1;
		aiminworldx=camx+aimx*camz*0.5f*screena;
		aiminworldy=camy+aimy*camz*0.5f;
		if(WiiButtonsHeld[0] & WPAD_BUTTON_A)jump=1;
		if(WiiButtonsHeld[0] & WPAD_BUTTON_B)swing=1;
	#endif
	//get gravity direction
	if(map[(int)floor(player.posx)][(int)floor(player.posy)]==maptype_gravitydown)
		gravitydirection=0;
	if(map[(int)floor(player.posx)][(int)floor(player.posy)]==maptype_gravityleft)
		gravitydirection=1;
	if(map[(int)floor(player.posx)][(int)floor(player.posy)]==maptype_gravityup)
		gravitydirection=2;
	if(map[(int)floor(player.posx)][(int)floor(player.posy)]==maptype_gravityright)
		gravitydirection=3;
	//gravity
	if(player.swinging==0){
		if(gravitydirection==0)player.movy+=0.02*gamespeed;
		if(gravitydirection==1)player.movx-=0.02*gamespeed;
		if(gravitydirection==2)player.movy-=0.02*gamespeed;
		if(gravitydirection==3)player.movx+=0.02*gamespeed;
	}else{
		if(gravitydirection==0)player.movy+=0.018*gamespeed;
		if(gravitydirection==1)player.movx-=0.018*gamespeed;
		if(gravitydirection==2)player.movy-=0.018*gamespeed;
		if(gravitydirection==3)player.movx+=0.018*gamespeed;
	}
	//move
	if(gravitydirection==0 || gravitydirection==2){
		player.movx+=cos(inputangle)*inputspeed*0.013f*gamespeed;
		if(player.swinging)player.movy+=sin(inputangle)*inputspeed*0.013f*gamespeed;
	}
	if(gravitydirection==1 || gravitydirection==3){
		if(player.swinging)player.movx+=cos(inputangle)*inputspeed*0.013f*gamespeed;
		player.movy+=sin(inputangle)*inputspeed*0.013f*gamespeed;
	}
	//swing
	bool updateswing=0;
	if(swing){
		if(player.swinging==0){
			swingaimangle=atan2(aiminworldy-player.posy,aiminworldx-player.posx);
		}else{
			swingaimangle=atan2(player.swingendy-player.posy,player.swingendx-player.posx);
		}
		updateswing=1;
	}else{
		player.swinging=0;
	}
	if(updateswing){
		float posx=player.posx;
		float posy=player.posy;
		player.swinging=0;
		float oldswingendx=player.swingendx;
		float oldswingendy=player.swingendy;
		for(int a=0;a<1000;a++){
			posx+=0.05f*cos(swingaimangle);
			posy+=0.05f*sin(swingaimangle);
			player.swingendx=posx;
			player.swingendy=posy;
			int x=(int)floor(posx);
			int y=(int)floor(posy);
			if(map[x][y]==maptype_blocknormal
			|| map[x][y]==maptype_blockharmful
			|| map[x][y]==maptype_blockghost){
				a=1000;
				player.swinging=1;
			}
			if(map[x][y]==maptype_blocknoswing){
				a=1000;
				player.swinging=0;
			}
		}
		if(player.swinging){
			if(dist2d(oldswingendx,oldswingendy,player.swingendx,player.swingendy)>0.5f){
				player.swinglength=dist2d(player.posx,player.posy,player.swingendx,player.swingendy);
			}else{
				player.swingendx=oldswingendx;
				player.swingendy=oldswingendy;
			}
		}
	}
	if(player.swinging==0){
		player.swinglength=0.f;
		player.swingendx=-10.f;
		player.swingendy=-10.f;
	}
	//jump
	if(jump){
		if(gravitydirection==0){
			if(player.grounded){
				player.movy=0.f-0.425f;
			}else if(player.swinging==0){
				if(player.movy<0.f)player.movy+=player.movy*0.105f*gamespeed;
			}
		}
		if(gravitydirection==1){
			if(player.grounded){
				player.movx=0.f+0.425f;
			}else if(player.swinging==0){
				if(player.movx>0.f)player.movx+=player.movx*0.105f*gamespeed;
			}
		}
		if(gravitydirection==2){
			if(player.grounded){
				player.movy=0.f+0.425f;
			}else if(player.swinging==0){
				if(player.movy>0.f)player.movy+=player.movy*0.105f*gamespeed;
			}
		}
		if(gravitydirection==3){
			if(player.grounded){
				player.movx=-0.425f;
			}else if(player.swinging==0){
				if(player.movx<0.f)player.movx+=player.movx*0.105f*gamespeed;
			}
		}
	}
	//apply motion
	player.posx+=player.movx*gamespeed;
	player.posy+=player.movy*gamespeed;
	//bump into the world
	bumpintoworld(&player.posx,&player.posy,0.6f);
	//check if grounded
	if(gravitydirection==0){
	if(player.posy<(float)(oldposy+player.movy*gamespeed)){
		player.grounded=1;}else{player.grounded=0;}}
	if(gravitydirection==3){
	if(player.posx>(float)(oldposx+player.movx*gamespeed)){
		player.grounded=1;}else{player.grounded=0;}}
	if(gravitydirection==2){
	if(player.posy>(float)(oldposy+player.movy*gamespeed)){
		player.grounded=1;}else{player.grounded=0;}}
	if(gravitydirection==3){
	if(player.posx<(float)(oldposx+player.movx*gamespeed)){
		player.grounded=1;}else{player.grounded=0;}}
	//correct distance from swing point
	if(player.swinging){
		float angle=atan2(player.swingendy-player.posy,player.swingendx-player.posx);
		player.posx=player.swingendx-cos(angle)*player.swinglength;
		player.posy=player.swingendy-sin(angle)*player.swinglength;
	}
	//bump into the world
	bumpintoworld(&player.posx,&player.posy,0.6f);
	//correct motion
	player.movx=(player.posx-oldposx)/gamespeed;
	player.movy=(player.posy-oldposy)/gamespeed;
	if(player.swinging){
		player.movx-=player.movx*0.012f*gamespeed;
		player.movy-=player.movy*0.012f*gamespeed;
	}else{
		player.movx-=player.movx*0.1f*gamespeed;
		player.movy-=player.movy*0.1f*gamespeed;
	}

	//update camera
	camx+=((player.posx*0.8f+aiminworldx*0.2f)-camx)*0.075f*gamespeed;
	camy+=((player.posy*0.8f+aiminworldy*0.2f)-camy)*0.075f*gamespeed;
	camz=12.5f;

	//collect extra time
	for(int a=0;a<ballcount;a++)if(balllist[a].type==balltype_extratime){
		if(dist2d(player.posx,player.posy,balllist[a].posx,balllist[a].posy)<1.f){
			for(int b=0;b<20;b++){
				makeball(balltype_glow,balllist[a].posx,balllist[a].posy);
				balllist[ballcount-1].swinglength=1.5f;
				balllist[ballcount-1].movx=(float)(rand()%200-100)*0.001f;
				balllist[ballcount-1].movy=(float)(rand()%200-100)*0.001f;
			}
			removeballfromlist(a);
			a-=1;
			score+=50.f;
		}
	}

	//update glow
	for(int a=0;a<ballcount;a++)if(balllist[a].type==balltype_glow){
		balllist[a].swinglength-=gamespeed*0.025f;
		balllist[a].posx+=balllist[a].movx*gamespeed;
		balllist[a].posy+=balllist[a].movy*gamespeed;
		if(balllist[a].swinglength<=0.f){
			removeballfromlist(a);
			a-=1;
		}
	}

	//spawn some glow
	glowspawnwait-=gamespeed;
	if(glowspawnwait<=0.f){
		for(int a=0;a<1;a++){
			makeball(balltype_glow,player.posx,player.posy);
			balllist[ballcount-1].swinglength=1.5f;
			balllist[ballcount-1].movx=(float)(rand()%200-100)*0.0001f;
			balllist[ballcount-1].movy=(float)(rand()%200-100)*0.0001f;
		}
		glowspawnwait+=1.f;
	}

	//game over
	if(touchtheharmfulblocks(player.posx,player.posy,0.6f)){
		gamestate=gamestate_titlescreen;
	}
	if(score==0.f){
		gamestate=gamestate_titlescreen;
	}
	for(int a=0;a<ballcount;a++)if(balllist[a].type==balltype_finish){
		if(dist2d(player.posx,player.posy,balllist[a].posx,balllist[a].posy)<2.f){
			gamestate=gamestate_titlescreen;
			if((int)ceil(score)>maphighscore[currentlevelnumber-1]){
				savescore(currentlevelnumber,(int)ceil(score));
				maphighscore[currentlevelnumber-1]=(int)ceil(score);
			}
		}
	}

}
