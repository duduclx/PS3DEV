#include "oskdialog.h"

u8 osk_loaded = 0;
FT_Face face;

char key_array[2][4][10] = {
	{
		{'!', '"', '·', '$', '%', '&', '/', '(', ')', '='},
		{'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
		{'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Ñ'},
		{'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_'}
	},
	{
		{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
		{'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
		{'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'ñ'},
		{'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-'}
	}
};

struct block_data{
	u8 blocked;
	u16 delay;
	long uval;
};

block_data lblock = {0}, rblock = {0}, ublock = {0}, dblock = {0};
block_data l1block = {0}, r1block = {0}, r2block = {0};
block_data xblock = {0}, tblock = {0};

void TTF_to_Bitmap(u8 chr, u8 * bitmap, short *w, short *h, short *y_correction){
	FT_Set_Pixel_Sizes(face, (*w), (*h));
    
	FT_GlyphSlot slot = face->glyph;

	memset(bitmap, 0, (*w) * (*h));

	if(FT_Load_Char(face, (char) chr, FT_LOAD_RENDER )) {(*w) = 0; return;}

	int n, m, ww;

	*y_correction = (*h) - 1 - slot->bitmap_top;
    
	ww = 0;

	for(n = 0; n < slot->bitmap.rows; n++) {
		for (m = 0; m < slot->bitmap.width; m++) {

			if(m >= (*w) || n >= (*h)) continue;
            
			bitmap[m] = (u8) slot->bitmap.buffer[ww + m];
		}
    
	bitmap += *w;

	ww += slot->bitmap.width;
	}

	*w = ((slot->advance.x + 31) >> 6) + ((slot->bitmap_left < 0) ? -slot->bitmap_left : 0);
	*h = slot->bitmap.rows;
}

void TTF_get_Size(u8 chr, u8 *w, u8 *h){    
	if(!face)
		return;

	FT_GlyphSlot slot = face->glyph;
	if(!slot)
		return;

	if(FT_Load_Char(face, (char) chr, FT_LOAD_RENDER ))
		return;

	*w = (slot->advance.x >> 6) + slot->bitmap_left;
	*h = (slot->advance.x >> 6) + ((slot->bitmap_left < 0) ? -slot->bitmap_left : 0);
}


OSK::OSK(u32 *texture_pointer, char *usrdir){
	this->png_displayer = &this->png_displayer_f;
	this->png_loader = NULL;
	this->status = OSK_INITIALIZED;
	this->mode = 1;
	this->sel_row = 0;
	this->sel_num = 0;
	this->font_slot = -1;
	this->texture_pointer = texture_pointer;

	if(osk_loaded == 0){
		char path[1024] = {0};
		
		sprintf(path, "%s/BTN.PNG", usrdir);
		this->btn = this->png_loader_f(path, this->texture_pointer);
		this->texture_pointer = this->btn->texture_pointer;
		
		sprintf(path, "%s/DEL.PNG", usrdir);
		this->del = this->png_loader_f(path, this->texture_pointer);
		this->del->width = 35.3333 + 35.3333/2;
		this->del->height = 41.2444;		
		this->texture_pointer = this->del->texture_pointer;

		osk_loaded = 1;
	}
}

OSK::OSK(method_a *png_loader, method_b *png_displayer, char *usrdir){
	this->png_loader = png_loader;
	this->png_displayer = png_displayer;
	this->status = OSK_INITIALIZED;
	this->mode = 1;
	this->sel_row = 0;
	this->sel_num = 0;
	this->font_slot = -1;
	this->texture_pointer = 0;

	if(osk_loaded == 0){
		char path[1024] = {0};
		
		sprintf(path, "%s/BTN.PNG", usrdir);
		this->btn = (*this->png_loader)(path);
				
		sprintf(path, "%s/DEL.PNG", usrdir);
		this->del = (*this->png_loader)(path);
		this->del->width = 35.3333 + 35.3333/2;
		this->del->height = 41.2444;

		osk_loaded = 1;
	}
}

u32* OSK::loadFont(u8 slot, char *usrdir, u32 *texture_pointer){
	this->font_slot = slot;
	
	if(!usrdir)
		return this->texture_pointer;

	if(!texture_pointer)
		return NULL;

	if(slot == 0)
		ResetFont();

	char path[1024] = {0};		
	sprintf(path, "%s/pala.ttf", usrdir);

	FT_Init_FreeType(&freetype);

    if(FT_New_Face(freetype, path, 0, &face)) return NULL;
	
	this->texture_pointer = (u32 *) AddFontFromTTF((u8 *) texture_pointer, 32, 255, 32, 32, TTF_to_Bitmap);
	
	FT_Done_FreeType(freetype);	

	return this->texture_pointer;
}

void OSK::DrawRect2D(u32 rgba, float x, float y, float width, float height){
    tiny3d_SetPolygon(TINY3D_QUADS);
	
    tiny3d_VertexPos(x  , y  , 65535);
    tiny3d_VertexColor(rgba);

    tiny3d_VertexPos(x + width, y  , 65535);

    tiny3d_VertexPos(x + width, y + height, 65535);

    tiny3d_VertexPos(x , y + height, 65535);
    tiny3d_End();
}

void OSK::DrawBorders2D(u32 rgba, float x, float y, float w, float h, u32 border){
	this->DrawRect2D(rgba, x-border, y-border, w+(border*2), border);
	this->DrawRect2D(rgba, x+w, y-border, border, h+(border*2));
	this->DrawRect2D(rgba, x-border, y+h, w+(border*2), border);
	this->DrawRect2D(rgba, x-border, y-border, border, h+(border*2));
}

u8 OSK::draw(){
	if(status != OSK_RUNNING)
		return -1;

	float x0;
	float y0;

	float x = x0 = this->pos.x;
	float y = y0 = this->pos.y;
	
	float w = 35.3333;
	float h = 41.2444;

	//barra donde se muestra lo escrito
	this->btn->x = x + w/2;
	this->btn->y = y;
	this->btn->width = (w+5)*9;
	this->btn->alpha = 0x99;
	if(this->png_displayer != NULL)
		(*this->png_displayer)(this->btn);
	else
		this->png_displayer_f(this->btn);
	
	if(this->font_slot >= 0){		
		SetCurrentFont(this->font_slot);
		SetFontSize(18, 20);
		SetFontColor(0xFFFFFFFF, 0x0);
		
		DrawString(x + w/2 + 15, y + h/2 - 20/2 - 5, "");
		u16 len = strlen(this->buffer);
		if(len > 0){
			for(int i = 0; i < len; i++){
				DrawFormatString(GetFontX(), y + h/2 - 20/2 - 5, "%c", this->buffer[i]);
			
				if(i+1 == cursor_pos && show_cursor){
					float tx = GetFontX();
					DrawString(GetFontX()-0.5f, y + h/2 - 20/2 - 5, "|");
					DrawString(tx, 0, "");
				}
			}
		}
		
		if(show_cursor && (len == 0 || cursor_pos == 0))
			DrawString(x + w/2 + 15 - 0.5f, y + h/2 - 20/2 - 5, "|");

		timeval time_now;
		gettimeofday(&time_now, NULL);
		long cur_time = time_now.tv_sec * 1000 + time_now.tv_usec/1000;
		long old_time = old_cursor.tv_sec * 1000 + old_cursor.tv_usec/1000;
		
		if(cur_time - old_time >= 400){
			show_cursor = !show_cursor;
			gettimeofday(&old_cursor, NULL);
		}
	}

	this->btn->width = w;
	this->btn->height = h;
	this->btn->alpha = 0xFF;

	y = y0 = y0 + h + 10;

	for(int i = 0; i < 5; i++){
		for(int n = 0; n < 10; n++){

			if( i < 4){
				this->btn->x = x;
				this->btn->y = y;

				if(this->png_displayer != NULL)
					(*this->png_displayer)(this->btn);
				else
					this->png_displayer_f(this->btn);

				if(this->sel_num == n && this->sel_row == i)
					this->DrawBorders2D(0xFFFFFFFF, x, y, w-1, h, 3);

				if(this->font_slot >= 0)
					DrawFormatString(x + w/2 - 18/2 + 3, y + h/2 - 20/2 - 5, "%c", key_array[this->mode][i][n]);

				x += w + 5;

				if(i == 0 && n == 9){
					this->del->x = x + 5;
					this->del->y = y;

					if(this->png_displayer != NULL)
						(*this->png_displayer)(this->del);
					else
						this->png_displayer_f(this->del);

					if(this->sel_num == 10 && this->sel_row == 0)
						this->DrawBorders2D(0xFFFFFFFF, x+5, y, this->del->width-1, this->del->height, 3);
				}
			}else{
				//SPECIAL KEYS			

				// ---- "<-" ---- //
				this->btn->x = this->pos.x;
				this->btn->y = y;
				this->btn->width = w;
				
				if(this->png_displayer != NULL)
					(*this->png_displayer)(this->btn);
				else
					this->png_displayer_f(this->btn);

				DrawString(this->btn->x + w/2 - 18 + 13, y + h/2 - 20/2 - 5, "<-");
				
				if(this->sel_row == 4 && this->sel_num == 0)
					this->DrawBorders2D(0xFFFFFFFF, this->btn->x, this->btn->y, this->btn->width-1, this->btn->height, 3);

				// ---- "->" ---- //
				this->btn->x += w + 5;
				if(this->png_displayer != NULL)
					(*this->png_displayer)(this->btn);
				else
					this->png_displayer_f(this->btn);

				DrawString(this->btn->x + w/2 - 18 + 13, y + h/2 - 20/2 - 5, "->");
				
				if(this->sel_row == 4 && this->sel_num == 1)
					this->DrawBorders2D(0xFFFFFFFF, this->btn->x, this->btn->y, this->btn->width-1, this->btn->height, 3);

				// ---- MODE ---- //

				// ---- SPACER ---- //
				this->btn->x = x + 2*w + w/2;
				this->btn->width = (w+5)*5;

				if(this->png_displayer != NULL)
					(*this->png_displayer)(this->btn);
				else
					this->png_displayer_f(this->btn);

				if(this->sel_row == 4 && this->sel_num == 2)
					this->DrawBorders2D(0xFFFFFFFF, this->btn->x, this->btn->y, this->btn->width-1, this->btn->height, 3);
			}
		}

		x = x0 = x0 + w/2;
		y = y0 = y0 + h + 10;
	}

	return 0;
}

void OSK::delAtPos(){
	if(this->cursor_pos <= 0)
		return;

	u8 len = strlen(this->buffer);

	for(int i = cursor_pos-1; i < len-1; i++)
		this->buffer[i] = this->buffer[i+1];
			
	this->buffer[len-1] = '\0';

	cursor_pos--;
}

void OSK::handleInput(){
	u8 len = strlen(this->buffer);

	if(this->sel_num >= 0 && this->sel_num <= 9 && this->sel_row >= 0 && this->sel_row <= 3){		
		if(len >= 255)
			return;
		
		if(cursor_pos != len){
			for(int i = len; i > this->cursor_pos; i--)
				this->buffer[i] = this->buffer[i-1];
		}

		this->buffer[cursor_pos] = key_array[this->mode][this->sel_row][this->sel_num];
		
		cursor_pos++;
	}else{
		//Special cases
		if(this->sel_row == 0 && this->sel_num == 10){ //DEL
			delAtPos();
		}
		else if(this->sel_row == 4 && this->sel_num == 0){ //<-
			if(cursor_pos > 0)
				cursor_pos--;
		}else if(this->sel_row == 4 && this->sel_num == 1){ //->
			if(cursor_pos < len)
				this->cursor_pos++;
		}

		if(strlen(this->buffer) >= 255)
			return;

		if(this->sel_row == 4 && this->sel_num == 2){ //SPACE
			if(cursor_pos != len){
				for(int i = len; i > this->cursor_pos; i--)
					this->buffer[i] = this->buffer[i-1];
			}

			this->buffer[cursor_pos] = key_array[this->mode][this->sel_row][this->sel_num];

			cursor_pos++;
		}
	}
}

u8 OSK::handlePad(){
	if(this->status != OSK_RUNNING)
		return -1;

	PadData paddata;
	PadInfo padinfo;

	ioPadGetInfo(&padinfo);

	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	long cur_time = time_now.tv_sec * 1000 + time_now.tv_usec/1000;
	
	for(int i = 0; i < MAX_PADS; i++){
		if(padinfo.status[i]){
			ioPadGetData(i, &paddata);
			
			//ioPadSetPortSetting(i, CELL_PAD_SETTING_PRESS_ON);
			ioPadSetPortSetting(i, CELL_PAD_SETTING_SENSOR_ON);

			s8 plusn = 0;
			s8 plusr = 0;

			if(paddata.BTN_RIGHT){
				if(!rblock.blocked){
					plusn = 1;
					rblock.blocked = 1;
					rblock.delay = 1000;
					rblock.uval = cur_time;
				}else{
					long elapsed = ((cur_time-rblock.uval > 0)?cur_time-rblock.uval:rblock.uval-cur_time);
					if(elapsed >= rblock.delay){
						plusn = 1;
						rblock.uval = cur_time;
						rblock.delay = 200;
					}
				}
			}else
				rblock.blocked = 0;
			
			if(paddata.BTN_LEFT){
				if(!lblock.blocked){
					plusn = -1;
					lblock.blocked = 1;
					lblock.delay = 1000;
					lblock.uval = cur_time;
				}else{
					long elapsed = ((cur_time-lblock.uval > 0)?cur_time-lblock.uval:lblock.uval-cur_time);
					if(elapsed >= lblock.delay){
						plusn = -1;
						lblock.uval = cur_time;
						lblock.delay = 200;
					}
				}
			}else
				lblock.blocked = 0;

			if(paddata.BTN_UP){
				if(!ublock.blocked){
					plusr = -1;
					ublock.blocked = 1;
					ublock.delay = 1000;
					ublock.uval = cur_time;
				}else{
					long elapsed = ((cur_time-ublock.uval > 0)?cur_time-ublock.uval:ublock.uval-cur_time);
					if(elapsed >= ublock.delay){
						plusr = -1;
						ublock.uval = cur_time;
						ublock.delay = 200;
					}
				}
			}else
				ublock.blocked = 0;

			if(paddata.BTN_DOWN){
				if(!dblock.blocked){
					plusr = 1;
					dblock.blocked = 1;
					dblock.delay = 1000;
					dblock.uval = cur_time;
				}else{
					long elapsed = ((cur_time-dblock.uval > 0)?cur_time-dblock.uval:dblock.uval-cur_time);
					if(elapsed >= dblock.delay){
						plusr = 1;
						dblock.uval = cur_time;
						dblock.delay = 200;
					}
				}
			}else
				dblock.blocked = 0;

			if(paddata.BTN_CROSS){
				if(!xblock.blocked){
					
					this->handleInput();

					xblock.blocked = 1;
					xblock.delay = 1000;
					xblock.uval = cur_time;
				}else{
					long elapsed = ((cur_time-xblock.uval > 0)?cur_time-xblock.uval:xblock.uval-cur_time);
					if(elapsed >= xblock.delay){
						
						this->handleInput();

						xblock.uval = cur_time;
						xblock.delay = 200;
					}
				}
			}else
				xblock.blocked = 0;

			if(paddata.BTN_TRIANGLE){
				if(!tblock.blocked){
					
					this->delAtPos();

					tblock.blocked = 1;
					tblock.delay = 1000;
					tblock.uval = cur_time;
				}else{
					long elapsed = ((cur_time-tblock.uval > 0)?cur_time-tblock.uval:tblock.uval-cur_time);
					if(elapsed >= tblock.delay){
						
						this->delAtPos();

						tblock.uval = cur_time;
						tblock.delay = 200;
					}
				}
			}else
				tblock.blocked = 0;

			if(paddata.BTN_L1){
				if(!l1block.blocked){
					
					if(this->cursor_pos > 0)
						this->cursor_pos--;

					l1block.blocked = 1;
					l1block.delay = 1000;
					l1block.uval = cur_time;
				}else{
					long elapsed = ((cur_time-l1block.uval > 0)?cur_time-l1block.uval:l1block.uval-cur_time);
					if(elapsed >= l1block.delay){
						
						if(this->cursor_pos > 0)
							this->cursor_pos--;

						l1block.uval = cur_time;
						l1block.delay = 200;
					}
				}
			}else
				l1block.blocked = 0;

			if(paddata.BTN_R1){
				if(!r1block.blocked){
					
					if(cursor_pos < strlen(this->buffer))
						this->cursor_pos++;

					r1block.blocked = 1;
					r1block.delay = 1000;
					r1block.uval = cur_time;
				}else{
					long elapsed = ((cur_time-r1block.uval > 0)?cur_time-r1block.uval:r1block.uval-cur_time);
					if(elapsed >= r1block.delay){
						
						if(cursor_pos < strlen(this->buffer))
							this->cursor_pos++;

						r1block.uval = cur_time;
						r1block.delay = 200;
					}
				}
			}else
				r1block.blocked = 0;

			if(paddata.BTN_R2){
				if(r2block.blocked){
					long elapsed = ((cur_time-r2block.uval > 0)?cur_time-r2block.uval:r2block.uval-cur_time);
					if(elapsed >= r2block.delay)
						r2block.blocked = 0;
				}
				if(!r2block.blocked){ //no else if, it's made on purpouse
					if(this->mode == 0)
						this->mode = 1;
					else
						this->mode = 0;

					r2block.blocked = 1;
					r2block.uval = cur_time;
					r2block.delay = 500;
				}
			}

			if(paddata.BTN_START){
				this->status = OSK_RETURN;
				//Callback
			}	
			
			if(plusr != 0){
				this->sel_row += plusr;

				if(this->sel_row < 0)
					this->sel_row = 4;
				else if(this->sel_row >= 5)
					this->sel_row = 0;

				if(this->sel_row == 4 && this->sel_num > 3)
					this->sel_num = 2;
			}

			if(plusn != 0){
				this->sel_num += plusn;
				
				u8 max_num = 10;
				if(this->sel_row == 0)
					max_num = 11;
				else if(this->sel_row == 4)
					max_num = 3;

				if(this->sel_num < 0)
					this->sel_num = max_num-1;
				else if(this->sel_num >= max_num)
					this->sel_num = 0;
				
			}

			break; //Solo queremos el PAD 0
		}		
	}

	return 0;
}

u8 OSK::open(){
	memset(this->buffer, 0, 256); 
	this->cursor_pos = 0;
	this->mode = 1;
	this->sel_row = 0;
	this->sel_num = 0;

	this->status = OSK_RUNNING;

	return 0; 
}

char *OSK::getBuffer(){ 
	this->status = OSK_END; 

	int len = strlen(this->buffer);

	if(len <= 0)
		return NULL;

	char *buf = (char*)malloc(len);
	strcpy(buf, this->buffer);

	return buf;
};

void OSK::setPos(osk_point npos){
	this->pos.x = npos.x;
	this->pos.y = npos.y;
}