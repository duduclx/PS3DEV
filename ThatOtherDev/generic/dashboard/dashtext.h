#ifdef SDL
SDL_Rect dash_text_frame[95];
#endif
#if defined(OPENGL) || defined(GX) || defined(RSX)
float dash_text_texturecoords[95][8];
#endif

void setupdashtext(){
	int a=0;
	#ifdef SDL
	for(int b=0; b<3; b++)for(int c=0; c<32; c++)if(a<95){
		dash_text_frame[a].x=c*20;
		dash_text_frame[a].y=b*20;
		dash_text_frame[a].w=20;
		dash_text_frame[a].h=20;
		a++;
	}
	a=0;
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	for(int b=0; b<3; b++)for(int c=0; c<32; c++)if(a<95){
		dashgentexturecoords(dash_text_texturecoords[a],c*20,b*20,20,20);
		a++;
	}
	#endif
}

void dashtext(int posx,int posy,char* text){
	#ifdef SDL
	if(usesdl){
		for(int a=0;a<(signed)strlen(text);a++){
			apply_surface(
				posx-5,
				posy,
				dash_sprite,
				screen,
				&dash_text_frame[text[a]-' ']);
			posx+=10;
		}
	}
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	if(useopengl || usegx){
		dashprepdraw();
		for(int a=0;a<(signed)strlen(text);a++){
			draw2dquad(
				posx-5,
				posy,
				20,
				20,
				dash_text_texturecoords[text[a]-' '],0,0);
			posx+=10;
		}
		dashdonedraw();
	}
	#endif
}

void dashtextcenter(int posx,int posy,char* text){
	posx-=(int)((float)((signed)strlen(text))*10.f*0.5f);
	dashtext(posx,posy,text);
}

void dashtextright(int posx,int posy,char* text){
	posx-=(int)((float)((signed)strlen(text))*10.f);
	dashtext(posx,posy,text);
}
