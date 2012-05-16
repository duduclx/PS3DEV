void dashloop(){
#ifdef PS3
	dashps3loop();
#else
	//adjust the speed of the game based on the frame rate
	float dashspeed=60.f/dash_framerate;
	//if(dashspeed<0.2f)dashspeed=0.2f;
	//if(dashspeed>2.0f)dashspeed=2.0f;
	dashspeed=1.f;

	dashtime();
	dashonoff(dashspeed);
	if(dashonpercent!=0){
		dashbars();
		dashmenu();
	}
	dashcursors();
	
	/*if(1){
		char temptext[256];
		sprintf(temptext,"%s%f","frames per second: ",dash_framerate);
		dashbutton(25,25,300,10,0,0,(char*)temptext);
	}*/
#endif
}
