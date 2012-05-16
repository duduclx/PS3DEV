//setup the file system
void setupfilesystem(){
	#ifdef WII
	//while(!fatInitDefault());
	fatInitDefault();
	#endif
}
