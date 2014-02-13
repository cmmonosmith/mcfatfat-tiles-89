#define USE_TI89

#define NO_EXIT_SUPPORT    // makes the program shorter, calls _main function directly
#define MIN_AMS 100        // minimum AMS version is 1.00

// find the program that uses these things and figure out what i need to put in here
#define COMMENT_STRING         "McFatfat Tiles 89 cmt"
#define COMMENT_PROGRAM_NAME   "McFatfat Tiles 89 name"
#define COMMENT_VERSION_STRING "McFatfat Tiles 89 vrsn"
#define COMMENT_VERSION_NUMBER 0,0,0,0 /* major, minor, revision, subrevision */
#define COMMENT_BW_ICON \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}
#define COMMENT_GRAY_ICON \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}, \
	{0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000, \
	 0b0000000000000000}

#include <system.h>
#include <graph.h>
#include <statline.h>
#include <intr.h>
#include <kbd.h>
#include <gray.h>
#include <mem.h>
#include <alloc.h>
#include <compat.h>

#include "scroll.h"
#include "keys.h"
#include "stupid.h"
#include "sprites.h"
#include "testmap.h"
#include "timer.h"
#include "drawing.h"
#include "game.h"

void _main(void)
{
	char statusMessage[] = "McFatfat Tiles 89";
	/*
		things to figure out again
			sprites
				masks
				proper rendering over other sprites
				partial drawing?
			other screen drawing (lines, etc)
			reading/writing files
	*/
	
	LCD_BUFFER *screenBuffer;
	INT_HANDLER save_int_1;
	INT_HANDLER save_int_5;
	
	// need to like... wait for this, or else... yeah
	//while (isKeyPressed());
	
	screenBuffer = (LCD_BUFFER *)malloc(LCD_SIZE);
	if (screenBuffer) {
		// save the screen contents to replace "#define SAVE_SCREEN"
		LCD_save(screenBuffer);
		
		// speed up system timer
		//short prgRate = PRG_getRate();
		//PRG_setRate(0);
		
		// repurpose hardware timer, disable system timer interrupt
		save_int_1 = GetIntVec(AUTO_INT_1);
		save_int_5 = GetIntVec(AUTO_INT_5);
		SetIntVec(AUTO_INT_1, my_int_1_handler);
		SetIntVec(AUTO_INT_5, DUMMY_HANDLER);
		
		//init buffers
		void *grayDBuf = malloc(GRAYDBUFFER_SIZE);
		if (grayDBuf) {
			unsigned short *scrollBufferLight = (unsigned short *)malloc(3744);
			if (scrollBufferLight) {
				unsigned short *scrollBufferDark  = (unsigned short *)malloc(3744);
				if (scrollBufferDark) {
					// turn on grayscale
					if (GrayOn()) {
						GrayDBufInit(grayDBuf);
						
						game(scrollBufferLight, scrollBufferDark);
						
						while (isKeyPressed());
						GrayOff();
					} else {
						//statusMessage = "GrayOn() failed!";
					}
					free(scrollBufferDark);
				}
				free(scrollBufferLight);
			} else {
				//statusMessage = "malloc(3456) failed!";
			}
			free(grayDBuf);
		} else {
			//statusMessage = "malloc(GRAYDBUFFER_SIZE) failed!";
		}
		
		// reset interrupt handlers
		SetIntVec(AUTO_INT_1, save_int_1);
		SetIntVec(AUTO_INT_5, save_int_5);
		
		// reset system timer rate
		//PRG_setRate(prgRate);
		
		// restore screen contents
		LCD_restore(screenBuffer);
		free(screenBuffer);
	} else {
		//statusMessage = "malloc(LCD_SIZE) failed!";
	}
	
	// be classy
	ST_helpMsg(statusMessage);
}
