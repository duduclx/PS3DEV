#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include <lv2/process.h>
#include <psl1ght/lv2/thread.h>
#include <sysmodule/sysmodule.h>
#include <sysutil/events.h>

#include <sys/stat.h>
#include <sysutil/events.h>
#include <io/msg.h>
#include <io/pad.h> 
#include <io/mouse.h> 
#include <sysmodule/sysmodule.h>

#include <tiny3d.h>
#include <pngdec\loadpng.h>
#include <io/pad.h> 
#include <sys\time.h>

#include "types.h"
#include "oskdialog.h"


//Tiny3D Resources
u32 *texture_mem;
u32 * texture_pointer;

//SDK modules
u32 module_flag;

volatile u8 running = 1;

void releaseAll() {
	
	sysUnregisterCallback(EVENT_SLOT0);
	//sys_ppu_thread_join(thread1_id, &retval);
	
	if(module_flag & 2)
		SysUnloadModule(SYSMODULE_PNGDEC);

	if(module_flag & 1)
		SysUnloadModule(SYSMODULE_FS);

	running = 0;
}

int loadModules( void ){
	if(SysLoadModule(SYSMODULE_FS)!=0) return 0; else module_flag |=1;

	if(SysLoadModule(SYSMODULE_PNGDEC)!=0) return 0; else module_flag |=2;

	return 1;
}

void loadTexture()
{

    texture_mem = (u32*)tiny3d_AllocTexture(64*1024*1024); // alloc 64MB of space for textures (this pointer can be global)    

    if(!texture_mem) return; // fail!

    texture_pointer = texture_mem;
}

static void sys_callback(uint64_t status, uint64_t param, void* userdata) {

     switch (status) {
		case EVENT_REQUEST_EXITAPP:
			releaseAll();
			sysProcessExit(1);
			break;
      
       default:
		   break;
         
	}
}

int main(int argc, const char* argv[], const char* envp[])
{
	tiny3d_Init(1024*1024);
	tiny3d_Project2D();

	loadModules();
		
	ioPadInit(7);
	
    loadTexture();
	
	sysRegisterCallback(EVENT_SLOT0, sys_callback, NULL);


	OSK *cOSK = new OSK(texture_pointer, "/dev_hdd0/game/RNA000001/USRDIR");
	texture_pointer = cOSK->getTexturePointer();

	texture_pointer = cOSK->loadFont(0, "/dev_hdd0/game/RNA000001/USRDIR", texture_pointer);

	osk_point point = {300, 200};
	cOSK->setPos(point);

	char *buffer = NULL;

	/*** - MAIN LOOP - ***/
	while( running ){
		
		tiny3d_Clear(0xff555555, TINY3D_CLEAR_ALL);

        // Enable alpha Test
        tiny3d_AlphaTest(1, 0x10, TINY3D_ALPHA_FUNC_GEQUAL);

        // Enable alpha blending.
        tiny3d_BlendFunc(1, (blend_src_func)(TINY3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA | TINY3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA),
            (blend_dst_func)(NV30_3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA | NV30_3D_BLEND_FUNC_DST_ALPHA_ZERO),
            (blend_func)(TINY3D_BLEND_RGB_FUNC_ADD | TINY3D_BLEND_ALPHA_FUNC_ADD));

		tiny3d_Project2D();

		if(cOSK->getStatus() == OSK_INITIALIZED)
			cOSK->open();
		else if(cOSK->getStatus() == OSK_RUNNING){
			cOSK->draw();
			cOSK->handlePad();
		}else if(cOSK->getStatus() == OSK_RETURN)
			buffer = cOSK->getBuffer();
		else if(cOSK->getStatus() == OSK_END)
			DrawString(200, 200, buffer);
				
        tiny3d_Flip();

		sysCheckCallback();

	}
	
	return 0;

}
