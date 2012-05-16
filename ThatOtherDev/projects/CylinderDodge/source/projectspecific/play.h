float cylinderspawnwait=0;

void play(float gamespeed){

	score+=0.2f*gamespeed;

	plrxpos+=1.35*gamespeed;

	#ifdef WII
	float speed=(float)gforce[0].y;
	speed*=0.95;
	if(speed>=1.f)speed=1.f;
	if(speed<=-1.f)speed=-1.f;
	plrzmov-=speed*0.025f*gamespeed;
	#endif

	#ifdef WIN
	if(keystate[SDLK_a]|keystate[SDLK_LEFT])
		plrzmov-=0.025f*gamespeed;
	if(keystate[SDLK_d]|keystate[SDLK_RIGHT])
		plrzmov+=0.025f*gamespeed;
	#endif

	#ifdef PS3
	float speed=-(float)(paddata[0].ANA_L_H-128)/128.f-(float)(paddata[0].ANA_R_H-128)/128.f;
	if(speed>=1.f)speed=1.f;
	if(speed<=-1.f)speed=-1.f;
	plrzmov-=speed*0.025f*gamespeed;
	#endif

	plrzpos+=plrzmov*gamespeed;
	plrzmov-=plrzmov*0.06*gamespeed;

	cylinderspawnwait-=gamespeed;
	while(cylinderspawnwait<0 && cylindercount<maxcylindercount){
		makecylinder(plrxpos+275.f,0.f,plrzpos+(float)(rand()%2800-1400)*0.125f);
		cylinderspawnwait+=1.25f;
	}
	for(int a=0;a<cylindercount;a++){
		if(cylinderlist[a].xpos<camxpos-5){
			removecylinderfromlist(a);
		}else{
			//cylinder radius = 1.2
			//sphere radius = 1.65
			if(mindist2d(
				plrxpos,
				plrzpos,
				cylinderlist[a].xpos,
				cylinderlist[a].zpos,
				3)<2.85){
				gamestate=3;
			}
		}
	}

	camxang=-27.5*radiansindegree;
	camyang=0;
	camzang=0;

	float camxposg=plrxpos;
	float camyposg=plrypos+10.5;
	float camzposg=plrzpos;
	//movein3dspace(camxposg,camyposg,camzposg,camyang,camxang,-5);
	#ifdef PS3
	camxang-=3.5f*radiansindegree;
	camyposg-=3.f*sin(camxang);
	camxposg-=3.f*cos(camxang)*cos(camyang);
	camzposg-=3.f*cos(camxang)*sin(camyang);
	#else
	camyposg-=5.f*sin(camxang);
	camxposg-=5.f*cos(camxang)*cos(camyang);
	camzposg-=5.f*cos(camxang)*sin(camyang);
	#endif

	camxpos+=(camxposg-camxpos)*0.11*gamespeed;
	camypos+=(camyposg-camypos)*0.03*gamespeed;
	camzpos+=(camzposg-camzpos)*0.03*gamespeed;

	camyang=(camzposg-camzpos)*0.025;

}
