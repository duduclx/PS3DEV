void drawhud(){

	float viewsizex=480.f*screena;
	float viewsizey=480.f;

	#ifdef PS3
	viewsizex=550.f*screena;
	viewsizey=550.f;
	#endif

	set2dcamera(0.f,viewsizey,0.f,viewsizex);

	#ifdef GX
	GX_LoadTexObj(&hudtexture_GXTexObj, GX_TEXMAP0);
	#endif
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,hudtexture);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif
	#ifdef RSX
	usetexture(hudtexture_image);
	#endif

	int linesize=17;
	drawcomicframe(20,30,230,(5-1)*linesize+textysize);

	//hud text
	char temptext[100];
	int x=30;
	int y=30+4*linesize;
	
	sprintf(temptext,"%s","energy:");
	drawtext(x,y,(char*)temptext,1);
	y-=linesize;
	sprintf(temptext,"%s","health:");
	drawtext(x,y,(char*)temptext,1);
	y-=linesize;
	sprintf(temptext,"%s","experience:");
	drawtext(x,y,(char*)temptext,1);
	y-=linesize;
	sprintf(temptext,"%s","score:");
	drawtext(x,y,(char*)temptext,1);
	y-=linesize;
	sprintf(temptext,"%s","high score:");
	drawtext(x,y,(char*)temptext,1);
	y-=linesize;

	x=240;
	y=30+4*linesize;

	sprintf(temptext,"%i",(int)ceil(playerenergy));
	drawtextrightaligned(x,y,(char*)temptext,1);
	y-=linesize;
	sprintf(temptext,"%i",(int)ceil(playerhealth));
	drawtextrightaligned(x,y,(char*)temptext,1);
	y-=linesize;
	sprintf(temptext,"%i",experience);
	drawtextrightaligned(x,y,(char*)temptext,1);
	y-=linesize;
	sprintf(temptext,"%i",score);
	drawtextrightaligned(x,y,(char*)temptext,1);
	y-=linesize;
	sprintf(temptext,"%i",highscore);
	drawtextrightaligned(x,y,(char*)temptext,1);
	y-=linesize;

	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
