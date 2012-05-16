//these defines dictate what libraries will be used and how things will be setup and function

//platform
//#define WIN
//#define WII
//#define GP2X
//#define PS3

#ifndef WIN
//#define WII
#define PS3
#endif

//supported rendering methods
//#define SDL
//#define OPENGL
//#define GX
//#define RSX

#ifdef WIN
#define SDL
#define OPENGL
#endif

#ifdef WII
#define GX
#endif

#ifdef PS3
#define RSX
#endif

#include "../../../generic/generic.h"

#include "settings.h"
#include "projectsetup.h"
#include "projectloop.h"

#ifdef PS3
s32 main(s32 argc, const char* argv[]){
#else
int main(int argc,char **argv){
#endif
	//you may not be able to load the settings files without this
	setupfilesystem();
	//load the generic settings
	loadgenericsettings();
	//load the project specific settings
	loadsettings();
	//generic setup
	genericsetup();
	//setup the dashboard
	dashsetup();
	//setup for the project
	projectsetup();
	//game loop
	while(shutdownprogram==0){
		//clear the screen and prep for renderinh
		clearscreen();
		//get what events have occured
		#ifdef SDL
		SDL_PumpEvents();
		#endif
		//get controller input
		updateinput();
		//update the game
		if(dashonpercent==0)
			projectloop();
		//update the dashboard
		dashloop();
		//show the frame
		drawscreen();
		//clear out left over events and shut down when appropriate
		#ifdef SDL
		SDL_Event event;
		while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_ALLEVENTS)>0)
			if(event.type==SDL_QUIT)shutdownprogram=1;
		#endif
	}
	// Clean up
	#ifdef SDL
    SDL_Quit();
	#endif
    return 0;
}

