void dashsavescreenshot(){
	#ifndef PS3
	char filename[256];
	#ifdef WII
	ifstream test;
	int filenumber=1;
	sprintf(filename,"sd:/screenshot%d.png",filenumber);
	test.open(filename);test.close();
	if(!test.fail()){
		while(!test.fail()){
			filenumber=filenumber+1;
			sprintf(filename,"sd:/screenshot%d.png",filenumber);
			test.open(filename);test.close();
		}
	}
	#endif
	#ifdef WIN
	ifstream test;
	int filenumber=1;
	sprintf(filename,"screenshot%d.png",filenumber);
	test.open(filename);test.close();
	if(!test.fail()){
		while(!test.fail()){
			filenumber=filenumber+1;
			sprintf(filename,"screenshot%d.png",filenumber);
			test.open(filename);test.close();
		}
	}
	#endif
	#ifdef SDL
	//if(usesdl)SDL_SaveBMP(dash_background_sprite,(char*)filename);
	if(usesdl)SDL_SavePNG(dash_background_sprite,(char*)filename);
	#endif
	#ifdef OPENGL
	if(useopengl){
		int w=screenw;
		int h=screenh;
		std::vector<unsigned char> image;
		image.resize(w * h * 4);
		for(int y = 0; y < h; y++)for(int x = 0; x < w; x++){
			image[4*w*y+4*x+0] = (unsigned char)dash_background_opengl[4*w*(h-1)-4*w*y+4*x+0];
			image[4*w*y+4*x+1] = (unsigned char)dash_background_opengl[4*w*(h-1)-4*w*y+4*x+1];
			image[4*w*y+4*x+2] = (unsigned char)dash_background_opengl[4*w*(h-1)-4*w*y+4*x+2];
			image[4*w*y+4*x+3] = (unsigned char)255;
		}
		//create encoder and set settings and info (optional)
		LodePNG::Encoder encoder;
		encoder.addText("Comment", "Created with LodePNG");
		encoder.getSettings().zlibsettings.windowSize = 2048;
		//encode and save
		std::vector<unsigned char> buffer;
		encoder.encode(buffer, image.empty() ? 0 : &image[0], w, h);
		LodePNG::saveFile(buffer, filename);
	}
	#endif
	#endif
}

void setupdashmenu(){

}

void dashmenu(){
	
	#ifndef PS3
	int x=screenw/2;
	int y=dashonslide(screenh/2-125,screenh/2-125+screenh);
	
	#ifdef WII
	if(dashbutton(x,y,300,15,1,1,(char*)"Resume game"))dashon=0;
	y+=50;
	if(dashbutton(x,y,300,15,1,1,(char*)"Exit to loader"))shutdownprogram=true;
	y+=50;
	if(dashbutton(x,y,300,15,1,1,(char*)"Restart Wii"))SYS_ResetSystem(SYS_RESTART,0,0);
	y+=50;
	if(dashbutton(x,y,300,15,1,1,(char*)"Shutdown Wii"))SYS_ResetSystem(SYS_POWEROFF,0,0);
	y+=50;
	if(usesdl)if(dashbutton(x,y,300,15,1,1,(char*)"Save screenshot to SD"))dashsavescreenshot();
	y+=50;
	#endif

	#ifdef WIN
	if(dashbutton(x,y,300,15,1,1,(char*)"Resume game"))dashon=0;
	y+=50;
	if(dashbutton(x,y,300,15,1,1,(char*)"Exit"))shutdownprogram=true;
	y+=50;
	if(dashbutton(x,y,300,15,1,1,(char*)"Save screenshot"))dashsavescreenshot();
	y+=50;
	#endif
	#endif

}
