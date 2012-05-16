void menu(){

	//hud
	set2dcamera(
		-400.f,400.f,-400.f*screena,400.f*screena);
	draw2dquad(
		-400.f*screena,-400.f,800.f*screena,800.f,
		backgroundtexturecoords,0,0.f);

	draw2dquad(
		-350.f,-350.f,700.f,700.f,
		logotexturecoords,0,0.f);

	char temptext[100];
	float textx=0.f;
	float texty=150.f;
	#ifdef WIN
	sprintf(temptext,"%s","Press SPACE to play");
	drawtextcenteraligned(textx,texty,(char*)temptext,1.f);texty+=50.f;
	sprintf(temptext,"%s","Press ENTER to edit");
	drawtextcenteraligned(textx,texty,(char*)temptext,1.f);texty+=50.f;
	#endif
	#ifdef PS3
	sprintf(temptext,"%s","Press START to play");
	drawtextcenteraligned(textx,texty,(char*)temptext,1.f);texty+=50.f;
	sprintf(temptext,"%s","Press SELECT to edit");
	drawtextcenteraligned(textx,texty,(char*)temptext,1.f);texty+=50.f;
	#endif

	#ifdef WII
	#endif
	#ifdef WIN
		if(keystate[SDLK_SPACE]==2)gamestate=1;
		if(keystate[SDLK_RETURN]==2)gamestate=2;
	#endif
	#ifdef PS3
		if(BTN_START[0]==2)gamestate=1;
		if(BTN_SELECT[0]==2)gamestate=2;
	#endif

	if(gamestate!=0){
		camx=0;
		camy=0;
		cama=0;
		camz=750;
		camxmov=0;
		camymov=0;
		camamov=0;
		camzmov=0;
		aimx=0;
		aimy=0;
		aiminworldx=0;
		aiminworldy=0;
		load();
	}

}
