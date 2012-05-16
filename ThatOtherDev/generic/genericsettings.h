//these variables should always exist
float screenw;
float screenh;
float screena;
float screenfov;
int screenbpp;

#ifndef PS3
bool fullscreen;
bool showcursor;
bool antialiasing;
bool mipmapping;
bool usesdl;
bool useopengl;
bool usegx;
bool usersx;
#endif

#ifdef PS3
int fullscreen;
int showcursor;
int antialiasing;
int mipmapping;
int usesdl;
int useopengl;
int usegx;
int usersx;
#endif

//set the settings
void loadgenericsettings(){

	#ifndef PS3
	//load the settings ini
	loadinifile((char*)"settings.ini");
	//load read the setttings
	screenw=readfloatfromini((char*)"screenw");
	screenh=readfloatfromini((char*)"screenh");
	screenbpp=(int)readfloatfromini((char*)"screenbpp");
	fullscreen=(bool)readfloatfromini((char*)"fullscreen");
	showcursor=(bool)readfloatfromini((char*)"showcursor");
	antialiasing=(bool)readfloatfromini((char*)"antialiasing");
	mipmapping=(bool)readfloatfromini((char*)"mipmapping");
	#endif

	//set the rendering method
	#ifdef SDL
		usesdl=1;
	#else
		usesdl=0;
	#endif

	#ifdef OPENGL
		useopengl=1;
	#else
		useopengl=0;
	#endif

	#ifdef GX
		usegx=1;
	#else
		usegx=0;
	#endif

	#ifdef RSX
		usersx=1;
	#else
		usersx=0;
	#endif

	if(useopengl){
		usesdl=0;
		usegx=0;
		usersx=0;
	}

	if(usegx){
		usesdl=0;
		usersx=0;
	}

	if(usersx){
		usesdl=0;
	}

	//Wii is never going to output hd video...
	#ifdef WII
		screenw=640;
		screenh=480;
		screenbpp=16;
		fullscreen=0;
		showcursor=0;
	#endif

	//calculate the screens aspect ratio
	screena = screenw/screenh;

}
