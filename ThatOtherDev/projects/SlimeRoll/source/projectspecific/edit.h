void edit(float gamespeed){

	//get input
	float inputspeed=0;
	float inputangle=0;
	bool spinleft=0;
	bool spinright=0;
	bool zoomin=0;
	bool zoomout=0;
	bool placewall=0;
	bool placeslime=0;
	bool placegoal=0;
	bool removesomething=0;
	bool exit=0;
	#ifdef WII
	#endif
	#ifdef WIN
		bool up=0,down=0,left=0,right=0;
		if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
		if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
		if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
		if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
		if(keystate[SDLK_q])spinleft=1;
		if(keystate[SDLK_e])spinright=1;
		inputangle=atan2((float)left-(float)right,(float)up-(float)down)-90.f*radiansindegree;
		inputspeed=dist2d((float)left-(float)right,(float)up-(float)down,0,0);
		if(inputspeed>1)inputspeed=1;
		aimx=((float)(cursorx[0])/screenw)*2.f-1.f;
		aimy=((float)(cursory[0])/screenh)*2.f-1.f;
		if(mousestate[SDL_BUTTON_LEFT])placewall=1;
		if(keystate[SDLK_r])placeslime=1;
		if(keystate[SDLK_f])placegoal=1;
		if(mousestate[SDL_BUTTON_RIGHT])removesomething=1;
		if(keystate[SDLK_BACKSPACE])exit=1;
	#endif
	#ifdef PS3
		inputspeed=dist2d(0,0,(float)(paddata[0].ANA_L_V-128),(float)(128-paddata[0].ANA_L_H))/128.f;
		if(inputspeed>0.2f){
			if(inputspeed>1.f)inputspeed=1.f;
			inputangle=atan2((float)(paddata[0].ANA_L_V-128),(float)(128-paddata[0].ANA_L_H));
		}else{
			inputspeed=0;
		}
		if(BTN_L1[0]==1)spinleft=1;
		if(BTN_R1[0]==1)spinright=1;
		if(BTN_L2[0]==1)zoomin=1;
		if(BTN_R2[0]==1)zoomout=1;
		if(BTN_CROSS[0]==1)placewall=1;
		if(BTN_SQUARE[0]==1)placeslime=1;
		if(BTN_CIRCLE[0]==1)placegoal=1;
		if(BTN_TRIANGLE[0]==1)removesomething=1;
		if(BTN_SELECT[0]==2)exit=1;
		aimx=0.f;
		aimy=0.f;
	#endif

	//prep for rotation
	float camacos=cos(-cama-radiansindegree*90.f);
	float camasin=sin(-cama-radiansindegree*90.f);
	float rotatedcamx=camx*camasin+camy*camacos;
	float rotatedcamy=camx*camacos-camy*camasin;

	//move camera
	camxmov-=camxmov*0.1f*gamespeed;
	camymov-=camymov*0.1f*gamespeed;
	camamov-=camamov*0.1f*gamespeed;
	camzmov-=camzmov*0.1f*gamespeed;
	camxmov+=cos(inputangle+cama)*inputspeed*0.5f*gamespeed;
	camymov+=sin(inputangle+cama)*inputspeed*0.5f*gamespeed;
	camamov+=(float)((int)spinright-(int)spinleft)*0.005f*gamespeed;
	camzmov+=(float)((int)zoomout-(int)zoomin)*0.8f*gamespeed;
	camx+=camxmov*gamespeed;
	camy+=camymov*gamespeed;
	cama+=camamov*gamespeed;
	camz+=camzmov*gamespeed;
	if(camz<500.f)camz=500.f;
	if(camz>1500.f)camz=1500.f;

	//get cursor position in world
	if(aimx<-1)aimx=-1;
	if(aimx>1)aimx=1;
	if(aimy<-1)aimy=-1;
	if(aimy>1)aimy=1;
	float aiminworldxprerotation=0.f+rotatedcamx+aimx*camz*0.5f*screena;
	float aiminworldyprerotation=0.f+rotatedcamy+aimy*camz*0.5f;
	aiminworldx=aiminworldxprerotation*camasin+aiminworldyprerotation*camacos;
	aiminworldy=aiminworldxprerotation*camacos-aiminworldyprerotation*camasin;

	//spawn walls
	if(placewall)spawning=1;
	if(spawning){
		if(placewall){
			spawnsize=dist2d(spawnposx,spawnposy,aiminworldx,aiminworldy)+5.f;
		}else{
			makeentity(entitytype_wall,
				spawnposx,
				spawnposy,
				0,0,spawnsize);
			spawning=0;
		}
	}else{
		spawnposx=aiminworldx;
		spawnposy=aiminworldy;
	}
	
	//spawn slime
	if(placeslime){
		bool doit=1;
		for(int a=0;a<entitycount;a++)if(entitylist[a].type==entitytype_slime)
			if(dist2d(entitylist[a].posx,entitylist[a].posy,aiminworldx,aiminworldy)<7.5f)
				doit=0;
		if(doit==1)makeentity(entitytype_slime,aiminworldx,aiminworldy,0,0,15.f);
	}

	//spawn goals
	if(placegoal){
		bool doit=1;
		for(int a=0;a<entitycount;a++)if(entitylist[a].type==entitytype_goal)
			if(dist2d(entitylist[a].posx,entitylist[a].posy,aiminworldx,aiminworldy)<7.5f)
				doit=0;
		if(doit==1)makeentity(entitytype_goal,aiminworldx,aiminworldy,0,0,15.f);
	}

	//remove things
	if(removesomething && entitycount>0){
		//removeentityfromlist(entitycount-1);
		for(int a=0;a<entitycount;a++)
		if(dist2d(entitylist[a].posx,entitylist[a].posy,aiminworldx,aiminworldy)<
		entitylist[a].size){
			removeentityfromlist(a);
			a-=1;
		}
	}

	//exit
	if(exit){
		gamestate=0;
		save();
	}

}
