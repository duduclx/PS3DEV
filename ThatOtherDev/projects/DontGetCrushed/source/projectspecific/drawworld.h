void draw2Dcircle(float x,float y,float radius,int sides){
	float verts[200];
	float texturecoords[200];
	verts[0]=x;
	verts[1]=y;
	int i=2;
	for(float angle=0; angle<2*3.14159265; angle+=2*3.14159265/sides){
		verts[i]=x+radius*cos(-angle);i++;
		verts[i]=y+radius*sin(-angle);i++;
	}
	verts[i]=verts[2];i++;
	verts[i]=verts[3];i++;
	for(int a=0;a<i;a++)texturecoords[a]=0.5f;
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,verts);
	glDrawArrays(GL_TRIANGLE_FAN,0,i/2);
	glDisableClientState(GL_VERTEX_ARRAY);*/
	#ifdef OPENGL
	glVertexPointer(2,GL_FLOAT,0,verts);
	glTexCoordPointer(2,GL_FLOAT,0,texturecoords);
	glDrawArrays(GL_TRIANGLE_FAN,0,i/2);
	#endif
	#ifdef RSX
	realityVertexBegin(context,REALITY_TRIANGLE_FAN);{
		for(int a=0;a<i/2;a++){
			realityTexCoord2f(context,texturecoords[a*2],texturecoords[a*2+1]);
			realityVertex4f(context,verts[a*2],verts[a*2+1],0.0,1.0);
		}
	}
	realityVertexEnd(context);
	#endif
}

void drawworld(){

	float worldstart=-350.f*screena;
	float worldend=350.f*screena;
	float floorheight=250.f;

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	//set the camera
	set2dcamera(-350.f,350.f,worldstart,worldend);

	//draw the background
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,whitetexture);
	#endif
	#ifdef RSX
	usetexture(whitetexture_image);
	#endif
	draw2dquad(
		-350.f*screena,
		-350.f,
		700.f*screena,
		700.f,
		whitetexturecoords,
		0,0.f);

	//load the black texture
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,blacktexture);
	#endif
	#ifdef RSX
	usetexture(blacktexture_image);
	#endif

	//draw the bouncing balls
	for(int a=0;a<n_enemys;a++)draw2Dcircle(
		enemys[a].posx,
		enemys[a].posy,
		enemys[a].size,
		40);

	//draw the player
	draw2Dcircle(
		youx,
		floorheight,
		30.f,
		40);
	draw2Dcircle(
		youx,
		floorheight,
		25.f,
		40);

	//draw the ground
	draw2dquad(
		-350.f*screena,
		floorheight,
		700.f*screena,
		700.f-floorheight,
		blacktexturecoords,
		0,0.f);

	//draw the scores
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,fonttexture);
	#endif
	#ifdef RSX
	usetexture(fonttexture_image);
	#endif
	char temptext[256];
	sprintf(temptext,"%s%i","Highscore   ",(int)ceil(highscore));
	drawtext(-300.f*screena,-300.f,(char*)temptext,0.75f);
	sprintf(temptext,"%s%i","Score       ",(int)ceil(score));
	drawtext(-300.f*screena,-250.f,(char*)temptext,0.75f);

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	#endif

}
