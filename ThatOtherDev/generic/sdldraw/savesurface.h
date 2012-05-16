//SDL_SaveBMP(,);

void SDL_SavePNG(SDL_Surface *surfacetosave,char* filename){

	int w=surfacetosave->w;
	int h=surfacetosave->h;
	
	Uint32 color=0;

	SDL_PixelFormat *fmt = screen->format;
	Uint32 rmask=fmt->Rmask,rshift=fmt->Rshift,rloss=fmt->Rloss;
	Uint32 gmask=fmt->Gmask,gshift=fmt->Gshift,gloss=fmt->Gloss;
	Uint32 bmask=fmt->Bmask,bshift=fmt->Bshift,bloss=fmt->Bloss;

	std::vector<unsigned char> image;
	image.resize(w * h * 4);
	for(int y = 0; y < h; y++)for(int x = 0; x < w; x++){
		color=getpixel(surfacetosave,x,y);
		image[4*w*y+4*x+0] = (unsigned char)((color&rmask)>>rshift)<<rloss;
		image[4*w*y+4*x+1] = (unsigned char)((color&gmask)>>gshift)<<gloss;
		image[4*w*y+4*x+2] = (unsigned char)((color&bmask)>>bshift)<<bloss;
		image[4*w*y+4*x+3] = (unsigned char)255;
	}

	//create encoder and set settings and info (optional)
	LodePNG::Encoder encoder;
	encoder.addText("Comment", "Created with LodePNG");
	encoder.getSettings().zlibsettings.windowSize = 2048;
	
	//encode and save
	std::vector<unsigned char> buffer;
	encoder.encode(buffer, image.empty() ? 0 : &image[0], w, h);
	LodePNG::saveFile(buffer, filename);

}
