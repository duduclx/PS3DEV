#ifdef SDL
SDL_Rect dash_cursor_frame[5];
#endif
#if defined(OPENGL) || defined(GX) || defined(RSX)
float dash_cursor_texturecoords[5][8];
#endif

bool dashusecursors=0;
bool dashusecursor[4]={0,0,0,0};

void setupdashcursor(){
	#ifdef SDL
	for(int a=0; a<5; a++){
		dash_cursor_frame[a].x=440+a*40;
		dash_cursor_frame[a].y=60;
		dash_cursor_frame[a].w=40;
		dash_cursor_frame[a].h=60;
	}
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	for(int a=0; a<5; a++){
		dashgentexturecoords(dash_cursor_texturecoords[a],440+a*40,60,40,60);
	}
	#endif
}

void dashdrawcursor(int x, int y,int cursornum){
	#ifdef SDL
	if(usesdl){
		apply_surface(
			x-12,
			y-10,
			dash_sprite,
			screen,
			&dash_cursor_frame[cursornum]);
	}
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	if(useopengl || usegx){
		dashprepdraw();
		draw2dquad(
			x-12,y-10,
			40,60,
			dash_cursor_texturecoords[cursornum],0,0);
		dashdonedraw();
	}
	#endif
}

void dashcursors(){
	for(int a=0;a<4;a++)dashusecursor[a]=0;
	#ifdef WII
	for(int a=0;a<4;a++){
		if(ir[a].valid){
			dashusecursor[a]=1;
		}else if(expans[a].type==WPAD_EXP_CLASSIC){
			dashusecursor[a]=1;
			double mag = expans[a].classic.rjs.mag;
			double ang = expans[a].classic.rjs.ang;
			if(mag>0){
				ang=(ang-90)*0.0174532925;
				cursorx[a]+=mag*cos(ang)*15;
				cursory[a]+=mag*sin(ang)*15;
			}
		}
	}
	if(dashusecursors){
		if(wiimoteactive[0] && !wiimoteactive[1] && !wiimoteactive[2] && !wiimoteactive[3]){
			if(dashusecursor[0])dashdrawcursor(cursorx[0],cursory[0],0);
		}else{
			if(dashusecursor[0])dashdrawcursor(cursorx[0],cursory[0],1);
			if(dashusecursor[1])dashdrawcursor(cursorx[1],cursory[1],2);
			if(dashusecursor[2])dashdrawcursor(cursorx[2],cursory[2],3);
			if(dashusecursor[3])dashdrawcursor(cursorx[3],cursory[3],4);
		}
	}
	#endif
	#ifdef WIN
	if(SDL_GetAppState() & SDL_APPMOUSEFOCUS)dashusecursor[0]=1;
	if(dashusecursors){
		if(dashusecursor[0])dashdrawcursor(cursorx[0],cursory[0],0);
	}
	#endif		
	dashusecursors=1;	
}
