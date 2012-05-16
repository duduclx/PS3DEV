void drawworld(){

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

	//texture coordinates
	float grasstexture[]={
		13.f/16.f +(1.f/1024),	3.f/16.f -(1.f/1024),
		16.f/16.f -(1.f/1024),	3.f/16.f -(1.f/1024),
		16.f/16.f -(1.f/1024),	0.f/16.f +(1.f/1024),
		13.f/16.f +(1.f/1024),	0.f/16.f +(1.f/1024),
	};
	float treetexture[]={
		5.f/16.f +(1.f/1024),	3.f/16.f -(1.f/1024),
		7.f/16.f -(1.f/1024),	3.f/16.f -(1.f/1024),
		7.f/16.f -(1.f/1024),	0.f/16.f +(1.f/1024),
		5.f/16.f +(1.f/1024),	0.f/16.f +(1.f/1024),
	};
	float chesttexture[]={
		14.f/16.f +(1.f/1024),	4.f/16.f -(1.f/1024),
		15.f/16.f -(1.f/1024),	4.f/16.f -(1.f/1024),
		15.f/16.f -(1.f/1024),	3.f/16.f +(1.f/1024),
		14.f/16.f +(1.f/1024),	3.f/16.f +(1.f/1024),
	};

	float viewrange=6.5f;

	//set the camera
	set2dcamera(
		0-viewrange,
		0+viewrange,
		0-viewrange*screena,
		0+viewrange*screena);

	int lowx=(int)floor(camx)-15;
	if(lowx<0)lowx=0;

	int highx=(int)floor(camx)+15+1;
	if(highx>mapsizex)highx=mapsizex;

	int lowy=(int)floor(camy)-18;
	if(lowy<0)lowy=0;

	int highy=(int)floor(camy)+18+1;
	if(highy>mapsizey)highy=mapsizey;

	//draw the grass
	for(int y=-3;y<4;y++)for(int x=-4;x<5;x++)
		draw2dquad(
			((float)x+floor(camx/3.f)+0.5f)*3.f-camx,
			((float)y+floor(camy/3.f)+0.5f)*3.f-camy,
			3.f,3.f,grasstexture,1,0.f);


	//keep track of what has and hasn't been drawn
	//keep in mind that things out of the cameras view dont need to be drawn
	bool playerdrawn=0;
	for(int a=0;a<thingcount;a++)
	if(thinglist[a].posy>=(float)lowy-0.5f && thinglist[a].posx>=(float)lowx-0.5f
	&& thinglist[a].posy<=(float)highy+0.5f && thinglist[a].posx<=(float)highx+0.5f){
		thinglist[a].drawn=0;
	}else{
		thinglist[a].drawn=1;
	}

	//draw corpses
	for(int a=0;a<thingcount;a++)if(thinglist[a].drawn==0 && thinglist[a].health==0){
		if(thinglist[a].type==thingtype_monster1)draw2dquad(
			thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
			1.f,2.f,monstertexture[0][thinglist[a].frame],1,0.f);
		if(thinglist[a].type==thingtype_monster2)draw2dquad(
			thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
			1.f,2.f,monstertexture[1][thinglist[a].frame],1,0.f);
		if(thinglist[a].type==thingtype_monster3)draw2dquad(
			thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
			1.f,2.f,monstertexture[2][thinglist[a].frame],1,0.f);
		if(thinglist[a].type==thingtype_monster4)draw2dquad(
			thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
			1.f,2.f,monstertexture[3][thinglist[a].frame],1,0.f);
		if(thinglist[a].type==thingtype_monster5)draw2dquad(
			thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
			1.f,2.f,monstertexture[4][thinglist[a].frame],1,0.f);
		thinglist[a].drawn=1;
	}

	//draw everything
	for(int y=lowy;y<highy;y++){
		//draw trees
		for(int x=lowx;x<highx;x++)if(map[x][y]=='t')draw2dquad(
			(float)x-camx,(float)y-camy-1.f,2.f,3.f,treetexture,1,0.f);
		//draw everything else
		for(int a=0;a<thingcount;a++){
			//draw the player
			if(playerdrawn==0 && player.posy<=(float)y+0.6f){
				bool dodraw=1;
				for(int b=0;b<thingcount;b++)if(thinglist[b].drawn==0)
					if(thinglist[b].posy<player.posy-0.1f)dodraw=0;
				if(dodraw==1){
					float sizex=playertexture[player.direction][player.frame][2]-playertexture[player.direction][player.frame][0];
					float sizey=playertexture[player.direction][player.frame][1]-playertexture[player.direction][player.frame][5];
					sizex*=1.f/(1.f/16.f);
					sizey*=1.f/(1.f/16.f);
					draw2dquad(
						player.posx-camx,
						player.posy-camy-0.5f,
						sizex,
						sizey,
						playertexture[player.direction][player.frame],
						1,0.f);
					playerdrawn=1;
				}
			}
			//draw monsters and chests
			if(thinglist[a].drawn==0 && thinglist[a].posy<=(float)y+0.5f){
				bool dodraw=1;
				for(int b=0;b<thingcount;b++)
					if(b!=a && thinglist[b].drawn==0 && thinglist[b].posy<thinglist[a].posy)
						dodraw=0;
				if(dodraw==1){
					if(thinglist[a].type==thingtype_monster1)draw2dquad(
						thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
						1.f,2.f,monstertexture[0][thinglist[a].frame],1,0.f);
					if(thinglist[a].type==thingtype_monster2)draw2dquad(
						thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
						1.f,2.f,monstertexture[1][thinglist[a].frame],1,0.f);
					if(thinglist[a].type==thingtype_monster3)draw2dquad(
						thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
						1.f,2.f,monstertexture[2][thinglist[a].frame],1,0.f);
					if(thinglist[a].type==thingtype_monster4)draw2dquad(
						thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
						1.f,2.f,monstertexture[3][thinglist[a].frame],1,0.f);
					if(thinglist[a].type==thingtype_monster5)draw2dquad(
						thinglist[a].posx-camx,thinglist[a].posy-camy-0.5f,
						1.f,2.f,monstertexture[4][thinglist[a].frame],1,0.f);
					if(thinglist[a].type==thingtype_chest)draw2dquad(
						thinglist[a].posx-camx,thinglist[a].posy-camy,
						1.f,1.f,chesttexture,1,0.f);
					thinglist[a].drawn=1;
					a=0;
				}
			}
		}
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
