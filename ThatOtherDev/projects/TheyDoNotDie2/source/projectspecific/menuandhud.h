void drawtileblack(float posx1,float posy1,float posx2,float posy2){
	draw2dquad(
		posx1,posy1,
		posx2-posx1,posy2-posy1,
		wallbordertexturecoords,
		0,0.f);
}

void drawtilebright(float posx1,float posy1,float posx2,float posy2){
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,tilebrighttexture);
	#endif
	#ifdef RSX
	usetexture(tilebrighttexture_image);
	#endif
	#ifdef GX
	GX_LoadTexObj(&tilebrighttexture_GXTexObj, GX_TEXMAP0);
	#endif
	float scale=1.f/64.f;
	float temptexturecoords[] = {
		posx1*scale,posy2*scale,
		posx2*scale,posy2*scale,
		posx2*scale,posy1*scale,
		posx1*scale,posy1*scale,};
	draw2dquad(
		posx1,posy1,
		posx2-posx1,posy2-posy1,
		temptexturecoords,
		0,0.f);
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
	#endif
	#ifdef RSX
	usetexture(spritesheettexture_image);
	#endif
	#ifdef GX
	GX_LoadTexObj(&spritesheettexture_GXTexObj, GX_TEXMAP0);
	#endif
}

void drawtiledark(float posx1,float posy1,float posx2,float posy2){
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,tiledarktexture);
	#endif
	#ifdef RSX
	usetexture(tiledarktexture_image);
	#endif
	#ifdef GX
	GX_LoadTexObj(&tiledarktexture_GXTexObj, GX_TEXMAP0);
	#endif
	float scale=1.f/64.f;
	float temptexturecoords[] = {
		posx1*scale,posy2*scale,
		posx2*scale,posy2*scale,
		posx2*scale,posy1*scale,
		posx1*scale,posy1*scale,};
	draw2dquad(
		posx1,posy1,
		posx2-posx1,posy2-posy1,
		temptexturecoords,
		0,0.f);
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
	#endif
	#ifdef RSX
	usetexture(spritesheettexture_image);
	#endif
	#ifdef GX
	GX_LoadTexObj(&spritesheettexture_GXTexObj, GX_TEXMAP0);
	#endif
}

void drawprogressbar(float posx1,float posy1,float posx2,float posy2,float border,float progress){
	drawtileblack(posx1-border,posy1-border,posx2+border,posy2+border);
	drawtiledark(posx1,posy1,posx2,posy2);
	progress=posx2*progress+posx1*(1.f-progress);
	drawtilebright(posx1,posy1,progress,posy2);
}

void drawingamehud(){

	//set the camera
	set2dcamera(-400.f,400.f,-400.f*screena,400.f*screena);

	#ifndef WII
		//draw the red borders
		#ifdef OPENGL
		glBindTexture(GL_TEXTURE_2D,borderbloodtexture);
		#endif
		#ifdef RSX
		usetexture(borderbloodtexture_image);
		#endif
		#ifdef GX
		//GX_LoadTexObj(&borderbloodtexture_GXTexObj, GX_TEXMAP0);
		#endif
		float scale=(personlist[0].health*0.0025f*5.92f+1.f);
		if(scale<1.f)scale=1.f;
		draw2dquad(
			0.f,0.f,
			scale*800.f*screena,
			scale*800.f,
			borderbloodtexturecoords,1,0.f);
		//draw the black borders
		#ifdef OPENGL
		glBindTexture(GL_TEXTURE_2D,borderdarknesstexture);
		#endif
		#ifdef RSX
		usetexture(borderdarknesstexture_image);
		#endif
		#ifdef GX
		//GX_LoadTexObj(&borderdarknesstexture_GXTexObj, GX_TEXMAP0);
		#endif
		draw2dquad(
			0.f,0.f,
			800.f*screena,
			800.f,
			borderdarknesstexturecoords,1,0.f);
		//reset the texture
		#ifdef OPENGL
		glBindTexture(GL_TEXTURE_2D,spritesheettexture);
		#endif
		#ifdef RSX
		usetexture(spritesheettexture_image);
		#endif
		#ifdef GX
		GX_LoadTexObj(&spritesheettexture_GXTexObj, GX_TEXMAP0);
		#endif
	#endif

	//draw health and energy bars
	for(int a=0;a<playercount;a++){
		float size=
			(800.f/(float)playercount-100.f/(float)playercount)*screena;
		float offset=
			(50.f/(float)playercount-400.f+800.f/(float)playercount*(float)a)*screena;
		float x1=offset;
		float x2=offset+size;
		drawprogressbar(x1,280.f,x2,310.f,3.f,energy[a]*0.01f);
		drawprogressbar(x1,320.f,x2,350.f,3.f,personlist[a].health*0.01f);
		drawtext(x1,270.f,(char*)"Energy",1.2f);
		drawtext(x1,310.f,(char*)"Health",1.2f);
	}

	char temptext[100];
	float textx=-400.f*screena+50.f;
	float texty=-350.f;

	sprintf(temptext,"%s%i","Most Zombies Killed: ",mostzombieskilled);
	drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	sprintf(temptext,"%s%i","Zombies Killed: ",zombieskilled);
	drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	//sprintf(temptext,"%s%i","Health: ",(int)ceil(personlist[0].health));
	//drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	//sprintf(temptext,"%s%i","Energy: ",(int)ceil(energy));
	//drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	//sprintf(temptext,"%s%i","zombie count: ",persontypecount[persontype_zombie]);
	//drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	//sprintf(temptext,"%s%i","survivor count: ",persontypecount[persontype_survivor]);
	//drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	//sprintf(temptext,"%s%i","total person count: ",personcount);
	//drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	//sprintf(temptext,"%s","Press SELECT to save");
	//drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;
	//sprintf(temptext,"%s","Press START to load");
	//drawtext(textx,texty,(char*)temptext,1.2f);texty+=30.f;

}

int menustate=0;
int menustaterendering=0;

bool menuitem(char* text,bool select){
	float textx=-400.f*screena+50.f;
	float texty=-200.f+30.f*(float)menustaterendering;
	if(menustaterendering==menustate)
		drawtilebright(-400.f*screena,texty,400.f*screena,texty+30.f);
	drawtext(textx,texty,text,1.2f);
	menustaterendering+=1;
	if(menustaterendering==menustate+1){
		return select;
	}else{
		return 0;
	}
}

void menu(){

	//set the camera
	set2dcamera(-400.f,400.f,-400.f*screena,400.f*screena);

	drawtiledark(-400.f*screena,-400.f,400.f*screena,400.f);

	//drawtextcenteraligned(0.f,-300.f,(char*)"They DO Not Die 2",1.5f);
	draw2dquad(0,-300.f,175.f*4.f,175.f,logotexturecoords,1,0.f);

	bool up=0,down=0,select=0;
	#ifdef WII
	#endif
	#ifdef WIN
		if(keystate[SDLK_w]==2|keystate[SDLK_UP]==2)up=1;
		if(keystate[SDLK_s]==2|keystate[SDLK_DOWN]==2)down=1;
		if(keystate[SDLK_SPACE]==2|keystate[SDLK_RETURN]==2)select=1;
	#endif
	#ifdef PS3
		if(BTN_UP[0]==2)up=1;
		if(BTN_DOWN[0]==2)down=1;
		if(BTN_CROSS[0]==2)select=1;
	#endif
	#ifdef WII
		if(WiiButtonsDown[0] & WPAD_BUTTON_UP)up=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_DOWN)down=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_A)select=1;
	#endif

	menustaterendering=0;

	if(gamestate==1)if(menuitem((char*)"Resume",select)){
		gamestate=gamestate_offlineplay;}
	if(menuitem((char*)"Start a new game (1 player)",select)){
		playercount=1;
		startnewgame();
		gamestate=gamestate_offlineplay;}
	if(menuitem((char*)"Start a new game (2 player)",select)){
		playercount=2;
		startnewgame();
		gamestate=gamestate_offlineplay;}
	if(menuitem((char*)"Start a new game (3 player)",select)){
		playercount=3;
		startnewgame();
		gamestate=gamestate_offlineplay;}
	if(menuitem((char*)"Start a new game (4 player)",select)){
		playercount=4;
		startnewgame();
		gamestate=gamestate_offlineplay;}
	if(gamestate==1)if(menuitem((char*)"Save game",select)){
		save();
		gamestate=gamestate_offlineplay;}
	if(menuitem((char*)"Load game",select)){
		load();
		gamestate=gamestate_offlineplay;}

	if(up)menustate-=1;
	if(down)menustate+=1;
	if(menustate<0)menustate=0;
	if(menustate>menustaterendering-1)menustate=menustaterendering-1;

}

