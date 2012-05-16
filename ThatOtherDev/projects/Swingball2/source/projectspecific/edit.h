int spawntype=0;

void edit(float gamespeed){

	//get input
	float inputspeed=0;
	float inputangle=0;
	bool spawn=0,spawntypeup=0,spawntypedown=0;
	bool saveandexit=0;
	#ifdef WIN
		bool up=0,down=0,left=0,right=0;
		if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
		if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
		if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
		if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
		inputangle=atan2((float)right-(float)left,(float)up-(float)down)-90.f*radiansindegree;
		inputspeed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
		if(inputspeed>1)inputspeed=1;
		aimx=((float)(cursorx[0])/screenw)*2.f-1.f;
		aimy=((float)(cursory[0])/screenh)*2.f-1.f;
		if(aimx<-1)aimx=-1;if(aimx>1)aimx=1;
		if(aimy<-1)aimy=-1;if(aimy>1)aimy=1;
		aiminworldx=camx+aimx*camz*0.5f*screena;
		aiminworldy=camy+aimy*camz*0.5f;
		if(mousestate[SDL_BUTTON_LEFT])spawn=1;
		if(keystate[SDLK_e]==2)spawntypeup=1;
		if(keystate[SDLK_q]==2)spawntypedown=1;
		if(keystate[SDLK_b]==2)saveandexit=1;
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
		aiminworldx=aiminworldx*0.75f+(camx+aimx*5.75f)*0.25f;
		aiminworldy=aiminworldy*0.75f+(camy+aimy*5.75f)*0.25f;
		if(BTN_R1[0])spawn=1;
		if(BTN_UP[0]==2 || BTN_RIGHT[0]==2)spawntypeup=1;
		if(BTN_DOWN[0]==2 || BTN_LEFT[0]==2)spawntypedown=1;
		if(BTN_CIRCLE[0]==2)saveandexit=1;
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
		if(WiiButtonsHeld[0] & WPAD_BUTTON_A)spawn=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_UP)spawntypeup=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_DOWN)spawntypedown=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_RIGHT)spawntypeup=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_LEFT)spawntypedown=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_B)saveandexit=1;
		
	#endif

	//update camera
	camx+=cos(inputangle)*inputspeed*0.1f*gamespeed;
	camy+=sin(inputangle)*inputspeed*0.1f*gamespeed;
	camz=12.5f;

	spawntype+=(int)spawntypeup-(int)spawntypedown;
	while(spawntype<0)spawntype+=12;
	while(spawntype>11)spawntype-=12;

	if(spawn){
		int x=(int)floor(aiminworldx);
		int y=(int)floor(aiminworldy);
		if(x>=0 && x<mapsizex && y>=0 && y<mapsizey)map[x][y]=spawntype;
	}

	if(saveandexit){
		savelevel(currentlevelnumber);
		gamestate=gamestate_titlescreen;
	}

}

void drawworldeditor(){

	//set the camera
	set2dcamera(
		camy-camz*0.5f,
		camy+camz*0.5f,
		camx-camz*0.5f*screena,
		camx+camz*0.5f*screena);

	//background
	draw2dquad(
		camx-camz*screena*0.5f,
		camy-camz*0.5f,
		camz*screena,
		camz,
		backgroundtexturecoords,0,0.f);

	//background map tiles
	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++){
		if(map[x][y]==maptype_blocknormal)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			blocknormaltexturecoords,0,0.f);
		if(map[x][y]==maptype_blockharmful)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			blockharmfultexturecoords,0,0.f);
		if(map[x][y]==maptype_blocknoswing)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			blocknoswingtexturecoords,0,0.f);
		if(map[x][y]==maptype_blockghost)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			blockghosttexturecoords,0,0.f);
		if(map[x][y]==maptype_gravitydown)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			gravitydowntexturecoords,0,0.f);
		if(map[x][y]==maptype_gravityleft)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			gravitylefttexturecoords,0,0.f);
		if(map[x][y]==maptype_gravityup)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			gravityuptexturecoords,0,0.f);
		if(map[x][y]==maptype_gravityright)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			gravityrighttexturecoords,0,0.f);
		if(map[x][y]==maptype_playerspawn)draw2dquad(
			(float)x+0.5f,(float)y+0.5f,1.2f*1.175f,1.2f*1.175f,
			balltexturecoords,1,0.f);
		if(map[x][y]==maptype_extratime)draw2dquad(
			(float)x+0.5f,(float)y+0.5f,0.75f,0.75f,
			extratimetexturecoords,1,0.f);
		if(map[x][y]==maptype_finish)draw2dquad(
			(float)x+0.5f,(float)y+0.5f,3.25f,3.25f,
			finishtexturecoords,1,0.f);
	}

	//cursor
	draw2dquad(
		aiminworldx,aiminworldy,2.25f,2.25f,
		reticletexturecoords,1,0.f);

	//on screen text
	set2dcamera(
		0.f-400.f,
		0.f+400.f,
		0.f-400.f*screena,
		0.f+400.f*screena);
	if(1){
		char text[256];
		if(spawntype==0)sprintf(text,"%s","maptype_nothing");
		if(spawntype==1)sprintf(text,"%s","maptype_blocknormal");
		if(spawntype==2)sprintf(text,"%s","maptype_blockharmful");
		if(spawntype==3)sprintf(text,"%s","maptype_blocknoswing");
		if(spawntype==4)sprintf(text,"%s","maptype_blockghost");
		if(spawntype==5)sprintf(text,"%s","maptype_gravitydown");
		if(spawntype==6)sprintf(text,"%s","maptype_gravityleft");
		if(spawntype==7)sprintf(text,"%s","maptype_gravityup");
		if(spawntype==8)sprintf(text,"%s","maptype_gravityright");
		if(spawntype==9)sprintf(text,"%s","maptype_playerspawn");
		if(spawntype==10)sprintf(text,"%s","maptype_extratime");
		if(spawntype==11)sprintf(text,"%s","maptype_finish");
		float posx=-450.f;
		float posy=-350.f;
		button(posx,posy,900.f,25.f,0);
		drawtext(posx-5.f,posy-7.5f,(char*)text,0.65f);
	}
	if(1){
		char text[256];
		#ifdef PS3
		sprintf(text,"%s","Press Circle to save and go back");
		#else
		sprintf(text,"%s","Press B to save and go back");
		#endif
		float posx=-450.f;
		float posy=350.f-25.f;
		button(posx,posy,900.f,25.f,0);
		drawtext(posx-5.f,posy-7.5f,(char*)text,0.65f);
	}

}
