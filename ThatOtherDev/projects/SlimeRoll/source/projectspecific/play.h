void play(float gamespeed){

	//get input
	float inputspeed=0;
	float inputangle=0;
	bool spinleft=0;
	bool spinright=0;
	bool zoomin=0;
	bool zoomout=0;
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
		if(BTN_SELECT[0]==2)exit=1;
	#endif

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

	//calculate gravity
	float gravmovex=cos(cama+radiansindegree*90.f)*0.5f;
	float gravmovey=sin(cama+radiansindegree*90.f)*0.5f;

	//update entities
	for(int a=0;a<entitycount;a++){
		//keep track of removed entities
		bool removed=0;
		//update the slime
		if(entitylist[a].type==entitytype_slime){
			//keep track of the starting position
			float oldposx=entitylist[a].posx;
			float oldposy=entitylist[a].posy;
			//lose momentum
			entitylist[a].movx-=entitylist[a].movx*0.2f*gamespeed;
			entitylist[a].movy-=entitylist[a].movy*0.2f*gamespeed;
			//get pushed by gravity
			entitylist[a].movx+=gravmovex*gamespeed;
			entitylist[a].movy+=gravmovey*gamespeed;
			//bump into walls and other slimes
			for(int b=0;b<entitycount;b++)if(a!=b){
				float correctdistance=entitylist[a].size+entitylist[b].size;
				if(entitylist[a].posx<entitylist[b].posx+correctdistance
				&& entitylist[a].posx>entitylist[b].posx-correctdistance
				&& entitylist[a].posy<entitylist[b].posy+correctdistance
				&& entitylist[a].posy>entitylist[b].posy-correctdistance){
					float distance=dist2d(
						entitylist[a].posx,entitylist[a].posy,
						entitylist[b].posx,entitylist[b].posy);
					if(distance<correctdistance){
						//float angle=atan2(
						//	entitylist[a].posy-entitylist[b].posy,
						//	entitylist[a].posx-entitylist[b].posx);
						float xspeed=entitylist[a].posx-entitylist[b].posx;
						float yspeed=entitylist[a].posy-entitylist[b].posy;
						float total=posfloat(xspeed)+posfloat(yspeed);
						if(entitylist[b].type==entitytype_slime){
							distance=(correctdistance-distance)*0.01f*gamespeed;
							//entitylist[a].movx+=cos(angle)*distance;
							//entitylist[a].movy+=sin(angle)*distance;
							//entitylist[b].movx-=cos(angle)*distance;
							//entitylist[b].movy-=sin(angle)*distance;
							xspeed=xspeed/total*distance;
							yspeed=yspeed/total*distance;
							entitylist[a].movx+=xspeed;
							entitylist[a].movy+=yspeed;
							entitylist[b].movx-=xspeed;
							entitylist[b].movy-=yspeed;
						}
						if(entitylist[b].type==entitytype_wall){
							distance=(correctdistance-distance)*0.175f*gamespeed;
							//entitylist[a].movx+=cos(angle)*distance;
							//entitylist[a].movy+=sin(angle)*distance;
							entitylist[a].movx+=xspeed/total*distance;
							entitylist[a].movy+=yspeed/total*distance;
						}
						if(entitylist[b].type==entitytype_goal){
							entitylist[b].type=entitytype_slime;
							entitytypecount[entitytype_slime]+=1;
							entitytypecount[entitytype_goal]-=1;
						}
					}
				}
			}
			//get moved by momentum
			entitylist[a].posx+=entitylist[a].movx*gamespeed;
			entitylist[a].posy+=entitylist[a].movy*gamespeed;
			//adjust momentum
			entitylist[a].movx=(entitylist[a].posx-oldposx)/gamespeed;
			entitylist[a].movy=(entitylist[a].posy-oldposy)/gamespeed;
		//we have run out of types to update
		}
		//we dont do any of the final updating if they were removed
		if(removed){
			a-=1;
		}else{
		}
	}

	//exit
	if(exit){
		gamestate=0;
	}

}
