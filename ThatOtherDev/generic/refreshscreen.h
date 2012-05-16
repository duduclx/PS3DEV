void clearscreen(){
	#ifdef OPENGL
	if(useopengl)glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	#endif
	#ifdef RSX
	//frame count increases
	frame++;
	//disable viewport culling
	realityZControl(context, 0, 1, 1);
//realityZControl(context, 0, 1, 1); // disable viewport culling
//realityDepthTestFunc(context, REALITY_ZFUNC_LESSOREQUAL);
//realityDepthWriteEnable(context, 1);
//realityDepthTestEnable(context, 1);
//realityAlphaEnable(context, 0);
//realityBlendEnable(context, 0);
	//enable alpha blending.
	realityBlendFunc(context,
		NV30_3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA | NV30_3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
		NV30_3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA | NV30_3D_BLEND_FUNC_DST_ALPHA_ZERO);
	realityBlendEquation(context,NV40_3D_BLEND_EQUATION_RGB_FUNC_ADD | NV40_3D_BLEND_EQUATION_ALPHA_FUNC_ADD);
	realityBlendEnable(context,1);
	//create a viewport that will fill the screen
	realityViewport(context,res.width,res.height);
	//get screen info
	screenw=res.width;
	screenh=res.height;
	screena=(float)screenw/(float)screenh;
	//target the buffer to render at	
	setupRenderTarget(currentBuffer);
	//set the clear color
	realitySetClearColor(context, 0x00000000);
	//and the depth clear value
	realitySetClearDepthValue(context, 0xffff);
	//Clear the buffers
	realityClearBuffers(context, REALITY_CLEAR_BUFFERS_COLOR_R |
		REALITY_CLEAR_BUFFERS_COLOR_G |
		REALITY_CLEAR_BUFFERS_COLOR_B |
		NV30_3D_CLEAR_BUFFERS_COLOR_A |
		NV30_3D_CLEAR_BUFFERS_STENCIL |
		REALITY_CLEAR_BUFFERS_DEPTH);
	//Load shaders, because the rsx won't do anything without them.
	realityLoadVertexProgram_old(context, &nv40_vp);
	realityLoadFragmentProgram_old(context, &nv30_fp); 
	#endif
}

void drawscreen(){
	#ifdef SDL
	if(usesdl){
		SDL_Flip(screen);
	}
	#endif
	#ifdef OPENGL
	if(useopengl){
		SDL_GL_SwapBuffers();
	}
	#endif
	#ifdef GX
	if(usegx){
		GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
		GX_SetColorUpdate(GX_TRUE);
		GX_CopyDisp(frameBuffer[fb],GX_TRUE);
		GX_DrawDone();		
		VIDEO_SetNextFramebuffer(frameBuffer[fb]);
		if(first_frame) {
			first_frame = 0;
			VIDEO_SetBlack(FALSE);
		}		
		VIDEO_Flush();
		VIDEO_WaitVSync();
		fb ^= 1;
	}
	#endif
	#ifdef RSX
	if(usersx){
		waitFlip(); // Wait for the last flip to finish, so we can draw to the old buffer
		flip(currentBuffer); // Flip buffer onto screen
		currentBuffer = !currentBuffer;
		sysCheckCallback();
	}
	#endif
}
