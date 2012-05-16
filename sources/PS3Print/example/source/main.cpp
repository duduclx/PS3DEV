#include <ppu-lv2.h>
#include <io/pad.h>
#include "VideoInit.h"
#include "PS3Printer.h"



#include <string>
#include "utilities.h"
using namespace::std;




s32 main(int argc, const char* argv[]) {
	
	padInfo padinfo;
	padData paddata;
	int i;
	VideoInit vid = VideoInit();//Initializes the screen

	ioPadInit(7);

	string str = "";

	long frame = 0; // To keep track of how many frames we have rendered.

	
	PS3Printer::Init(vid.GetCurrentBuffer()->width, vid.GetCurrentBuffer()->height);
	
	
	// Ok, everything is setup. Now for the main loop.
	while(1){
		// Check the pads.
		ioPadGetInfo(&padinfo);
		for(i=0; i<MAX_PADS; i++){
			if(padinfo.status[i]){
				ioPadGetData(i, &paddata);
				
				if(paddata.BTN_CROSS){
					return 0;
				}
			}
		}
		
	
		        
		vid.WaitFlip();
		vid.DrawBackground(0xffffffff);//White background (format AARRGGBB)
		frame++;
		PS3Printer::SetFontColor(0x50000000); //black with half transparency
		PS3Printer::SetFont(PS3Printer::ARIAL, 8);
		PS3Printer::Print(0.025, 0.025, "Arial 8 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 9);
		PS3Printer::Print(0.025, 0.040, "Arial 9 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 10);
		PS3Printer::Print(0.025, 0.060, "Arial 10 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 11);
		PS3Printer::Print(0.025, 0.080, "Arial 11 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 12);
		PS3Printer::Print(0.025, 0.100, "Arial 12 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 14);
		PS3Printer::Print(0.025, 0.120, "Arial 14 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 16);
		PS3Printer::Print(0.025, 0.145, "Arial 16 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 18);
		PS3Printer::Print(0.025, 0.170, "Arial 18 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 20);
		PS3Printer::Print(0.025, 0.195, "Arial 20 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 22);
		PS3Printer::Print(0.025, 0.225, "Arial 22 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 24);
		PS3Printer::Print(0.025, 0.255, "Arial 24 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 26);
		PS3Printer::Print(0.025, 0.285, "Arial 26 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 28);
		PS3Printer::Print(0.025, 0.315, "Arial 28 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 36);
		PS3Printer::Print(0.025, 0.345, "Arial 36 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 48);
		PS3Printer::Print(0.025, 0.385, "Arial 48 example font", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::ARIAL, 72);
		PS3Printer::Print(0.025, 0.740, "Arial 72 example font", vid.GetCurrentBuffer()->ptr);

		PS3Printer::SetFontColor(FONT_COLOR_BLACK);// no transparency
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 8);
		PS3Printer::Print(0.400, 0.025, "Bitstream Vera Sans Mono 8", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 9);
		PS3Printer::Print(0.400, 0.040, "Bitstream Vera Sans Mono 9", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 10);
		PS3Printer::Print(0.400, 0.060, "Bitstream Vera Sans Mono 10", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 11);
		PS3Printer::Print(0.400, 0.080, "Bitstream Vera Sans Mono 11", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 12);
		PS3Printer::Print(0.400, 0.100, "Bitstream Vera Sans Mono 12", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 14);
		PS3Printer::Print(0.400, 0.120, "Bitstream Vera Sans Mono 14", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 16);
		PS3Printer::Print(0.400, 0.145, "Bitstream Vera Sans Mono 16", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 18);
		PS3Printer::Print(0.400, 0.170, "Bitstream Vera Sans Mono 18", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 20);
		PS3Printer::Print(0.400, 0.195, "Bitstream Vera Sans Mono 20", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 22);
		PS3Printer::Print(0.400, 0.225, "Bitstream Vera Sans Mono 22", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 24);
		PS3Printer::Print(0.400, 0.255, "Bitstream Vera Sans Mono 24", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 26);
		PS3Printer::Print(0.400, 0.285, "Bitstream Vera Sans Mono 26", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 28);
		PS3Printer::Print(0.400, 0.315, "Bitstream Vera Sans Mono 28", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 36);
		PS3Printer::Print(0.400, 0.345, "Bitstream Vera Sans Mono 36", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFontColor(FONT_COLOR_YELLOW); // no transparency
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 48);
		PS3Printer::Print(0.400, 0.385, "Bitstream Vera Sans Mono 48", vid.GetCurrentBuffer()->ptr);
		PS3Printer::SetFontColor(0x5000ff00);
		PS3Printer::SetFont(PS3Printer::BITSTREAMVERASANSMONO, 72);
		PS3Printer::Print(0.025, 0.840, "Bitstream Vera Sans Mono 72", vid.GetCurrentBuffer()->ptr);


		PS3Printer::PrintError(0.025, 0.700, "This is an error message!!!", vid.GetCurrentBuffer()->ptr);

		PS3Printer::PrintWarning(0.025, 0.730, "This is a warning message", vid.GetCurrentBuffer()->ptr);
		
		PS3Printer::SetFontColor(0x7FFF0000); //RED
		PS3Printer::SetFont(PS3Printer::SEGOESCRIPT, 16);
		PS3Printer::Print(0.025, 0.5, "Frame: " + LongToString(frame), vid.GetCurrentBuffer()->ptr);

		vid.Flip();

	}
	
	return 0;
}
