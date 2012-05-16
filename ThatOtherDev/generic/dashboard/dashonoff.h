float dashonpercent=0.f;
bool dashon=0;

#ifdef SDL
SDL_Surface *dash_background_sprite = NULL;
SDL_Surface *dash_backgroundblurred_sprite = NULL;
#endif

#ifdef OPENGL
Uint8* dash_background_opengl;
#endif

int dashonslide(int onpos,int offpos){
	return(int)((float)onpos*dashonpercent*0.01f+(float)offpos*(1.f-dashonpercent*0.01f));
}

void setupdashonoff(){

	dashonpercent=0;
	dashon=0;
	
	#ifdef SDL
	if(usesdl){
		dash_background_sprite = SDL_CreateRGBSurface(
			screen->flags,
			screen->w,
			screen->h,
			screen->format->BitsPerPixel,
			screen->format->Rmask,
			screen->format->Gmask,
			screen->format->Bmask,
			screen->format->Amask);
		dash_backgroundblurred_sprite = SDL_CreateRGBSurface(
			screen->flags,
			screen->w,
			screen->h,
			screen->format->BitsPerPixel,
			screen->format->Rmask,
			screen->format->Gmask,
			screen->format->Bmask,
			screen->format->Amask);
	}
	#endif

	#ifdef OPENGL
	if(useopengl){
		dash_background_opengl = new Uint8 [4*screenw*screenh];
	}
	#endif
	
}

void dashonoff(float dashspeed){

	#ifndef PS3
	#ifdef WII
	if((WiiButtonsDown[0] & WPAD_BUTTON_HOME) || (WiiButtonsDown[0] & WPAD_CLASSIC_BUTTON_HOME)
	|| (WiiButtonsDown[1] & WPAD_BUTTON_HOME) || (WiiButtonsDown[1] & WPAD_CLASSIC_BUTTON_HOME)
	|| (WiiButtonsDown[2] & WPAD_BUTTON_HOME) || (WiiButtonsDown[2] & WPAD_CLASSIC_BUTTON_HOME)
	|| (WiiButtonsDown[3] & WPAD_BUTTON_HOME) || (WiiButtonsDown[3] & WPAD_CLASSIC_BUTTON_HOME)){
	#endif
	#ifdef WIN
	if(keystate[SDLK_ESCAPE]==2){
	#endif
		if(dashon==0){
			dashon=1;
			#ifdef SDL
			if(usesdl)if(dashonpercent==0){
				apply_surface(0,0,screen,dash_background_sprite,NULL);
				filtersurface(
					dash_background_sprite,
					dash_backgroundblurred_sprite,
					3,2,1,2,0,50,50,50);
			}
			#endif
			#ifdef OPENGL
			if(useopengl)if(dashonpercent==0){
				glReadPixels(0,0,screenw,screenh,GL_RGBA,GL_UNSIGNED_BYTE,dash_background_opengl);
			}
			#endif
		}else{
			dashon=0;
		}
	}

	#ifdef SDL
	if(usesdl){
		if(dashonpercent==0){
		}else if(dashonpercent==100){
			apply_surface(0,0,dash_backgroundblurred_sprite,screen,NULL);
		}else{
			apply_surface(0,0,dash_backgroundblurred_sprite,screen,NULL);
			SDL_SetAlpha(
				dash_background_sprite,
				SDL_SRCALPHA,
				(int)(255.f*(100.f-dashonpercent)*0.01f));
			apply_surface(0,0,dash_background_sprite,screen,NULL);
			SDL_SetAlpha(
				dash_background_sprite,
				SDL_SRCALPHA,
				255);
		}
	}
	#endif
	#ifdef OPENGL
	if(useopengl)if(dashonpercent!=0){
		glDrawPixels(screenw,screenh,GL_RGBA,GL_UNSIGNED_BYTE,dash_background_opengl);
	}
	#endif

	if(dashon){
		dashonpercent+=5.f*dashspeed;
		//if(dashonpercent>100)dashonpercent=100;
	}else{
		dashonpercent-=5.f*dashspeed;
		//if(dashonpercent<0)dashonpercent=0;
	}
	if(dashonpercent>100)dashonpercent=100;
	if(dashonpercent<0)dashonpercent=0;
	if(dashonpercent!=dashonpercent)dashonpercent=0;
	#endif

}
