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
		camy-camz*0.5f,
		camy+camz*0.5f,
		camx-camz*0.5f*screena,
		camx+camz*0.5f*screena);

	//draw the background
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,othertexture);
	#endif
	#ifdef RSX
	usetexture(othertexture_image);
	#endif
	draw2dquad(
		0.f,
		0.f,
		7.5f,
		7.5f*(1024.f-242.f)/1024.f,
		backgroundtexturecoords,
		1,0.f);

	//draw the player
	for(int playernum=0;playernum<playercount;playernum++){
		if(player[playernum].drawingversion>10.f){
			#ifdef OPENGL
			glBindTexture(GL_TEXTURE_2D,fighter1texture);
			#endif
			#ifdef RSX
			usetexture(fighter1texture_image);
			#endif
		}else{
			#ifdef OPENGL
			glBindTexture(GL_TEXTURE_2D,fighter2texture);
			#endif
			#ifdef RSX
			usetexture(fighter2texture_image);
			#endif
		}
		draw2dquad(
			player[playernum].posx+(0.5f-(float)player[playernum].direction)*0.25f,
			player[playernum].posy,
			1.f,
			1.f,
			fightertexturecoords[player[playernum].direction][player[playernum].frame],
			1,0.f);
	}

	//hud
	set2dcamera(-400.f,400.f,-400.f*screena,400.f*screena);
	#ifdef OPENGL
	glBindTexture(GL_TEXTURE_2D,othertexture);
	#endif
	#ifdef RSX
	usetexture(othertexture_image);
	#endif
	if(playercount>0){
		float temptexture[]={
			0.f/1024.f,		242.f/1024.f,
			381.f/1024.f,	242.f/1024.f,
			381.f/1024.f,	121.f/1024.f,
			0.f/1024.f,		121.f/1024.f,
		};
		float sizex=temptexture[2]-temptexture[0];
		float sizey=temptexture[1]-temptexture[5];
		draw2dquad(
			0.f-sizex*450.f-250.f,
			0.f-sizey*450.f-275.f,
			sizex*900.f,
			sizey*900.f,
			temptexture,0,0.f);
		temptexture[1]-=sizey;
		temptexture[3]-=sizey;
		temptexture[5]-=sizey;
		temptexture[7]-=sizey;
		float progress=player[0].health;
		temptexture[2]=temptexture[0]+sizex*progress;
		temptexture[4]=temptexture[0]+sizex*progress;
		draw2dquad(
			0.f-sizex*450.f-250.f,
			0.f-sizey*450.f-275.f,
			sizex*900.f*progress,
			sizey*900.f,
			temptexture,0,0.f);
	}
	if(playercount>0){
		float temptexture[]={
			0.f/1024.f,		242.f/1024.f,
			381.f/1024.f,	242.f/1024.f,
			381.f/1024.f,	121.f/1024.f,
			0.f/1024.f,		121.f/1024.f,
		};
		float sizex=temptexture[2]-temptexture[0];
		float sizey=temptexture[1]-temptexture[5];
		draw2dquad(
			0.f-sizex*450.f+250.f,
			0.f-sizey*450.f-275.f,
			sizex*900.f,
			sizey*900.f,
			temptexture,0,0.f);
		temptexture[1]-=sizey;
		temptexture[3]-=sizey;
		temptexture[5]-=sizey;
		temptexture[7]-=sizey;
		float progress=player[1].health;
		temptexture[2]=temptexture[0]+sizex*progress;
		temptexture[4]=temptexture[0]+sizex*progress;
		draw2dquad(
			0.f-sizex*450.f+250.f,
			0.f-sizey*450.f-275.f,
			sizex*900.f*progress,
			sizey*900.f,
			temptexture,0,0.f);
	}

	//splashscreen
	if(gamestate==0){
		#ifdef OPENGL
		glBindTexture(GL_TEXTURE_2D,splashscreentexture);
		#endif
		#ifdef RSX
		usetexture(splashscreentexture_image);
		#endif
		float temptexture[]={
			0.f,	1024.f/1024.f,
			1.f,	1024.f/1024.f,
			1.f,	448.f/1024.f,
			0.f,	448.f/1024.f,
		};
		draw2dquad(
			-400.f*(1024.f/448.f),
			-400.f,
			800.f*(1024.f/448.f),
			800.f,
			temptexture,0,0.f);
	}

	//startscreen
	if(gamestate==1){
		if(player[0].health==0.f){
			#ifdef OPENGL
			glBindTexture(GL_TEXTURE_2D,splashscreentexture);
			#endif
			#ifdef RSX
			usetexture(splashscreentexture_image);
			#endif
			float temptexture[]={
				578.f/1024.f+10.f/1024.f,	224.f/1024.f-10.f/1024.f,
				1024.f/1024.f-10.f/1024.f,	224.f/1024.f-10.f/1024.f,
				1024.f/1024.f-10.f/1024.f,	0.f/1024.f+10.f/1024.f,
				578.f/1024.f+10.f/1024.f,	0.f/1024.f+10.f/1024.f,
			};
			float sizex=temptexture[2]-temptexture[0];
			float sizey=temptexture[1]-temptexture[5];
			draw2dquad(
				-sizex*400.f,
				-sizey*400.f,
				sizex*800.f,
				sizey*800.f,
				temptexture,0,0.f);
		}else if(player[1].health==0.f){
			#ifdef OPENGL
			glBindTexture(GL_TEXTURE_2D,splashscreentexture);
			#endif
			#ifdef RSX
			usetexture(splashscreentexture_image);
			#endif
			float temptexture[]={
				578.f/1024.f+10.f/1024.f,	448.f/1024.f-10.f/1024.f,
				1024.f/1024.f-10.f/1024.f,	448.f/1024.f-10.f/1024.f,
				1024.f/1024.f-10.f/1024.f,	224.f/1024.f+10.f/1024.f,
				578.f/1024.f+10.f/1024.f,	224.f/1024.f+10.f/1024.f,
			};
			float sizex=temptexture[2]-temptexture[0];
			float sizey=temptexture[1]-temptexture[5];
			draw2dquad(
				-sizex*400.f,
				-sizey*400.f,
				sizex*800.f,
				sizey*800.f,
				temptexture,0,0.f);
		}else{
			#ifdef OPENGL
			glBindTexture(GL_TEXTURE_2D,splashscreentexture);
			#endif
			#ifdef RSX
			usetexture(splashscreentexture_image);
			#endif
			float temptexture[]={
				0.f/1024.f,		448.f/1024.f,
				578.f/1024.f,	448.f/1024.f,
				578.f/1024.f,	0.f/1024.f,
				0.f/1024.f,		0.f/1024.f,
			};
			float sizex=temptexture[2]-temptexture[0];
			float sizey=temptexture[1]-temptexture[5];
			draw2dquad(
				-sizex*400.f,
				-sizey*400.f,
				sizex*800.f,
				sizey*800.f,
				temptexture,0,0.f);
		}
		if(1){
			#ifdef OPENGL
			glBindTexture(GL_TEXTURE_2D,othertexture);
			#endif
			#ifdef RSX
			usetexture(othertexture_image);
			#endif
			float temptexture[]={
				584.f/1024.f,	121.f/1024.f,
				1024.f/1024.f,	121.f/1024.f,
				1024.f/1024.f,	0.f/1024.f,
				584.f/1024.f,	0.f/1024.f,
			};
			float sizex=temptexture[2]-temptexture[0];
			float sizey=temptexture[1]-temptexture[5];
			draw2dquad(
				-sizex*400.f,
				-sizey*400.f+150.f,
				sizex*800.f,
				sizey*800.f,
				temptexture,0,0.f);
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

}
