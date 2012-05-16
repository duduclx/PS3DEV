float camdist=45;

void play(float gamespeed){

	//reusable variables
	float angle=0.f,speed=0.f;
	float xmove=0.f,zmove=0.f;
	
	//turn the camera
	#ifdef PS3
	speed=dist2d(0,0,(float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128))/128.f;
	if(speed>0.2f){
		if(speed>1.f)speed=1.f;
		angle=atan2((float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128));
	}else{
		speed=0.f;
	}
	camyangmov+=cos(angle)*speed*0.0075f*gamespeed;
	camxangmov-=sin(angle)*speed*0.0075f*gamespeed;
	camxang+=camxangmov*gamespeed;
	camyang+=camyangmov*gamespeed;
	camxangmov-=camxangmov*0.125*gamespeed;
	camyangmov-=camyangmov*0.125*gamespeed;
	camzangmov-=camzangmov*0.125*gamespeed;
	angle=0.f;
	speed=0.f;
	#else
	camyang += (float)(cursorx[0]-screenw/2)/screenw*0.095*gamespeed;
	camxang -= (float)(cursory[0]-screenh/2)/screenh*0.075*gamespeed;
	#endif

	//dont look too far up or down
	if(camxang<0-90*radiansindegree)camxang=0-90*radiansindegree;//looking down
	if(camxang>0+20*radiansindegree)camxang=0+20*radiansindegree;//looking up
	
	//keep track of the players starting position
	float oldplayerxpos=playerxpos;
	float oldplayerypos=playerypos;
	float oldplayerzpos=playerzpos;
	
	//jump
	playerjumping=0;
	#ifdef WII
	if((WiiButtonsHeld[0] & WPAD_BUTTON_A))
	#endif
	#ifdef WIN
	if(keystate[SDLK_SPACE])
	#endif
	#ifdef PS3
	if(BTN_CROSS[0])
	#endif
		playerjumping=1;
	//fly
	playerflying=0;
	if(playerenergy>0){
		#ifdef WII
		if((WiiButtonsHeld[0] & WPAD_NUNCHUK_BUTTON_Z))
		#endif
		#ifdef WIN
		if(keystate[SDLK_LSHIFT])
		#endif
		#ifdef PS3
		if(BTN_CIRCLE[0])
		#endif
			playerflying=1;
	}
	//attack
	if(playerattackingl==0 && playerattackingr==0){
		#ifdef WII
		if((WiiButtonsHeld[0] & WPAD_NUNCHUK_BUTTON_C)){
		#endif
		#ifdef WIN
		if(mousestate[SDL_BUTTON_LEFT]==2){
		#endif
		#ifdef PS3
		if(BTN_SQUARE[0]==2){
		#endif
			playerattackingl=1;
		#ifdef WII
		}else if((WiiButtonsHeld[0] & WPAD_BUTTON_B)){
		#endif
		#ifdef WIN
		}else if(mousestate[SDL_BUTTON_RIGHT]==2){
		#endif
		#ifdef PS3
		}else if(BTN_TRIANGLE[0]==2){
		#endif
			playerattackingr=1;
		}
	}
	//there can be only one
	if(!playergrounded){
		playerattackingl=0;
		playerattackingr=0;
	}
	if(playerflying){
		playerjumping=0;
		playerattackingl=0;
		playerattackingr=0;
	}
	if(playerattackingl || playerattackingr){
		playerjumping=0;
	}
	//jumping takes effect
	if(playerjumping){
		if(playergrounded){
			playeryposmov=0.65;
		}else if(playeryposmov>0.1){
			playeryposmov+=(0.015+playeryposmov*0.08)*gamespeed;
		}else{
			playerjumping=0;
		}
	}

	playerenergyregenwait+=0.1*gamespeed;
	if(playerenergyregenwait>5)playerenergy+=0.5*gamespeed;
	if(playerenergy>100)playerenergy=100;

	playerhealthregenwait+=0.1*gamespeed;
	if(playerhealthregenwait>15)playerhealth+=0.1*gamespeed;
	if(playerhealth>100)playerhealth=100;

	//move the player
	if(playerflying){
		playeryposmov+=0.05f*sin(camxang);
		playerxposmov+=0.05f*cos(camxang)*cos(camyang);
		playerzposmov+=0.05f*cos(camxang)*sin(camyang);
		playerenergy-=0.1*gamespeed;
		if(playerenergy<0)playerenergy=0;
		playerenergyregenwait=0;
		if(dist2d(playerxposmov,playerzposmov,0,0)>0){
			playeryang=turntoangle(
				playeryang,
				atan2(playerzposmov,playerxposmov),
				dist2d(playerxposmov,playerzposmov,0,0)*0.3);	
		}
	}else{
		speed=0;
		angle=0;
		#ifdef WII
			speed=expans[0].nunchuk.js.mag;
			if(speed>0.1){
				if(speed>1)speed=1;
				angle=(expans[0].nunchuk.js.ang)*radiansindegree;
			}
		#endif
		#ifdef WIN
			bool up=0,down=0,left=0,right=0;
			if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
			if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
			if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
			if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
			angle=atan2((float)right-(float)left,(float)up-(float)down);
			speed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
			if(speed>1)speed=1;
		#endif
		#ifdef PS3
		speed=dist2d(0,0,(float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))/128.f;
		if(speed>0.2f){
			if(speed>1.f)speed=1.f;
			angle=atan2((float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))+90.f*radiansindegree;
		}else{
			speed=0.f;
		}
		#endif
		if(playerattackingl || playerattackingr){
			if(speed>0.1f){
				playerxposmov+=speed*cos(camyang+angle)*0.005*gamespeed;
				playerzposmov+=speed*sin(camyang+angle)*0.005*gamespeed;
			}
			playeryposmov-=0.04*gamespeed;
		}else{
			if(speed>0.1f){
				playerxposmov+=speed*cos(camyang+angle)*0.040*gamespeed;
				playerzposmov+=speed*sin(camyang+angle)*0.040*gamespeed;
			}
			playeryposmov-=0.04*gamespeed;
		}
		playeryang=turntoangle(playeryang,camyang+angle,speed*0.1f);	
	}
	playerxpos+=playerxposmov*gamespeed;
	playerypos+=playeryposmov*gamespeed;
	playerzpos+=playerzposmov*gamespeed;

	//update npc people
	for(int x=highint(0,playerxgridpos-peopleviewrange-1); x<lowint(worldgridsizex,playerxgridpos+peopleviewrange+2); x++)
	for(int z=highint(0,playerzgridpos-peopleviewrange-1); z<lowint(worldgridsizez,playerzgridpos+peopleviewrange+2); z++)
	for(int a=0; a<personcount[x][z]; a++){
		//animate
		if(personlist[x][z][a].type==persontype_zombie){
			personlist[x][z][a].frame+=0.075*gamespeed;
			while(personlist[x][z][a].frame>4)personlist[x][z][a].frame-=4;
		}
		if(personlist[x][z][a].type==persontype_bigmonster){
			personlist[x][z][a].frame+=0.035*gamespeed;
			while(personlist[x][z][a].frame>4)personlist[x][z][a].frame-=4;
		}
		if(personlist[x][z][a].type==persontype_robot){
			personlist[x][z][a].frame+=0.075*gamespeed;
			while(personlist[x][z][a].frame>4)personlist[x][z][a].frame-=4;
		}
		//face the player and move towards them
		if(playerxpos!=personlist[x][z][a].xpos
		&& playerzpos!=personlist[x][z][a].zpos){
			angle=atan2(
				playerzpos-personlist[x][z][a].zpos,
				playerxpos-personlist[x][z][a].xpos);
			angle=turntoangle(personlist[x][z][a].yang,angle,0.1f*gamespeed);
			personlist[x][z][a].yang=angle;
		}else{
			angle=personlist[x][z][a].yang;
		}
		personlist[x][z][a].xmov+=persontype_movespeed[personlist[x][z][a].type]*cos(angle)*gamespeed;
		personlist[x][z][a].zmov+=persontype_movespeed[personlist[x][z][a].type]*sin(angle)*gamespeed;
		personlist[x][z][a].xpos+=personlist[x][z][a].xmov*gamespeed;
		personlist[x][z][a].zpos+=personlist[x][z][a].zmov*gamespeed;
		personlist[x][z][a].xmov-=personlist[x][z][a].xmov*0.065f*gamespeed;
		personlist[x][z][a].zmov-=personlist[x][z][a].zmov*0.065f*gamespeed;
		//gravity
		if(playergrounded==0){
			personlist[x][z][a].ypos-=0.2f*gamespeed;
		}else{
			personlist[x][z][a].ypos-=0.05f*gamespeed;
		}
		//bump into other people
		for(int x2=highint(0,x-1); x2<lowint(worldgridsizex,x+2); x2++)
		for(int z2=highint(0,z-1); z2<lowint(worldgridsizez,z+2); z2++)
		for(int b=0; b<personcount[x2][z2]; b++)
		if(x!=x2 || z!=z2 || a!=b){
			speed=dist2d(
				personlist[x][z][a].xpos,
				personlist[x][z][a].zpos,
				personlist[x2][z2][b].xpos,
				personlist[x2][z2][b].zpos);
			float correctdist=
				persontype_radius[personlist[x][z][a].type]+
				persontype_radius[personlist[x2][z2][b].type];
			if(speed<correctdist){
				angle=atan2(
					personlist[x][z][a].zpos-personlist[x2][z2][b].zpos,
					personlist[x][z][a].xpos-personlist[x2][z2][b].xpos);
				speed=(correctdist-speed)*0.005;
				xmove=speed*cos(angle);
				zmove=speed*sin(angle);
				personlist[x][z][a].xmov+=xmove;
				personlist[x][z][a].zmov+=zmove;
				personlist[x2][z2][b].xmov-=xmove;
				personlist[x2][z2][b].zmov-=zmove;
			}
		}
		//bump into walls
		bumpintoworld(
			&personlist[x][z][a].xpos,
			&personlist[x][z][a].ypos,
			&personlist[x][z][a].zpos,
			persontype_radius[personlist[x][z][a].type]);
		//update grid position
		int xgridpos=(int)((personlist[x][z][a].xpos+worldtilesize*0.5)/worldtilesize);
		int zgridpos=(int)((personlist[x][z][a].zpos+worldtilesize*0.5)/worldtilesize);
		if(xgridpos!=x || zgridpos!=z)
		if(personcount[xgridpos][zgridpos]<maxpersoncount){
			personlist[xgridpos][zgridpos][(int)personcount[xgridpos][zgridpos]] = personlist[x][z][a];
			personcount[xgridpos][zgridpos]+=1;
			totalpersontypecount[personlist[x][z][a].type]+=1;
			totalpersoncount+=1;
			removepersonfromlist(x,z,a);
		}
	}
	//bump into the player
	for(int x=highint(0,playerxgridpos-1); x<lowint(worldgridsizex,playerxgridpos+2); x++)
	for(int z=highint(0,playerzgridpos-1); z<lowint(worldgridsizez,playerzgridpos+2); z++)
	for(int a=0; a<personcount[x][z]; a++)
	if(personlist[x][z][a].ypos>playerypos-persontype_height[personlist[x][z][a].type]){
		speed=dist2d(
			personlist[x][z][a].xpos,
			personlist[x][z][a].zpos,
			playerxpos,
			playerzpos);
		float correctdist=persontype_radius[personlist[x][z][a].type]+playerradius;
		if(speed<correctdist){
			angle=atan2(
				personlist[x][z][a].zpos-playerzpos,
				personlist[x][z][a].xpos-playerxpos);
			speed=(correctdist-speed)*0.02;
			xmove=speed*cos(angle);
			zmove=speed*sin(angle);
			personlist[x][z][a].xmov+=xmove;
			personlist[x][z][a].zmov+=zmove;
			playerxpos-=xmove*1.5;
			playerzpos-=zmove*1.5;
			playerhealth-=0.1*gamespeed;
			playerhealthregenwait=0;
		}
	}
	if(playerhealth<0)playerhealth=0;
	
	//bump against walls
	bumpintoworldcorrect(&playerxpos,&playerypos,&playerzpos,2.75);
	
	//bump against the ends of the world
	if(playerxpos<(1)*worldtilesize)
		playerxpos=(1)*worldtilesize;
	if(playerxpos>(worldgridsizex-2)*worldtilesize)
		playerxpos=(worldgridsizex-2)*worldtilesize;
	if(playerzpos<(1)*worldtilesize)
		playerzpos=(1)*worldtilesize;
	if(playerzpos>(worldgridsizez-2)*worldtilesize)
		playerzpos=(worldgridsizez-2)*worldtilesize;

	//check if you are on the ground
	if(playerypos>(float)(oldplayerypos+playeryposmov*gamespeed)+0.0001){
		playergrounded=1;
	}else{
		playergrounded=0;
	}

	//update player move speed and direction
	playerxposmov=(playerxpos-oldplayerxpos)/gamespeed;
	playeryposmov=(playerypos-oldplayerypos)/gamespeed;
	playerzposmov=(playerzpos-oldplayerzpos)/gamespeed;
	if(playerflying==0){
		playerxposmov-=playerxposmov*0.09*gamespeed;
		playeryposmov-=playeryposmov*0.04*gamespeed;
		playerzposmov-=playerzposmov*0.09*gamespeed;
	}else{
		playerxposmov-=playerxposmov*0.02*gamespeed;
		playeryposmov-=playeryposmov*0.02*gamespeed;
		playerzposmov-=playerzposmov*0.02*gamespeed;
	}
	
	//update the grid position
	playerxgridpos=(int)((playerxpos+worldtilesize*0.5f)/worldtilesize);
	playerygridpos=(int)((playerypos+worldtilesize*0.5f)/worldtilesize);
	playerzgridpos=(int)((playerzpos+worldtilesize*0.5f)/worldtilesize);
	
	bool attack=0;

	if(playerattackingl || playerattackingr){
		playerframeprogress+=0.175*gamespeed;
	}else if(playergrounded
	&& playerlastframe>=0 && playerlastframe<=3
	&& playernextframe>=0 && playernextframe<=3){
		playerframeprogress+=dist2d(0,0,playerxposmov,playerzposmov)*0.4*gamespeed;
	}else{
		playerframeprogress+=0.075*gamespeed;
	}
	if(playerframeprogress>=1){
		playerlastframe=playernextframe;
		playerframeprogress=0;
		if(playerattackingl || playerattackingr){
			if(playerattackingl)playernextframe=6;
			if(playerattackingr)playernextframe=7;
			playerattackingl=0;
			playerattackingr=0;
			attack=1;
		}else if(playergrounded){
			if(playernextframe==0)playernextframe=1;
			else if(playernextframe==1)playernextframe=2;
			else if(playernextframe==2)playernextframe=3;
			else if(playernextframe==3)playernextframe=0;
			else playernextframe=0;
		}else if(playerflying){
			playernextframe=5;
		}else{
			playernextframe=4;
		}
		if(playernextframe==playerlastframe)playerframeprogress=1;
	}

	if(attack){
		for(int x=highint(0,playerxgridpos-1); x<lowint(worldgridsizex,playerxgridpos+2); x++)
		for(int z=highint(0,playerzgridpos-1); z<lowint(worldgridsizez,playerzgridpos+2); z++)
		for(int a=0; a<personcount[x][z]; a++)
		if(personlist[x][z][a].ypos>playerypos-persontype_height[personlist[x][z][a].type]){
			speed=dist2d(
				personlist[x][z][a].xpos,
				personlist[x][z][a].zpos,
				playerxpos,
				playerzpos);
			float correctdist=persontype_radius[personlist[x][z][a].type]+playerradius*2.f;
			if(speed<correctdist){
				angle=atan2(
					personlist[x][z][a].zpos-playerzpos,
					personlist[x][z][a].xpos-playerxpos);
				if(angledifference(playeryang,angle)<0+90*radiansindegree
				&& angledifference(playeryang,angle)>0-90*radiansindegree){
					speed=(correctdist-speed)*0.02;
					personlist[x][z][a].xmov+=1.2*cos(angle);
					personlist[x][z][a].zmov+=1.2*sin(angle);
					if(personlist[x][z][a].type==persontype_zombie)
						personlist[x][z][a].health-=50;
					if(personlist[x][z][a].type==persontype_bigmonster)
						personlist[x][z][a].health-=25;
					if(personlist[x][z][a].type==persontype_robot)
						personlist[x][z][a].health-=20;
					if(personlist[x][z][a].health<=0){
						if(personlist[x][z][a].type==persontype_zombie){
							score+=5;
							experience+=5;
						}
						if(personlist[x][z][a].type==persontype_bigmonster){
							score+=20;
							experience+=20;
						}
						if(personlist[x][z][a].type==persontype_robot){
							score+=10;
							experience+=10;
						}
						removepersonfromlist(x,z,a);
						a-=1;
					}
				}
			}
		}
	}

	//position camera
	float goalcamdist=30;
	if(playerflying)goalcamdist=10;
	camdist+=(goalcamdist-camdist)*0.025*gamespeed;
	camxpos=playerxpos;
	camypos=playerypos+5.75;
	camzpos=playerzpos;
	camypos-=camdist*sin(camxang);
	camxpos-=camdist*cos(camxang)*cos(camyang);
	camzpos-=camdist*cos(camxang)*sin(camyang);

	//populate the world
	if(totalpersoncount<300){
		int x=rand()%worldgridsizex;
		int z=rand()%worldgridsizez;
		if(bumpgrid[x][z]==0 && personcount[x][z]==0)
		if(x<playerxgridpos-peopleviewrange || x>playerxgridpos+peopleviewrange
		|| z<playerzgridpos-peopleviewrange || z>playerzgridpos+peopleviewrange)
			makeperson(
				rand()%persontypecount,
				x*worldtilesize,
				0-worldtilesize,
				z*worldtilesize);
	}

}
