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
	#ifdef WIN
	if(!mousestate[SDL_BUTTON_RIGHT])
	#endif
	#ifdef WII
	if(!(WiiButtonsHeld[0] & WPAD_BUTTON_A))
	#endif
	if(dashusecursor[0]){
		camyang += (float)(cursorx[0]-screenw/2)/screenw*0.095*gamespeed;
		camxang -= (float)(cursory[0]-screenh/2)/screenh*0.065*gamespeed;
	}
	#endif

	//dont look too far up or down
	if(camxang<0-35*radiansindegree)camxang=0-35*radiansindegree;//looking down
	if(camxang>0+35*radiansindegree)camxang=0+35*radiansindegree;//looking up
	
	//keep track of the cams starting position
	float oldcamxpos=camxpos;
	float oldcamypos=camypos;
	float oldcamzpos=camzpos;
	
	//update people
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	for(int a=0; a<personcount[x][z]; a++){
		//face the cam and move towards them
		angle=atan2(
			camzpos-personlist[x][z][a].zpos,
			camxpos-personlist[x][z][a].xpos);
		personlist[x][z][a].xpos+=0.75*cos(angle)*gamespeed;
		personlist[x][z][a].zpos+=0.75*sin(angle)*gamespeed;
		personlist[x][z][a].yang=angle;
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
			if(speed<happypeopleradius*2){
				angle=atan2(
					personlist[x][z][a].zpos-personlist[x2][z2][b].zpos,
					personlist[x][z][a].xpos-personlist[x2][z2][b].xpos);
				speed=(happypeopleradius*2-speed)*0.25;
				xmove=speed*cos(angle);
				zmove=speed*sin(angle);
				personlist[x][z][a].xpos+=xmove;
				personlist[x][z][a].zpos+=zmove;
				personlist[x2][z2][b].xpos-=xmove;
				personlist[x2][z2][b].zpos-=zmove;
			}
		}
		//bump into walls
		bumpintoworld(
			&personlist[x][z][a].xpos,
			&personlist[x][z][a].ypos,
			&personlist[x][z][a].zpos,
			happypeopleradius);
	}
	//bump into the cam
	for(int x=highint(0,camxgridpos-1); x<lowint(worldgridsizex,camxgridpos+2); x++)
	for(int z=highint(0,camzgridpos-1); z<lowint(worldgridsizez,camzgridpos+2); z++)
	for(int a=0; a<personcount[x][z]; a++){
		speed=dist2d(
			personlist[x][z][a].xpos,
			personlist[x][z][a].zpos,
			camxpos,
			camzpos);
		if(speed<happypeopleradius*2.1f){
			health-=0.5*gamespeed;
			playerhurt=1;
		}
		if(speed<happypeopleradius*2){
			angle=atan2(
				personlist[x][z][a].zpos-camzpos,
				personlist[x][z][a].xpos-camxpos);
			speed=(happypeopleradius*2-speed)*0.25;
			xmove=speed*cos(angle);
			zmove=speed*sin(angle);
			personlist[x][z][a].xpos+=xmove*4.0;
			personlist[x][z][a].zpos+=zmove*4.0;
			camxpos-=xmove*0.25;
			camzpos-=zmove*0.25;
		}
	}
	//update grid positions
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	for(int a=0; a<personcount[x][z]; a++){
		int xgridpos=(int)floor(personlist[x][z][a].xpos/worldtilesize+0.5f);
		int zgridpos=(int)floor(personlist[x][z][a].zpos/worldtilesize+0.5f);
		if(xgridpos!=x || zgridpos!=z)
		if(personcount[x][z]<maxpersoncount){
			personlist[xgridpos][zgridpos][(int)personcount[xgridpos][zgridpos]] = personlist[x][z][a];
			personcount[xgridpos][zgridpos]+=1;
			totalpersoncount+=1;
			removepersonfromlist(x,z,a);
		}
	}

	//update things
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	for(int a=0; a<thingcount[x][z]; a++){
		//move
		thinglist[x][z][a].xpos+=thinglist[x][z][a].xposmov*gamespeed;
		thinglist[x][z][a].ypos+=thinglist[x][z][a].yposmov*gamespeed;
		thinglist[x][z][a].zpos+=thinglist[x][z][a].zposmov*gamespeed;
		//shots hit people
		if(thinglist[x][z][a].type==thingtype_blast)
		for(int x2=highint(0,x-1); x2<lowint(worldgridsizex,x+2); x2++)
		for(int z2=highint(0,z-1); z2<lowint(worldgridsizez,z+2); z2++)
		for(int b=0; b<personcount[x2][z2]; b++){
			speed=dist2d(
				thinglist[x][z][a].xpos,
				thinglist[x][z][a].zpos,
				personlist[x2][z2][b].xpos,
				personlist[x2][z2][b].zpos);
			if(speed<happypeopleradius){
				personlist[x2][z2][b].xpos+=thinglist[x][z][a].xposmov*2.5f;
				personlist[x2][z2][b].zpos+=thinglist[x][z][a].zposmov*2.5f;
				removethingfromlist(x,z,a);
				personlist[x2][z2][b].health-=1;
				if(personlist[x2][z2][b].health<=0){
					removepersonfromlist(x2,z2,b);
					score+=10;
				}
				x2=lowint(worldgridsizex,x+2);
				z2=lowint(worldgridsizez,z+2);
				b=personcount[x2][z2];
				a-=1;
			}
		}
	}
	//bump into the cam
	for(int x=highint(0,camxgridpos-1); x<lowint(worldgridsizex,camxgridpos+2); x++)
	for(int z=highint(0,camzgridpos-1); z<lowint(worldgridsizez,camzgridpos+2); z++)
	for(int a=0; a<thingcount[x][z]; a++){
		speed=dist2d(
			thinglist[x][z][a].xpos,
			thinglist[x][z][a].zpos,
			camxpos,
			camzpos);
		if(speed<happypeopleradius*1.2f){
			if(thinglist[x][z][a].type==thingtype_ammo){
				removethingfromlist(x,z,a);
				ammo+=50;
				a-=1;
			}else if(thinglist[x][z][a].type==thingtype_medkit){
				removethingfromlist(x,z,a);
				health+=10;
				a-=1;
			}
		}
	}
	//update grid positions
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	for(int a=0; a<thingcount[x][z]; a++){
		int xgridpos=(int)floor(thinglist[x][z][a].xpos/worldtilesize+0.5f);
		int zgridpos=(int)floor(thinglist[x][z][a].zpos/worldtilesize+0.5f);
		if(xgridpos!=x || zgridpos!=z)
		if(thingcount[xgridpos][zgridpos]<maxthingcount){
			thinglist[xgridpos][zgridpos][(int)thingcount[xgridpos][zgridpos]] = thinglist[x][z][a];
			thingcount[xgridpos][zgridpos]+=1;
			totalthingcount+=1;
			totalthingtypecount[thinglist[x][z][a].type]+=1;
			removethingfromlist(x,z,a);
		}
	}
	//delete when in a wall
	for(int x=0; x<worldgridsizex; x++)
	for(int z=0; z<worldgridsizez; z++)
	if(worldgrid[x][z])
	for(int a=0; a<thingcount[x][z]; a++){
		removethingfromlist(x,z,a);
		a-=1;
	}

	//move the cam
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
	if(speed>0.1){
		camxposmov+=speed*cos(camyang+angle)*0.040*gamespeed;
		camzposmov+=speed*sin(camyang+angle)*0.040*gamespeed;
	}
	camxpos+=camxposmov*gamespeed;
	camypos+=camyposmov*gamespeed;
	camzpos+=camzposmov*gamespeed;
	//bump into walls
	bumpintoworld(&camxpos,&camypos,&camzpos,worldtilesize*0.3f);
	//correct speed
	camxposmov=(camxpos-oldcamxpos)/gamespeed;
	camyposmov=(camypos-oldcamypos)/gamespeed;
	camzposmov=(camzpos-oldcamzpos)/gamespeed;
	camxposmov-=camxposmov*0.02*gamespeed;
	camyposmov-=camyposmov*0.02*gamespeed;
	camzposmov-=camzposmov*0.02*gamespeed;
	//there is no movement on the y axis right now
	camypos=0;

	//update the grid position
	camxgridpos=(int)floor(camxpos/worldtilesize+0.5f);
	camygridpos=(int)floor(camypos/worldtilesize+0.5f);
	camzgridpos=(int)floor(camzpos/worldtilesize+0.5f);
	
	//shoot
	shootwait-=gamespeed;
	#ifdef WIN
	if(mousestate[SDL_BUTTON_LEFT])
	#endif
	#ifdef WII
	if(WiiButtonsHeld[0] & WPAD_BUTTON_B)
	#endif
	#ifdef PS3
	if(BTN_R1[0]==1)
	#endif
	if(shootwait<0 && ammo>0){
		float angle=camyang;
		#ifndef PS3
		angle+=(cursorx[0]-screenw/2)/screenh*50*radiansindegree;
		#endif
		makething(
			thingtype_blast,
			camxpos+5.f*cos(angle),
			camypos-worldtilesize*0.1f,
			camzpos+5.f*sin(angle),
			camyang,
			2.0f*cos(angle)+camxposmov*0.25f,
			0.f,
			2.0f*sin(angle)+camzposmov*0.25f);
		shootwait=9.f;
		ammo-=1;
	}
	
	//spawn people and things
	genpeopleandthings();

}
