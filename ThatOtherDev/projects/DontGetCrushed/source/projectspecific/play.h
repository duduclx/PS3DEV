void play(float gamespeed){

	float worldstart=-350.f*screena;
	float worldend=350.f*screena;
	float floorheight=250.f;

	//earn points for not getting crushed
	score+=10.f/60.f*gamespeed;

	//the game gets faster
	float speedup=1.f+score*0.001f;
	if(speedup>2.f)speedup=2.f;
	gamespeed*=speedup;

	//move
	youmovex-=youmovex*0.2*gamespeed;
	youx+=youmovex*gamespeed;
	#ifdef WIN
	if(keystate[SDLK_LEFT])youmovex-=gamespeed;
	if(keystate[SDLK_RIGHT])youmovex+=gamespeed;
	#endif
	#ifdef PS3
	float xaxis=((float)paddata[0].ANA_L_H-128.f)/128.f+((float)paddata[0].ANA_R_H-128.f)/128.f;
	if(xaxis<-1)xaxis=-1;
	if(xaxis>1)xaxis=1;
	youmovex+=xaxis*1.15*gamespeed;
	#endif
	if(youx<worldstart+30.f)youx=worldstart+30.f;
	if(youx>worldend-30.f)youx=worldend-30.f;

	//spawn new bouncing balls
	if(rand()%(int)(60.f/gamespeed)==0 || n_enemys<4){
		float angle=(rand()%(180-60)-(90-30))*radiansindegree;
		makeenemy(
			worldstart-100.f-(float)(rand()%100),
			floorheight-325+rand()%175,
			2.75*cos(angle),
			2.75*sin(angle),
			rand()%50+20);
	}

	//move the bouncing balls
	for(int a=0;a<n_enemys;a++){
		enemys[a].posx+=enemys[a].movex*1.4*gamespeed;
		enemys[a].posy+=enemys[a].movey*1.4*gamespeed;
		enemys[a].movey+=0.05*1.4*gamespeed;
		if(enemys[a].posy>floorheight-enemys[a].size){
			enemys[a].posy=floorheight-enemys[a].size;
			enemys[a].movey*=-1;
		}
		if(enemys[a].posx>worldend+200.f){
			deleteenemy(a);
			a--;
		}else if(dist2d(enemys[a].posx,enemys[a].posy,youx,floorheight)<enemys[a].size+30){
			resetgame();
		}
	}

}
