//define some things
#define keycount                    (500)
#define buttoncount                 (20)
#define mousecount                  (10)

#ifdef GP2X
#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_X               (14)
#define GP2X_BUTTON_Y               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)
#endif

#ifdef PS3
#define MAXCONTROLLERS              (4)
#endif

//controller input variables
int cursorx[4];
int cursory[4];
int cursorxmov[4];
int cursorymov[4];
bool centercursor=0;

int keystate[keycount];
int buttonstate[keycount];
int mousestate[mousecount];

#ifdef PS3
PadInfo padinfo;
PadData paddata[MAXCONTROLLERS];
int BTN_LEFT[MAXCONTROLLERS];
int BTN_DOWN[MAXCONTROLLERS];
int BTN_RIGHT[MAXCONTROLLERS];
int BTN_UP[MAXCONTROLLERS];
int BTN_START[MAXCONTROLLERS];
int BTN_R3[MAXCONTROLLERS];
int BTN_L3[MAXCONTROLLERS];
int BTN_SELECT[MAXCONTROLLERS];
int BTN_SQUARE[MAXCONTROLLERS];
int BTN_CROSS[MAXCONTROLLERS];
int BTN_CIRCLE[MAXCONTROLLERS];
int BTN_TRIANGLE[MAXCONTROLLERS];
int BTN_R1[MAXCONTROLLERS];
int BTN_L1[MAXCONTROLLERS];
int BTN_R2[MAXCONTROLLERS];
int BTN_L2[MAXCONTROLLERS];
#endif

#ifdef WII
bool wiimoteactive[4];
u32 WiiButtonsHeld[4];
u32 WiiButtonsDown[4];
u32 WiiButtonsUp[4];
u16 GCButtonsHeld[4];
u16 GCButtonsDown[4];
u16 GCButtonsUp[4];
ir_t ir[4];
expansion_t expans[4];
#ifdef USEACCELEROMETER
gforce_t gforce[4];
#endif
s8 HWButton = -1;
void WiiResetPressed(){HWButton = SYS_RETURNTOMENU;}
void WiiPowerPressed(){HWButton = SYS_POWEROFF;}
void WiimotePowerPressed(s32 chan){HWButton = SYS_POWEROFF;}
#endif

//prep for input
void setupinput(){
	#ifdef WII
	WPAD_Init();
	WPAD_SetVRes(WPAD_CHAN_ALL,screenw,screenh);
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);
	#endif
	#ifdef PS3
	ioPadInit(7);
	#endif
}

//recieve input
#ifdef WIN
void updateinput(){
	SDL_Event event;
	for(int a=0;a<keycount;a++)if(keystate[a]==2)keystate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_KEYDOWN)))
		keystate[event.key.keysym.sym]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_KEYUP)))
		keystate[event.key.keysym.sym]=0;
	for(int a=0;a<buttoncount;a++)if(buttonstate[a]==2)buttonstate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_JOYBUTTONDOWN)))
		buttonstate[event.jbutton.button]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_JOYBUTTONUP)))
		buttonstate[event.jbutton.button]=0;
	for(int a=0;a<mousecount;a++)if(mousestate[a]==2)mousestate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_MOUSEBUTTONDOWN)))
		mousestate[event.button.button]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_MOUSEBUTTONUP)))
		mousestate[event.button.button]=0;
	if(centercursor){
		//SDL_WM_GrabInput(SDL_GRAB_ON);
		SDL_GetMouseState(&cursorx[0],&cursory[0]);
		//SDL_GetRelativeMouseState(&cursorxmov[0],&cursorymov[0]);
		SDL_WarpMouse(screen->w/2,screen->h/2);
		cursorxmov[0]=cursorx[0]-screen->w/2;
		cursorymov[0]=cursory[0]-screen->h/2;
	}else{
		int oldx=cursorx[0];
		int oldy=cursory[0];
		SDL_GetMouseState(&cursorx[0],&cursory[0]);
		cursorxmov[0]=cursorx[0]-oldx;
		cursorymov[0]=cursory[0]-oldy;
	}
}
#endif

#ifdef GP2X
void updateinput(){
	SDL_Event event;
	for(int a=0;a<buttoncount;a++)if(buttonstate[a]==2)buttonstate[a]=1;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_JOYBUTTONDOWN)))
		buttonstate[event.jbutton.button]=2;
	while(SDL_PeepEvents(&event,1,SDL_GETEVENT,SDL_EVENTMASK(SDL_JOYBUTTONUP)))
		buttonstate[event.jbutton.button]=0;
}
#endif

#ifdef PS3
void updateinput(){
	ioPadGetInfo(&padinfo);
	//int a=0;
	for(int a=0; a<MAX_PADS; a++){
		if(padinfo.status[a] && a<MAXCONTROLLERS){
			ioPadGetData(a,&paddata[a]);
			if(paddata[a].BTN_LEFT){		if(BTN_LEFT[a]==0){			BTN_LEFT[a]=3;			}else{	BTN_LEFT[a]=2;			}	}
			if(paddata[a].BTN_DOWN){		if(BTN_DOWN[a]==0){			BTN_DOWN[a]=3;			}else{	BTN_DOWN[a]=2;			}	}
			if(paddata[a].BTN_RIGHT){		if(BTN_RIGHT[a]==0){		BTN_RIGHT[a]=3;			}else{	BTN_RIGHT[a]=2;			}	}
			if(paddata[a].BTN_UP){			if(BTN_UP[a]==0){			BTN_UP[a]=3;			}else{	BTN_UP[a]=2;			}	}
			if(paddata[a].BTN_START){		if(BTN_START[a]==0){		BTN_START[a]=3;			}else{	BTN_START[a]=2;			}	}
			if(paddata[a].BTN_R3){			if(BTN_R3[a]==0){			BTN_R3[a]=3;			}else{	BTN_R3[a]=2;			}	}
			if(paddata[a].BTN_L3){			if(BTN_L3[a]==0){			BTN_L3[a]=3;			}else{	BTN_L3[a]=2;			}	}
			if(paddata[a].BTN_SELECT){		if(BTN_SELECT[a]==0){		BTN_SELECT[a]=3;		}else{	BTN_SELECT[a]=2;		}	}
			if(paddata[a].BTN_SQUARE){		if(BTN_SQUARE[a]==0){		BTN_SQUARE[a]=3;		}else{	BTN_SQUARE[a]=2;		}	}
			if(paddata[a].BTN_CROSS){		if(BTN_CROSS[a]==0){		BTN_CROSS[a]=3;			}else{	BTN_CROSS[a]=2;			}	}
			if(paddata[a].BTN_TRIANGLE){	if(BTN_TRIANGLE[a]==0){		BTN_TRIANGLE[a]=3;		}else{	BTN_TRIANGLE[a]=2;		}	}
			if(paddata[a].BTN_CIRCLE){		if(BTN_CIRCLE[a]==0){		BTN_CIRCLE[a]=3;		}else{	BTN_CIRCLE[a]=2;		}	}
			if(paddata[a].BTN_R1){			if(BTN_R1[a]==0){			BTN_R1[a]=3;			}else{	BTN_R1[a]=2;			}	}
			if(paddata[a].BTN_L1){			if(BTN_L1[a]==0){			BTN_L1[a]=3;			}else{	BTN_L1[a]=2;			}	}
			if(paddata[a].BTN_R2){			if(BTN_R2[a]==0){			BTN_R2[a]=3;			}else{	BTN_R2[a]=2;			}	}
			if(paddata[a].BTN_L2){			if(BTN_L2[a]==0){			BTN_L2[a]=3;			}else{	BTN_L2[a]=2;			}	}
		}
		//a++;
	}
	for(int a=0; a<MAXCONTROLLERS; a++){
		if(BTN_LEFT[a]>0)BTN_LEFT[a]-=1;
		if(BTN_DOWN[a]>0)BTN_DOWN[a]-=1;
		if(BTN_RIGHT[a]>0)BTN_RIGHT[a]-=1;
		if(BTN_UP[a]>0)BTN_UP[a]-=1;
		if(BTN_START[a]>0)BTN_START[a]-=1;
		if(BTN_R3[a]>0)BTN_R3[a]-=1;
		if(BTN_L3[a]>0)BTN_L3[a]-=1;
		if(BTN_SELECT[a]>0)BTN_SELECT[a]-=1;
		if(BTN_SQUARE[a]>0)BTN_SQUARE[a]-=1;
		if(BTN_CROSS[a]>0)BTN_CROSS[a]-=1;
		if(BTN_CIRCLE[a]>0)BTN_CIRCLE[a]-=1;
		if(BTN_TRIANGLE[a]>0)BTN_TRIANGLE[a]-=1;
		if(BTN_R1[a]>0)BTN_R1[a]-=1;
		if(BTN_L1[a]>0)BTN_L1[a]-=1;
		if(BTN_R2[a]>0)BTN_R2[a]-=1;
		if(BTN_L2[a]>0)BTN_L2[a]-=1;
	}
}
#endif

#ifdef WII
void updateinput(){
	//this could totally be done with a for loop
	//instead of having almost everything written out four times
	WPAD_ScanPads();
	//PAD_ScanPads();
	u32 ext;
	wiimoteactive[0]=(WPAD_Probe(WPAD_CHAN_0,&ext)!=WPAD_ERR_NO_CONTROLLER);
	wiimoteactive[1]=(WPAD_Probe(WPAD_CHAN_1,&ext)!=WPAD_ERR_NO_CONTROLLER);
	wiimoteactive[2]=(WPAD_Probe(WPAD_CHAN_2,&ext)!=WPAD_ERR_NO_CONTROLLER);
	wiimoteactive[3]=(WPAD_Probe(WPAD_CHAN_3,&ext)!=WPAD_ERR_NO_CONTROLLER);
	WiiButtonsHeld[0]=WPAD_ButtonsHeld(WPAD_CHAN_0);
	WiiButtonsDown[0]=WPAD_ButtonsDown(WPAD_CHAN_0);
	WiiButtonsUp[0]=WPAD_ButtonsUp(WPAD_CHAN_0);
	WiiButtonsHeld[1]=WPAD_ButtonsHeld(WPAD_CHAN_1);
	WiiButtonsDown[1]=WPAD_ButtonsDown(WPAD_CHAN_1);
	WiiButtonsUp[1]=WPAD_ButtonsUp(WPAD_CHAN_1);
	WiiButtonsHeld[2]=WPAD_ButtonsHeld(WPAD_CHAN_2);
	WiiButtonsDown[2]=WPAD_ButtonsDown(WPAD_CHAN_2);
	WiiButtonsUp[2]=WPAD_ButtonsUp(WPAD_CHAN_2);
	WiiButtonsHeld[3]=WPAD_ButtonsHeld(WPAD_CHAN_3);
	WiiButtonsDown[3]=WPAD_ButtonsDown(WPAD_CHAN_3);
	WiiButtonsUp[3]=WPAD_ButtonsUp(WPAD_CHAN_3);
	WPAD_IR(WPAD_CHAN_0,&ir[0]);
	WPAD_IR(WPAD_CHAN_1,&ir[1]);
	WPAD_IR(WPAD_CHAN_2,&ir[2]);
	WPAD_IR(WPAD_CHAN_3,&ir[3]);
	WPAD_Expansion(WPAD_CHAN_0,&expans[0]);
	WPAD_Expansion(WPAD_CHAN_1,&expans[1]);
	WPAD_Expansion(WPAD_CHAN_2,&expans[2]);
	WPAD_Expansion(WPAD_CHAN_3,&expans[3]);
	#ifdef USEACCELEROMETER
	WPAD_GForce(0,&gforce[0]);
	WPAD_GForce(1,&gforce[1]);
	WPAD_GForce(2,&gforce[2]);
	WPAD_GForce(3,&gforce[3]);
	#endif
	//GCButtonsHeld[0]=PAD_ButtonsHeld(0);
	//GCButtonsDown[0]=PAD_ButtonsDown(0);
	//GCButtonsUp[0]=PAD_ButtonsUp(0);
	SYS_SetResetCallback(WiiResetPressed);
	SYS_SetPowerCallback(WiiPowerPressed);
	WPAD_SetPowerButtonCallback(WiimotePowerPressed);
	if(HWButton != -1){SYS_ResetSystem(HWButton, 0, 0);}
	if(ir[0].valid){cursorx[0]=ir[0].x*1.25-80;cursory[0]=ir[0].y*1.25-60;}
	if(ir[1].valid){cursorx[1]=ir[1].x*1.25-80;cursory[1]=ir[1].y*1.25-60;}
	if(ir[2].valid){cursorx[2]=ir[2].x*1.25-80;cursory[2]=ir[2].y*1.25-60;}
	if(ir[3].valid){cursorx[3]=ir[3].x*1.25-80;cursory[3]=ir[3].y*1.25-60;}
	for(int a=0;a<4;a++){
		if(cursorx[a]<0)cursorx[a]=0;
		if(cursorx[a]>640)cursorx[a]=640;
		if(cursory[a]<0)cursory[a]=0;
		if(cursory[a]>480)cursory[a]=480;
	}
}
#endif

