void drawhud(){

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
	#endif
	#ifdef RSX
	usetexture(spritesheettexture_image);
	#endif
	#ifdef GX
	GX_LoadTexObj(&spritesheettexture_GXTexObj,GX_TEXMAP0);
	GX_SetBlendMode(GX_BM_BLEND,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	#endif

	set2dcamera(0-1.f,0+1.f,0-1.f*screena,0+1.f*screena);

	//exp
	if(1){
		float temptexture[]={
			5.f/16.f +(1.f/1024),	16.f/16.f -(1.f/1024),
			12.f/16.f -(1.f/1024),	16.f/16.f -(1.f/1024),
			12.f/16.f -(1.f/1024),	15.f/16.f +(1.f/1024),
			5.f/16.f +(1.f/1024),	15.f/16.f +(1.f/1024),
		};
		float size=2.5f;
		float sizex=temptexture[2]-temptexture[0];
		float sizey=temptexture[1]-temptexture[5];
		float x=0.f-sizex*size*0.5f;
		float y=0.6f;
		draw2dquad(x,y,sizex*size,sizey*size,temptexture,0,0.f);
		temptexture[1]-=1.f/16.f;
		temptexture[3]-=1.f/16.f;
		temptexture[5]-=1.f/16.f;
		temptexture[7]-=1.f/16.f;
		float progress=(float)(playerexp-playerexplastlevel)/(float)(playerexpnextlevel-playerexplastlevel);
		temptexture[2]=temptexture[0]+sizex*progress;
		temptexture[4]=temptexture[0]+sizex*progress;
		draw2dquad(x,y,sizex*size*progress,sizey*size,temptexture,0,0.f);
		char temptext[100];
		sprintf(temptext,"%s%i%s%i%s%i","Level ",playerlevel," EXP ",playerexp,"/",playerexpnextlevel);
		drawtext(0,x+0.05f,y+0.05f,(char*)temptext,0.003f);
	}

	//health
	if(1){
		float temptexture[]={
			5.f/16.f +(1.f/1024),	16.f/16.f -(1.f/1024),
			12.f/16.f -(1.f/1024),	16.f/16.f -(1.f/1024),
			12.f/16.f -(1.f/1024),	15.f/16.f +(1.f/1024),
			5.f/16.f +(1.f/1024),	15.f/16.f +(1.f/1024),
		};
		float size=2.5f;
		float sizex=temptexture[2]-temptexture[0];
		float sizey=temptexture[1]-temptexture[5];
		float x=0.f-sizex*size*0.5f;
		float y=0.75f;
		draw2dquad(x,y,sizex*size,sizey*size,temptexture,0,0.f);
		temptexture[1]-=2.f/16.f;
		temptexture[3]-=2.f/16.f;
		temptexture[5]-=2.f/16.f;
		temptexture[7]-=2.f/16.f;
		float progress=(float)player.health/(float)playermaxhealth;
		temptexture[2]=temptexture[0]+sizex*progress;
		temptexture[4]=temptexture[0]+sizex*progress;
		draw2dquad(x,y,sizex*size*progress,sizey*size,temptexture,0,0.f);
		char temptext[100];
		sprintf(temptext,"%s%i%s%i","Health ",player.health,"/",playermaxhealth);
		drawtext(0,x+0.05f,y+0.05f,(char*)temptext,0.003f);
	}

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	#endif
	#ifdef GX
	GX_SetAlphaUpdate(GX_FALSE);
	#endif

}

void drawtitlescreen(){

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,spritesheettexture);
	#endif
	#ifdef RSX
	usetexture(spritesheettexture_image);
	#endif
	#ifdef GX
	GX_LoadTexObj(&spritesheettexture_GXTexObj,GX_TEXMAP0);
	GX_SetBlendMode(GX_BM_BLEND,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_CLEAR);
	GX_SetAlphaUpdate(GX_TRUE);
	#endif

	set2dcamera(0-1.f,0+1.f,0-1.f*screena,0+1.f*screena);

	draw2dquad(0.f,-0.2f,6.f*0.3f,3.f*0.3f,logotexture,1,0.f);
	drawtextcenteraligned(1,0.f,0.1f,(char*)"press X to play",0.003f);

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	#endif
	#ifdef GX
	GX_SetAlphaUpdate(GX_FALSE);
	#endif

}
