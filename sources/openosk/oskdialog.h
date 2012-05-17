#ifndef OSK_DIALOG_H
#define OSK_DIALOG_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>

#include <tiny3d.h>
#include <pngdec\loadpng.h>
#include <io/pad.h> 
#include <sys/time.h>

#include <libfont.h>
#include <ft2build.h>
#include <freetype/freetype.h> 
#include <freetype/ftglyph.h>

#include <time.h>

#include "types.h"

struct _png_loader{
	PngDatas png;
	u32 offset;
	u16 width;
	u16 height;
	u16 x;
	u16 y;

	u8 alpha;

	u32 *texture_pointer;
};

enum osk_status{
	OSK_INITIALIZED=0,
	OSK_RUNNING,
	OSK_ABORT,
	OSK_RETURN,
	OSK_END
};

struct osk_point{
	float x;
	float y;
};



typedef _png_loader* (method_a)(char*);
typedef u8 (method_b)(_png_loader*);

class OSK{
private:
	method_a *png_loader;
	method_b *png_displayer;
	u32 *texture_pointer;

	FT_Library freetype;
	u8 font_slot;

	osk_status status;
	osk_point pos;

	_png_loader *btn;
	_png_loader *del;
	_png_loader *space;

	u8 mode;
	s8 sel_num;
	s8 sel_row;

	u8 cursor_pos;
	u8 show_cursor;
	timeval old_cursor;

	char buffer[256];

	void delAtPos();
	void handleInput();

	static _png_loader* png_loader_f(char * path, u32 *texture_pointer){
		_png_loader *png = (_png_loader*)malloc(sizeof(_png_loader));
		memset(png, 0, sizeof(_png_loader));

		LoadPNG(&(png->png), path);

		if(png->png.bmp_out){
			memcpy(texture_pointer, png->png.bmp_out, png->png.wpitch * png->png.height);
            
			free(png->png.bmp_out);
			png->png.bmp_out = texture_pointer;
			texture_pointer += (png->png.wpitch/4 * png->png.height + 3) & ~3; 
			png->offset = tiny3d_TextureOffset(png->png.bmp_out);
		}

		png->texture_pointer = texture_pointer;
		png->alpha = 0xFF;

		return png;
	};

	static u8 png_displayer_f(_png_loader* png){
		tiny3d_SetTexture(0, png->offset, png->png.width, png->png.height, png->png.wpitch, TINY3D_TEX_FORMAT_A8R8G8B8, 1);
		tiny3d_SetPolygon(TINY3D_QUADS);
	
		tiny3d_VertexPos(png->x  , png->y  , 1);   
		tiny3d_VertexColor(0xFFFFFF00 + png->alpha);
		tiny3d_VertexTexture(0.0f, 0.0f);

		tiny3d_VertexPos(png->x + png->width, png->y  , 1);
		tiny3d_VertexTexture(1.0f, 0.0f);

		tiny3d_VertexPos(png->x + png->width, png->y + png->height, 1);
		tiny3d_VertexTexture(1.0f, 1.0f);

		tiny3d_VertexPos(png->x  , png->y + png->height, 1);
		tiny3d_VertexTexture(0.0f, 1.0f);
		tiny3d_End();

		return 0;
	};

	void DrawRect2D(u32 rgba, float x, float y, float width, float height);
	void DrawBorders2D(u32 rgba, float x, float y, float w, float h, u32 border);

public:
	OSK(){ status = OSK_INITIALIZED; sel_row = 0; sel_num = 0; png_loader = NULL; png_displayer = NULL; font_slot = -1; mode = 1; };
	OSK(u32 *texture_pointer, char *usrdir);
	OSK(method_a *png_loader, method_b *png_displayer, char *usrdir);

	~OSK(){ FT_Done_FreeType(freetype); };

	u32* loadFont(u8 slot, char *usrdir, u32 *texture_pointer);

	u8 draw();
	u8 handlePad();

	u8 open();

	u32 *getTexturePointer(){ return this->texture_pointer; };
	osk_status getStatus(){ return this->status; };

	char *getBuffer();

	void setPos(osk_point npos);
};

#endif
