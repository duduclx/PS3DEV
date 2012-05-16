void drawworld(){

	//prep for rotation
	float camacos=cos(-cama-radiansindegree*90.f);
	float camasin=sin(-cama-radiansindegree*90.f);
	float rotatedcamx=camx*camasin+camy*camacos;
	float rotatedcamy=camx*camacos-camy*camasin;

	//set the camera
	set2dcamera(
		rotatedcamy-camz*0.5f,
		rotatedcamy+camz*0.5f,
		rotatedcamx-camz*0.5f*screena,
		rotatedcamx+camz*0.5f*screena);

	//draw the background
	draw2dquad(
		rotatedcamx-camz*0.5f*screena,
		rotatedcamy-camz*0.5f,
		camz*screena,
		camz,
		backgroundtexturecoords,0,0.f);

	//draw entities
	for(int a=0;a<entitycount;a++)if(entitylist[a].type==entitytype_goal)draw2dquad(
		entitylist[a].posx*camasin+entitylist[a].posy*camacos,
		entitylist[a].posx*camacos-entitylist[a].posy*camasin,
		(entitylist[a].size*2.f)*126.f/110.f,
		(entitylist[a].size*2.f)*126.f/110.f,
		texturecoords[3],
		1,0.f);
	for(int a=0;a<entitycount;a++)if(entitylist[a].type==entitytype_slime)draw2dquad(
		entitylist[a].posx*camasin+entitylist[a].posy*camacos,
		entitylist[a].posx*camacos-entitylist[a].posy*camasin,
		(entitylist[a].size*2.f+10.f)*126.f/110.f,
		(entitylist[a].size*2.f+10.f)*126.f/110.f,
		texturecoords[0],
		1,0.f);
	for(int a=0;a<entitycount;a++)if(entitylist[a].type==entitytype_slime)draw2dquad(
		entitylist[a].posx*camasin+entitylist[a].posy*camacos,
		entitylist[a].posx*camacos-entitylist[a].posy*camasin,
		(entitylist[a].size*2.f+0.f)*126.f/110.f,
		(entitylist[a].size*2.f+0.f)*126.f/110.f,
		texturecoords[1],
		1,0.f);
	for(int a=0;a<entitycount;a++)if(entitylist[a].type==entitytype_wall)draw2dquad(
		entitylist[a].posx*camasin+entitylist[a].posy*camacos,
		entitylist[a].posx*camacos-entitylist[a].posy*camasin,
		(entitylist[a].size*2.f)*126.f/110.f,
		(entitylist[a].size*2.f)*126.f/110.f,
		texturecoords[2],
		1,0.f);

	if(gamestate==2){
		draw2dquad(
			spawnposx*camasin+spawnposy*camacos,
			spawnposx*camacos-spawnposy*camasin,
			highfloat(dist2d(spawnposx,spawnposy,aiminworldx,aiminworldy)*2.f*126.f/110.f,10.f),
			highfloat(dist2d(spawnposx,spawnposy,aiminworldx,aiminworldy)*2.f*126.f/110.f,10.f),
			reticletexturecoords,
			1,0.f);
	}

	//hud
	set2dcamera(-400.f,400.f,-400.f*screena,400.f*screena);
	char temptext[100];
	float textx=50.f-400.f*screena;
	float texty=100.f-400.f;
	#ifdef WIN
	if(gamestate==1)sprintf(temptext,"%s","press BACKSPACE to exit");
	if(gamestate==2)sprintf(temptext,"%s","Press BACKSPACE to save and exit");
	drawtext(textx,texty,(char*)temptext,1.f);texty+=50.f;
	#endif
	#ifdef PS3
	if(gamestate==1)sprintf(temptext,"%s","press SELECT to exit");
	if(gamestate==2)sprintf(temptext,"%s","Press SELECT to save and exit");
	drawtext(textx,texty,(char*)temptext,1.f);texty+=50.f;
	#endif
	if(gamestate==1){
		sprintf(temptext,"%i%s",entitytypecount[entitytype_goal]," blue blobs remaining");
		drawtext(textx,texty,(char*)temptext,1.f);texty+=50.f;
	}

}
