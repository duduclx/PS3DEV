void play(float gamespeed){

	//everyone bumps into everyone
	for(int a=0;a<playercount;a++)for(int b=0;b<playercount;b++)if(a!=b){
		if(player[a].posy<player[b].posy+0.25f
		&& player[a].posy>player[b].posy-0.25f){
			float distance=player[a].posx-player[b].posx;
			if(distance<0.4f && distance>-0.4f){
				if(distance>0.f){
					distance=0.4f-distance;
				}else{
					distance=-0.4f-distance;
				}
				player[a].movx+=distance*0.02f*gamespeed;
				player[b].movx-=distance*0.02f*gamespeed;
			}
		}
	}

	for(int playernum=0;playernum<playercount;playernum++){

		//get controller input
		bool left=0,right=0,jump=0,crouch=0,punch=0,kick=0;
		#ifdef WII
		#endif
		#ifdef WIN
		if(playernum==0){
			if(keystate[SDLK_a])left=1;
			if(keystate[SDLK_d])right=1;
			if(keystate[SDLK_w]==2)jump=1;
			if(keystate[SDLK_s])crouch=1;
			if(keystate[SDLK_q]==2)punch=1;
			if(keystate[SDLK_e]==2)kick=1;
		}
		if(playernum==1){
			if(keystate[SDLK_j])left=1;
			if(keystate[SDLK_l])right=1;
			if(keystate[SDLK_i]==2)jump=1;
			if(keystate[SDLK_k])crouch=1;
			if(keystate[SDLK_u]==2)punch=1;
			if(keystate[SDLK_o]==2)kick=1;
		}
		#endif
		#ifdef PS3
		if(BTN_LEFT[playernum])left=1;
		if(BTN_RIGHT[playernum])right=1;
		if(BTN_CROSS[playernum]==2)jump=1;
		if(BTN_DOWN[playernum])crouch=1;
		if(BTN_SQUARE[playernum]==2)punch=1;
		if(BTN_CIRCLE[playernum]==2)kick=1;
		#endif

		//ignore controller input when it isn't appropriate
		if(player[playernum].animation==playeranimation_hurt){
			left=0;
			right=0;
			punch=0;
			kick=0;
			jump=0;
			crouch=0;
		}
		if(player[playernum].grounded==0){
			left=0;
			right=0;
			jump=0;
			crouch=0;
		}
		if(player[playernum].animation==playeranimation_crouching){
			left=0;
			right=0;
		}
		if(player[playernum].animation==playeranimation_punching
		|| player[playernum].animation==playeranimation_kicking){
			left=0;
			right=0;
			punch=0;
			kick=0;
		}

		//change the direction that the player is facing
		if(right==1 && left==0)player[playernum].direction=0;
		if(right==0 && left==1)player[playernum].direction=1;

		//initiate animations and progress them
		if(player[playernum].animation!=playeranimation_hurt){
			if(player[playernum].animation==playeranimation_none
			|| player[playernum].animation==playeranimation_crouching
			|| player[playernum].animation==playeranimation_walking){
				if(player[playernum].grounded && crouch){
					player[playernum].animation=playeranimation_crouching;
					player[playernum].animationtime=0;
				}
				if(left || right){
					player[playernum].animation=playeranimation_walking;
					if(player[playernum].animation!=playeranimation_walking)player[playernum].animationtime=0;
				}
				if(punch){
					player[playernum].animation=playeranimation_punching;
					player[playernum].animationtime=0;
				}
				if(kick){
					player[playernum].animation=playeranimation_kicking;
					player[playernum].animationtime=0;
				}
			}
			if(player[playernum].animation==playeranimation_crouching && player[playernum].animationtime>0.f){
				player[playernum].animation=playeranimation_none;
				player[playernum].animationtime=0;
			}
			if(player[playernum].animation==playeranimation_punching && player[playernum].animationtime>40.f){
				player[playernum].animation=playeranimation_none;
				player[playernum].animationtime=0;
			}
			if(player[playernum].animation==playeranimation_kicking && player[playernum].animationtime>15.f){
				player[playernum].animation=playeranimation_none;
				player[playernum].animationtime=0;
			}
			if(player[playernum].animation==playeranimation_walking && (player[playernum].animationtime>40.f || player[playernum].grounded==0 || (left==0 && right==0))){
				player[playernum].animation=playeranimation_none;
				player[playernum].animationtime=0;
			}
		}else{
			if(player[playernum].animationtime>15.f){
				player[playernum].animation=playeranimation_none;
				player[playernum].animationtime=0;
			}
		}
		player[playernum].animationtime+=gamespeed;

		//lose momentum
		if(player[playernum].grounded==1)player[playernum].movx-=player[playernum].movx*0.2f*gamespeed;
		player[playernum].movy-=player[playernum].movy*0.1f*gamespeed;

		//gain momentum based on input
		player[playernum].movx+=(float)((int)right-(int)left)*0.01f*gamespeed;
		player[playernum].movy+=0.008f*gamespeed;
		if(player[playernum].grounded && jump)player[playernum].movy=-0.275f*gamespeed;

		//movement takes effect
		float oldposx=player[playernum].posx;
		float oldposy=player[playernum].posy;
		player[playernum].posx+=player[playernum].movx*gamespeed;
		player[playernum].posy+=player[playernum].movy*gamespeed;
		if(player[playernum].posy>0.f+1.65f)player[playernum].posy=0.f+1.65f;
		if(player[playernum].posx>0.f+2.75f)player[playernum].posx=0.f+2.75f;
		if(player[playernum].posx<0.f-2.75f)player[playernum].posx=0.f-2.75f;
		if(player[playernum].posy<(float)(oldposy+player[playernum].movy*gamespeed)){
			player[playernum].grounded=1;}else{player[playernum].grounded=0;}
		player[playernum].movx=(player[playernum].posx-oldposx)/gamespeed;
		player[playernum].movy=(player[playernum].posy-oldposy)/gamespeed;

		//get the frame for rendering
		if(player[playernum].animation==playeranimation_none){
			if(player[playernum].grounded==1){
				player[playernum].frame=0;
			}else{
				player[playernum].frame=8;
			}
		}
		if(player[playernum].animation==playeranimation_punching){
			if(player[playernum].grounded==1){
				player[playernum].frame=4;
			}else{
				player[playernum].frame=12;
			}
			if(player[playernum].animationtime>10.f){
				if(player[playernum].grounded==1){
					player[playernum].frame=6;
				}else{
					player[playernum].frame=14;
				}
			}
			if(player[playernum].animationtime>20.f){
				if(player[playernum].grounded==1){
					player[playernum].frame=5;
				}else{
					player[playernum].frame=13;
				}
			}
			if(player[playernum].animationtime>30.f){
				if(player[playernum].grounded==1){
					player[playernum].frame=6;
				}else{
					player[playernum].frame=14;
				}
			}
		}
		if(player[playernum].animation==playeranimation_kicking){
			if(player[playernum].grounded==1){
				player[playernum].frame=2;
			}else{
				player[playernum].frame=10;
			}
		}
		if(player[playernum].animation==playeranimation_crouching){
			player[playernum].frame=3;
		}
		if(player[playernum].animation==playeranimation_walking){
			player[playernum].frame=15;
			if(player[playernum].animationtime>10.f){
				player[playernum].frame=11;
			}
			if(player[playernum].animationtime>20.f){
				player[playernum].frame=7;
			}
			if(player[playernum].animationtime>30.f){
				player[playernum].frame=11;
			}
		}
		if(player[playernum].animation==playeranimation_hurt){
			if(player[playernum].grounded==1){
				player[playernum].frame=1;
			}else{
				player[playernum].frame=9;
			}
		}
		player[playernum].drawingversion+=gamespeed;
		while(player[playernum].drawingversion>20.f)player[playernum].drawingversion-=20.f;

		//just for the sake of keeping it short
		int a=playernum;
		//attack other players
		if(player[a].animation==playeranimation_kicking)
		for(int b=0;b<playercount;b++)if(a!=b){
			if(player[a].posy<player[b].posy+0.25f
			&& player[a].posy>player[b].posy-0.25f){
				if(player[a].direction==0
				&& player[b].posx>player[a].posx+0.f
				&& player[b].posx<player[a].posx+0.75f){
					player[b].movx+=0.01f*gamespeed;
					player[b].movy-=0.01f*gamespeed;
					player[b].animation=playeranimation_hurt;
					player[b].animationtime=0;
					player[b].health-=0.005f*gamespeed;
				}
				if(player[a].direction==1
				&& player[b].posx<player[a].posx-0.f
				&& player[b].posx>player[a].posx-0.75f){
					player[b].movx-=0.01f*gamespeed;
					player[b].movy-=0.01f*gamespeed;
					player[b].animation=playeranimation_hurt;
					player[b].animationtime=0;
					player[b].health-=0.005f*gamespeed;
				}
			}
		}
		if(player[a].animation==playeranimation_punching)
		for(int b=0;b<playercount;b++)if(a!=b){
			if(player[a].posy<player[b].posy+0.25f
			&& player[a].posy>player[b].posy-0.25f){
				if(player[a].direction==0
				&& player[b].posx>player[a].posx+0.f
				&& player[b].posx<player[a].posx+0.75f){
					player[b].movx+=0.005f*gamespeed;
					player[b].animation=playeranimation_hurt;
					player[b].animationtime=0;
					player[b].health-=0.005f*gamespeed;
				}
				if(player[a].direction==1
				&& player[b].posx<player[a].posx-0.f
				&& player[b].posx>player[a].posx-0.75f){
					player[b].movx-=0.005f*gamespeed;
					player[b].animation=playeranimation_hurt;
					player[b].animationtime=0;
					player[b].health-=0.005f*gamespeed;
				}
			}
		}

	}

	//update the camera
	float averagecamx=0.f;
	float averagecamy=0.f;
	for(int playernum=0;playernum<playercount;playernum++)
		averagecamx+=player[playernum].posx;
	for(int playernum=0;playernum<playercount;playernum++)
		averagecamy+=player[playernum].posy;
	averagecamx/=(float)playercount;
	averagecamy/=(float)playercount;
	camx+=(averagecamx-camx)*0.1f*gamespeed;
	camy+=(averagecamy-0.5f-camy)*0.1f*gamespeed;
	float camdist=0.f;
	for(int playernum=0;playernum<playercount;playernum++)
		if(dist2d(player[playernum].posx,player[playernum].posy*0.5f,camx,camy*0.5f)>camdist)
			camdist=dist2d(player[playernum].posx,player[playernum].posy*0.5f,camx,camy*0.5f);
	camz+=(2.5f+camdist*2.f-camz)*0.05f*gamespeed;

}
