void drawworld(){

	//set the camera
	set2dcamera(
		camy-camz*0.5f,
		camy+camz*0.5f,
		camx-camz*0.5f*screena,
		camx+camz*0.5f*screena);

	//background
	draw2dquad(
		camx-camz*screena*0.5f,
		camy-camz*0.5f,
		camz*screena,
		camz,
		backgroundtexturecoords,0,0.f);

	//background map tiles
	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++){
		/*if(map[x][y]==maptype_nothing
		|| map[x][y]==maptype_playerspawn
		|| map[x][y]==maptype_extratime
		|| map[x][y]==maptype_finish)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			backgroundtiletexturecoords,0,0.f);*/
		if(map[x][y]==maptype_blockghost)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			blockghosttexturecoords,0,0.f);
		if(map[x][y]==maptype_gravitydown)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			gravitydowntexturecoords,0,0.f);
		if(map[x][y]==maptype_gravityleft)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			gravitylefttexturecoords,0,0.f);
		if(map[x][y]==maptype_gravityup)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			gravityuptexturecoords,0,0.f);
		if(map[x][y]==maptype_gravityright)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			gravityrighttexturecoords,0,0.f);
	}

	//balls
	for(int a=0;a<ballcount;a++)if(balllist[a].type==balltype_finish)draw2dquad(
		balllist[a].posx,balllist[a].posy,
		3.25f,3.25f,finishtexturecoords,1,0.f);
	for(int a=0;a<ballcount;a++)if(balllist[a].type==balltype_glow)draw2dquad(
		balllist[a].posx,balllist[a].posy,
		balllist[a].swinglength,balllist[a].swinglength,glowtexturecoords,1,0.f);
	for(int a=0;a<ballcount;a++)if(balllist[a].type==balltype_extratime)draw2dquad(
		balllist[a].posx,balllist[a].posy,
		0.75f,0.75f,extratimetexturecoords,1,0.f);

	//swing rope
	if(player.swinging){
		float angle=atan2(player.swingendy-player.posy,player.swingendx-player.posx);
		draw2dquad(
			player.posx-cos(angle)*0.2f,player.posy-sin(angle)*0.2f,
			0.4f,0.4f,linestarttexturecoords,1,angle);
		draw2dquad(
			(player.swingendx+player.posx)*0.5f,
			(player.swingendy+player.posy)*0.5f,
			dist2d(player.posx,player.posy,player.swingendx,player.swingendy),
			0.4f,
			linemiddletexturecoords,
			1,angle);
		draw2dquad(
			player.swingendx+cos(angle)*0.2f,player.swingendy+sin(angle)*0.2f,
			0.4f,0.4f,linestoptexturecoords,1,angle);
	}

	//player
	draw2dquad(
		player.posx,player.posy,1.2f*1.175f,1.2f*1.175f,
		balltexturecoords,1,0.f);

	//solid map tiles
	for(int x=0;x<mapsizex;x++)for(int y=0;y<mapsizey;y++){
		if(map[x][y]==maptype_blocknormal)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			blocknormaltexturecoords,0,0.f);
		if(map[x][y]==maptype_blockharmful)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			blockharmfultexturecoords,0,0.f);
		if(map[x][y]==maptype_blocknoswing)draw2dquad(
			(float)x,(float)y,1.f,1.f,
			blocknoswingtexturecoords,0,0.f);
	}

	//cursor
	draw2dquad(
		aiminworldx,aiminworldy,2.25f,2.25f,
		reticletexturecoords,1,0.f);

	//on screen text
	set2dcamera(
		0.f-400.f,
		0.f+400.f,
		0.f-400.f*screena,
		0.f+400.f*screena);
	char text[256];
	sprintf(text,"%s%i","Score ",(int)ceil(score));
	//drawtext(-400.f*screena,-350.f,(char*)text,1.f);
	float posx=-450.f;
	//float posy=-140.f;
	float posy=-350.f;
	button(posx,posy,900.f,25.f,0);
	drawtext(posx-5.f,posy-7.5f,(char*)text,0.65f);
	posy+=70.f;

}
