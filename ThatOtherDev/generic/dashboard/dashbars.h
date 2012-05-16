#ifdef SDL
SDL_Rect dash_bars_frame[2];
#endif
#if defined(OPENGL) || defined(GX) || defined(RSX)
float dash_bars_texturecoords[2][8];
#endif

char dash_bars_credits[2][256];

char dash_bars_gamename[256];
float dash_bars_gameversion=0;

void setupdashbars(){
	#ifdef SDL
	dash_bars_frame[0].x=0;
	dash_bars_frame[0].y=120;
	dash_bars_frame[0].w=640;
	dash_bars_frame[0].h=68;
	dash_bars_frame[1].x=0;
	dash_bars_frame[1].y=188;
	dash_bars_frame[1].w=640;
	dash_bars_frame[1].h=68;
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	dashgentexturecoords(dash_bars_texturecoords[0],0,120,640,68);
	dashgentexturecoords(dash_bars_texturecoords[1],0,188,640,68);
	#endif
	sprintf(dash_bars_credits[0],"%s","");
	sprintf(dash_bars_credits[1],"%s","ThatOtherDev.com");
}

void dashbars(){

	int trans=dashonslide(0,68);

	#ifdef SDL
	if(usesdl){
		apply_surface(0,-trans,dash_sprite,screen,&dash_bars_frame[0]);
		apply_surface(0,screenh-60+trans,dash_sprite,screen,&dash_bars_frame[1]);
	}
	#endif
	#if defined(OPENGL) || defined(GX) || defined(RSX)
	if(useopengl || usegx){
		dashprepdraw();
		draw2dquad(
			0,-trans,
			screenw,60,
			dash_bars_texturecoords[0],0,0);
		draw2dquad(
			0,screenh-60+trans,
			screenw,60,
			dash_bars_texturecoords[1],0,0);
		dashdonedraw();
	}
	#endif

	dashtext(20,-70-trans+131-43,dash_bars_gamename);
	//if(dash_bars_gameversion || dash_bars_gamename){
	char temptext[256];
	sprintf(temptext,"%s%f","v",dash_bars_gameversion);
	while(strlen(temptext)>2
	&& temptext[strlen(temptext)-2]!='.'
	&& temptext[strlen(temptext)-1]=='0'){
		//temptext[strlen(temptext)-1]=NULL;
		temptext[strlen(temptext)-1]='\0';
	}
	dashtext(20,-70-trans+131-23,temptext);
	//}

	dashtextright(screenw-20,-70-trans+131-43,dash_composedtext_date);
	dashtextright(screenw-20,-70-trans+131-23,dash_composedtext_time);

	dashtext(20,screenh-61+trans+3,(char*)dash_bars_credits[0]);
	dashtext(20,screenh-61+trans+23,(char*)dash_bars_credits[1]);

}
