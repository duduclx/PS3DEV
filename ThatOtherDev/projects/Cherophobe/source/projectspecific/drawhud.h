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

	drawcomicframe(20,30,230,60+textysize);

	//hud text
	char temptext[256];
	int x=30;
	int y=30;

	sprintf(temptext,"%s","ammo:");
	drawtext(x,y,(char*)temptext,1);
	y+=20;
	sprintf(temptext,"%s","health:");
	drawtext(x,y,(char*)temptext,1);
	y+=20;
	sprintf(temptext,"%s","score:");
	drawtext(x,y,(char*)temptext,1);
	y+=20;
	sprintf(temptext,"%s","high score:");
	drawtext(x,y,(char*)temptext,1);
	y+=20;

	x=240;
	y=30;
	sprintf(temptext,"%i",ammo);
	drawtextrightaligned(x,y,(char*)temptext,1);
	y+=20;
	sprintf(temptext,"%i",(int)ceil(health));
	drawtextrightaligned(x,y,(char*)temptext,1);
	y+=20;
	sprintf(temptext,"%i",score);
	drawtextrightaligned(x,y,(char*)temptext,1);
	y+=20;
	sprintf(temptext,"%i",highscore);
	drawtextrightaligned(x,y,(char*)temptext,1);
	y+=20;

	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
