void drawworld(){

	//set the camera
	set2dcamera(
		camy-camz*0.5f,
		camy+camz*0.5f,
		camx-camz*0.5f*screena,
		camx+camz*0.5f*screena);

	int viewrangex=8;
	int viewrangey=6;
	int lowx=highint(0,(int)floor(camx+0.5f)-viewrangex);
	int highx=lowint(mapsizex,(int)floor(camx+0.5f)+viewrangex);
	int lowy=highint(0,(int)floor(camy+0.5f)-viewrangey);
	int highy=lowint(mapsizey,(int)floor(camy+0.5f)+viewrangey);

	//draw the ground
	for(int x=lowx;x<highx;x++)for(int y=lowy;y<highy;y++)
		draw2dquad(
			(float)x+0.5f,
			(float)y+0.5f,
			1.f,
			1.f,
			tilesettexturecoords[(int)map[x][y]],
			1,(float)maprotation[x][y]*90.f*radiansindegree);

	//draw decals
	for(int a=0;a<decalcount;a++){
		#ifdef OPENGL
		glColor4f(1.f,1.f,1.f,(float)a/(float)maxdecalcount); 
		#endif
		draw2dquad(
			decallist[a].posx,
			decallist[a].posy,
			0.75f,0.75f,
			decaltexturecoords[decallist[a].type],
			1,decallist[a].angle);
	}
	#ifdef OPENGL
	glColor4f(1.f,1.f,1.f,1.f); 
	#endif

	//draw reticle
	for(int a=0;a<playercount;a++)draw2dquad(
		aiminworldx[a],
		aiminworldy[a],
		1.5f,
		1.5f,
		reticletexturecoords,
		1,0.f);

	//draw explosions
	for(int a=0;a<explosioncount;a++){
		#ifdef OPENGL
		glColor4f(1.f,1.f,1.f,explosionlist[a].health*0.01f); 
		#endif
		draw2dquad(
			explosionlist[a].posx,
			explosionlist[a].posy,
			2.75f,2.75f,
			explosiontexturecoords,
			1,explosionlist[a].angle);
	}
	#ifdef OPENGL
	glColor4f(1.f,1.f,1.f,1.f); 
	#endif

	//draw shots
	for(int a=0;a<shotcount;a++){
		draw2dquad(
			(shotlist[a].startx+shotlist[a].endx)*0.5f,
			(shotlist[a].starty+shotlist[a].endy)*0.5f,
			dist2d(shotlist[a].startx,shotlist[a].starty,shotlist[a].endx,shotlist[a].endy),
			0.75f,
			flashlinetexturecoords,
			1,shotlist[a].angle);
		draw2dquad(
			shotlist[a].endx,
			shotlist[a].endy,
			2.f,
			2.f,
			flashpointtexturecoords,
			1,shotlist[a].angle);
	}

	//draw rockets
	for(int a=0;a<rocketcount;a++){ 
		draw2dquad(
			rocketlist[a].posx,
			rocketlist[a].posy,
			0.75f,0.75f,
			rockettexturecoords,
			1,rocketlist[a].angle);
	}

	//draw persons
	for(int a=0;a<personcount;a++){
		draw2dquad(
			personlist[a].posx,
			personlist[a].posy,
			0.75f,0.75f,
			persontexturecoords[personlist[a].type],
			1,personlist[a].angle);
	}

	//draw objects
	for(int x=lowx;x<highx;x++)for(int y=lowy;y<highy;y++)
	for(int a=0;a<objectcount[x][y];a++){
		if(objectlist[x][y][a].type==objecttype_car)draw2dquad(
			objectlist[x][y][a].posx,
			objectlist[x][y][a].posy,
			2.f,1.f,
			cartexturecoords,
			1,objectlist[x][y][a].angle);
		if(objectlist[x][y][a].type==objecttype_crate)draw2dquad(
			objectlist[x][y][a].posx,
			objectlist[x][y][a].posy,
			1.f,1.f,
			cratetexturecoords[0],
			1,objectlist[x][y][a].angle);
		if(objectlist[x][y][a].type==objecttype_crateexplosive)draw2dquad(
			objectlist[x][y][a].posx,
			objectlist[x][y][a].posy,
			1.f,1.f,
			cratetexturecoords[1],
			1,objectlist[x][y][a].angle);
		if(objectlist[x][y][a].type==objecttype_cratemedical)draw2dquad(
			objectlist[x][y][a].posx,
			objectlist[x][y][a].posy,
			1.f,1.f,
			cratetexturecoords[2],
			1,objectlist[x][y][a].angle);
		if(objectlist[x][y][a].type==objecttype_crateammo)draw2dquad(
			objectlist[x][y][a].posx,
			objectlist[x][y][a].posy,
			1.f,
			1.f,
			cratetexturecoords[3],
			1,objectlist[x][y][a].angle);
	}

	//draw walls
	for(int x=lowx;x<highx;x++)for(int y=lowy;y<highy;y++)for(int a=0;a<wallcount[x][y];a++)
		draw2dquad(
			walllist[x][y][a].posx-wallbordersize,
			walllist[x][y][a].posy-wallbordersize,
			walllist[x][y][a].sizex+wallbordersize*2.f,
			walllist[x][y][a].sizey+wallbordersize*2.f,
			wallbordertexturecoords,
			0,0.f);
	for(int x=lowx;x<highx;x++)for(int y=lowy;y<highy;y++)for(int a=0;a<wallcount[x][y];a++)
		draw2dquad(
			walllist[x][y][a].posx,
			walllist[x][y][a].posy,
			walllist[x][y][a].sizex,
			walllist[x][y][a].sizey,
			walltexturecoords,
			0,0.f);

	//draw cloud shadows
	#ifndef WII
	#ifndef PS3
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,cloudshadowtexture);
	#endif
	#ifdef RSX
	usetexture(cloudshadowtexture_image);
	#endif
	for(int x=lowx;x<highx+10;x+=10)for(int y=lowy;y<highy+10;y+=10)
		draw2dquad(
			floor((float)x/10.f)*10.f+0.5f,
			floor((float)y/10.f)*10.f+0.5f,
			10.f,
			10.f,
			cloudshadowtexturecoords,
			1,0.f);
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
	#endif
	#ifdef RSX
	usetexture(spritesheettexture_image);
	#endif
	#endif
	#endif

	drawingamehud();

}
