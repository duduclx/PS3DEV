void drawworld(){

	//prep for drawing
	#ifdef GX
	GX_LoadTexObj(&texture_GXTexObj,GX_TEXMAP0);
	#endif
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,texture);
	#endif
	#ifdef RSX
	usetexture(worldtexture_image);
	#endif

	//setup the camera
	set3dcamera(
		camxpos,camypos,camzpos,
		-camxang,camyang+90.f*radiansindegree,camzang,
		50.f,screena,0.1f,1000.f);

	//draw people
	for(int x=highint(0,camxgridpos-viewrange); x<lowint(worldgridsizex,camxgridpos+viewrange+1); x++)
	for(int z=highint(0,camzgridpos-viewrange); z<lowint(worldgridsizez,camzgridpos+viewrange+1); z++)
	for(int a=0; a<personcount[x][z]; a++){
		savecammatrix();
		translatecam(
			personlist[x][z][a].xpos,
			personlist[x][z][a].ypos,
			personlist[x][z][a].zpos);
		rotatecam(-personlist[x][z][a].yang*degreesinradian,0,1,0);
		draw3dtrianglemesh(
			happypeoplevertexcount,happypeoplevertexarray,happypeopletexturearray,NULL,NULL);
		loadcammatrix();
	}

	//draw things
	for(int x=highint(0,camxgridpos-viewrange); x<lowint(worldgridsizex,camxgridpos+viewrange+1); x++)
	for(int z=highint(0,camzgridpos-viewrange); z<lowint(worldgridsizez,camzgridpos+viewrange+1); z++)
	for(int a=0; a<thingcount[x][z]; a++){
		savecammatrix();
		translatecam(
			thinglist[x][z][a].xpos,
			thinglist[x][z][a].ypos,
			thinglist[x][z][a].zpos);
		rotatecam(-thinglist[x][z][a].yang*degreesinradian,0,1,0);
		if(thinglist[x][z][a].type==0)draw3dtrianglemesh(
			ammovertexcount,ammovertexarray,ammotexturearray,NULL,NULL);
		if(thinglist[x][z][a].type==1)draw3dtrianglemesh(
			medkitvertexcount,medkitvertexarray,medkittexturearray,NULL,NULL);
		if(thinglist[x][z][a].type==2)draw3dtrianglemesh(
			blastvertexcount,blastvertexarray,blasttexturearray,NULL,NULL);
		loadcammatrix();
	}
	
	//draw the world
	#ifndef PS3
	for(int x=highint(0,camxgridpos-viewrange); x<lowint(worldgridsizex,camxgridpos+viewrange+1); x++)
	for(int z=highint(0,camzgridpos-viewrange); z<lowint(worldgridsizez,camzgridpos+viewrange+1); z++){
		float xpos=(float)x*worldtilesize-worldtilesize*0.5f;
		float ypos=(float)0*worldtilesize-worldtilesize*0.5f;
		float zpos=(float)z*worldtilesize-worldtilesize*0.5f;
		if(worldgrid[x][z]){//draw walls
			float texturecoords[]={
				0.55f,	0.95f,
				0.95f,	0.95f,
				0.95f,	0.55f,
				0.55f,	0.55f,};
			if(x<camxgridpos && worldgrid[x+1][z]==0){//wall 1
				float verts[]={
					xpos+1*worldtilesize,	ypos+0*worldtilesize,	zpos+0*worldtilesize,
					xpos+1*worldtilesize,	ypos+1*worldtilesize,	zpos+0*worldtilesize,
					xpos+1*worldtilesize,	ypos+1*worldtilesize,	zpos+1*worldtilesize,
					xpos+1*worldtilesize,	ypos+0*worldtilesize,	zpos+1*worldtilesize,};
				draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
			}
			if(x>camxgridpos && worldgrid[x-1][z]==0){//wall 2
				float verts[]={
					xpos+0*worldtilesize,	ypos+0*worldtilesize,	zpos+1*worldtilesize,
					xpos+0*worldtilesize,	ypos+1*worldtilesize,	zpos+1*worldtilesize,
					xpos+0*worldtilesize,	ypos+1*worldtilesize,	zpos+0*worldtilesize,
					xpos+0*worldtilesize,	ypos+0*worldtilesize,	zpos+0*worldtilesize,};
				draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
			}
			if(z<camzgridpos && worldgrid[x][z+1]==0){//wall 3
				float verts[]={
					xpos+1*worldtilesize,	ypos+0*worldtilesize,	zpos+1*worldtilesize,
					xpos+1*worldtilesize,	ypos+1*worldtilesize,	zpos+1*worldtilesize,
					xpos+0*worldtilesize,	ypos+1*worldtilesize,	zpos+1*worldtilesize,
					xpos+0*worldtilesize,	ypos+0*worldtilesize,	zpos+1*worldtilesize,};
				draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
			}
			if(z>camzgridpos && worldgrid[x][z-1]==0){//wall 4
				float verts[]={
					xpos+0*worldtilesize,	ypos+0*worldtilesize,	zpos+0*worldtilesize,
					xpos+0*worldtilesize,	ypos+1*worldtilesize,	zpos+0*worldtilesize,
					xpos+1*worldtilesize,	ypos+1*worldtilesize,	zpos+0*worldtilesize,
					xpos+1*worldtilesize,	ypos+0*worldtilesize,	zpos+0*worldtilesize,};
				draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
			}
		}else{//draw floor and ceiling
			float texturecoords[]={
				0.05f,	0.95f,
				0.45f,	0.95f,
				0.45f,	0.55f,
				0.05f,	0.55f,};
			if(1){//floor
				float verts[]={
					xpos+0*worldtilesize,	0-worldtilesize*0.5,	zpos+1*worldtilesize,
					xpos+1*worldtilesize,	0-worldtilesize*0.5,	zpos+1*worldtilesize,
					xpos+1*worldtilesize,	0-worldtilesize*0.5,	zpos+0*worldtilesize,
					xpos+0*worldtilesize,	0-worldtilesize*0.5,	zpos+0*worldtilesize,};
				draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
			}
			if(1){//ceiling
				float verts[]={
					xpos+0*worldtilesize,	0+worldtilesize*0.5,	zpos+0*worldtilesize,
					xpos+1*worldtilesize,	0+worldtilesize*0.5,	zpos+0*worldtilesize,
					xpos+1*worldtilesize,	0+worldtilesize*0.5,	zpos+1*worldtilesize,
					xpos+0*worldtilesize,	0+worldtilesize*0.5,	zpos+1*worldtilesize,};
				draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
			}
		}
	}
	#endif
	
	//draw the world
	#ifdef PS3
	#define sections	(2)
	for(int x=highint(0,camxgridpos-viewrange); x<lowint(worldgridsizex,camxgridpos+viewrange+1); x++)
	for(int z=highint(0,camzgridpos-viewrange); z<lowint(worldgridsizez,camzgridpos+viewrange+1); z++){
		float xpos=(float)x*worldtilesize-worldtilesize*0.5f;
		float ypos=(float)0*worldtilesize-worldtilesize*0.5f;
		float zpos=(float)z*worldtilesize-worldtilesize*0.5f;
		if(worldgrid[x][z]){//draw walls
			if(x<camxgridpos && worldgrid[x+1][z]==0){//wall 1
				for(int a=0;a<sections;a++)for(int b=0;b<sections;b++){
					float texturecoords[]={
						0.55f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+0),
						0.55f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+1),
						0.55f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+1),
						0.55f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+0),};
					float verts[]={
						xpos+1*worldtilesize,	ypos+(b+0)*worldtilesize/sections,	zpos+(a+0)*worldtilesize/sections,
						xpos+1*worldtilesize,	ypos+(b+1)*worldtilesize/sections,	zpos+(a+0)*worldtilesize/sections,
						xpos+1*worldtilesize,	ypos+(b+1)*worldtilesize/sections,	zpos+(a+1)*worldtilesize/sections,
						xpos+1*worldtilesize,	ypos+(b+0)*worldtilesize/sections,	zpos+(a+1)*worldtilesize/sections,};
					draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
				}
			}
			if(x>camxgridpos && worldgrid[x-1][z]==0){//wall 2
				for(int a=0;a<sections;a++)for(int b=0;b<sections;b++){
					float texturecoords[]={
						0.55f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+0),
						0.55f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+1),
						0.55f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+1),
						0.55f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+0),};
					float verts[]={
						xpos+0*worldtilesize,	ypos+(b+0)*worldtilesize/sections,	zpos+(a+1)*worldtilesize/sections,
						xpos+0*worldtilesize,	ypos+(b+1)*worldtilesize/sections,	zpos+(a+1)*worldtilesize/sections,
						xpos+0*worldtilesize,	ypos+(b+1)*worldtilesize/sections,	zpos+(a+0)*worldtilesize/sections,
						xpos+0*worldtilesize,	ypos+(b+0)*worldtilesize/sections,	zpos+(a+0)*worldtilesize/sections,};
					draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
				}
			}
			if(z<camzgridpos && worldgrid[x][z+1]==0){//wall 3
				for(int a=0;a<sections;a++)for(int b=0;b<sections;b++){
					float texturecoords[]={
						0.55f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+0),
						0.55f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+1),
						0.55f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+1),
						0.55f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+0),};
					float verts[]={
						xpos+(a+1)*worldtilesize/sections,	ypos+(b+0)*worldtilesize/sections,	zpos+1*worldtilesize,
						xpos+(a+1)*worldtilesize/sections,	ypos+(b+1)*worldtilesize/sections,	zpos+1*worldtilesize,
						xpos+(a+0)*worldtilesize/sections,	ypos+(b+1)*worldtilesize/sections,	zpos+1*worldtilesize,
						xpos+(a+0)*worldtilesize/sections,	ypos+(b+0)*worldtilesize/sections,	zpos+1*worldtilesize,};
					draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
				}
			}
			if(z>camzgridpos && worldgrid[x][z-1]==0){//wall sections
				for(int a=0;a<sections;a++)for(int b=0;b<sections;b++){
					float texturecoords[]={
						0.55f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+0),
						0.55f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+1),
						0.55f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+1),
						0.55f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+0),};
					float verts[]={
						xpos+(a+0)*worldtilesize/sections,	ypos+(b+0)*worldtilesize/sections,	zpos+0*worldtilesize,
						xpos+(a+0)*worldtilesize/sections,	ypos+(b+1)*worldtilesize/sections,	zpos+0*worldtilesize,
						xpos+(a+1)*worldtilesize/sections,	ypos+(b+1)*worldtilesize/sections,	zpos+0*worldtilesize,
						xpos+(a+1)*worldtilesize/sections,	ypos+(b+0)*worldtilesize/sections,	zpos+0*worldtilesize,};
					draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
				}
			}
		}else{//draw floor and ceiling
			if(1){//floor
				for(int a=0;a<sections;a++)for(int b=0;b<sections;b++){
					float texturecoords[]={
						0.05f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+1),
						0.05f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+1),
						0.05f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+0),
						0.05f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+0),};
					float verts[]={
						xpos+(a+0)*worldtilesize/sections,	0-worldtilesize*0.5,	zpos+(b+1)*worldtilesize/sections,
						xpos+(a+1)*worldtilesize/sections,	0-worldtilesize*0.5,	zpos+(b+1)*worldtilesize/sections,
						xpos+(a+1)*worldtilesize/sections,	0-worldtilesize*0.5,	zpos+(b+0)*worldtilesize/sections,
						xpos+(a+0)*worldtilesize/sections,	0-worldtilesize*0.5,	zpos+(b+0)*worldtilesize/sections,};
					draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
				}
			}
			if(1){//ceiling
				for(int a=0;a<sections;a++)for(int b=0;b<sections;b++){
					float texturecoords[]={
						0.05f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+0),
						0.05f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+0),
						0.05f+0.4f/sections*(a+1),	0.55f+0.4f/sections*(b+1),
						0.05f+0.4f/sections*(a+0),	0.55f+0.4f/sections*(b+1),};
					float verts[]={
						xpos+(a+0)*worldtilesize/sections,	0+worldtilesize*0.5,	zpos+(b+0)*worldtilesize/sections,
						xpos+(a+1)*worldtilesize/sections,	0+worldtilesize*0.5,	zpos+(b+0)*worldtilesize/sections,
						xpos+(a+1)*worldtilesize/sections,	0+worldtilesize*0.5,	zpos+(b+1)*worldtilesize/sections,
						xpos+(a+0)*worldtilesize/sections,	0+worldtilesize*0.5,	zpos+(b+1)*worldtilesize/sections,};
					draw3dquadmesh(4,verts,texturecoords,NULL,NULL);
				}
			}
		}
	}
	#endif

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	#endif

}
