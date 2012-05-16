#ifdef SDL
SDL_Surface *screen;
#endif

#ifdef GX
#define DEFAULT_FIFO_SIZE	(256*1024)
typedef struct tagtexdef{
	void *pal_data;
	void *tex_data;
	u32 sz_x;
	u32 sz_y;
	u32 fmt;
	u32 min_lod;
	u32 max_lod;
	u32 min;
	u32 mag;
	u32 wrap_s;
	u32 wrap_t;
	void *nextdef;
} texdef;
static GXRModeObj *rmode = NULL;
static void *frameBuffer[2] = { NULL, NULL};
f32 yscale = 0;
u32 xfbHeight;
u32 fb = 0;
u32 first_frame = 1;
void *gpfifo = NULL;
GXColor background = {0, 0, 0, 0xff};
#endif

#ifdef RSX
int currentBuffer = 0;
long frame = 0;
#endif

void initsdl(){
	#ifdef SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	if(fullscreen==1)
		screen = SDL_SetVideoMode((int)screenw,(int)screenh,screenbpp,SDL_FULLSCREEN);
	if(fullscreen==0)
		screen = SDL_SetVideoMode((int)screenw,(int)screenh,screenbpp,SDL_DOUBLEBUF);
	SDL_WM_SetCaption( "ThatOtherDev.com", NULL );
	#endif
}

void initopengl(){
	#ifdef OPENGL
	#ifdef SDL
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);
    //Window Settings
	SDL_WM_SetCaption( "ThatOtherDev.com", NULL );
	//enable anti aliasing
	if(antialiasing){
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
		glEnable(GL_MULTISAMPLE);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
	}
	//Create Video Surface
	//there seems to be a problem with opengl plus a screen width or height of zero
	if(screenw==0 || screenh==0){
		screen = SDL_SetVideoMode((int)screenw,(int)screenh,screenbpp,SDL_DOUBLEBUF);
		screenw=screen->w;
		screenh=screen->h;
		screena = screenw/screenh;
		SDL_FreeSurface(screen);
	}
	if(fullscreen==1)
		screen = SDL_SetVideoMode((int)screenw,(int)screenh,screenbpp,SDL_OPENGL|SDL_FULLSCREEN);
	if(fullscreen==0)
		screen = SDL_SetVideoMode((int)screenw,(int)screenh,screenbpp,SDL_OPENGL);
	if (!screen) { SDL_Quit(); exit(3); }
	//Size OpenGL to Video Surface
	glViewport(0, 0, screenw, screenh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(screenfov,screena,1.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
	//Set Pixel Format
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	//OpenGL Render Settings
	glClearColor(0,0,0,1);
	glClearDepth(1000.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER,0.0f);
	#endif
	#endif
}

void initgx(){
	#ifdef GX
	VIDEO_Init();
	rmode = VIDEO_GetPreferredMode(NULL);
	//allocate the fifo buffer
	gpfifo = memalign(32,DEFAULT_FIFO_SIZE);
	memset(gpfifo,0,DEFAULT_FIFO_SIZE);
	//allocate 2 framebuffers for double buffering
	frameBuffer[0] = SYS_AllocateFramebuffer(rmode);
	frameBuffer[1] = SYS_AllocateFramebuffer(rmode);
	//configure video
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(frameBuffer[fb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
	fb ^= 1;
	//init the flipper
	GX_Init(gpfifo,DEFAULT_FIFO_SIZE);
 	//clears the bg to color and clears the z buffer
	GX_SetCopyClear(background, 0x00ffffff);
 	//other gx setup
	GX_SetViewport(0,0,rmode->fbWidth,rmode->efbHeight,0,1);
	yscale = GX_GetYScaleFactor(rmode->efbHeight,rmode->xfbHeight);
	xfbHeight = GX_SetDispCopyYScale(yscale);
	GX_SetScissor(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopySrc(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopyDst(rmode->fbWidth,xfbHeight);
	GX_SetCopyFilter(rmode->aa,rmode->sample_pattern,GX_TRUE,rmode->vfilter);
	GX_SetFieldMode(rmode->field_rendering,((rmode->viHeight==2*rmode->xfbHeight)?GX_ENABLE:GX_DISABLE));
 	if (rmode->aa)
        GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    else
        GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
	GX_SetCullMode(GX_CULL_FRONT);
	//GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(frameBuffer[fb],GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);
	//setup the vertex attribute table
	//describes the data
	//args: vat location 0-7, type of data, data format, size, scale
	//so for ex. in the first call we are sending position data with
	//3 values X,Y,Z of size F32. scale sets the number of fractional
	//bits for non float data.
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0);	
    GX_InvVtxCache();
	GX_SetNumChans(1);
	GX_SetNumTexGens(1);
	GX_SetTevOp(GX_TEVSTAGE0, GX_REPLACE);
	GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
	GX_InvalidateTexAll();
	#endif
}

#ifdef PS3
bool xmbup=0;
static void eventHandle(u64 status, u64 param, void * userdata) {
    (void)param;
    (void)userdata;
	if(status == EVENT_REQUEST_EXITAPP){
		printf("Quit game requested\n");
		exit(0);
	}else if(status == EVENT_MENU_OPEN){
		xmbup=1;
	}else if(status == EVENT_MENU_CLOSE){
		xmbup=0;
	}else if(status == EVENT_DRAWING_BEGIN){
	}else if(status == EVENT_DRAWING_END){
	}else{
		printf("Unhandled event: %08llX\n", (unsigned long long int)status);
	}
}

void appCleanup(){
	sysUnregisterCallback(EVENT_SLOT0);
	printf("Exiting for real.\n");
}
#endif

void initrsx(){
	#ifdef RSX
	atexit(appCleanup);
	init_screen();
	sysRegisterCallback(EVENT_SLOT0, eventHandle, NULL);
	u32 *frag_mem = rsxMemAlign(256, 256);
	printf("frag_mem = 0x%08lx\n", (u64) frag_mem);
	realityInstallFragmentProgram_old(context, &nv30_fp, frag_mem);
	#endif
}

void initvideo(){
	//fov is 45 by default
	screenfov=45;
	//the setup
	if(usesdl)initsdl();
	if(useopengl)initopengl();
	if(usegx)initgx();
	if(usersx)initrsx();
	//get correct info about the screen
	#ifdef SDL
	screenw = screen->w;
	screenh = screen->h;
	screena = screenw/screenh;
	screenbpp = screen->format->BitsPerPixel;
	#endif
	#ifdef GX
	screenw = rmode->viWidth;
    screenh = rmode->viHeight;
	screena = screenw/screenh;
	#endif
	//show or hide the cursor
	#ifdef SDL
	SDL_ShowCursor(showcursor);
	#endif
}
