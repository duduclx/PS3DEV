void draw2dcircle(float x,float y,float radius,int sides){
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

	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	#endif

	//draw the background
	set2dcamera(-350.f,350.f,-350.f*screena,350.f*screena);
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

	set2dcamera(-1.f,1.f,-1.f*screena,1.f*screena);

	for(int a=0;a<wallcount;a++)draw2dquad(
		walllist[a].x,
		-walllist[a].y-walllist[a].h,
		walllist[a].w,
		walllist[a].h,
		blacktexturecoords,
		0,0.f);

	draw2dquad(
		-1.f*screena,
		-1.f,
		1.f*screena-0.9f,
		2.f,
		blacktexturecoords,
		0,0.f);

	draw2dquad(
		0.9f,
		-1.f,
		1.f*screena-0.9f,
		2.f,
		blacktexturecoords,
		0,0.f);

	draw2dcircle(
		youx,
		-youy,
		yousize,
		40);

	//draw the scores
	set2dcamera(-350.f,350.f,-350.f*screena,350.f*screena);
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
