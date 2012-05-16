GLuint loadtoif(char* filename,bool mipmap){
	int xsize=64;
	int ysize=64;
	ifstream indata;
	indata.open(filename);
	if(indata){
		indata >> xsize;
		indata >> ysize;
	}
	GLubyte* checkImage;
	checkImage=new GLubyte [ysize*xsize*4];
	for(int a=0; a<ysize*xsize*4; a++)checkImage[a]=255;
	if(indata.good()){
		int r=0,g=0,b=0,a=255;
		for(int y=0;y<ysize;y++)for(int x=0;x<xsize;x++){
			if(indata.good())indata >> r;
			if(indata.good())indata >> g;
			if(indata.good())indata >> b;
			if(indata.good())indata >> a;
			checkImage[(ysize-y-1)*xsize*4+x*4+0]=(GLubyte)r;
			checkImage[(ysize-y-1)*xsize*4+x*4+1]=(GLubyte)g;
			checkImage[(ysize-y-1)*xsize*4+x*4+2]=(GLubyte)b;
			checkImage[(ysize-y-1)*xsize*4+x*4+3]=(GLubyte)a;
		}
		indata.close();
	}
	GLuint texName;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
	glGenTextures(1,&texName);
	glBindTexture(GL_TEXTURE_2D,texName);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	if(mipmap){
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,xsize,ysize,
			GL_RGBA,GL_UNSIGNED_BYTE,checkImage);
	}else{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,xsize,ysize,
			0,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);
	}
	delete checkImage;
	return texName;
}
