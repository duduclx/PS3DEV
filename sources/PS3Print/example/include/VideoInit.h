/*
  VideoInit:
  Author: Juan Sebastian Munnoz (naruse@gmail.com)

  Simple class that simplifies all the initializing
  process for drawing stuff on the screen.

  Uses Double Buffering for drawing.
  
*/

#ifndef _VIDEOINIT_
#define _VIDEOINIT_

#include <ppu-lv2.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <sysutil/video.h>
#include <rsx/gcm_sys.h>
#include <rsx/rsx.h>


class VideoInit {

	typedef struct {
		int height;
		int width;
		uint32_t *ptr;
		uint32_t offset;// Internal stuff
	} buffer; //Represents the display where we are going to draw our stuff

	gcmContextData *context;
	videoResolution res; //dont access this, if you want to access the res.width/height, use GetCurrentBuffer->height/width instead
	int currentBuffer;
	buffer *buffers[2]; // Buffers we are going to draw into (double buffering)

	void Flip(s32 buffer);//Only used by InitScreen()
	void MakeBuffer(int id, int size);//scognito's	
 public:
	VideoInit();
	~VideoInit();
	

	void InitScreen();
	void Flip();//flips the currentBuffer automatically from 0->1 / 1->0
	void WaitFlip();

	buffer* GetCurrentBuffer() {return buffers[currentBuffer];}
	
	void DrawBackground(s32 color);
};
#endif
