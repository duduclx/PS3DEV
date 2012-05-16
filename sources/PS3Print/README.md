PS3Printer
====

Version 1.1

**Author**: Juan Sebastian Munnoz

**Email**: naruse@gmail.com

**Twitter**: @jmunozar

PS3Print is based on Scognito's sconsole. (http://scognito.wordpress.com/2010/11/07/sconsole-a-simple-function-for-printing-strings-on-ps3/)

PS3Print is a simple class written in C++ and it helps you out visualizing strings on the PS3 screen.
This library works with PSL1GHT but its not tied to it.

This library only has 3 main files.

* `PS3Printer.h`
* `PS3Printer.cpp`
* `Fonts/*` (a folder with the fonts)

Just place the `PS3Printer.h` and the `Fonts` folder under the `include` folder and `PS3Printer.cpp` under the `source` folder.


Usage
---

    #include "PS3Printer.h"

    //Make sure to init the PS3Printer class.
    //by default it uses a black font with a transparent background.
    PS3Printer::Init(screenWidth, screenHeight);

    //And just feel free to call any of the functions.
    PS3Printer::SetFont(PS3Printer::ARIAL, 8);
    PS3Printer::SetFontColor(FONT_COLOR_BLACK);
    PS3Printer::Print(0.025, 0.025, "This is a normal string!", *buffer);

    PS3Printer::SetFontColor(FONT_COLOR_GREEN);
    PS3Printer::SetFont(PS3Printer::SEGOESCRIPT, 16);
    PS3Printer::Print(0.25, 0.25, "This is another green string!" + str, *buffer);

    PS3Printer::SetFontColor(0x50ff00ff); //purple; Colors have the syntax 0xAARRGGBB (This color is semi transparent, check the 50 in the alpha channel)
    PS3Printer::SetFont(PS3Printer::SEGOESCRIPT, 16);
    PS3Printer::Print(0.5, 0.5, "Frame: " + LongToString(frame), *buffer);

    PS3Printer::SetFontColor(FONT_COLOR_BLACK);
    PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO,16);
    PS3Printer::Print(0.5, 0.6, "This is an Arial 8 test!", *buffer);

    //Draws the error message on a Red Background with Yellow Letters.
    PS3Printer::PrintError(0.75, 0.75, "This is an error message!!!", *buffer);

    // Draws the warning message with a transparent background and yellow Letters
    PS3Printer::PrintWarning(0.8, 0.95, "This is a warning message :O", *buffer);

**Note**: Warning messages and Error messages are printed with Arial 14.

Supported Fonts
---
* PS3Printer::ARIAL 8,9,10,11,12,14,16,18,20,22,24,26,28,36,48,72
* PS3Printer::BITSTREAMVERASANSMONO 8,9,10,11,12,14,16,18,20,22,24,26,28,36,48,72
* PS3Printer::SEGOESCRIPT 16

Additional Notes
---
Alpha channel goes from `0x00` to `0xFF` where `FF is no transparency at all.

Position values (x,y) go from 0 to 1 where 0,0 is the top left corner of the screen and
1,1 is the botom right side of the screen.

Example
---
Check the "example" folder for a ready to compile example; just type `make pkg`.
