#include "PS3Printer.h"
#include <bitset>


//****** Include fonts here **********//
/*************** Arial *************/
#include "Fonts/Arial/Arial8.h" 
#include "Fonts/Arial/Arial9.h"
#include "Fonts/Arial/Arial10.h"//Dont remove this include, is the default one when no Font/size is found
#include "Fonts/Arial/Arial11.h"
#include "Fonts/Arial/Arial12.h"
#include "Fonts/Arial/Arial14.h"
#include "Fonts/Arial/Arial16.h"
#include "Fonts/Arial/Arial18.h"
#include "Fonts/Arial/Arial20.h"
#include "Fonts/Arial/Arial22.h"
#include "Fonts/Arial/Arial24.h"
#include "Fonts/Arial/Arial26.h"
#include "Fonts/Arial/Arial28.h"
#include "Fonts/Arial/Arial36.h"
#include "Fonts/Arial/Arial48.h"
#include "Fonts/Arial/Arial72.h" 
/**** Bit Stream Vera Sans Mono ****/
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono8.h" 
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono9.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono10.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono11.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono12.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono14.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono16.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono18.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono20.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono22.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono24.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono26.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono28.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono36.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono48.h"
#include "Fonts/BitStreamVeraSansMono/BitStreamVeraSansMono72.h"
/*********** Segoe Script************/
#include "Fonts/SegoeScript16.h"
/************************************/

//Initialization of the static vars.
bool PS3Printer::s_console::__monospaced = false;
unsigned short PS3Printer::s_console::__fontHeight = 16;
unsigned short PS3Printer::s_console::__dataLength = 8;
unsigned char* PS3Printer::s_console::__fontDataTable = NULL;
unsigned char* PS3Printer::s_console::__fontIndexTable = NULL;
// When the font width is variable we use.
unsigned int*  PS3Printer::s_console::__fontOffsetTable = NULL;
unsigned char* PS3Printer::s_console::__fontWidthTable = NULL;
// When the font width is the same (monospaced) we use
unsigned int PS3Printer::s_console::__fontOffset = 0;
unsigned char PS3Printer::s_console::__fontWidth = 0;


PS3Printer::FONTNAME PS3Printer::s_console::__fontName = ARIAL;
int PS3Printer::s_console::__fontSize = 10;

int PS3Printer::s_console::__screenWidth = 640;
int PS3Printer::s_console::__screenHeight = 480;
int PS3Printer::s_console::__curX = 0;
int PS3Printer::s_console::__curY = 0;
int PS3Printer::s_console::__fgColor = 0;
int PS3Printer::s_console::__bgColor = 0;



void PS3Printer::Init(int screenWidth, int screenHeight) {
	sconsole.__screenWidth = screenWidth;
	sconsole.__screenHeight = screenHeight;
	sconsole.__curX = 0;
	sconsole.__curY = 0;
	sconsole.__bgColor = FONT_COLOR_NONE;
	sconsole.__fgColor = FONT_COLOR_BLACK;

	/**** Set Font by default Arial 14 ****/
	SetDefaultValues();
	/**************************************/
}

void PS3Printer::Init(int screenWidth, int screenHeight, FONTNAME f, int fontSize) {
	sconsole.__screenWidth = screenWidth;
	sconsole.__screenHeight = screenHeight;
	sconsole.__curX = 0;
	sconsole.__curY = 0;
	sconsole.__bgColor = FONT_COLOR_NONE;
	sconsole.__fgColor = FONT_COLOR_BLACK;
	sconsole.__fontSize = fontSize;
	SetFont(f, fontSize);
}

void PS3Printer::SetFontColor(int _bgColor, int _fgColor) {
	sconsole.__bgColor = _bgColor;
	sconsole.__fgColor = _fgColor;
}
void PS3Printer::SetFontColor(int _fgColor) {
	sconsole.__bgColor = FONT_COLOR_NONE;
	sconsole.__fgColor = _fgColor;
}

uint32_t PS3Printer::CalculateAlpha(const uint32_t &src, const uint32_t &bg) {//bg -> Background; src -> Color we want to calculate-alpha
	uint32_t a = src >> 24;    // alpha
 
	//return background if the color is transparent
	if (0 == a) 
		return bg;
	if(0xff == a)
		return src;
	
	// alpha blending the source and background colors
	uint32_t rb = (((src & 0x00ff00ff) * a) +  
	                   ((bg & 0x00ff00ff) * (0xff - a))) & 0xff00ff00;
	uint32_t g  = (((src & 0x0000ff00) * a) + 
	                      ((bg & 0x0000ff00) * (0xff - a))) & 0x00ff0000;

	return (src & 0xff000000) | ((rb | g) >> 8);
}


//used when the font widths are variable
void PS3Printer::SetFontValues(const unsigned short dataLength, const unsigned short fontHeight,
                               const unsigned char* dataTable, const unsigned int* offsetTable,
                               const unsigned char* indexTable, const unsigned char* widthTable) {
	sconsole.__monospaced = false;
	sconsole.__dataLength = dataLength;
	sconsole.__fontHeight = fontHeight;
	sconsole.__fontDataTable = (unsigned char*) dataTable;
	sconsole.__fontOffsetTable = (unsigned int*) offsetTable;
	sconsole.__fontIndexTable = (unsigned char*) indexTable;
	sconsole.__fontWidthTable = (unsigned char*) widthTable;

	// These values are only used for monospaced fonts
	sconsole.__fontWidth = 0;
	sconsole.__fontOffset = 0;
}
// Used when the font widths are the same (monospaced)
void PS3Printer::SetFontValuesMonospaced(const unsigned short dataLength, const unsigned short fontHeight,
                               const unsigned char* dataTable, const unsigned int offset,
                               const unsigned char* indexTable, const unsigned char width) {
	sconsole.__monospaced = true;
	sconsole.__dataLength = dataLength;
	sconsole.__fontHeight = fontHeight;
	sconsole.__fontDataTable = (unsigned char*) dataTable;
	sconsole.__fontOffset = offset;
	sconsole.__fontIndexTable = (unsigned char*) indexTable;
	sconsole.__fontWidth = width;

	// These arrays are only used when the font widht is variable.
	sconsole.__fontOffsetTable = NULL;
	sconsole.__fontWidthTable = NULL; 
}

// Default Font Arial 14.
void PS3Printer::SetDefaultValues() {
	SetFont(ARIAL, 14);
}


// Private function used when someone sets a Font/Size that is not found
// in the Fonts/ folder.
// It draws the text that was supposed to be written in Arial 14 in a red
// background with a yellow font
void PS3Printer::SetErrorValues() {
	SetDefaultValues();	
	// No font was found so use Arial 14 and use
	// yellow text with red background
	sconsole.__bgColor = 0xffffff00;//AARRGGBB
	sconsole.__fgColor = 0xffff0000;
}

void PS3Printer::SetFontSize(int size) {
	sconsole.__fontSize = size;
	SetFont(sconsole.__fontName, size);
}


/*
  _x goes from 0 to 1; where 0 is left and 1 is the right side of your screen.
  _y goes from 0 to 1; where 0 represents the top of the screen and 1 represents the bottom of the screen
  txt is the message you want to display
  buffer represents the current framebuffer.
*/
void PS3Printer::Print(float _x, float _y, std::string txt, uint32_t* buffer) {
	int x = (int) (_x * (float)sconsole.__screenWidth);
	int y = (int) (_y * (float)sconsole.__screenHeight);
	sconsole.__curX = x;
	sconsole.__curY = y;
	int oldConsoleX = sconsole.__curX;
	int offsetX = 0;//scans the font bitmap
	int offsetY = 0;//scans the font bitmap	

	for(unsigned int indexTxt = 0; indexTxt < txt.length(); ++indexTxt) {
		if(txt[indexTxt] == '\n') {
			sconsole.__curX = x;
			sconsole.__curY += sconsole.__fontHeight;
		} else {
			if(txt[indexTxt] < 32 || txt[indexTxt] > 132)
				txt[indexTxt] = 180;

			// Get some char info.
			const unsigned char index = sconsole.__fontIndexTable[(unsigned int) txt[indexTxt]]; //index_table[(unsigned int) txt[indexTxt]];
			const unsigned int offset = sconsole.__monospaced ? sconsole.__fontOffset*index : sconsole.__fontOffsetTable[index]; //offset_table[index];
			//array of hex codes that represents the bitmap of the letter we are drawing
			const unsigned char *charData = sconsole.__fontDataTable + sizeof(unsigned char) * offset;			
			const unsigned short charWidth = sconsole.__monospaced ? sconsole.__fontWidth : sconsole.__fontWidthTable[index];
			
			short bitIndex = sconsole.__dataLength-1;
			for (unsigned short j = 0; j < sconsole.__fontHeight * charWidth; j++) {		     
				std::bitset<sizeof(char) * 8> bitMap(*charData);
				if(bitMap.test(bitIndex)) { //means is part of the fgColor
					if(sconsole.__fgColor != FONT_COLOR_NONE)
						buffer[(sconsole.__curY + offsetY)*sconsole.__screenWidth + sconsole.__curX + offsetX] = CalculateAlpha(sconsole.__fgColor, buffer[(sconsole.__curY + offsetY)*sconsole.__screenWidth + sconsole.__curX + offsetX]);
				} else {
					if(sconsole.__bgColor != FONT_COLOR_NONE)
						buffer[(sconsole.__curY + offsetY)*sconsole.__screenWidth + sconsole.__curX + offsetX] = CalculateAlpha(sconsole.__bgColor, buffer[(sconsole.__curY + offsetY)*sconsole.__screenWidth + sconsole.__curX + offsetX]);
				}
				if(bitIndex == 0) {
					bitIndex = 7;
					++charData;
				} else {
					bitIndex--;
				}
				offsetX++;
				if(offsetX == charWidth) {//sconsole.__width
					offsetX = 0;
					offsetY++;
				}
			}
			offsetY = 0;
			sconsole.__curX += charWidth;
		}
	}
	sconsole.__curY += sconsole.__fontHeight;
	sconsole.__curX = oldConsoleX;
}

void PS3Printer::PrintError(float x, float y, std::string errorMsg, uint32_t* buffer) {
	FONTNAME oldFontName = sconsole.__fontName;
	int oldFontSize = sconsole.__fontSize;
	int oldbgColor = sconsole.__bgColor;
	int oldfgColor = sconsole.__fgColor;
	
	SetDefaultValues();	
	SetFontColor(FONT_COLOR_RED, FONT_COLOR_YELLOW);//red background, yellow letters
	Print(x, y, errorMsg, buffer);

	SetFont(oldFontName, oldFontSize);       
	SetFontColor(oldbgColor, oldfgColor);
}

void PS3Printer::PrintWarning(float x, float y, std::string warnMsg, uint32_t* buffer) {
	FONTNAME oldFontName = sconsole.__fontName;
	int oldFontSize = sconsole.__fontSize;
	int oldbgColor = sconsole.__bgColor;
	int oldfgColor = sconsole.__fgColor;
	
	SetDefaultValues();
	SetFontColor(FONT_COLOR_BLACK, FONT_COLOR_YELLOW);//Black background, yellow letters
	Print(x, y, warnMsg, buffer);

	SetFont(oldFontName, oldFontSize);
	SetFontColor(oldbgColor, oldfgColor);
}






































void PS3Printer::SetFont(PS3Printer::FONTNAME f, int size) {
	sconsole.__fontName = f;
	sconsole.__fontSize = size;
	switch (f) {
	case ARIAL:
		switch(size) {
		case 8://Arial8.h
			SetFontValues(Arial8DataLength,Arial8CharHeight,Arial8Data_table,Arial8Offset_table,Arial8Index_table,Arial8Width_table);
			break;
		case 9://Arial9.h
			SetFontValues(Arial9DataLength,Arial9CharHeight,Arial9Data_table,Arial9Offset_table,Arial9Index_table,Arial9Width_table);
			break;
		case 10://Arial10.h
			SetFontValues(Arial10DataLength,Arial10CharHeight,Arial10Data_table,Arial10Offset_table,Arial10Index_table,Arial10Width_table);
			break;
		case 11://Arial11.h
			SetFontValues(Arial11DataLength,Arial11CharHeight,Arial11Data_table,Arial11Offset_table,Arial11Index_table,Arial11Width_table);
			break;
		case 12://Arial12.h
			SetFontValues(Arial12DataLength,Arial12CharHeight,Arial12Data_table,Arial12Offset_table,Arial12Index_table,Arial12Width_table);
			break;
		case 14://Arial14.h
			SetFontValues(Arial14DataLength,Arial14CharHeight,Arial14Data_table,Arial14Offset_table,Arial14Index_table,Arial14Width_table);
			break;
		case 16://Arial16.h
			SetFontValues(Arial16DataLength,Arial16CharHeight,Arial16Data_table,Arial16Offset_table,Arial16Index_table,Arial16Width_table);
			break;
		case 18://Arial18.h
			SetFontValues(Arial18DataLength,Arial18CharHeight,Arial18Data_table,Arial18Offset_table,Arial18Index_table,Arial18Width_table);
			break;
		case 20://Arial20.h
			SetFontValues(Arial20DataLength,Arial20CharHeight,Arial20Data_table,Arial20Offset_table,Arial20Index_table,Arial20Width_table);
			break;
		case 22://Arial22.h
			SetFontValues(Arial22DataLength,Arial22CharHeight,Arial22Data_table,Arial22Offset_table,Arial22Index_table,Arial22Width_table);
			break;
		case 24://Arial24.h
			SetFontValues(Arial24DataLength,Arial24CharHeight,Arial24Data_table,Arial24Offset_table,Arial24Index_table,Arial24Width_table);
			break;
		case 26://Arial26.h
			SetFontValues(Arial26DataLength,Arial26CharHeight,Arial26Data_table,Arial26Offset_table,Arial26Index_table,Arial26Width_table);
			break;
		case 28://Arial28.h
			SetFontValues(Arial28DataLength,Arial28CharHeight,Arial28Data_table,Arial28Offset_table,Arial28Index_table,Arial28Width_table);
			break;
		case 36://Arial36.h
			SetFontValues(Arial36DataLength,Arial36CharHeight,Arial36Data_table,Arial36Offset_table,Arial36Index_table,Arial36Width_table);
			break;
		case 48://Arial48.h
			SetFontValues(Arial48DataLength,Arial48CharHeight,Arial48Data_table,Arial48Offset_table,Arial48Index_table,Arial48Width_table);
			break;
		case 72://Arial72.h
			SetFontValues(Arial72DataLength,Arial72CharHeight,Arial72Data_table,Arial72Offset_table,Arial72Index_table,Arial72Width_table);
			break;
		default://Error Value: Any text written with the wrong Font/size gets replaced with Arial 10 with Yellow Text and red Background
			SetErrorValues();
			break;
		}
		break; //case ARIAL
	case BITSTREAMVERASANSMONO: // This is a monospaced font
		switch(size) {
		case 8://BitStreamVeraSansMono8.h
			SetFontValuesMonospaced(BitStreamVeraSansMono8DataLength,BitStreamVeraSansMono8CharHeight,BitStreamVeraSansMono8Data_table,BitStreamVeraSansMono8Offset,BitStreamVeraSansMono8Index_table,BitStreamVeraSansMono8Width);
			break;
		case 9://BitStreamVeraSansMono9.h
			SetFontValuesMonospaced(BitStreamVeraSansMono9DataLength,BitStreamVeraSansMono9CharHeight,BitStreamVeraSansMono9Data_table,BitStreamVeraSansMono9Offset,BitStreamVeraSansMono9Index_table,BitStreamVeraSansMono9Width);
			break;
		case 10://BitStreamVeraSansMono10.h
			SetFontValuesMonospaced(BitStreamVeraSansMono10DataLength,BitStreamVeraSansMono10CharHeight,BitStreamVeraSansMono10Data_table,BitStreamVeraSansMono10Offset,BitStreamVeraSansMono10Index_table,BitStreamVeraSansMono10Width);
			break;
		case 11://BitStreamVeraSansMono11.h
			SetFontValuesMonospaced(BitStreamVeraSansMono11DataLength,BitStreamVeraSansMono11CharHeight,BitStreamVeraSansMono11Data_table,BitStreamVeraSansMono11Offset,BitStreamVeraSansMono11Index_table,BitStreamVeraSansMono11Width);
			break;
		case 12://BitStreamVeraSansMono12.h
			SetFontValuesMonospaced(BitStreamVeraSansMono12DataLength,BitStreamVeraSansMono12CharHeight,BitStreamVeraSansMono12Data_table,BitStreamVeraSansMono12Offset,BitStreamVeraSansMono12Index_table,BitStreamVeraSansMono12Width);
			break;
		case 14://BitStreamVeraSansMono14.h
			SetFontValuesMonospaced(BitStreamVeraSansMono14DataLength,BitStreamVeraSansMono14CharHeight,BitStreamVeraSansMono14Data_table,BitStreamVeraSansMono14Offset,BitStreamVeraSansMono14Index_table,BitStreamVeraSansMono14Width);
			break;
		case 16://BitStreamVeraSansMono16.h
			SetFontValuesMonospaced(BitStreamVeraSansMono16DataLength,BitStreamVeraSansMono16CharHeight,BitStreamVeraSansMono16Data_table,BitStreamVeraSansMono16Offset,BitStreamVeraSansMono16Index_table,BitStreamVeraSansMono16Width);
			break;
		case 18://BitStreamVeraSansMono18.h
			SetFontValuesMonospaced(BitStreamVeraSansMono18DataLength,BitStreamVeraSansMono18CharHeight,BitStreamVeraSansMono18Data_table,BitStreamVeraSansMono18Offset,BitStreamVeraSansMono18Index_table,BitStreamVeraSansMono18Width);
			break;
		case 20://BitStreamVeraSansMono20.h
			SetFontValuesMonospaced(BitStreamVeraSansMono20DataLength,BitStreamVeraSansMono20CharHeight,BitStreamVeraSansMono20Data_table,BitStreamVeraSansMono20Offset,BitStreamVeraSansMono20Index_table,BitStreamVeraSansMono20Width);
			break;
		case 22://BitStreamVeraSansMono22.h
			SetFontValuesMonospaced(BitStreamVeraSansMono22DataLength,BitStreamVeraSansMono22CharHeight,BitStreamVeraSansMono22Data_table,BitStreamVeraSansMono22Offset,BitStreamVeraSansMono22Index_table,BitStreamVeraSansMono22Width);
			break;
		case 24://BitStreamVeraSansMono24.h
			SetFontValuesMonospaced(BitStreamVeraSansMono24DataLength,BitStreamVeraSansMono24CharHeight,BitStreamVeraSansMono24Data_table,BitStreamVeraSansMono24Offset,BitStreamVeraSansMono24Index_table,BitStreamVeraSansMono24Width);
			break;
		case 26://BitStreamVeraSansMono26.h
			SetFontValuesMonospaced(BitStreamVeraSansMono26DataLength,BitStreamVeraSansMono26CharHeight,BitStreamVeraSansMono26Data_table,BitStreamVeraSansMono26Offset,BitStreamVeraSansMono26Index_table,BitStreamVeraSansMono26Width);
			break;
		case 28://BitStreamVeraSansMono28.h
			SetFontValuesMonospaced(BitStreamVeraSansMono28DataLength,BitStreamVeraSansMono28CharHeight,BitStreamVeraSansMono28Data_table,BitStreamVeraSansMono28Offset,BitStreamVeraSansMono28Index_table,BitStreamVeraSansMono28Width);
			break;
		case 36://BitStreamVeraSansMono36.h
			SetFontValuesMonospaced(BitStreamVeraSansMono36DataLength,BitStreamVeraSansMono36CharHeight,BitStreamVeraSansMono36Data_table,BitStreamVeraSansMono36Offset,BitStreamVeraSansMono36Index_table,BitStreamVeraSansMono36Width);
			break;
		case 48://BitStreamVeraSansMono48.h
			SetFontValuesMonospaced(BitStreamVeraSansMono48DataLength,BitStreamVeraSansMono48CharHeight,BitStreamVeraSansMono48Data_table,BitStreamVeraSansMono48Offset,BitStreamVeraSansMono48Index_table,BitStreamVeraSansMono48Width);
			break;
		case 72://BitStreamVeraSansMono72.h
			SetFontValuesMonospaced(BitStreamVeraSansMono72DataLength,BitStreamVeraSansMono72CharHeight,BitStreamVeraSansMono72Data_table,BitStreamVeraSansMono72Offset,BitStreamVeraSansMono72Index_table,BitStreamVeraSansMono72Width);
			break;
		default://Error Value is Any text written with the wrong Font/size gets replaced with Arial 10 with Yellow Text and red Background
			SetErrorValues();
			break;
		}
		break; // case BITSTREAMVERASANS
	case SEGOESCRIPT:
		switch(size) {
		case 16: //SegoeScript16.h
			SetFontValues(SegoeScript16DataLength, SegoeScript16CharHeight, SegoeScript16Data_table, SegoeScript16Offset_table, SegoeScript16Index_table, SegoeScript16Width_table);
			break;
		default://Error Value is Any text written with the wront Font/size gets replaced with Arial 10 with Yellow Text and red Background
			SetErrorValues();
			break;
		}
		break; // case SEGOESCRIPT
	default://ERROR, No font found
		SetErrorValues();
		break;
	}
}
