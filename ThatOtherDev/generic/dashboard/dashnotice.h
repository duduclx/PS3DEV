#ifdef SDL
SDL_Rect dash_nice_frame;
#endif
#if defined(OPENGL) || defined(GX) || defined(RSX)
float dash_nice_texturecoords[8];
#endif

void setupdashnotice(){
	#ifdef SDL
	for(int a=0; a<2; a++)for(int b=0; b<3; b++)for(int c=0; c<3; c++){
		dash_nice_frame[a][b*3+c].x=b*20+60*a;
		dash_nice_frame[a][b*3+c].y=c*20+60;
		dash_nice_frame[a][b*3+c].w=20;
		dash_nice_frame[a][b*3+c].h=20;
	}
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	for(int a=0; a<2; a++)for(int b=0; b<3; b++)for(int c=0; c<3; c++){
		dashgentexturecoords(dash_nice_texturecoords[a][b*3+c],b*20+60*a,c*20+60,20,20);
	}
	#endif
}

void dashdrawnotice(){
	#ifdef SDL
	if(usesdl){
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	if(useopengl || usegx || usersx){
		//start
		dashprepdraw();
		//corners
		draw2dquad(x-20,y-20,20,20,dash_button_texturecoords[glow][0]);
		draw2dquad(x-20,y+h,20,20,dash_button_texturecoords[glow][2]);
		draw2dquad(x+w,y-20,20,20,dash_button_texturecoords[glow][6]);
		draw2dquad(x+w,y+h,20,20,dash_button_texturecoords[glow][8]);
		//edge 1
		for(int a=0; a<w/20; a++)
			draw2dquad(x+a*20,y+h,20,20,dash_button_texturecoords[glow][5]);
		draw2dquad(x+w/20*20,y+h,w-w/20*20,20,dash_button_texturecoords[glow][5]);
		//edge 2
		for(int a=0; a<w/20; a++)
			draw2dquad(x+a*20,y-20,20,20,dash_button_texturecoords[glow][3]);
		draw2dquad(x+w/20*20,y-20,w-w/20*20,20,dash_button_texturecoords[glow][3]);
		//edge 3
		for(int a=0; a<h/20; a++)
			draw2dquad(x+w,y+a*20,20,20,dash_button_texturecoords[glow][7]);
		draw2dquad(x+w,y+h/20*20,20,h-h/20*20,dash_button_texturecoords[glow][7]);
		//edge 4
		for(int a=0; a<h/20; a++)
			draw2dquad(x-20,y+a*20,20,20,dash_button_texturecoords[glow][1]);
		draw2dquad(x-20,y+h/20*20,20,h-h/20*20,dash_button_texturecoords[glow][1]);
		//insides
		for(int a=0; a<h/20; a++)for(int b=0; b<w/20; b++)
			draw2dquad(x+b*20,y+a*20,20,20,dash_button_texturecoords[glow][4]);
		for(int a=0; a<h/20; a++)
			draw2dquad(x+w/20*20,y+a*20,w-w/20*20,20,dash_button_texturecoords[glow][4]);
		for(int a=0; a<w/20; a++)
			draw2dquad(x+a*20,y+h/20*20,20,h-h/20*20,dash_button_texturecoords[glow][4]);
		draw2dquad(x+w/20*20,y+h/20*20,w-w/20*20,h-h/20*20,dash_button_texturecoords[glow][4]);
		//done
		dashdonedraw();
	}
	#endif
}

bool dashbutton(int x, int y,int w,int h,bool center,bool clickable,char* text){

	bool clicked=0;
	bool glow=0;

	if(center){
		x=x-w/2;
		y=y-h/2;
	}

	#ifdef WIN
	if(clickable
	&& cursorx[0]>x-14 && cursory[0]>y-14 && cursorx[0]<x+w+13 && cursory[0]<y+h+13){
		if(mousestate[SDL_BUTTON_LEFT]==2)clicked=1;
		glow=1;
	}
	#endif

	#ifdef WII
	if(clickable)for(int a=0;a<4;a++){
		if(cursorx[a]>x-14 && cursory[a]>y-14 && cursorx[a]<x+w+13 && cursory[a]<y+h+13){
			if(WiiButtonsDown[a] & WPAD_BUTTON_A)clicked=1;
			if(WiiButtonsDown[a] & WPAD_CLASSIC_BUTTON_A)clicked=1;
			glow=1;
		}
	}
	#endif

	dashdrawbutton(x,y,w,h,glow);

	x=x+w/2;
	y=y+h/2;

	dashtextcenter(x,y-21/2,text);

	return clicked;

}
