void drawworld(){

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	//setup the camera
	set3dcamera(
		camxpos,camypos,camzpos,
		-camxang,camyang+90.f*radiansindegree,camzang,
		50,screena,0.1f,10000.f);

	//Calculate the frustum for culling
	#ifdef OPENGL
	CFrustum g_Frustum;
	g_Frustum.CalculateFrustum();
	#endif

	//use the world texture
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,worldtexture);
	#endif
	#ifdef GX
	GX_LoadTexObj(&worldtexture_GXTexObj,GX_TEXMAP0);
	#endif
	#ifdef RSX
	usetexture(worldtexture_image);
	#endif

	#ifndef PS3
	//draw the sky
	savecammatrix();
	translatecam(
		worldgridsizex*worldtilesize*0.5f-worldtilesize*0.5f,
		(worldgridsizex+worldgridsizez)*worldtilesize*0.25f-worldtilesize*2.f,
		worldgridsizez*worldtilesize*0.5f-worldtilesize*0.5f);
	draw3dtrianglemesh(skyvertexcount,&skyvertexarray[0],&skytexturearray[0],NULL,NULL);
	loadcammatrix();

	//draw the large scale water
	float watervertexarray[]={-5,-7,5,5,-7,5,5,-7,-5,5,-7,-5,-5,-7,-5,-5,-7,5,};
	float watertexturearray[]={0.375,0.875,0.5,0.875,0.5,1,0.5,1,0.375,1,0.375,0.875,};
	float scalex=worldgridsizex;
	float scalez=worldgridsizez;
	for(int a=0;a<6;a++){
		watervertexarray[a*3+0]*=scalex;
		watervertexarray[a*3+2]*=scalez;
		watertexturearray[a*2+1]*=-1;
	}
	savecammatrix();
	translatecam(
		worldgridsizex*worldtilesize*0.5f-worldtilesize*0.5f,
		-worldtilesize,
		worldgridsizez*worldtilesize*0.5f-worldtilesize*0.5f);
	draw3dtrianglemesh(6,&watervertexarray[0],&watertexturearray[0],NULL,NULL);
	loadcammatrix();
	#endif

	//draw the game world
	for(int x=highint(0,playerxgridpos-worldviewrange); x<lowint(worldgridsizex,playerxgridpos+worldviewrange+1); x++)
	for(int z=highint(0,playerzgridpos-worldviewrange); z<lowint(worldgridsizez,playerzgridpos+worldviewrange+1); z++)
	if(dist2d(x,z,playerxgridpos,playerzgridpos)<worldviewrange){
		#ifdef OPENGL
		glColor4f(worldgridcolor[x][z][0],worldgridcolor[x][z][1],worldgridcolor[x][z][2],1);
		#endif
		for(int y=0; y<worldgridsizey; y++)
		#ifdef OPENGL
		if(g_Frustum.CubeInFrustum(x*worldtilesize,y*worldtilesize,z*worldtilesize,worldtilesize))
		#endif
		{
			int a=(int)worldgrid[x][y][z][0];
			if(a>0){
				int b=(int)worldgrid[x][y][z][1];
				savecammatrix();
				translatecam(x*worldtilesize,y*worldtilesize,z*worldtilesize);
				#ifdef GX
				GX_Begin(GX_TRIANGLES,GX_VTXFMT0,tilevertexcount[a]);	
				for(int c=0; c<tilevertexcount[a]; a++){
					GX_Position3f32(
						tilevertexarray[a][b][c*3+0],
						tilevertexarray[a][b][c*3+1],
						tilevertexarray[a][b][c*3+2]);
					GX_Color3f32(
						worldgridcolor[x][z][0],
						worldgridcolor[x][z][1],
						worldgridcolor[x][z][2]);
					GX_TexCoord2f32(
						tiletexturearray[a][c*2+0],
						tiletexturearray[a][c*2+1]);
				}
				GX_End();
				#else
				draw3dtrianglemesh(tilevertexcount[a],&tilevertexarray[a][b][0],&tiletexturearray[a][0],NULL,NULL);
				#endif
				loadcammatrix();
			}
		}
	}
	#ifdef OPENGL
	glColor4f(1,1,1,1);
	#endif

	//draw the player
	float *tempvertexarray=(float*)malloc(hero_defaultvertexcount*3*sizeof(float));
	for(int a=0; a<hero_defaultvertexcount*3; a++)
		tempvertexarray[a]=
			herovertexarray[playerlastframe][a]*(1.f-playerframeprogress)+
			herovertexarray[playernextframe][a]*(playerframeprogress);
	savecammatrix();
	translatecam(playerxpos,playerypos,playerzpos);
	rotatecam(-playeryang*degreesinradian,0,1,0);
	draw3dtrianglemesh(hero_defaultvertexcount,&tempvertexarray[0],&hero_defaulttexturearray[0],NULL,NULL);
	loadcammatrix();
	free(tempvertexarray);

	//draw people
	for(int x=highint(0,playerxgridpos-peopleviewrange); x<lowint(worldgridsizex,playerxgridpos+peopleviewrange+1); x++)
	for(int z=highint(0,playerzgridpos-peopleviewrange); z<lowint(worldgridsizez,playerzgridpos+peopleviewrange+1); z++)
	if(dist2d(x,z,playerxgridpos,playerzgridpos)<worldviewrange)for(int b=0; b<personcount[x][z]; b++){
		if(personlist[x][z][b].type==persontype_zombie){
			savecammatrix();
			translatecam(personlist[x][z][b].xpos,personlist[x][z][b].ypos,personlist[x][z][b].zpos);
			rotatecam(-personlist[x][z][b].yang*degreesinradian,0,1,0);
			draw3dtrianglemesh(zombie_defaultvertexcount,&zombievertexarray[(int)(personlist[x][z][b].frame*(float)aniframes)][0],&zombie_defaulttexturearray[0],NULL,NULL);
			loadcammatrix();
		}else if(personlist[x][z][b].type==persontype_bigmonster){
			savecammatrix();
			translatecam(personlist[x][z][b].xpos,personlist[x][z][b].ypos,personlist[x][z][b].zpos);
			rotatecam(-personlist[x][z][b].yang*degreesinradian,0,1,0);
			draw3dtrianglemesh(bigmonster_defaultvertexcount,&bigmonstervertexarray[(int)(personlist[x][z][b].frame*(float)aniframes)][0],&bigmonster_defaulttexturearray[0],NULL,NULL);
			loadcammatrix();
		}else if(personlist[x][z][b].type==persontype_robot){
			savecammatrix();
			translatecam(personlist[x][z][b].xpos,personlist[x][z][b].ypos,personlist[x][z][b].zpos);
			rotatecam(-personlist[x][z][b].yang*degreesinradian,0,1,0);
			draw3dtrianglemesh(robot_defaultvertexcount,&robotvertexarray[(int)(personlist[x][z][b].frame*(float)aniframes)][0],&robot_defaulttexturearray[0],NULL,NULL);
			loadcammatrix();
		}
	}

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
