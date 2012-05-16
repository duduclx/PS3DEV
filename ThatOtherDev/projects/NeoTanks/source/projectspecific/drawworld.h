void drawworld(){

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	//set the camera
	set3dcamera(
		camxpos,camypos,camzpos,
		-camxang,
		camyang+90.f*radiansindegree,
		camzang,
		45.f,screena,0.1f,1000.f);

	//load the texture
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,worldtexture);
	#endif
	#ifdef GX
	GX_LoadTexObj(&worldtexture_GXTexObj,GX_TEXMAP0);
	#endif
	#ifdef RSX
	usetexture(worldtexture_image);
	#endif

	//draw the ground
	for(int x=0; x<40; x++)for(int z=0; z<40; z++){
		savecammatrix();
		translatecam(((float)x-20.f)*0.5f,0.f,((float)z-20.f)*0.5f);
		draw3dtrianglemesh(
			floorgridtilevertexcount,&floorgridtilevertexarray[0],&floorgridtiletexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//draw red tanks
	for(int a=0; a<redtankcount; a++){
		savecammatrix();
		translatecam(redtanklist[a].x,redtanklist[a].y,redtanklist[a].z);
		rotatecam(90.f-redtanklist[a].ba*degreesinradian,0,1,0);
		draw3dtrianglemesh(
			tankbottomvertexcount,&tankbottomvertexarray[0],&redtankbottomtexturearray[0],NULL,NULL);
		loadcammatrix();
		savecammatrix();
		translatecam(redtanklist[a].x,redtanklist[a].y,redtanklist[a].z);
		rotatecam(90.f-redtanklist[a].ta*degreesinradian,0,1,0);
		draw3dtrianglemesh(
			tanktopvertexcount,&tanktopvertexarray[0],&redtanktoptexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//draw blue tanks
	for(int a=0; a<bluetankcount; a++){
		savecammatrix();
		translatecam(bluetanklist[a].x,bluetanklist[a].y,bluetanklist[a].z);
		rotatecam(90.f-bluetanklist[a].ba*degreesinradian,0,1,0);
		draw3dtrianglemesh(
			tankbottomvertexcount,&tankbottomvertexarray[0],&tankbottomtexturearray[0],NULL,NULL);
		loadcammatrix();
		savecammatrix();
		translatecam(bluetanklist[a].x,bluetanklist[a].y,bluetanklist[a].z);
		rotatecam(90.f-bluetanklist[a].ta*degreesinradian,0,1,0);
		draw3dtrianglemesh(
			tanktopvertexcount,&tanktopvertexarray[0],&tanktoptexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//draw blasts
	for(int a=0; a<blastcount; a++){
		savecammatrix();
		translatecam(blastlist[a].x,blastlist[a].y,blastlist[a].z);
		scalecam(0.0015f,0.0015f,0.0015f);
		draw3dtrianglemesh(
			spherevertexcount,&spherevertexarray[0],&spheretexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//draw explosions
	for(int a=0; a<explosioncount; a++)
	if(explosionlist[a].a==1){
		savecammatrix();
		translatecam(explosionlist[a].x,explosionlist[a].y,explosionlist[a].z);
		scalecam(0.05f*explosionlist[a].s,0.05f*explosionlist[a].s,0.05f*explosionlist[a].s);
		draw3dtrianglemesh(
			spherevertexcount,&spherevertexarray[0],&spheretexturearray[0],NULL,NULL);
		loadcammatrix();
	}

	//hud
	if(gamestate==1){
		#ifdef OPENGL
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		#endif
		set2dcamera(0,500.f,0,500.f*screena);
		//int font=rand()%2;
		//drawtextcenteraligned(font,250.f*screena,200.f,(char*)"NeoTanks",1.5f);
		//drawtextcenteraligned(font,250.f*screena,275.f,(char*)"press X to play",0.5f);
		//int font=0;
		//drawblackbox(0,395,500.f*screena,75);
		//drawtext(font,35.f,375.f,(char*)"NeoTanks",1.5f);
		//drawtext(font,35.f,445.f,(char*)" press X to play",0.5f);
		int font=0;
		drawblackbox(0,445,500.f*screena,textysize*0.5f);
		drawtext(font,35.f,445.f,(char*)"Neo Tanks - press X to play",0.5f);
		#ifdef OPENGL
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		#endif
	}

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
