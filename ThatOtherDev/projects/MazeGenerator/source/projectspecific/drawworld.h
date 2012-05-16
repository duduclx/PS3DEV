void drawworld(){

	//set the camera
	set2dcamera(-400.f,400.f,-400.f*screena,400.f*screena);

	//background
	draw2dquad(0.f,0.f,800.f*screena,800.f,backgroundtexturecoords,1,0.f);

	//on screen text
	char temptext[256];
	sprintf(temptext,"%i%s",solvecount," mazes solved");
	drawtextcenteraligned(
		0.f,
		300.f,
		(char*)temptext,
		1.f);

	//get the scale of the world
	float size=800.f/(float)mazesizex;
	float xpos=-size*(float)mazesizex*0.5f;
	float ypos=-size*(float)mazesizey*0.5f;

	if(gamestate==gamestate_menu){
		set2dcamera(-300.f,300.f,-300.f*screena,300.f*screena);
		draw2dquad(0.f,-50.f,800.f,80.f*2.f,titletexturecoords,1,0.f);
		draw2dquad(0.f,70.f,800.f,80.f*1.f,infotexturecoords,1,0.f);
		if(menustate==0)draw2dquad(0.f,130.f,800.f,80.f*0.5f,size1texturecoords,1,0.f);
		if(menustate==1)draw2dquad(0.f,130.f,800.f,80.f*0.5f,size2texturecoords,1,0.f);
		if(menustate==2)draw2dquad(0.f,130.f,800.f,80.f*0.5f,size3texturecoords,1,0.f);
		set2dcamera(-400.f,400.f,-400.f*screena,400.f*screena);
	}

	if(gamestate==gamestate_play){
		//draw the maze
		if(mazecomplete==1){
			draw2dquad(
				xpos+playerposx*size,
				ypos+playerposy*size,
				size,size,playertexturecoords,1,0.f);
			for(int y=0;y<mazesizey;y++){
				for(int x=0;x<mazesizex;x++){
					if(maze[x][y])
						draw2dquad(xpos,ypos,size,size,colorpalettetexturecoords[0],0,0.f);
					xpos+=size;
				}
				xpos-=size*mazesizex;
				ypos+=size;
			}
			ypos-=size*mazesizey;
			draw2dquad(
				xpos+(float)(mazesizex-2)*size,
				ypos+(float)(mazesizey-2)*size,
				size,size,colorpalettetexturecoords[4],0,0.f);
		}else{
			for(int y=0;y<mazesizey;y++){
				for(int x=0;x<mazesizex;x++){
					if(maze[x][y]==1)
						draw2dquad(xpos,ypos,size,size,colorpalettetexturecoords[0],0,0.f);
					if(maze[x][y]==2)
						draw2dquad(xpos,ypos,size,size,colorpalettetexturecoords[1],0,0.f);
					if(maze[x][y]==3)
						draw2dquad(xpos,ypos,size,size,colorpalettetexturecoords[2],0,0.f);
					if(maze[x][y]==4)
						draw2dquad(xpos,ypos,size,size,colorpalettetexturecoords[3],0,0.f);
					xpos+=size;
				}
				xpos-=size*mazesizex;
				ypos+=size;
			}
			ypos-=size*mazesizey;
		}
	}

}
