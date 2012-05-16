void drawsplashscreen(){
#ifdef WII

	float texturecoords[]={
		0,				480.f/512.f,
		640.f/1024.f,	480.f/512.f,
		640.f/1024.f,	0,
		0,				0,};

	set2dcamera(0,screenh,0,screenw);

	GX_LoadTexObj(&splashscreen_GXTexObj, GX_TEXMAP0);

	draw2dquad(0,0,screenw,screenh,texturecoords,0,0);

#endif
}
