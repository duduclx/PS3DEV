#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <png.h>

#include <pngdec/loadpng.h>

#include <rsx/reality.h>
#include <rsx/commands.h>
#include <rsx/nv40.h>

#include "texture.h"

extern gcmContextData *context;

void load_tex(uint32_t unit, uint32_t offset, uint32_t width, uint32_t height, uint32_t stride, uint32_t fmt, int smooth ){
	realityTexture tex;
	tex.swizzle =
		NV30_3D_TEX_SWIZZLE_S0_X_S1 | NV30_3D_TEX_SWIZZLE_S0_Y_S1 |
		NV30_3D_TEX_SWIZZLE_S0_Z_S1 | NV30_3D_TEX_SWIZZLE_S0_W_S1 |
		NV30_3D_TEX_SWIZZLE_S1_X_X | NV30_3D_TEX_SWIZZLE_S1_Y_Y |
		NV30_3D_TEX_SWIZZLE_S1_Z_Z | NV30_3D_TEX_SWIZZLE_S1_W_W ;

	tex.offset = offset;

	tex.format = fmt |
		NV40_3D_TEX_FORMAT_LINEAR  | 
		NV30_3D_TEX_FORMAT_DIMS_2D |
		NV30_3D_TEX_FORMAT_DMA0 |
		NV30_3D_TEX_FORMAT_NO_BORDER | (0x8000) |
		(1 << NV40_3D_TEX_FORMAT_MIPMAP_COUNT__SHIFT);

	tex.wrap =
		NV30_3D_TEX_WRAP_S_REPEAT |
		NV30_3D_TEX_WRAP_T_REPEAT |
		NV30_3D_TEX_WRAP_R_REPEAT;
	//tex->wrap =
	//	NV30_3D_TEX_WRAP_S_CLAMP_TO_EDGE | 
	//	NV30_3D_TEX_WRAP_T_CLAMP_TO_EDGE | 
	//	NV30_3D_TEX_WRAP_R_CLAMP_TO_EDGE;

	tex.enable = NV40_3D_TEX_ENABLE_ENABLE;

	if(smooth)
		tex.filter =
			NV30_3D_TEX_FILTER_MIN_LINEAR |
			NV30_3D_TEX_FILTER_MAG_LINEAR | 0x3fd6;
	else
		tex.filter =
			NV30_3D_TEX_FILTER_MIN_NEAREST |
			NV30_3D_TEX_FILTER_MAG_NEAREST | 0x3fd6;

	tex.width = width;
	tex.height = height;
	tex.stride = stride;

	realitySetTexture(context, unit, &tex);

}

void ReadDataFromMemory(png_structp png_ptr, png_bytep outBytes, 
	png_size_t byteCountToRead);
void *seek; // Yeah, this isn't threadsafe, so only load 1 png at a time.

void parseRGB(uint32_t *dest, uint32_t width, uint32_t height,
		png_structp png_ptr, png_infop info_ptr) {

	png_uint_32 bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
	uint8_t *rowData = malloc(bytesPerRow);

	// Read each row
	int row, col;
	for(row = 0; row < height; row++) {
		png_read_row(png_ptr, (png_bytep) rowData, NULL);

		int index = 0;
		for(col = 0; col < width; col++) {
			uint8_t red   = rowData[index++];
			uint8_t green = rowData[index++];
			uint8_t blue  = rowData[index++];

			*dest = red << 16 | green << 8 | blue;
			dest++;	
		}
	}

	free(rowData);
}

void parseRGBA(uint32_t *dest, uint32_t width, uint32_t height,
		png_structp png_ptr, png_infop info_ptr) {

	png_uint_32 bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
	uint8_t *rowData = malloc(bytesPerRow);

	// Read each row
	int row, col;
	for(row = 0; row < height; row++) {
		png_read_row(png_ptr, (png_bytep) rowData, NULL);

		int index = 0;
		for(col = 0; col < width; col++) {
			uint8_t red   = rowData[index++];
			uint8_t green = rowData[index++];
			uint8_t blue  = rowData[index++];
			uint8_t alpha = rowData[index++];

			*dest = alpha << 24 | red << 16 | green << 8 | blue;
			dest++;	
		}
	}
	free(rowData);
}

// Load a png from ram 
// I can't be bothered handling errors correctly, lets just abort
Image loadPng(const uint8_t *png) {
	// Make sure we have a valid png here.
	assert(png_sig_cmp((png_bytep) png, 0, 8) == 0);

	// get PNG file info struct
	png_structp png_ptr = NULL;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	assert(png_ptr != NULL);

	// get PNG image data info struct
	png_infop info_ptr = NULL;
	info_ptr = png_create_info_struct(png_ptr);
	assert(info_ptr != NULL);

	png_set_read_fn(png_ptr, (png_bytep) png, ReadDataFromMemory);

	// seek to start of png.
	seek = NULL;

	png_read_info(png_ptr, info_ptr);

	png_uint_32 width = 0;
	png_uint_32 height = 0;
	int bitDepth = 0;
	int colorType = -1;
	assert(png_get_IHDR(png_ptr, info_ptr,
		&width,
		&height,
		&bitDepth,
		&colorType,
		NULL, NULL, NULL) == 1);

	Image image;
	image.data = rsxMemAlign(16, 2*1024*1024);
	//image.data = rsxMemAlign(32,width*height);
	//image.data = rsxMemAlign(16,2*width*height);
	image.width = width;
	image.height = height;

	switch(colorType) {
	case PNG_COLOR_TYPE_RGB:
		parseRGB(image.data, width, height, png_ptr, info_ptr);
		break;
	case PNG_COLOR_TYPE_RGBA:
		parseRGBA(image.data, width, height, png_ptr, info_ptr);
		break;
	default:
		printf("Unsupported png type\n");
		abort();
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	return image;
}

void ReadDataFromMemory(png_structp png_ptr, png_bytep outBytes, 
	png_size_t byteCountToRead) {
	if (seek == NULL) seek = png_get_io_ptr(png_ptr);

	memcpy(outBytes, seek, byteCountToRead);
	seek = seek + byteCountToRead;
}

void usetexture(Image image){
	u32 tx_offset;
	assert(realityAddressToOffset(image.data, &tx_offset) == 0);
	load_tex(0, tx_offset, image.width, image.height, image.width*4,  NV40_3D_TEX_FORMAT_FORMAT_A8R8G8B8, 1);
}

