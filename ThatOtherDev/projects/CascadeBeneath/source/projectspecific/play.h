void play(float gamespeed){

	//earn points for not getting crushed
	score+=10.f/60.f*gamespeed;

	//the game gets fastet
	float speedup=0.75f+score*0.001f;
	if(speedup>2.f)speedup=2.f;
	gamespeed*=speedup;

	//move and delete walls
	for(int a=0;a<wallcount;a++){
		walllist[a].y+=0.0125*gamespeed;
		if(walllist[a].y>1){
			removewallfromlist(a);
			a--;
		}
	}

	//wallinfo
	float wallx=-0.9f;
	float wally=-1.25f;
	float wallwidth=1.8f;
	float wallheight=0.05f;
	float minwallsize=0.1f;
	float holesize=yousize*3.f;

	//spawn walls
	wallspawntime+=gamespeed;
	if(wallspawntime>22){
		wallspawntime-=22;				
		float holex1=(float)(rand()%(int)(1000.f*(wallwidth-holesize-minwallsize*2.f)))*0.001f+minwallsize;
		float holex2=(float)(rand()%(int)(1000.f*(wallwidth-holesize-minwallsize*2.f)))*0.001f+minwallsize;		
		makewall(
			wallx,
			wally,
			holex1,
			wallheight);
		if(holex1+holex2+holesize*2+minwallsize<wallwidth){
			makewall(
				wallx+holex1+holesize,
				wally,
				holex2,
				wallheight);
			makewall(
				wallx+holex1+holesize+holex2+holesize,
				wally,
				wallwidth-(holex1+holesize+holex2+holesize),
				wallheight);
		}else{
			makewall(
				wallx+holex1+holesize,
				wally,
				wallwidth-(holex1+holesize),
				wallheight);	
		}
	}

	//move
	youxmov-=youxmov*0.175f*gamespeed;
	youymov-=youymov*0.175f*gamespeed;
	youymov-=0.0065*gamespeed;
	#ifdef WIN
	if(keystate[SDLK_LEFT])youxmov-=gamespeed*0.008f;
	if(keystate[SDLK_RIGHT])youxmov+=gamespeed*0.008f;
	#endif
	#ifdef PS3
	float xaxis=((float)paddata[0].ANA_L_H-128.f)/128.f+((float)paddata[0].ANA_R_H-128.f)/128.f;
	if(xaxis<-1)xaxis=-1;
	if(xaxis>1)xaxis=1;
	youxmov+=xaxis*0.008f*gamespeed;
	#endif
	float oldyoux=youx;
	float oldyouy=youy;
	youx+=youxmov*gamespeed;
	youy+=youymov*gamespeed;
	//spherebumpworld(youx,youy,yousize);
	spherebumpworld();
	if(youx!=youx)youx=oldyoux;
	if(youy!=youy)youy=oldyouy;
	youxmov=(youx-oldyoux)/gamespeed;
	youymov=(youy-oldyouy)/gamespeed;

	//gameover
	if(youy>1.f+yousize)resetgame();

}
