//http://www.codeproject.com/KB/cpp/endianness.aspx

unsigned long EndianFlipUnsignedLong(unsigned long nLongNumber){
   return (((nLongNumber&0x000000FF)<<24)+((nLongNumber&0x0000FF00)<<8)+
   ((nLongNumber&0x00FF0000)>>8)+((nLongNumber&0xFF000000)>>24));
}

long EndianFlipLong(long nLongNumber){
   return (((nLongNumber&0x000000FF)<<24)+((nLongNumber&0x0000FF00)<<8)+
   ((nLongNumber&0x00FF0000)>>8)+((nLongNumber&0xFF000000)>>24));
}

unsigned short EndianFlipUnsignedShort(unsigned short nValue){
	return (((nValue>> 8)) | (nValue << 8));
}

short EndianFlipShort(short nValue){
	return (((nValue>> 8)) | (nValue << 8));
}

GLuint loadbmp(char* filename,bool mipmap){

	unsigned short Type;          // signature - 'BM'
	unsigned long  Size;          // file size in bytes
	unsigned short Reserved1;     // 0
	unsigned short Reserved2;     // 0
	unsigned long  OffBits;       // offset to bitmap
	unsigned long  StructSize;    // size of this struct (40)
	unsigned long  Width;         // bmap width in pixels
	unsigned long  Height;        // bmap height in pixels
	unsigned short Planes;        // num planes - always 1
	unsigned short BitCount;      // bits per pixel
	unsigned long  Compression;   // compression flag
	unsigned long  SizeImage;     // image size in bytes
	long           XPelsPerMeter; // horz resolution
	long           YPelsPerMeter; // vert resolution
	unsigned long  ClrUsed;       // 0 -> color table size
	unsigned long  ClrImportant;  // important color count

	unsigned char	*pPixels = NULL;

	FILE	*fp = NULL;

	fp = fopen(filename,"r");

	fread(&Type,sizeof(unsigned short),1,fp);
	fread(&Size,sizeof(unsigned long),1,fp);
	fread(&Reserved1,sizeof(unsigned short),1,fp);
	fread(&Reserved2,sizeof(unsigned short),1,fp);
	fread(&OffBits,sizeof(unsigned long),1,fp);
	fread(&StructSize,sizeof(unsigned long),1,fp);
	fread(&Width,sizeof(unsigned long),1,fp);
	fread(&Height,sizeof(unsigned long),1,fp);
	fread(&Planes,sizeof(unsigned short),1,fp);
	fread(&BitCount,sizeof(unsigned short),1,fp);
	fread(&Compression,sizeof(unsigned long),1,fp);
	fread(&SizeImage,sizeof(unsigned long),1,fp);
	fread(&XPelsPerMeter,sizeof(long),1,fp);
	fread(&YPelsPerMeter,sizeof(long),1,fp);
	fread(&ClrUsed,sizeof(unsigned long),1,fp);
	fread(&ClrImportant,sizeof(unsigned long),1,fp);

#ifndef WIN32
	Type = EndianFlipUnsignedShort(Type);
	Size = EndianFlipUnsignedLong(Size);
	Reserved1 = EndianFlipUnsignedShort(Reserved1);
	Reserved2 = EndianFlipUnsignedShort(Reserved2);
	OffBits = EndianFlipUnsignedLong(OffBits);
	StructSize = EndianFlipUnsignedLong(StructSize);
	Width = EndianFlipUnsignedLong(Width);
	Height = EndianFlipUnsignedLong(Height);
	Planes = EndianFlipUnsignedShort(Planes);
	BitCount = EndianFlipUnsignedShort(BitCount);
	Compression = EndianFlipUnsignedLong(Compression);
	SizeImage = EndianFlipUnsignedLong(SizeImage);
	XPelsPerMeter = EndianFlipLong(XPelsPerMeter);
	YPelsPerMeter = EndianFlipLong(YPelsPerMeter);
	ClrUsed = EndianFlipUnsignedLong(ClrUsed);
	ClrImportant = EndianFlipUnsignedLong(ClrImportant);
#endif

	pPixels = new unsigned char[Width * Height * BitCount];
	fread(pPixels, BitCount, Width * Height, fp);
	fclose(fp);

	GLuint texName;
	glGenTextures(1,&texName);
	glBindTexture(GL_TEXTURE_2D,texName);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	if(mipmap){
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		/*if(BitCount==16)
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB16,Width,Height,
			#ifdef WIN32
			GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
			#else
			GL_BGR,GL_UNSIGNED_BYTE,pPixels);
			#endif*/
		if(BitCount==24)
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,Width,Height,
			#ifdef WIN32
			GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
			#else
			GL_BGR,GL_UNSIGNED_BYTE,pPixels);
			#endif
		if(BitCount==32)
			gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,Width,Height,
			GL_BGRA,GL_UNSIGNED_BYTE,pPixels);
	}else{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		/*if(BitCount==16)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Width,Height,
			#ifdef WIN32
			0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
			#else
			0,GL_BGR,GL_UNSIGNED_BYTE,pPixels);
			#endif*/
		if(BitCount==24)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,Width,Height,
			#ifdef WIN32
			0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixels);
			#else
			0,GL_BGR,GL_UNSIGNED_BYTE,pPixels);
			#endif
		if(BitCount==32)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,Width,Height,
			0,GL_BGRA,GL_UNSIGNED_BYTE,pPixels);
	}

	delete pPixels;

	return texName;

}
