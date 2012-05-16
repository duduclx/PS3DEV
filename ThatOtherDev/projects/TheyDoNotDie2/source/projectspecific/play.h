void play(float gamespeed){

	//some usefull variables
	float playermovespeed=0.011f*gamespeed;
	float zombiemovespeed=0.0045f*gamespeed;
	float survivormovespeed=0.0055f*gamespeed;

	bool pause=0;
	bool gameover=0;

	//remove old gun shots
	while(shotcount>0)removeshotfromlist(0);

	//update players
	for(int a=0;a<playercount;a++){
		//get input
		float inputspeed=0;
		float inputangle=0;
		bool shoot_machinegun=0;
		bool shoot_rocketlauncher=0;
		bool shoot_shotgun=0;
		bool run=0;
		#ifdef WIN
		if(a==0){
			bool up=0,down=0,left=0,right=0;
			if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
			if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
			if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
			if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
			inputangle=atan2((float)right-(float)left,(float)up-(float)down)-90.f*radiansindegree;
			inputspeed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
			if(inputspeed>1)inputspeed=1;
			aimx[a]=((float)(cursorx[a])/screenw)*2.f-1.f;
			aimy[a]=((float)(cursory[a])/screenh)*2.f-1.f;
			if(mousestate[SDL_BUTTON_LEFT])shoot_machinegun=1;
			if(mousestate[SDL_BUTTON_RIGHT])shoot_rocketlauncher=1;
			if(keystate[SDLK_LSHIFT])run=1;
			if(keystate[SDLK_SPACE]==2|keystate[SDLK_RETURN]==2)pause=1;
		}
		#endif
		#ifdef PS3
		if(padinfo.status[a]){
			inputspeed=dist2d(0,0,(float)(paddata[a].ANA_L_V-128),(float)(paddata[a].ANA_L_H-128))/128.f;
			if(inputspeed>0.2f){
				if(inputspeed>1.f)inputspeed=1.f;
				inputangle=atan2((float)(paddata[a].ANA_L_V-128),(float)(paddata[a].ANA_L_H-128));
			}else{
				inputspeed=0;
			}
			/*//swingball 2 style aiming
			float rightinputspeed=dist2d(0,0,(float)(paddata[a].ANA_R_V-128),(float)(paddata[a].ANA_R_H-128))/128.f;
			float rightinputangle=0;
			if(rightinputspeed>0.2f){
				if(rightinputspeed>1.f)rightinputspeed=1.f;
				rightinputangle=atan2((float)(paddata[a].ANA_R_V-128),(float)(paddata[a].ANA_R_H-128));
			}else{
				rightinputspeed=0;
			}
			aimx[a]=aimx[a]*0.75f+rightinputspeed*cos(rightinputangle)*0.25f;
			aimy[a]=aimy[a]*0.75f+rightinputspeed*sin(rightinputangle)*0.25f;
			aiminworldx[a]=aiminworldx[a]*0.75f+(personlist[a].posx+aimx[a]*5.75f)*0.25f;
			aiminworldy[a]=aiminworldy[a]*0.75f+(personlist[a].posy+aimy[a]*5.75f)*0.25f;*/
			float rightinputspeed=dist2d(0,0,(float)(paddata[a].ANA_R_V-128),(float)(paddata[a].ANA_R_H-128))/128.f;
			float rightinputangle=0;
			if(rightinputspeed>0.2f){
				if(rightinputspeed>1.f)rightinputspeed=1.f;
				rightinputangle=atan2((float)(paddata[a].ANA_R_V-128),(float)(paddata[a].ANA_R_H-128));
			}else{
				rightinputspeed=0;
			}
			aimx[a]+=cos(rightinputangle)*rightinputspeed*0.03f*gamespeed;
			aimy[a]+=sin(rightinputangle)*rightinputspeed*0.03f*gamespeed*screena;
			if(BTN_R1[a])shoot_machinegun=1;
			if(BTN_L1[a])shoot_rocketlauncher=1;
			if(BTN_L2[a])shoot_shotgun=1;
			if(BTN_L3[a])run=1;
			if(BTN_START[a]==2)pause=1;
		}
		#endif
		#ifdef WII
			inputspeed=expans[a].nunchuk.js.mag;
			if(inputspeed>0.1f){
				if(inputspeed>1.f)inputspeed=1.f;
				inputangle=(expans[a].nunchuk.js.ang-90.f)*radiansindegree;
			}else{
				inputspeed=0.f;
			}
			aimx[a]=((float)(cursorx[a])/screenw)*2.f-1.f;
			aimy[a]=((float)(cursory[a])/screenh)*2.f-1.f;
			if(WiiButtonsHeld[a] & WPAD_BUTTON_A)run=1;
			if(WiiButtonsHeld[a] & WPAD_BUTTON_B)shoot_machinegun=1;
			if(WiiButtonsHeld[a] & WPAD_BUTTON_DOWN)shoot_machinegun=1;
			if(WiiButtonsHeld[a] & WPAD_BUTTON_LEFT)shoot_rocketlauncher=1;
			if(WiiButtonsHeld[a] & WPAD_BUTTON_RIGHT)shoot_shotgun=1;
			if(WiiButtonsHeld[a] & WPAD_BUTTON_PLUS)pause=1;
			if(WiiButtonsHeld[a] & WPAD_BUTTON_MINUS)pause=1;
		#endif
		if(aimx[a]<-1)aimx[a]=-1;
		if(aimx[a]>1)aimx[a]=1;
		if(aimy[a]<-1)aimy[a]=-1;
		if(aimy[a]>1)aimy[a]=1;
		aiminworldx[a]=camx+aimx[a]*camz*0.5f*screena;
		aiminworldy[a]=camy+aimy[a]*camz*0.5f;
		if(run){
			if(inputspeed>0.75f){
				inputspeed=1.5f;
				energy[a]-=0.5f*gamespeed;
				energyregenwait[a]=30;
			}else{
				run=0;
			}
		}
		//movement takes effect
		personlist[a].movx+=cos(inputangle)*inputspeed*playermovespeed;
		personlist[a].movy+=sin(inputangle)*inputspeed*playermovespeed;
		personlist[a].angle=atan2(aiminworldy[a]-personlist[a].posy,aiminworldx[a]-personlist[a].posx);
		//attack
		shootwait[a]-=gamespeed;
		if(shoot_machinegun && shootwait[a]<0){
			makeshot(
				personlist[a].angle+((float)(rand()%201)*0.001f-0.1f),
				personlist[a].posx,
				personlist[a].posy,
				0.1f,
				8.f+(float)(rand()%100)*0.01f,
				20.f,
				a);
			shootwait[a]=4;
			energyregenwait[a]=30;
		}
		if(shoot_rocketlauncher && shootwait[a]<0){
			makerocket(a,
				personlist[a].posx+cos(personlist[a].angle)*0.25f,
				personlist[a].posy+sin(personlist[a].angle)*0.25f,
				cos(personlist[a].angle)*0.11f,
				sin(personlist[a].angle)*0.11f,
				personlist[a].angle);
			shootwait[a]=20;
			energyregenwait[a]=30;
		}
		if(shoot_shotgun && shootwait[a]<0){
			for(int b=0;b<8;b++)makeshot(
				personlist[a].angle
					+4.f*radiansindegree*(float)b
					-4.f*radiansindegree*4.f
					+(float)((float)(rand()%201)*0.001f-0.1f),
				personlist[a].posx,
				personlist[a].posy,
				0.1f,
				2.f+(float)(rand()%100)*0.01f,
				50.f,
				a);
			shootwait[a]=20;
			energyregenwait[a]=30;
		}
		camx+=(personlist[a].posx*0.75f+aiminworldx[a]*0.25f-camx)*0.1f*gamespeed;
		camy+=(personlist[a].posy*0.75f+aiminworldy[a]*0.25f-camy)*0.1f*gamespeed;
		camz+=(personlist[a].health*0.01f*5.5f+2.f-camz)*0.1f*gamespeed;
		//player energy
		if(energy[a]<0.f){
			personlist[a].health+=energy[a]*0.5f;
			healwait[a]=60.f;
			energy[a]=0.f;
		}
		energyregenwait[a]-=gamespeed;
		if(energyregenwait[a]<0){
			energy[a]+=0.15f*gamespeed;
			if(energy[a]>100.f)energy[a]=100.f;
		}
		//player health
		if(personlist[a].health<=0.f){
			personlist[a].health=0.f;
			gameover=1;
		}
		healwait[a]-=gamespeed;
		if(healwait[a]<0){
			personlist[a].health+=0.15f*energy[a]*0.01f*gamespeed;
			if(personlist[a].health>100.f)personlist[a].health=100.f;
		}
	}

	//update rockets
	for(int a=0;a<rocketcount;a++){
		if(rocketlist[a].posx>camx+14.f || rocketlist[a].posx<camx-14.f
		|| rocketlist[a].posy>camy+14.f || rocketlist[a].posy<camy-14.f){
			removerocketfromlist(a);
			a--;
		}else if(rocketlist[a].health<=0.f){
			digintowalls(
				rocketlist[a].posx-0.6f,
				rocketlist[a].posy-0.6f,
				1.2f,1.2f);
			makeexplosion(
				rocketlist[a].posx,
				rocketlist[a].posy,
				rocketlist[a].angle);
			removerocketfromlist(a);
			a--;
		}else{
			rocketlist[a].posx+=rocketlist[a].movx*gamespeed;
			rocketlist[a].posy+=rocketlist[a].movy*gamespeed;
			if(touchworld(rocketlist[a].posx,rocketlist[a].posy,0.115f,0))
				rocketlist[a].health=0.f;
			for(int b=0;b<personcount;b++)
			if(rocketlist[a].shotby!=b)
			if(rocketlist[a].posx<personlist[b].posx+0.46f
			&& rocketlist[a].posx>personlist[b].posx-0.46f
			&& rocketlist[a].posy<personlist[b].posy+0.46f
			&& rocketlist[a].posy>personlist[b].posy-0.46f){
				float distance=dist2d(
					rocketlist[a].posx,rocketlist[a].posy,
					personlist[b].posx,personlist[b].posy);
				if(distance<0.46f)
					rocketlist[a].health=0.f;
			}
		}
	}

	//update explosions 
	for(int a=0;a<explosioncount;a++){
		for(int b=0;b<personcount;b++)
		if(explosionlist[a].posx<personlist[b].posx+1.5f
		&& explosionlist[a].posx>personlist[b].posx-1.5f
		&& explosionlist[a].posy<personlist[b].posy+1.5f
		&& explosionlist[a].posy>personlist[b].posy-1.5f){
			float distance=dist2d(
				explosionlist[a].posx,explosionlist[a].posy,
				personlist[b].posx,personlist[b].posy);
			if(distance<1.5f){
				distance=1.5f-distance;
				if(personlist[b].type==persontype_player){
					distance*=0.1f;
					healwait[b]=60.f;
				}
				if(personlist[b].type==persontype_zombie){
					personlist[b].havetarget=1;
					personlist[b].targetnum=0;
					personlist[b].updateturn=-1;
				}
				float angle=atan2(
					explosionlist[a].posy-personlist[b].posy,
					explosionlist[a].posx-personlist[b].posx);
				//if(personlist[b].type!=persontype_player){
					personlist[b].health-=distance*25.f*gamespeed;
					if(personlist[b].bleedwait<0.f){
						makedecal(
							decaltype_blood,
							personlist[b].posx,
							personlist[b].posy,
							angle+((float)(rand()%200)*0.1f-10.f)*radiansindegree);
						personlist[b].bleedwait=10.f;
					}
				//}
				distance*=0.045f*gamespeed;
				personlist[b].movx-=cos(angle)*distance;
				personlist[b].movy-=sin(angle)*distance;
			}
		}
		explosionlist[a].health-=15.f*gamespeed;
		if(explosionlist[a].health<=0.f){
			removeexplosionfromlist(a);
			a--;
		}
	}

	//spawn zombies
	if(persontypecount[persontype_zombie]<400 && (persontypecount[persontype_zombie]+persontypecount[persontype_survivor])<500){
		float angle=randangle();
		float distance=8.f+(float)(rand()%30)*0.1f;
		float x=camx+cos(angle)*distance;
		float y=camy+sin(angle)*distance;
		if(touchworld(x,y,0.23f,1)==0)
			makeperson(persontype_zombie,x,y,0.f,0.f,randangle());
	}

	//spawn survivors
	if(persontypecount[persontype_survivor]<100 && (persontypecount[persontype_zombie]+persontypecount[persontype_survivor])<500){
		float angle=randangle();
		float distance=8.f+(float)(rand()%30)*0.1f;
		float x=camx+cos(angle)*distance;
		float y=camy+sin(angle)*distance;
		if(touchworld(x,y,0.23f,1)==0)
			makeperson(persontype_survivor,x,y,0.f,0.f,randangle());
	}

	//persons take turns being updated
	updateturn+=1;
	if(updateturn>=10)updateturn=0;

	//update persons
	for(int a=0;a<personcount;a++){
		//keep track of some info
		bool removed=0;
		float oldposx=personlist[a].posx;
		float oldposy=personlist[a].posy;
		//update the players
		if(personlist[a].type==persontype_player){
		//update the zombies
		}else if(personlist[a].type==persontype_zombie){
			if(personlist[a].updateturn==updateturn || personlist[a].havetarget==0){
				personlist[a].havetarget=0;
				float distance=findnearesttarget(a,persontype_player,20.f);
				findnearesttarget(a,persontype_survivor,distance);
			}
			if(personlist[a].havetarget){
				personlist[a].angle=atan2(
					personlist[personlist[a].targetnum].posy-personlist[a].posy,
					personlist[personlist[a].targetnum].posx-personlist[a].posx);
				personlist[a].movx+=cos(personlist[a].angle)*zombiemovespeed;
				personlist[a].movy+=sin(personlist[a].angle)*zombiemovespeed;
			}
			if(personlist[a].posx>camx+14.f || personlist[a].posx<camx-14.f
			|| personlist[a].posy>camy+14.f || personlist[a].posy<camy-14.f){
				removed=1;
				removepersonfromlist(a);
			}
		//update the survivors
		}else if(personlist[a].type==persontype_survivor){
			if(personlist[a].updateturn==updateturn || personlist[a].havetarget==0){
				personlist[a].havetarget=0;
				findnearesttarget(a,persontype_zombie,2.5f);
			}
			if(personlist[a].havetarget){
				personlist[a].angle=atan2(
					personlist[a].posy-personlist[personlist[a].targetnum].posy,
					personlist[a].posx-personlist[personlist[a].targetnum].posx);
				personlist[a].movx+=cos(personlist[a].angle)*survivormovespeed;
				personlist[a].movy+=sin(personlist[a].angle)*survivormovespeed;
			}
			if(personlist[a].posx>camx+14.f || personlist[a].posx<camx-14.f
			|| personlist[a].posy>camy+14.f || personlist[a].posy<camy-14.f){
				removed=1;
				removepersonfromlist(a);
			}
		//we have run out of types to update
		}
		//the dead get removed
		if(!removed)if(personlist[a].health<=0){
			if(personlist[a].type==persontype_player){
			}else if(personlist[a].type==persontype_zombie){
				makedecal(
					decaltype_corpse,
					personlist[a].posx,
					personlist[a].posy,
					personlist[a].angle);
				zombieskilled+=1;
				removed=1;
				removepersonfromlist(a);
			}else if(personlist[a].type==persontype_survivor){
				personlist[a].health=100.f;
				personlist[a].type=persontype_zombie;
				persontypecount[persontype_survivor]-=1;
				persontypecount[persontype_zombie]+=1;
			}else{
				removed=1;
				removepersonfromlist(a);
			}
		}
		//we dont do any of the final updating if they were removed
		if(removed){
			a-=1;
		}else{
			//everyone bumps into everyone else
			for(int b=0;b<personcount;b++)if(a!=b)
			if(personlist[a].posx<personlist[b].posx+0.46f && personlist[a].posx>personlist[b].posx-0.46f
			&& personlist[a].posy<personlist[b].posy+0.46f && personlist[a].posy>personlist[b].posy-0.46f){
				float distance=dist2d(
					personlist[a].posx,personlist[a].posy,
					personlist[b].posx,personlist[b].posy);
				if(distance<0.46f){
					if(personlist[a].type==persontype_zombie
					&& personlist[b].type!=persontype_zombie){
						personlist[b].health-=0.5f*gamespeed;
						if(personlist[b].type==persontype_player)
							healwait[b]=60.f;
						if(personlist[b].bleedwait<0.f){
							makedecal(
								decaltype_blood,
								personlist[b].posx,
								personlist[b].posy,
								randangle());
							personlist[b].bleedwait=10.f;
						}
					}
					distance=(0.46f-distance)*0.015f*gamespeed;
					/*float angle=atan2(
						personlist[a].posy-personlist[b].posy,
						personlist[a].posx-personlist[b].posx);
					personlist[a].movx+=cos(angle)*distance;
					personlist[a].movy+=sin(angle)*distance;
					personlist[b].movx-=cos(angle)*distance;
					personlist[b].movy-=sin(angle)*distance;*/
					float xspeed=personlist[a].posx-personlist[b].posx;
					float yspeed=personlist[a].posy-personlist[b].posy;
					float total=posfloat(xspeed)+posfloat(yspeed);
					if(total!=0.f){
						xspeed=xspeed/total*distance;
						yspeed=yspeed/total*distance;
						personlist[a].movx+=xspeed;
						personlist[a].movy+=yspeed;
						personlist[b].movx-=xspeed;
						personlist[b].movy-=yspeed;
					}
				}
			}
			//count down to bleed some more
			personlist[a].bleedwait-=gamespeed;
			//everyone is moved by momentum
			personlist[a].posx+=personlist[a].movx*gamespeed;
			personlist[a].posy+=personlist[a].movy*gamespeed;
			//everyone bumps into the world
			bumpintoworld(&personlist[a].posx,&personlist[a].posy,0.23f,1);
			//adjust momentum
			personlist[a].movx=(personlist[a].posx-oldposx)/gamespeed;
			personlist[a].movy=(personlist[a].posy-oldposy)/gamespeed;
			personlist[a].movx-=personlist[a].movx*0.2f*gamespeed;
			personlist[a].movy-=personlist[a].movy*0.2f*gamespeed;
		}
	}

	//go back to the menu
	if(pause==1)gamestate=gamestate_pausemenu;
	if(gameover==1){
		if(zombieskilled>mostzombieskilled){
			mostzombieskilled=zombieskilled;
			savestats();
		}
		gamestate=gamestate_mainmenu;
	}

	//feed data to clients
	//if(gamestate==

}
