void play(float gamespeed){

	#ifdef PS3
	gamespeed=3.5f;
	#endif

	//reusable variables
	float angle=0,speed=0;
	
	//turn the camera
	#ifdef WII
	if(WiiButtonsHeld[0] & WPAD_BUTTON_UP)
		goalcamyang -= 0.0125*gamespeed;
	if(WiiButtonsHeld[0] & WPAD_BUTTON_DOWN)
		goalcamyang += 0.0125*gamespeed;
	if(WiiButtonsHeld[0] & WPAD_BUTTON_LEFT)
		goalcamxang += 0.0125*gamespeed;
	if(WiiButtonsHeld[0] & WPAD_BUTTON_RIGHT)
		goalcamxang -= 0.0125*gamespeed;
	#endif
	#ifdef WIN
	goalcamxang -= (float)(cursory[0]-240)*0.00005*gamespeed;
	goalcamyang += (float)(cursorx[0]-320)*0.00005*gamespeed;
	#endif
	#ifdef PS3
	speed=dist2d(0,0,(float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128))/128.f;
	if(speed>0.2f){
		if(speed>1.f)speed=1.f;
		angle=atan2((float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128));
	}else{
		speed=0.f;
	}
	goalcamyang += speed*cos(angle)*0.0125f*gamespeed;
	goalcamxang -= speed*sin(angle)*0.0125f*gamespeed;
	angle=0.f;
	speed=0.f;
	#endif
	//dont look to far up or down
	if(goalcamxang<0-90*radiansindegree)goalcamxang=0-90*radiansindegree;//looking down
	if(goalcamxang>0-5*radiansindegree)goalcamxang=0-5*radiansindegree;//looking up
	//make the move
	camxang+=(goalcamxang-camxang)*0.1*gamespeed;
	camyang+=(goalcamyang-camyang)*0.1*gamespeed;
	camzang+=(goalcamzang-camzang)*0.1*gamespeed;
	
	//keep track of the players starting position
	float oldplayerxpos=playerxpos;
	float oldplayerzpos=playerzpos;
	
	//move the player
	#ifdef WII
		/*speed=expans[0].nunchuk.js.mag;
		if(speed>0.1)
			angle=(expans[0].nunchuk.js.ang)*radiansindegree;*/
		speed=dist2d(-(float)gforce[0].y,(float)gforce[0].x,0,0);
		speed*=1.25f;
		if(speed>0.1f)
			angle=atan2(-(float)gforce[0].y,(float)gforce[0].x);
	#endif
	#ifdef WIN
		bool up=0,down=0,left=0,right=0;
		if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
		if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
		if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
		if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
		angle=atan2((float)right-(float)left,(float)up-(float)down);
		speed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
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
	if(speed>1)speed=1;
	speed*=(0.5+playersize*0.5);
	playerxposmov+=speed*cos(camyang+angle)*0.035*gamespeed;
	playerzposmov+=speed*sin(camyang+angle)*0.035*gamespeed;
	playerxpos+=playerxposmov*gamespeed;
	playerzpos+=playerzposmov*gamespeed;
	
	//bump into trees
	bumpintoworld(&playerxpos,&playerzpos,1.25+7.5*playersize);
	
	//update player move speed and direction
	playerxposmov=(playerxpos-oldplayerxpos)/gamespeed;
	playerzposmov=(playerzpos-oldplayerzpos)/gamespeed;
	if(dist2d(playerxposmov,playerzposmov,0,0)>0){
		playeryang=turntoangle(
			playeryang,
			atan2(playerzposmov,playerxposmov),
			dist2d(playerxposmov,playerzposmov,0,0)*0.25);	
	}
	playerxposmov-=playerxposmov*0.09*gamespeed;
	playerzposmov-=playerzposmov*0.09*gamespeed;
	
	//update the grid position
	playerxgridpos=(int)((playerxpos+worldtilesize*0.5)/worldtilesize);
	playerzgridpos=(int)((playerzpos+worldtilesize*0.5)/worldtilesize);
	
	//collect snow
	playersize-=(0.00005+0.00065*playersize)*gamespeed;
	for(int x=0; x<worldgridsizex*2; x++)
	for(int z=0; z<worldgridsizez*2; z++)if(snowgrid[x][z])
	if(dist2d(
		x*worldtilesize*0.5,
		z*worldtilesize*0.5,
		playerxpos,playerzpos)<1.25+7.5*playersize+worldtilesize*0.25){
			playersize+=0.002f;
			snowcollected+=1;
			snowgrid[x][z]=0;
	}
	if(playersize<0)playersize=0;
	if(playersize>1)playersize=1;

	if(snowcollected==totalsnow){
		currentlevel+=1;
		if(currentlevel>10)currentlevel=1;
		setupgame();
	}

	//position camera
	float goalcamxpos=playerxpos;
	float goalcamypos=5.75+15*playersize;
	float goalcamzpos=playerzpos;
	//movein3dspace(goalcamxpos,goalcamypos,goalcamzpos,camyang,camxang,-30-50*playersize);
	goalcamypos+=(-30-50*playersize)*sin(camxang);
	goalcamxpos+=(-30-50*playersize)*cos(camxang)*cos(camyang);
	goalcamzpos+=(-30-50*playersize)*cos(camxang)*sin(camyang);

	camxpos+=(goalcamxpos-camxpos)*0.075*gamespeed;
	camypos+=(goalcamypos-camypos)*0.075*gamespeed;
	camzpos+=(goalcamzpos-camzpos)*0.075*gamespeed;

}
