void button(float posx,float posy,float sizex,float sizey,int glow){
	float edgesize=32.f;
	draw2dquad(
		posx-edgesize,	posy-edgesize,
		edgesize,		edgesize,
		buttontexturecoords[glow][0],0,0.f);
	draw2dquad(
		posx,			posy-edgesize,
		sizex,			edgesize,
		buttontexturecoords[glow][1],0,0.f);
	draw2dquad(
		posx+sizex,		posy-edgesize,
		edgesize,		edgesize,
		buttontexturecoords[glow][2],0,0.f);
	if(sizey>0.f){
		draw2dquad(
			posx-edgesize,	posy,
			edgesize,		sizey,
			buttontexturecoords[glow][3],0,0.f);
		draw2dquad(
			posx,			posy,
			sizex,			sizey,
			buttontexturecoords[glow][4],0,0.f);
		draw2dquad(
			posx+sizex,		posy,
			edgesize,		sizey,
			buttontexturecoords[glow][5],0,0.f);
	}
	draw2dquad(
		posx-edgesize,	posy+sizey,
		edgesize,		edgesize,
		buttontexturecoords[glow][6],0,0.f);
	draw2dquad(
		posx,			posy+sizey,
		sizex,			edgesize,
		buttontexturecoords[glow][7],0,0.f);
	draw2dquad(
		posx+sizex,		posy+sizey,
		edgesize,		edgesize,
		buttontexturecoords[glow][8],0,0.f);
}

void menu(){

	//set the camera
	set2dcamera(
		0.f-400.f,
		0.f+400.f,
		0.f-400.f*screena,
		0.f+400.f*screena);

	//background
	draw2dquad(0.f,0.f,800.f*screena,800.f,backgroundtexturecoords,1,0.f);

	//logo
	draw2dquad(0.f,-300.f,800.f,200.f,logotexturecoords,1,0.f);

	//input
	bool up=0,down=0,select=0,goback=0;
	#ifdef WII
	#endif
	#ifdef WIN
		if(keystate[SDLK_w]==2|keystate[SDLK_UP]==2)up=1;
		if(keystate[SDLK_s]==2|keystate[SDLK_DOWN]==2)down=1;
		if(keystate[SDLK_SPACE]==2|keystate[SDLK_RETURN]==2)select=1;
		if(keystate[SDLK_b]==2)goback=1;
	#endif
	#ifdef PS3
		if(BTN_UP[0]==2)up=1;
		if(BTN_DOWN[0]==2)down=1;
		if(BTN_CROSS[0]==2)select=1;
		if(BTN_CIRCLE[0]==2)goback=1;
	#endif
	#ifdef WII
		if(WiiButtonsDown[0] & WPAD_BUTTON_UP)up=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_DOWN)down=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_A)select=1;
		if(WiiButtonsDown[0] & WPAD_BUTTON_B)goback=1;
	#endif

	//update menustate
	if(up)menustate-=1;
	if(down)menustate+=1;

	if(gamestate==gamestate_titlescreen){
		//limit menu scroll
		if(menustate<0)menustate=0;
		if(menustate>1)menustate=1;
		//select a sub menu
		if(select && menustate==0){
			gamestate=gamestate_menutoplay;
		}
		if(select && menustate==1){
			gamestate=gamestate_menutoedit;
		}
		//draw the menu
		float posx=-450.f;
		float posy=-140.f;
		for(int a=0;a<2;a++){
			if(menustate==a){
				button(posx,posy,900.f,25.f,1);
			}else{
				button(posx,posy,900.f,25.f,0);
			}
			char text[256];
			if(a==0)sprintf(text,"%s","Play");
			if(a==1)sprintf(text,"%s","Edit");
			drawtext(posx-5.f,posy-7.5f,(char*)text,0.65f);
			posy+=70.f;
		}
	}else if(gamestate==gamestate_menutoplay || gamestate==gamestate_menutoedit){
		//just back out
		if(goback==1){
			gamestate=gamestate_titlescreen;
		}
		//limit menu scroll
		if(menustate<menuscroll){
			menuscroll-=1;
			if(menuscroll<0)menuscroll=0;
			menustate=menuscroll;
		}
		if(menustate>menuscroll+5){
			menuscroll+=1;
			if(menuscroll>mapfoundcount-6)menuscroll=mapfoundcount-6;
			menustate=menuscroll+5;
		}
		//select a level
		if(select && gamestate==gamestate_menutoplay && mapfound[menustate]){
			gamestate=gamestate_play;
			startnewgame(menustate+1);
		}
		if(select && gamestate==gamestate_menutoedit && mapfound[menustate]){
			gamestate=gamestate_edit;
			startnewgame(menustate+1);
		}
		//text
		if(gamestate==gamestate_menutoplay)
			drawtext(-450.f,-210.f-7.5f,(char*)"Select a level to play",0.6f);
		if(gamestate==gamestate_menutoedit)
			drawtext(-450.f,-210.f-7.5f,(char*)"Select a level to edit",0.6f);
		#ifdef PS3
		drawtextrightaligned(450.f,280.f-7.5f,(char*)"Press Circle to go back",0.6f);
		#else
		drawtextrightaligned(450.f,280.f-7.5f,(char*)"Press B to go back",0.6f);
		#endif
		//scroll buttons
		if(menuscroll>0)button(0.f+50.f,-210.f,400.f,25.f,0);
		if(menuscroll<mapfoundcount-6)button(-450.f,280.f,400.f,25.f,0);
		//draw the menu
		float posx=-450.f;
		float posy=-140.f;
		for(int a=menuscroll;a<menuscroll+6;a++){
			if(menustate==a){
				button(posx,posy,900.f,25.f,1);
			}else{
				button(posx,posy,900.f,25.f,0);
			}
			char text[256];
			sprintf(text,"%s%i%s%s","Level ",a+1," - ",mapname[a]);
			drawtext(posx-5.f,posy-7.5f,(char*)text,0.65f);
			sprintf(text,"%i",maphighscore[a]);
			drawtextrightaligned(-posx+5.f,posy-7.5f,(char*)text,0.65f);
			posy+=70.f;
		}
	}

}
