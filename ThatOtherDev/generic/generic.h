//define bool
#ifdef PS3
    #define bool int
    #define false ((bool)0)
    #define true  ((bool)1)
#endif

//important variable
bool shutdownprogram = 0;

//super ultra mega generic includes
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#ifdef WIN
	#include <windows.h>
	#ifdef SDL
		#include <sdl.h>
		#include <SDL_image.h>
		#include <SDL_mixer.h>
		#include <SDL_net.h>
		#ifdef OPENGL
			#include <sdl_opengl.h>
		#endif
	#endif
	#include <vector>
	#include <iostream>
	using std::cerr;
	using std::cout;
	using std::endl;
	#include <fstream>
	using std::ofstream;
	using std::ifstream;
	#include <cstdlib>
	#include <string>
#endif

#ifdef WII
	#include <gccore.h>
	#include <wiiuse/wpad.h> 
	#ifdef SDL
		#include <SDL/sdl.h>
		#include <SDL/sdl_image.h>
		#include <SDL/SDL_mixer.h>
	#endif
	#include <fat.h>
	#include <dirent.h>
	#include <unistd.h>
	#include <asndlib.h>
	#include <mp3player.h>
	#include <ogc/lwp_watchdog.h>
	#include <vector>
	#include <iostream>
	using std::cerr;
	using std::cout;
	using std::endl;
	#include <fstream>
	using std::ofstream;
	using std::ifstream;
	#include <cstdlib>
	#include <string>
#endif

#ifdef PS3
	#include <assert.h>
	#include <unistd.h>
	#include <rsx/commands.h>
	#include <rsx/nv40.h>
	#include <rsx/reality.h>
	#include <io/pad.h>
	#include <sysmodule/sysmodule.h>
	#include "texture.h"
	#include "rsxutil.h"
	#include "nv_shaders.h"
	#include "sysutil/events.h"
#endif

//super generic
#include "genericmath.h"
#include "filesystem.h"
#include "readinifiles.h"
#include "genericsettings.h"
#include "dirlist.h"
#include "initvideo.h"
#include "input.h"
#include "bresenham.h"
#include "3dfunctions.h"
#include "refreshscreen.h"

#ifndef PS3
	#include "loadobj.h"
	#include "3DMath.h"
	#include "meshbump.h"
	#include "frustum.h"
	#include "lodepng.h"
#endif

//specific to SDL surfaces
#ifdef SDL
	#include "sdldraw/loadanddrawsurfaces.h"
	#include "sdldraw/getputpixel.h"
	#include "sdldraw/drawcircle.h"
	#include "sdldraw/drawline.h"
	#include "sdldraw/drawpolygon.h"
	#include "sdldraw/drawhexagon.h"
	#include "sdldraw/filtersurface.h"
	#include "sdldraw/rotoscale.h"
	#include "sdldraw/savesurface.h"
#endif

//specific to OpenGL
#ifdef OPENGL
	//glu works fine and makes these unnecessary
	//#include "opengl/Build2DMipMapsGL.h"
	//#include "opengl/perspectiveGL.h"
	#ifdef SDL
		#include "opengl/loadtexture.h"
	#else
		#include "opengl/loadbmp.h"
		#include "opengl/loadtga.h"
		#include "opengl/loadtoif.h"
	#endif
#endif

//the dashboard and related functions
#include "dashboard/dashsetup.h"
#include "dashboard/dashloop.h"

void genericsetup(){
	//seed the random number generator
	srand((int)time(NULL));
	//setup the screen or window
	initvideo();
	//setup for the controller input
	setupinput();
}
