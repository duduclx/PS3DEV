#ifdef SDL
SDL_Rect dash_button_frame[3][9];
#endif
#if defined(OPENGL) || defined(GX) || defined(RSX)
float dash_button_texturecoords[3][9][8];
#endif

void setupdashbutton(){
	#ifdef SDL
	for(int a=0; a<3; a++)for(int b=0; b<3; b++)for(int c=0; c<3; c++){
		dash_button_frame[a][b*3+c].x=b*20+60*a;
		dash_button_frame[a][b*3+c].y=c*20+60;
		dash_button_frame[a][b*3+c].w=20;
		dash_button_frame[a][b*3+c].h=20;
	}
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	for(int a=0; a<3; a++)for(int b=0; b<3; b++)for(int c=0; c<3; c++){
		dashgentexturecoords(dash_button_texturecoords[a][b*3+c],b*20+60*a,c*20+60-1,20,20);
	}
	#endif
}

void dashdrawbutton(int x, int y,int w,int h,int type){
	#ifdef SDL
	if(usesdl){
		SDL_Rect temprect = {0,0,0,0};
		//corners
		apply_surface(x-20,y-20,dash_sprite,screen,&dash_button_frame[type][0]);
		apply_surface(x-20,y+h,dash_sprite,screen,&dash_button_frame[type][2]);
		apply_surface(x+w,y-20,dash_sprite,screen,&dash_button_frame[type][6]);
		apply_surface(x+w,y+h,dash_sprite,screen,&dash_button_frame[type][8]);
		//edge 1
		for(int a=0; a<w/20; a++)
			apply_surface(x+a*20,y+h,dash_sprite,screen,&dash_button_frame[type][5]);
		temprect=dash_button_frame[type][5];
		temprect.w=w-w/20*20;
		apply_surface(x+w/20*20,y+h,dash_sprite,screen,&temprect);
		//edge 2
		for(int a=0; a<w/20; a++)
			apply_surface(x+a*20,y-20,dash_sprite,screen,&dash_button_frame[type][3]);
		temprect=dash_button_frame[type][3];
		temprect.w=w-w/20*20;
		apply_surface(x+w/20*20,y-20,dash_sprite,screen,&temprect);
		//edge 3
		for(int a=0; a<h/20; a++)
			apply_surface(x+w,y+a*20,dash_sprite,screen,&dash_button_frame[type][7]);
		temprect=dash_button_frame[type][7];
		temprect.h=h-h/20*20;
		apply_surface(x+w,y+h/20*20,dash_sprite,screen,&temprect);
		//edge 4
		for(int a=0; a<h/20; a++)
			apply_surface(x-20,y+a*20,dash_sprite,screen,&dash_button_frame[type][1]);
		temprect=dash_button_frame[type][1];
		temprect.h=h-h/20*20;
		apply_surface(x-20,y+h/20*20,dash_sprite,screen,&temprect);
		//insides
		for(int a=0; a<h/20; a++)for(int b=0; b<w/20; b++)
			apply_surface(x+b*20,y+a*20,dash_sprite,screen,&dash_button_frame[type][4]);
		temprect=dash_button_frame[type][4];
		temprect.w=w-w/20*20;
		for(int a=0; a<h/20; a++)
			apply_surface(x+w/20*20,y+a*20,dash_sprite,screen,&temprect);
		temprect=dash_button_frame[type][4];
		temprect.h=h-h/20*20;
		for(int a=0; a<w/20; a++)
			apply_surface(x+a*20,y+h/20*20,dash_sprite,screen,&temprect);
		temprect=dash_button_frame[type][4];
		temprect.w=w-w/20*20;
		temprect.h=h-h/20*20;
		apply_surface(x+w/20*20,y+h/20*20,dash_sprite,screen,&temprect);
	}
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	if(useopengl || usegx){
		y-=1;
		//start
		dashprepdraw();
		//corners
		draw2dquad(x-20,y-20,20,20,dash_button_texturecoords[type][0],0,0);
		draw2dquad(x-20,y+h,20,20,dash_button_texturecoords[type][2],0,0);
		draw2dquad(x+w,y-20,20,20,dash_button_texturecoords[type][6],0,0);
		draw2dquad(x+w,y+h,20,20,dash_button_texturecoords[type][8],0,0);
		//edge 1
		for(int a=0; a<w/20; a++)
			draw2dquad(x+a*20,y+h,20,20,dash_button_texturecoords[type][5],0,0);
		draw2dquad(x+w/20*20,y+h,w-w/20*20,20,dash_button_texturecoords[type][5],0,0);
		//edge 2
		for(int a=0; a<w/20; a++)
			draw2dquad(x+a*20,y-20,20,20,dash_button_texturecoords[type][3],0,0);
		draw2dquad(x+w/20*20,y-20,w-w/20*20,20,dash_button_texturecoords[type][3],0,0);
		//edge 3
		for(int a=0; a<h/20; a++)
			draw2dquad(x+w,y+a*20,20,20,dash_button_texturecoords[type][7],0,0);
		draw2dquad(x+w,y+h/20*20,20,h-h/20*20,dash_button_texturecoords[type][7],0,0);
		//edge 4
		for(int a=0; a<h/20; a++)
			draw2dquad(x-20,y+a*20,20,20,dash_button_texturecoords[type][1],0,0);
		draw2dquad(x-20,y+h/20*20,20,h-h/20*20,dash_button_texturecoords[type][1],0,0);
		//insides
		for(int a=0; a<h/20; a++)for(int b=0; b<w/20; b++)
			draw2dquad(x+b*20,y+a*20,20,20,dash_button_texturecoords[type][4],0,0);
		for(int a=0; a<h/20; a++)
			draw2dquad(x+w/20*20,y+a*20,w-w/20*20,20,dash_button_texturecoords[type][4],0,0);
		for(int a=0; a<w/20; a++)
			draw2dquad(x+a*20,y+h/20*20,20,h-h/20*20,dash_button_texturecoords[type][4],0,0);
		draw2dquad(x+w/20*20,y+h/20*20,w-w/20*20,h-h/20*20,dash_button_texturecoords[type][4],0,0);
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
