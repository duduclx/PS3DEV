void play(float gamespeed){

	//lose momentum
	player.movx-=player.movx*0.15*gamespeed;
	player.movy-=player.movy*0.15*gamespeed;

	//gain momentum and turn based on input
	float movespeed=0;
	float moveangle=0;
	float lookspeed=0;
	float lookangle=0;
	bool attack=0;
	#ifdef WII
		movespeed=expans[0].nunchuk.js.mag;
		if(movespeed>0.1f){
			if(movespeed>1.f)movespeed=1.f;
			moveangle=(expans[0].nunchuk.js.ang)*radiansindegree;
		}else{movespeed=0.f;}
		if(WiiButtonsDown[0] & WPAD_BUTTON_A)attack=1;
	#endif
	#ifdef WIN
		bool up=0,down=0,left=0,right=0;
		if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
		if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
		if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
		if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
		moveangle=atan2((float)right-(float)left,(float)up-(float)down);
		movespeed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
		if(movespeed>1)movespeed=1;
		if(keystate[SDLK_SPACE]==2)attack=1;
	#endif
	#ifdef PS3
	movespeed=dist2d(0,0,(float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))/128.f;
	if(movespeed>0.2f){
		if(movespeed>1.f)movespeed=1.f;
		moveangle=atan2((float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))+90.f*radiansindegree;
	}else{
		movespeed=0;
	}
	lookspeed=dist2d(0,0,(float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128))/128.f;
	if(lookspeed>0.2f){
		if(lookspeed>1.f)lookspeed=1.f;
		lookangle=atan2((float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128))+0.f*radiansindegree;
		lookspeed*=5.75f;
	}else{
		lookspeed=0;
	}
	if(paddata[0].BTN_CROSS && playerattacking==0)attack=1;
	playerattacking=0;
	if(paddata[0].BTN_CROSS)playerattacking=1;
	#endif
	if(player.frame==3){
		movespeed=2.75f;
		if(player.direction==0)moveangle=0*radiansindegree;
		if(player.direction==1)moveangle=315*radiansindegree;
		if(player.direction==2)moveangle=45*radiansindegree;
		if(player.direction==3)moveangle=270*radiansindegree;
		if(player.direction==4)moveangle=90*radiansindegree;
		if(player.direction==5)moveangle=225*radiansindegree;
		if(player.direction==6)moveangle=135*radiansindegree;
		if(player.direction==7)moveangle=180*radiansindegree;
	}
	if(movespeed>0.1f){
		player.movy-=0.0125*cos(moveangle)*movespeed*gamespeed;
		player.movx+=0.0125*sin(moveangle)*movespeed*gamespeed;
	}

	//attack
	if(player.frame==3){
		for(int a=0;a<thingcount;a++)
		if(thinglist[a].type==thingtype_monster1
		|| thinglist[a].type==thingtype_monster2
		|| thinglist[a].type==thingtype_monster3
		|| thinglist[a].type==thingtype_monster4
		|| thinglist[a].type==thingtype_monster5)
		if(thinglist[a].health>0)
		if(dist2d(player.posx,player.posy,thinglist[a].posx,thinglist[a].posy)<1.f){
			thinglist[a].health=0;
			if(thinglist[a].type==thingtype_monster1)playerexp+=1;
			if(thinglist[a].type==thingtype_monster2)playerexp+=2;
			if(thinglist[a].type==thingtype_monster3)playerexp+=5;
			if(thinglist[a].type==thingtype_monster4)playerexp+=25;
			if(thinglist[a].type==thingtype_monster5)playerexp+=100;
		}
	}

	//momentum takes effect, collission detection happens and momentum is corrected
	float oldposx=player.posx;
	float oldposy=player.posy;
	player.posx+=player.movx*gamespeed;
	player.posy+=player.movy*gamespeed;
	bumpintoworld_player(0);
	player.movx=(player.posx-oldposx)/gamespeed;
	player.movy=(player.posy-oldposy)/gamespeed;

	//animate
	if(movespeed>0.1f){
		moveangle*=degreesinradian;
		while(moveangle<0)moveangle+=360;
		while(moveangle>360)moveangle-=360;
		if(moveangle>=360.f-45.f/2 || moveangle<=45.f-45.f/2)player.direction=0;
		if(moveangle>=315.f-45.f/2 && moveangle<=315.f+45.f/2)player.direction=1;
		if(moveangle>=45.f-45.f/2 && moveangle<=45.f+45.f/2)player.direction=2;
		if(moveangle>=270.f-45.f/2 && moveangle<=270.f+45.f/2)player.direction=3;
		if(moveangle>=90.f-45.f/2 && moveangle<=90.f+45.f/2)player.direction=4;
		if(moveangle>=225.f-45.f/2 && moveangle<=225.f+45.f/2)player.direction=5;
		if(moveangle>=135.f-45.f/2 && moveangle<=135.f+45.f/2)player.direction=6;
		if(moveangle>=180.f-45.f/2 && moveangle<=180.f+45.f/2)player.direction=7;
	}
	if(attack && player.frame!=3){
		player.frame=3;
		player.frametime=20;
	}else{
		if(player.frame==3){
			player.frametime-=gamespeed;
		}else{
			player.frametime-=gamespeed*dist2d(0,0,player.movx,player.movy)*15.f;
		}
		if(player.frametime<0){
			player.frame+=1;
			if(player.frame>=3)player.frame=0;
			player.frametime=10;
		}
	}

	//monsters
	for(int a=0;a<thingcount;a++)
	if(thinglist[a].type==thingtype_monster1
	|| thinglist[a].type==thingtype_monster2
	|| thinglist[a].type==thingtype_monster3
	|| thinglist[a].type==thingtype_monster4
	|| thinglist[a].type==thingtype_monster5){
		if((thinglist[a].posx<camx-20 || thinglist[a].posx>camx+20 || thinglist[a].posy<camy-20 || thinglist[a].posy>camy+20)
		&& (thinglist[a].spawnx<camx-20 || thinglist[a].spawnx>camx+20 || thinglist[a].spawny<camy-20 || thinglist[a].spawny>camy+20)){
			thinglist[a].health=100;
			thinglist[a].posx=thinglist[a].spawnx;
			thinglist[a].posy=thinglist[a].spawny;
		}else if(thinglist[a].health>0.f){
			//lose momentum
			thinglist[a].movx-=thinglist[a].movx*0.15*gamespeed;
			thinglist[a].movy-=thinglist[a].movy*0.15*gamespeed;
			//gain momentum and move towards the player
			float angle=atan2(thinglist[a].posy-player.posy,thinglist[a].posx-player.posx)-90*radiansindegree;
			if(thinglist[a].type==thingtype_monster1){
				thinglist[a].movy-=0.0025*cos(angle)*gamespeed;
				thinglist[a].movx+=0.0025*sin(angle)*gamespeed;
			}
			if(thinglist[a].type==thingtype_monster2){
				thinglist[a].movy-=0.0035*cos(angle)*gamespeed;
				thinglist[a].movx+=0.0035*sin(angle)*gamespeed;
			}
			if(thinglist[a].type==thingtype_monster3){
				thinglist[a].movy-=0.0055*cos(angle)*gamespeed;
				thinglist[a].movx+=0.0055*sin(angle)*gamespeed;
			}
			if(thinglist[a].type==thingtype_monster4){
				thinglist[a].movy-=0.0075*cos(angle)*gamespeed;
				thinglist[a].movx+=0.0075*sin(angle)*gamespeed;
			}
			if(thinglist[a].type==thingtype_monster5){
				thinglist[a].movy-=0.0100*cos(angle)*gamespeed;
				thinglist[a].movx+=0.0100*sin(angle)*gamespeed;
			}
			//momentum takes effect, collission detection happens and momentum is corrected
			float oldposx=thinglist[a].posx;
			float oldposy=thinglist[a].posy;
			thinglist[a].posx+=thinglist[a].movx*gamespeed;
			thinglist[a].posy+=thinglist[a].movy*gamespeed;
			//bump into other monsters
			for(int b=0;b<thingcount;b++)
			if(thinglist[b].type==thingtype_monster1
			|| thinglist[b].type==thingtype_monster2
			|| thinglist[b].type==thingtype_monster3
			|| thinglist[b].type==thingtype_monster4
			|| thinglist[b].type==thingtype_monster5)
			if(thinglist[b].health>0)if(a!=b)
			if(thinglist[a].posx<thinglist[b].posx+1.f && thinglist[a].posx>thinglist[b].posx-1.f
			&& thinglist[a].posy<thinglist[b].posy+1.f && thinglist[a].posy>thinglist[b].posy-1.f){
				float distance=dist2d(thinglist[a].posx,thinglist[a].posy*2.f,thinglist[b].posx,thinglist[b].posy*2.f);
				if(distance<monsterradius*2.f){
					angle=atan2(thinglist[a].posy*2.f-thinglist[b].posy*2.f,thinglist[a].posx-thinglist[b].posx);
					distance=(monsterradius*2.f-distance)*0.05f;
					float xmove=distance*cos(angle);
					float ymove=distance*sin(angle);
					thinglist[a].posx+=xmove;
					thinglist[a].posy+=ymove;
					thinglist[b].posx-=xmove;
					thinglist[b].posy-=ymove;
				}
			}
			//bump into the player
			float distance=dist2d(thinglist[a].posx,thinglist[a].posy*2.f,player.posx,player.posy*2.f);
			if(distance<playerradius+monsterradius){
				angle=atan2(thinglist[a].posy*2.f-player.posy*2.f,thinglist[a].posx-player.posx);
				distance=(playerradius+monsterradius-distance)*0.05f;
				float xmove=distance*cos(angle);
				float ymove=distance*sin(angle);
				thinglist[a].posx+=xmove;
				thinglist[a].posy+=ymove;
				player.movx-=cos(angle)*0.25f;
				player.movy-=sin(angle)*0.25f;
				if(thinglist[a].type==thingtype_monster1)player.health-=10;
				if(thinglist[a].type==thingtype_monster2)player.health-=25;
				if(thinglist[a].type==thingtype_monster3)player.health-=50;
				if(thinglist[a].type==thingtype_monster4)player.health-=100;
				if(thinglist[a].type==thingtype_monster5)player.health-=250;
			}
			bumpintoworld_monster(a);
			thinglist[a].movx=(thinglist[a].posx-oldposx)/gamespeed;
			thinglist[a].movy=(thinglist[a].posy-oldposy)/gamespeed;
			//animate
			thinglist[a].frametime-=gamespeed;
			if(thinglist[a].frametime<0){
				thinglist[a].frame+=1;
				if(thinglist[a].frame>=6)thinglist[a].frame=0;
				thinglist[a].frametime=15;
			}
			if(thinglist[a].posy>player.posy){
				if(thinglist[a].frame<3)thinglist[a].frame+=3;
			}else{
				if(thinglist[a].frame>2)thinglist[a].frame-=3;
			}
		}else{
			thinglist[a].frame=6;
		}
	}

	if(player.health<0)player.health=0;
	while(playerexp>=playerexpnextlevel){
		playerexplastlevel=playerexpnextlevel;
		playerexpnextlevel*=2;
		playermaxhealth+=25;
		player.health=playermaxhealth;
		playerlevel+=1;
	}

	//camera
	camx+=(player.posx+cos(lookangle)*lookspeed-camx)*0.075*gamespeed;
	camy+=(player.posy+sin(lookangle)*lookspeed-camy)*0.075*gamespeed;

	if(player.health<=0){
		startnewgame();
		gamestate=0;
	}

}
