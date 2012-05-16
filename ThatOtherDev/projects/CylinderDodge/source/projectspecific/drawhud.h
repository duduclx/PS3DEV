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

	int x=20;
	int y=viewsizey-((2-1)*20+textysize)-30;

	#ifdef PS3
	x+=10;
	#endif

	drawcomicframe(x-10,y,230+20,(2-1)*20+textysize);

	char temptext[100];
	
	y+=20;
	sprintf(temptext,"%s","score:");
	drawtext(x,y,(char*)temptext,1);
	y-=20;
	sprintf(temptext,"%s","high score:");
	drawtext(x,y,(char*)temptext,1);
	
	x+=230;
	sprintf(temptext,"%i",highscore);
	drawtextrightaligned(x,y,(char*)temptext,1);
	y+=20;
	sprintf(temptext,"%i",(int)ceil(score));
	drawtextrightaligned(x,y,(char*)temptext,1);

	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
