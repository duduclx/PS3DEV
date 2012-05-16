
#include "VideoInit.h"


void VideoInit::InitScreen() {
	// Allocate a 1Mb buffer, alligned to a 1Mb boundary to be our shared IO memory with the RSX.
	void *host_addr = memalign(1024*1024, 1024*1024);
	assert(host_addr != NULL);

	// Initilise Reality, which sets up the command buffer and shared IO memory
	context = rsxInit(0x10000, 1024*1024, host_addr); 
	assert(context != NULL);

	videoState state;
	assert(videoGetState(0, 0, &state) == 0); // Get the state of the display
	assert(state.state == 0); // Make sure display is enabled

	// Get the current resolution
	assert(videoGetResolution(state.displayMode.resolution, &res) == 0);
	
	// Configure the buffer format to xRGB
	videoConfiguration vconfig;
	memset(&vconfig, 0, sizeof(videoConfiguration));
	vconfig.resolution = state.displayMode.resolution;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch = res.width * 4;
	vconfig.aspect=state.displayMode.aspect;
	assert(videoConfigure(0, &vconfig, NULL, 0) == 0);
	assert(videoGetState(0, 0, &state) == 0); 

	s32 buffer_size = 4 * res.width * res.height; // each pixel is 4 bytes
	gcmSetFlipMode(GCM_FLIP_VSYNC); // Wait for VSYNC to flip

	// Allocate two buffers for the RSX to draw to the screen (double buffering)
	MakeBuffer(0, buffer_size);
	MakeBuffer(1, buffer_size);
        
	gcmResetFlipStatus();
	Flip(1);
}
// Waits until the previous flip operation has finished
void VideoInit::WaitFlip() {
	while(gcmGetFlipStatus() != 0)
		usleep(200);
	gcmResetFlipStatus();
}

// flips the buffer and make RSX use the other bugffer
void VideoInit::Flip() {
	assert(gcmSetFlip(context, currentBuffer) == 0);
	rsxFlushBuffer(context);
	gcmSetWaitFlip(context); //prevent RSX from continuing until the flip has finished

	//Automatically change the current buffer
	currentBuffer = !currentBuffer;
}
//Only used for InitScreen
void VideoInit::Flip(s32 buffer) {
	assert(gcmSetFlip(context, buffer) == 0);
	rsxFlushBuffer(context);
	gcmSetWaitFlip(context); //prevent RSX from continuing until the flip has finished
}
// Creates a buffer based on the resolution of the Screen.
void VideoInit::MakeBuffer(int id, int size) {
	buffer *buf = (buffer*) malloc(sizeof(buffer));
	buf->ptr = (uint32_t*) rsxMemalign(16, size);
	assert(buf->ptr != NULL);
	assert(rsxAddressToOffset(buf->ptr, &buf->offset) == 0);
	assert(gcmSetDisplayBuffer(id, buf->offset, res.width * 4, res.width, res.height) == 0);
	buf->width = res.width;
	buf->height = res.height;
	buffers[id] = buf;
}

// Draws a background of a single color
void VideoInit::DrawBackground(s32 color) {
	s32 i, j;
	for(i = 0; i < res.height; i++)
		for(j = 0; j < res.width; j++)
			buffers[currentBuffer]->ptr[i*res.width + j] = color;

}

//TODO: Make drawBackground with an image as well.

//Constructor / destructor

VideoInit::VideoInit() {
	currentBuffer = 0;
	InitScreen();
}

VideoInit::~VideoInit() {
	free(buffers);
	free(context);
}

