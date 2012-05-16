#ifdef SDL
Mix_Music *music = NULL;
#endif

#ifdef WII
long lSize;
char * buffer;
#endif

void musicsetup(){
/*
#ifdef SDL
	Mix_OpenAudio(0,0,0,0);
	music = Mix_LoadMUS("Media/music.ogg");
	Mix_PlayMusic(music, -1);
#endif
*/
#ifdef WII
	ASND_Init();
	MP3Player_Init();
	FILE *BGM = 0;
	size_t result;
	BGM = fopen("Media/music.mp3", "rb");
	fseek (BGM , 0 , SEEK_END);
	lSize = ftell (BGM);
	rewind (BGM);
	buffer = (char*) malloc (sizeof(char)*lSize);
	result = fread (buffer,1,lSize,BGM);
	fclose(BGM);
#endif

}

void musicplay(){

#ifdef WII
	if(!MP3Player_IsPlaying()) {
		MP3Player_PlayBuffer(buffer, lSize, NULL);
	}
#endif

}
