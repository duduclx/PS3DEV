#ifdef SDL
Mix_Music *music = NULL;
#endif

#ifdef WII
long lSize;
char * buffer;
#endif

void musicsetup(){
	
#ifdef SDL
	Mix_OpenAudio(0,0,0,0);
	music = Mix_LoadMUS("Media/music.ogg");
	//Mix_VolumeMusic(75);
	Mix_PlayMusic(music, -1);
#endif

/*#ifdef WII
	ASND_Init();
	MP3Player_Init();
	FILE *BGM = 0;
	long lSize;
	char * buffer;
	size_t result;
	//BGM = fopen(temptext, "rb");
	BGM = fopen("Media/music.mp3", "rb");
	fseek (BGM , 0 , SEEK_END);
	lSize = ftell (BGM);
	rewind (BGM);
	buffer = (char*) malloc (sizeof(char)*lSize);
	result = fread (buffer,1,lSize,BGM);
	fclose(BGM);

	MP3Player_PlayBuffer(buffer, lSize, NULL);
	free(buffer);
#endif*/

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
		/*FILE *BGM = 0;
		long lSize;
		char * buffer;
		size_t result;
		BGM = fopen("Media/music.mp3", "rb");
		fseek (BGM , 0 , SEEK_END);
		lSize = ftell (BGM);
		rewind (BGM);
		buffer = (char*) malloc (sizeof(char)*lSize);
		result = fread (buffer,1,lSize,BGM);
		fclose(BGM);*/
		MP3Player_PlayBuffer(buffer, lSize, NULL);
		//free(buffer);
	}
	#endif

}
