void drawsplashscreen(){
#ifndef PS3

	set2dcamera(0,screenh,0,screenw);

	float texturecoords[]={
		0,				480.f/512.f,
		640.f/1024.f,	480.f/512.f,
		640.f/1024.f,	0,
		0,				0,};

	#ifdef GX
	GX_LoadTexObj(&splashscreen_GXTexObj, GX_TEXMAP0);
	#endif

	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,splashscreen);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	draw2dquad(0,0,screenw,screenh,texturecoords,0,0);

	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

#endif
}
