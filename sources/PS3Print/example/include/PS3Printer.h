/*
  PS3Printer:
  Author: Juan Sebastian Munoz (naruse@gmail.com)

  Simple class to help out printing strings on the screen.

  This class is based on scognito's sconsole.
  http://scognito.wordpress.com/2010/11/07/sconsole-a-simple-function-for-printing-strings-on-ps3/

*/

#ifndef _PS3PRINTER_
#define _PS3PRINTER_

#include <string>


#define FONT_COLOR_NONE   -1
#define FONT_COLOR_BLACK  0xff000000
#define FONT_COLOR_WHITE  0xffffffff
#define FONT_COLOR_RED    0xffff0000
#define FONT_COLOR_GREEN  0xff00ff00
#define FONT_COLOR_BLUE   0xff0000ff
#define FONT_COLOR_YELLOW 0xffffff00

// Static class to print on the framebuffer
class PS3Printer {
 public:
	enum FONTNAME { ARIAL = 0, BITSTREAMVERASANSMONO = 1, SEGOESCRIPT = 2 };
 private:
	struct s_console {
		// For accessing each char depending on the font //
		static bool __monospaced;
		static unsigned short __dataLength;
		static unsigned short __fontHeight;
		static unsigned char* __fontDataTable;
		static unsigned char* __fontIndexTable;
		// if the font width is always the same (monospaced)
		static unsigned int __fontOffset;
		static unsigned char __fontWidth;
		// else if the font width is variable (isnt monospaced) we use tables for the widths and offsets
		static unsigned int* __fontOffsetTable;
		static unsigned char* __fontWidthTable;
		//***********************************************//
		
		static FONTNAME __fontName;
		static int __fontSize;
		static int __screenWidth;
		static int __screenHeight;
		static int __curX;
		static int __curY;
		static int __fgColor;
		static int __bgColor;

	};
	static s_console sconsole;	
	PS3Printer();//dont let anyone create an instance of this class
	static void SetDefaultValues(); // Default Font: Arial 14.
	static void SetErrorValues(); // Used when whe font or size hasnt been found when calling Init

	static void SetFontValues(const unsigned short dataLength, const unsigned short fontHeight, 
	                          const unsigned char* dataTable, const unsigned int* offsetTable,
	                          const unsigned char* indexTable, const unsigned char* widthTable);

	static void SetFontValuesMonospaced(const unsigned short dataLength, const unsigned short fontHeight,
	                          const unsigned char* dataTable, const unsigned int offset,
	                          const unsigned char* indexTable, const unsigned char width);
	static uint32_t CalculateAlpha(const uint32_t& src, const uint32_t& bg);

 public:

	static void Init(int _screenWidth, int _screenHeight, FONTNAME f, int fontSize);
	static void Init(int _screenWidth, int _screenHeight);

	
	static void Print(float x, float y, std::string  text, uint32_t* buffer);
	static void PrintError(float x, float y, std::string errorMsg, uint32_t* buffer);
	static void PrintWarning(float x, float y, std::string warnMsg, uint32_t* buffer);

	
	static void SetFontColor(int _bgColor, int _fgColor);
	static void SetFontColor(int _fgColor);


	static void SetFont(FONTNAME f, int size);
	static void SetFontSize(int _size);
	
};



#endif
