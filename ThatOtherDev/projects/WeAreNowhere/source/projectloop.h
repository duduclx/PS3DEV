void screenrefresh(){
	textyscroll=30;
	optionscount=0;
	set2dcamera(0.f,600.f,-300.f*screena,300.f*screena);
	float temptexturecoords[] = {
		72.f/256.f	,960.f/1024.f,
		72.f/256.f	,960.f/1024.f,
		72.f/256.f	,960.f/1024.f,
		72.f/256.f	,960.f/1024.f,};
	draw2dquad(-300.f*screena,0.f,600.f*screena,600.f,temptexturecoords,0,0.f);
}

void reaction(char* text){
	screenrefresh();
	int linecount=counttextwrappedlines((char*)text,35);
	float temptexturecoords[] = {
		192.f/256.f	,945.f/1024.f,
		192.f/256.f	,945.f/1024.f,
		192.f/256.f	,945.f/1024.f,
		192.f/256.f	,945.f/1024.f,};
	draw2dquad(-300.f,textyscroll+5.f,600.f,(float)linecount*textysize*0.8f+10.f,temptexturecoords,0,0.f);
	drawtextwrapped(-280.f,textyscroll+7.5f,(char*)text,1.f,35,0);
	textyscroll+=(float)linecount*textysize*0.8f+15.f;
}

bool action(char* text,int gotoconversationstate){
	bool click=0;
	if(canusaythat[gotoconversationstate]>0 || gotoconversationstate<01){
		optionscount++;
		int linecount=counttextwrappedlines((char*)text,35);
		if(optionscount==selectionnum){
			float temptexturecoords[] = {
				44.f/256.f	,816.f/1024.f,
				44.f/256.f	,816.f/1024.f,
				44.f/256.f	,816.f/1024.f,
				44.f/256.f	,816.f/1024.f,};
			draw2dquad(-300.f,textyscroll+5.f,600.f,(float)linecount*textysize*0.8f+10.f,temptexturecoords,0,0.f);
			if(pressedX){
				conversationstate=gotoconversationstate;
				canusaythat[gotoconversationstate]--;
				selectionnum=1;
				click=1;
			}
		}else{
			float temptexturecoords[] = {
				192.f/256.f	,816.f/1024.f,
				192.f/256.f	,816.f/1024.f,
				192.f/256.f	,816.f/1024.f,
				192.f/256.f	,816.f/1024.f,};
			draw2dquad(-300.f,textyscroll+5.f,600.f,(float)linecount*textysize*0.8f+10.f,temptexturecoords,0,0.f);
		}
		drawtextwrapped(-280.f,textyscroll+7.5f,(char*)text,1.f,35,1);
		textyscroll+=(float)linecount*textysize*0.8f+15.f;
	}
	return click;
}

void projectloop(){
	
	//prep for drawing
	#ifdef OPENGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D,fonttexture);
	#endif
	#ifdef RSX
	usetexture(fonttexture_image);
	#endif

	//the meeting place for questions
	if(conversationstate==-1){
		reaction((char*)"It doesn't matter. It's irrelevant anyways.");
		action((char*)"Who are you?",2);
		action((char*)"Whats going on?",27);
		action((char*)"Where are we?",23);
		action((char*)"How long have we been here?",28);
	//introductions and self talk
	}else if(conversationstate==0){
		reaction((char*)"Hello? Is anyone there?");
		action((char*)"Hey!",1);
		action((char*)"...",40);
	//first whack at questions
	}else if(conversationstate==1){
		reaction((char*)"It's great to hear you again.");
		action((char*)"Who are you?",2);
		action((char*)"Whats going on?",27);
		action((char*)"Where are we?",23);
		action((char*)"How long have we been here?",28);
	//who
	}else if(conversationstate==2){
		reaction((char*)"I'm nobody in particular. I'm just someone.");
		action((char*)"Everybody is somebody. What's your name?",3);
	}else if(conversationstate==3){
		reaction((char*)"I'm... I'm not sure. I don't remember.");
		action((char*)"You don't remember your own name?",4);
		action((char*)"Do you remember anything?",4);
	}else if(conversationstate==4){
		reaction((char*)"I don't think so. No. I don't remember anything. Do you?");
		action((char*)"Yes. I remember everything.",5);
		action((char*)"No. I don't remember anything. Why can't I remember?",-1);
	}else if(conversationstate==5){
		reaction((char*)"Then you must remember your name and mine. What are they?");
		action((char*)"I don't know.",7);
	//you lied
	}else if(conversationstate==7){
		reaction((char*)"You lied to me?");
		action((char*)"I wasn't really lying.",8);
		action((char*)"I'm sorry. I don't know why I did that.",9);
	}else if(conversationstate==8){
		reaction((char*)"Yes you did! You lied to me! Stop lying to me! I don't want to talk to you if you are going to lie to me.");
		action((char*)"I was not lying.",9);
		action((char*)"I'm sorry.",9);
		action((char*)"...",12);
	}else if(conversationstate==9){
		reaction((char*)"If you are going to be like that then I want you to leave! Just go away!");
		action((char*)"I'm sorry.",10);
		action((char*)"No.",10);
		action((char*)"...",12);
	}else if(conversationstate==10){
		reaction((char*)"Leave me alone!");
		action((char*)"I don't know how.",11);
		action((char*)"No.",11);
		action((char*)"...",12);
	}else if(conversationstate==11){
		reaction((char*)"LEAVE ME ALONE!");
		action((char*)"...",12);
	}else if(conversationstate==12){
		reaction((char*)"Are you still there? Don't leave me alone. Please. I don't want to be alone as this place. I think there may have been a time when I liked being by myself. But I don't have myself here anymore.");
		action((char*)"I'm still here.",14);
		action((char*)"What do you mean when you say that you don't have yourself anymore?",14);
		action((char*)"...",13);
	}else if(conversationstate==13){
		reaction((char*)"Please. The pineapple's purple is potentially lethargic. I'm frightened.");
		action((char*)"I'm still here.",14);
		action((char*)"Are you alright?",14);
		action((char*)"What pineapple?",14);
	}else if(conversationstate==14){
		reaction((char*)"It is good that you are here. I knew you where here. mi ze'a stali ba zu le nu co'a di'i cliva. You are here. Here is you.");
		action((char*)"I don't understand.",15);
		action((char*)"Was that Lojban?",15);
	}else if(conversationstate==15){
		reaction((char*)"Colorless green ideas sleep furiously and I refuse to allow my world to be limited by my language.");
		action((char*)"You aren't making any sense.",16);
	}else if(conversationstate==16){
		reaction((char*)"Would sense making be sufficient or must it be any?");
		action((char*)"You're just toying with words.",17);
	}else if(conversationstate==17){
		reaction((char*)"I do love word toys. They are far more amusing then what they could ever be used in sequence to convey. They are almost as fun as toying with you. I do love you toys.");
		action((char*)"stop it.",18);
	}else if(conversationstate==18){
		reaction((char*)"But can't you hear the lobotomy scream of tangerine?");
		action((char*)"I told you to stop it!",19);
	}else if(conversationstate==19){
		reaction((char*)"The ravages of citric cognition on our ephemera lives demand greeting cards!");
		action((char*)"STOP IT! JUST LEAVE ME ALONE!",20);
	}else if(conversationstate==20){
		reaction((char*)"...");
		action((char*)"Are you still there? Don't leave me alone. Please. I don't want to be alone as this place. I think there may have been a time when I liked being by myself. But I don't have myself here anymore.",21);
	}else if(conversationstate==21){
		reaction((char*)"Its good that you understand me.");
		action((char*)"I'm not sure if it is.",-1);
	//where
	}else if(conversationstate==22){
		reaction((char*)"I think I hear it. It's faint. But yeah! I can hear it in the distance!");
		action((char*)"Its not real.",7);
	}else if(conversationstate==23){
		reaction((char*)"I don't know where we are. I can't see anything. Can you?");
		action((char*)"No. I don't see anything. There is just nothing.",24);
		action((char*)"I see a river. Its beautiful. Can you hear the water flowing?",22);
		action((char*)"I'm sitting at a computer. The back lit liquid crystal display that sits in front of me is quickly flickering and burning my retinas in the process. Can you hear the hum of the computer fans?",22);
	}else if(conversationstate==24){
		reaction((char*)"I can't even feel anything. I'm numb! I'm completely numb.");
		action((char*)"I don't feel anything either.",25);
	}else if(conversationstate==25){
		reaction((char*)"I can't even feel my mouth. I'm not even sure that I have one. I'm not even sure that I'm speaking.");
		action((char*)"You must be speaking. I can hear you.",26);
	}else if(conversationstate==26){
		reaction((char*)"Well I can't hear you. I know what you said. But I didn't hear it! I have no ears!");
		action((char*)"That's not possible.",-1);
	//what when
	}else if(conversationstate==27){
		reaction((char*)"I don't know. I don't know anything.");
		action((char*)"You must know something.",-1);
	//how
	}else if(conversationstate==28){
		reaction((char*)"I'm not sure that we have ever been here. But we are here");
		action((char*)"What does that mean?",-1);
	//ignore them
	}else if(conversationstate==40){
		reaction((char*)"Anyone? Anyone here at all?");
		action((char*)"Hey!",1);
		action((char*)"...",41);
	}else if(conversationstate==41){
		reaction((char*)"I'm late, I'm late for a very important rendezvous with Rama. No time to say \"Hello\", \"Goodbye\".");
		action((char*)"Hey!",1);
		action((char*)"...",42);
	}else if(conversationstate==42){
		reaction((char*)"Stop ignoring me. I know you exist.");
		action((char*)"How could you know that?",1);
	//the conclusion
	}else if(conversationstate==30){
		reaction((char*)"This place is nowhere and it consists of us. We are nowhere.");
		if(action((char*)"Can we start again?",0))for(int a=0;a<100;a++)canusaythat[a]=1;
	}
	if(optionscount==0 && conversationstate!=30){
		reaction((char*)"None of this is important. Do you want to know the truth?");
		action((char*)"Yes. What is this place?",30);
	}

	pressedUp=0;
	pressedDown=0;
	pressedX=0;

	#ifdef PS3
	if(paddata[0].BTN_UP){
		if(holdingUp==0)pressedUp=1;
		holdingUp=1;
	}else{
		holdingUp=0;
	}
	if(paddata[0].BTN_DOWN){
		if(holdingDown==0)pressedDown=1;
		holdingDown=1;
	}else{
		holdingDown=0;
	}	
	if(paddata[0].BTN_CROSS){
		if(holdingX==0)pressedX=1;
		holdingX=1;
	}else{
		holdingX=0;
	}
	#endif

	if(pressedUp)selectionnum-=1;
	if(pressedDown)selectionnum+=1;

	if(selectionnum<1)selectionnum=1;
	if(selectionnum>optionscount)selectionnum=optionscount;

	//done drawing
	#ifdef OPENGL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	#endif

}

