void play(float gamespeed){

	//move based on input
	float movespeed=0;
	float moveangle=0;
	#ifdef WII
		movespeed=expans[0].nunchuk.js.mag;
		if(movespeed>0.1){
			if(movespeed>1)movespeed=1;
			moveangle=(expans[0].nunchuk.js.ang)*radiansindegree;
		}
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
	#endif
	#ifdef PS3
	movespeed=dist2d(0,0,(float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))/128.f;
	if(movespeed>1.f)movespeed=1.f;
	if(movespeed>0.2f)moveangle=atan2((float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))+90*radiansindegree;
	#endif
	playerangl=turntoangle(playerangl,moveangle,0.1f*movespeed*gamespeed);
	playermovy-=0.00055*cos(playerangl)*movespeed*gamespeed;
	playermovx+=0.00055*sin(playerangl)*movespeed*gamespeed;

	playerposx+=playermovx;
	playerposy+=playermovy;
	playermovx-=playermovx*0.05*gamespeed;
	playermovy-=playermovy*0.05*gamespeed;

	worldangl=turntoangle(worldangl,atan2(playerposy-worldposy,playerposx-worldposx),0.1f*gamespeed);
	worldmovy+=0.0005*cos(worldangl-90*radiansindegree)*gamespeed;	
	worldmovx-=0.0005*sin(worldangl-90*radiansindegree)*gamespeed;
	worldposx+=worldmovx;
	worldposy+=worldmovy;
	worldmovx-=worldmovx*0.05*gamespeed;
	worldmovy-=worldmovy*0.05*gamespeed;

	//asteroids
	for(int a=0;a<n_asteroids;a++){
		asteroids[a].posx+=asteroids[a].movx*gamespeed;
		asteroids[a].posy+=asteroids[a].movy*gamespeed;
		if(asteroids[a].posx<camx-2)asteroids[a].posx+=4;
		if(asteroids[a].posx>camx+2)asteroids[a].posx-=4;
		if(asteroids[a].posy<camy-2)asteroids[a].posy+=4;
		if(asteroids[a].posy>camy+2)asteroids[a].posy-=4;
		asteroids[a].angle+=asteroids[a].movangle*gamespeed;
	}

	camx+=(playerposx-camx)*0.075*gamespeed;
	camy+=(playerposy-camy)*0.075*gamespeed;

}
