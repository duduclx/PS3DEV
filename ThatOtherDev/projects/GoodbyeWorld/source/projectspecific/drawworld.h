void drawworld(){

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	//set the camera
	set2dcamera(
		camy-0.5f,
		camy+0.5f,
		camx-0.5f*screena,
		camx+0.5f*screena);

	//reusable texture coordinates
	float fulltexture[]={0,1,1,1,1,0,0,0,};

	//draw the sky
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,skytexture);
	#endif
	#ifdef RSX
	usetexture(sky_image);
	#endif
	for(int x=-1;x<3;x++)for(int y=-1;y<2;y++)
		draw2dquad((float)x+floor(camx),(float)y+floor(camy),1.f,1.f,fulltexture,1,0);

	//draw the asteroids
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,asteroidtexture);
	#endif
	#ifdef RSX
	usetexture(asteroid_image);
	#endif
	for(int a=0;a<n_asteroids;a++)
		draw2dquad(asteroids[a].posx,asteroids[a].posy,asteroids[a].sizex*2.f,asteroids[a].sizey*2.f,fulltexture,1,asteroids[a].angle);

	//draw the lonely world's plea
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,dontgotexture);
	#endif
	#ifdef RSX
	usetexture(dontgo_image);
	#endif
	draw2dquad(worldposx+0.125f,worldposy-0.125f,0.2f,0.2f,fulltexture,1,0);

	//draw the world
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,worldtexture);
	#endif
	#ifdef RSX
	usetexture(world_image);
	#endif
	draw2dquad(worldposx,worldposy,0.2f,0.2f,fulltexture,1,worldangl);

	//draw the player
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,shiptexture);
	#endif
	#ifdef RSX
	usetexture(ship_image);
	#endif
	draw2dquad(playerposx,playerposy,0.2f,0.2f,fulltexture,1,playerangl+90.f*radiansindegree);

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	#endif

}
