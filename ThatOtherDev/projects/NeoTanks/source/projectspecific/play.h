const float tankmovespeed=0.0005;
const float blastspeed=0.0275*1.5;
const float blastgrav=0.00007*1.75;
const float blastodds=1750;

int tankstocheck=0;
const int tankcheckrange=20;

void play(float gamespeed){

	//generic reusable variables
	float targetdistance,checkdistance,goalangle,angle,distance;
	float startx,starty,startz;
	float inputspeed=0.f,inputangle=0.f;

	if(playertank==NULL){
		//place camera
		camxang=-30*radiansindegree;
		#ifdef PS3
		camxang=-35*radiansindegree;
		#endif
		camyang+=0.002f*gamespeed;
		camzang=0.f;
		float camdist=5.75f;
		#ifdef PS3
		//camdist=4.f;
		#endif
		camxpos=-camdist*cos(camxang)*cos(camyang);
		camypos=1.5;
		#ifdef PS3
		//camypos=1.f;
		#endif
		camzpos=-camdist*cos(camxang)*sin(camyang);
		//start playing
		#ifdef WIN
		if(mousestate[SDL_BUTTON_LEFT]==2)gamestate=2;
		#endif
		#ifdef PS3
		if(BTN_CROSS[0]==2)gamestate=2;
		#endif
		if(gamestate==2){if(rand()%2==0){
			if(redtankcount>0){
				int num=rand()%redtankcount;
				playertank=&redtanklist[num];
				camxang=-20*radiansindegree;
				camyang=playertank->ta;
				camzang=0.f;
			}
		}else{
			if(bluetankcount>0){
				int num=rand()%bluetankcount;
				playertank=&bluetanklist[num];
				camxang=-20*radiansindegree;
				camyang=playertank->ta;
				camzang=0.f;
			}
		}}
	}else{
		//this tank should not be controlled by ai
		playertank->player=1;
		//aim
		#ifdef PS3
		inputspeed=dist2d(0,0,(float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128))/128.f;
		if(inputspeed>0.2f){
			if(inputspeed>1.f)inputspeed=1.f;
			inputangle=atan2((float)(paddata[0].ANA_R_V-128),(float)(paddata[0].ANA_R_H-128));
		}else{
			inputspeed=0.f;
		}
		camyangmov+=cos(inputangle)*inputspeed*0.0075f*gamespeed;
		//camxangmov-=sin(inputangle)*inputspeed*0.0075f*gamespeed;
		camxang+=camxangmov*gamespeed;
		camyang+=camyangmov*gamespeed;
		camxangmov-=camxangmov*0.125*gamespeed;
		camyangmov-=camyangmov*0.125*gamespeed;
		camzangmov-=camzangmov*0.125*gamespeed;
		inputangle=0.f;
		inputspeed=0.f;
		#else
		#ifdef WIN
		if(!mousestate[SDL_BUTTON_RIGHT])
		#endif
		#ifdef WII
		if(!(WiiButtonsHeld[0] & WPAD_BUTTON_A))
		#endif
		if(dashusecursor[0]){
			camyang += (float)(cursorx[0]-screenw/2)/screenw*0.095*gamespeed;
			//camxang -= (float)(cursory[0]-screenh/2)/screenh*0.065*gamespeed;
		}
		#endif
		//get movement input
		#ifdef WIN
		bool up=0,down=0,left=0,right=0;
		if(keystate[SDLK_w]|keystate[SDLK_UP])up=1;
		if(keystate[SDLK_s]|keystate[SDLK_DOWN])down=1;
		if(keystate[SDLK_a]|keystate[SDLK_LEFT])left=1;
		if(keystate[SDLK_d]|keystate[SDLK_RIGHT])right=1;
		inputangle=atan2((float)right-(float)left,(float)up-(float)down)-90.f*radiansindegree;
		inputspeed=dist2d((float)right-(float)left,(float)up-(float)down,0,0);
		if(inputspeed>1.f)inputspeed=1.f;
		#endif
		#ifdef PS3
		inputspeed=dist2d(0,0,(float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128))/128.f;
		if(inputspeed>0.2f){
			if(inputspeed>1.f)inputspeed=1.f;
			inputangle=atan2((float)(paddata[0].ANA_L_V-128),(float)(paddata[0].ANA_L_H-128));
		}else{
			inputspeed=0.f;
		}
		#endif
		#ifdef WII
		inputspeed=expans[0].nunchuk.js.mag;
		if(inputspeed>0.1f){
			if(inputspeed>1.f)inputspeed=1.f;
			inputangle=(expans[0].nunchuk.js.ang)*radiansindegree-90.f*radiansindegree;
		}else{inputspeed=0.f;}
		#endif
		//shoot
		playershootwait-=gamespeed;
		#ifdef WIN
		if(mousestate[SDL_BUTTON_LEFT])
		#endif
		#ifdef WII
		if(WiiButtonsHeld[0] & WPAD_BUTTON_B)
		#endif
		#ifdef PS3
		if(BTN_R1[0])gamestate=2;
		#endif
		if(playershootwait<0){
			startx=playertank->x+0.26*cos(playertank->ta);
			starty=playertank->y+0.18;
			startz=playertank->z+0.26*sin(playertank->ta);
			targetdistance=dist2d(playertank->x,playertank->z,playertank->x,playertank->z+3.5f);
			makeblast(startx,starty,startz,cos(playertank->ta)*blastspeed,((targetdistance-0.26)/blastspeed-0.18)*blastgrav/2,sin(playertank->ta)*blastspeed);
			playershootwait=15.f;
		}
		//move
		playerxposmov=playerxposmov*(1-0.1f*gamespeed)-inputspeed*cos(inputangle+camyang-90.f*radiansindegree)*0.0035f*gamespeed;
		playerzposmov=playerzposmov*(1-0.1f*gamespeed)-inputspeed*sin(inputangle+camyang-90.f*radiansindegree)*0.0035f*gamespeed;
		playertank->x+=playerxposmov*gamespeed;
		playertank->z+=playerzposmov*gamespeed;
		distance=dist2d(0,0,playerxposmov,playerzposmov);
		if(distance>0.f){
			goalangle=atan2(playerzposmov,playerxposmov);
			playertank->ba=turntoangle(playertank->ba,goalangle,distance*1.5f*gamespeed);
		}
		//place camera
		playertank->ta=camyang;
		//camxang=-20*radiansindegree;
		//camyang=playertank->ta;
		//camzang=0.f;
		float camdist=2.5f;
		#ifdef PS3
		//camdist=2.f;
		#endif
		camxpos=playertank->x-camdist*cos(camxang)*cos(camyang);
		camypos=1.5f;//playertank->y-camdist*sin(camxang);
		#ifdef PS3
		//camypos=1.25f;
		#endif
		camzpos=playertank->z-camdist*cos(camxang)*sin(camyang);
	}

	//explosions grow and fade
	for(int a=0; a<explosioncount; a++){
		explosionlist[a].a-=0.030*gamespeed;
		explosionlist[a].s+=0.015*gamespeed;
		if(explosionlist[a].a<0){
			removeexplosionfromlist(a);
			a--;
		}
	}

	//spawn more tanks
	if(redtankcount<maxtankcount)makeredtank(rand()%20-10,0,0-10,90/57.2957795);
	if(bluetankcount<maxtankcount)makebluetank(rand()%20-10,0,0+10,270/57.2957795);
	
	//find the closest target
	for(int a=tankstocheck; a<lowint(redtankcount,tankstocheck+tankcheckrange); a++)
	if(!redtanklist[a].player){
		targetdistance=dist2d(redtanklist[a].x,redtanklist[a].z,
			bluetanklist[redtanklist[a].target].x,bluetanklist[redtanklist[a].target].z);
		checkdistance=0;
		for(int b=0; b<bluetankcount; b++){
			checkdistance=mindist2d(
				redtanklist[a].x,redtanklist[a].z,
				bluetanklist[b].x,bluetanklist[b].z,
				targetdistance);
			if(checkdistance<targetdistance){
				redtanklist[a].target=b;
				targetdistance=checkdistance;
			}
		}
	}
	for(int a=tankstocheck; a<lowint(bluetankcount,tankstocheck+tankcheckrange); a++)
	if(!bluetanklist[a].player){
		targetdistance=dist2d(bluetanklist[a].x,bluetanklist[a].z,
			redtanklist[bluetanklist[a].target].x,redtanklist[bluetanklist[a].target].z);
		checkdistance=0;
		for(int b=0; b<redtankcount; b++){
			checkdistance=mindist2d(
				bluetanklist[a].x,bluetanklist[a].z,
				redtanklist[b].x,redtanklist[b].z,
				targetdistance);
			if(checkdistance<targetdistance){
				bluetanklist[a].target=b;
				targetdistance=checkdistance;
			}
		}
	}

	//turn tanks to face their target
	for(int a=0; a<redtankcount; a++)if(!redtanklist[a].player){
		goalangle=atan2(
			bluetanklist[redtanklist[a].target].z-redtanklist[a].z,
			bluetanklist[redtanklist[a].target].x-redtanklist[a].x);
		redtanklist[a].ba=turntoangle(redtanklist[a].ba,goalangle,0.010*gamespeed);
		redtanklist[a].ta=turntoangle(redtanklist[a].ta,goalangle,0.045*gamespeed);
	}
	for(int a=0; a<bluetankcount; a++)if(!bluetanklist[a].player){
		goalangle=atan2(
			redtanklist[bluetanklist[a].target].z-bluetanklist[a].z,
			redtanklist[bluetanklist[a].target].x-bluetanklist[a].x);
		bluetanklist[a].ba=turntoangle(bluetanklist[a].ba,goalangle,0.010*gamespeed);
		bluetanklist[a].ta=turntoangle(bluetanklist[a].ta,goalangle,0.045*gamespeed);
	}

	//tanks move forward
	for(int a=0; a<redtankcount; a++)if(!redtanklist[a].player){
		redtanklist[a].xm-=redtanklist[a].xm*0.1*gamespeed;
		redtanklist[a].zm-=redtanklist[a].zm*0.1*gamespeed;
		redtanklist[a].xm+=cos(redtanklist[a].ba)*tankmovespeed*gamespeed;
		redtanklist[a].zm+=sin(redtanklist[a].ba)*tankmovespeed*gamespeed;
		redtanklist[a].x+=redtanklist[a].xm*gamespeed;
		redtanklist[a].z+=redtanklist[a].zm*gamespeed;
	}
	for(int a=0; a<bluetankcount; a++)if(!bluetanklist[a].player){
		bluetanklist[a].xm-=bluetanklist[a].xm*0.1*gamespeed;
		bluetanklist[a].zm-=bluetanklist[a].zm*0.1*gamespeed;
		bluetanklist[a].xm+=cos(bluetanklist[a].ba)*tankmovespeed*gamespeed;
		bluetanklist[a].zm+=sin(bluetanklist[a].ba)*tankmovespeed*gamespeed;
		bluetanklist[a].x+=bluetanklist[a].xm*gamespeed;
		bluetanklist[a].z+=bluetanklist[a].zm*gamespeed;
	}

	//tanks shoot
	if(bluetankcount)for(int a=0; a<redtankcount; a++)
	if(!redtanklist[a].player)
		if(rand()%((int)(blastodds/gamespeed))==0){
		startx=redtanklist[a].x+0.26*cos(redtanklist[a].ta);
		starty=redtanklist[a].y+0.18;
		startz=redtanklist[a].z+0.26*sin(redtanklist[a].ta);
		targetdistance=dist2d(redtanklist[a].x,redtanklist[a].z,
			bluetanklist[redtanklist[a].target].x,bluetanklist[redtanklist[a].target].z);
		makeblast(startx,starty-0.18,startz,
			cos(redtanklist[a].ta)*blastspeed,
			((targetdistance-0.26)/blastspeed-0.18)*blastgrav/2,
			sin(redtanklist[a].ta)*blastspeed);
	}
	if(redtankcount)for(int a=0; a<bluetankcount; a++)
	if(!bluetanklist[a].player)
		if(rand()%((int)(blastodds/gamespeed))==0){
		startx=bluetanklist[a].x+0.26*cos(bluetanklist[a].ta);
		starty=bluetanklist[a].y+0.18;
		startz=bluetanklist[a].z+0.26*sin(bluetanklist[a].ta);
		targetdistance=dist2d(bluetanklist[a].x,bluetanklist[a].z,
			redtanklist[bluetanklist[a].target].x,redtanklist[bluetanklist[a].target].z);
		makeblast(startx,starty-0.18,startz,
			cos(bluetanklist[a].ta)*blastspeed,
			((targetdistance-0.26)/blastspeed-0.18)*blastgrav/2,
			sin(bluetanklist[a].ta)*blastspeed);
	}

	//blasts move forward and get pulled down by gravity
	for(int a=0; a<blastcount; a++){
		blastlist[a].ym-=blastgrav*gamespeed;
		blastlist[a].x+=blastlist[a].xm*gamespeed;
		blastlist[a].y+=blastlist[a].ym*gamespeed;
		blastlist[a].z+=blastlist[a].zm*gamespeed;
	}

	//bump harmlessly into friendly tanks
	for(int a=tankstocheck; a<lowint(redtankcount,tankstocheck+tankcheckrange); a++)
	for(int b=0; b<redtankcount; b++)if(b!=a){
		distance=mindist2d(redtanklist[a].x,redtanklist[a].z,redtanklist[b].x,redtanklist[b].z,0.5);
		if(distance<0.5){
			angle=atan2(redtanklist[a].z-redtanklist[b].z,redtanklist[a].x-redtanklist[b].x);
			redtanklist[a].xm+=cos(angle)*(0.5-distance)*0.015*gamespeed;
			redtanklist[a].zm+=sin(angle)*(0.5-distance)*0.015*gamespeed;
			redtanklist[b].xm-=cos(angle)*(0.5-distance)*0.015*gamespeed;
			redtanklist[b].zm-=sin(angle)*(0.5-distance)*0.015*gamespeed;
		}
	}
	for(int a=tankstocheck; a<lowint(bluetankcount,tankstocheck+tankcheckrange); a++)
	for(int b=0; b<bluetankcount; b++)if(b!=a){
		distance=mindist2d(bluetanklist[a].x,bluetanklist[a].z,bluetanklist[b].x,bluetanklist[b].z,0.55f);
		if(distance<0.5f){
			angle=atan2(bluetanklist[a].z-bluetanklist[b].z,bluetanklist[a].x-bluetanklist[b].x);
			bluetanklist[a].xm+=cos(angle)*(0.5f-distance)*0.015f*gamespeed;
			bluetanklist[a].zm+=sin(angle)*(0.5f-distance)*0.015f*gamespeed;
			bluetanklist[b].xm-=cos(angle)*(0.5f-distance)*0.015f*gamespeed;
			bluetanklist[b].zm-=sin(angle)*(0.5f-distance)*0.015f*gamespeed;
		}
	}

	//ram into enemy tanks and explode
	for(int a=tankstocheck; a<lowint(redtankcount,tankstocheck+tankcheckrange); a++)
	for(int b=0; b<bluetankcount; b++){
		distance=mindist2d(redtanklist[a].x,redtanklist[a].z,bluetanklist[b].x,bluetanklist[b].z,0.5f);
		if(distance<0.45f){
			makeexplosion(
				(redtanklist[a].x+bluetanklist[b].x)*0.5f,
				(redtanklist[a].y+bluetanklist[b].y)*0.5f,
				(redtanklist[a].z+bluetanklist[b].z)*0.5f,0.3f);
		}
	}

	//blasts hit the ground
	for(int a=0; a<blastcount; a++)if(blastlist[a].y<0){
		makeexplosion(blastlist[a].x,0,blastlist[a].z,0.3);
		removeblastfromlist(a);
		a-=1;
	}

	//new explosions destroy stuff
	for(int a=0; a<explosioncount; a++)if(explosionlist[a].a==1){
		for(int b=0; b<redtankcount; b++)
		if(mindist2d(explosionlist[a].x,explosionlist[a].z,redtanklist[b].x,redtanklist[b].z,0.75)<0.75){
			for(int c=0; c<bluetankcount; c++){
				if(bluetanklist[c].target==b)bluetanklist[c].target=0;
				if(bluetanklist[c].target>b)bluetanklist[c].target-=1;
			}
			if(redtanklist[b].player==1){
				playertank=NULL;
				gamestate=1;
			}
			removeredtankfromlist(b);
			b-=1;
		}
		for(int b=0; b<bluetankcount; b++)
		if(mindist2d(explosionlist[a].x,explosionlist[a].z,bluetanklist[b].x,bluetanklist[b].z,0.75)<0.75){
			for(int c=0; c<redtankcount; c++){
				if(redtanklist[c].target==b)redtanklist[c].target=0;
				if(redtanklist[c].target>b)redtanklist[c].target-=1;
			}
			if(bluetanklist[b].player==1){
				playertank=NULL;
				gamestate=1;
			}
			removebluetankfromlist(b);
			b-=1;
		}
	}

	tankstocheck+=tankcheckrange;
	if(tankstocheck>redtankcount && tankstocheck>bluetankcount)tankstocheck=0;
	
}
