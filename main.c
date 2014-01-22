#define USE_TI89

#define NO_EXIT_SUPPORT    // makes the program shorter, calls _main function directly
#define MIN_AMS 100        // minimum AMS version is 1.00

// find the program that uses these things and figure out what i need to put in here
#define COMMENT_STRING         "McFatfat Playtime cmt"
#define COMMENT_PROGRAM_NAME   "McFatfat Playtime name"
#define COMMENT_VERSION_STRING "McFatfat Playtime vrsn"
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

void _main(void)
{
	char statusMessage[] = "McFatfat Playtime";
	/*
		things to figure out again
			double-buffering (smoother rendering)
			sprites
				masks
				proper rendering over other sprites
				partial drawing?
			other screen drawing (lines, etc)
			reading/writing files
	*/
	
	LCD_BUFFER *screenBuffer;
	INT_HANDLER save_int_1;
	
	// need to like... wait for this, or else... yeah
	while (isKeyPressed());
	
	screenBuffer = (LCD_BUFFER *)malloc(LCD_SIZE);
	if (screenBuffer) {
		// save the screen contents to replace "#define SAVE_SCREEN"
		LCD_save(screenBuffer);
		
		// set USER_TIMER for a 1/20th of a second delay
		OSFreeTimer(USER_TIMER);
		OSRegisterTimer(USER_TIMER, 1);
		
		// turn off the status line only
		save_int_1 = GetIntVec(AUTO_INT_1);
		SetIntVec(AUTO_INT_1, DUMMY_HANDLER);
		
		//init buffers
		void *grayDBuf = malloc(GRAYDBUFFER_SIZE);
		if (grayDBuf) {
			unsigned short *scrollBuffer = (unsigned short *)malloc(3456);
			if (scrollBuffer) {
				// turn on grayscale
				if (GrayOn()) {
					GrayDBufInit(grayDBuf);
					
					// fill buffers with alternating 0xAA and 0x55 (by line)
					fillBufferWithJunk(scrollBuffer);
					
					// do stuff...
					while (!_keytest(RR_ESC)) {
						if (_keytest(RR_LEFT) && !_keytest(RR_RIGHT)) {
							scrollLeft(scrollBuffer);
						} else if (_keytest(RR_RIGHT) && !_keytest(RR_LEFT)) {
							scrollRight(scrollBuffer);
						}
						if (_keytest(RR_UP) && !_keytest(RR_DOWN)) {
							scrollUp(scrollBuffer);
						} else if (_keytest(RR_DOWN) && !_keytest(RR_UP)) {
							scrollDown(scrollBuffer);
						}
						
						short idx = GrayDBufGetHiddenIdx();
						copyScrollBuffer(scrollBuffer, GrayDBufGetPlane(idx, LIGHT_PLANE));
						copyScrollBuffer(scrollBuffer, GrayDBufGetPlane(idx, DARK_PLANE));
						GrayDBufToggle();
					}
					
					while (isKeyPressed());
					GrayOff();
				} else {
					//statusMessage = "GrayOn() failed!";
				}
				free(scrollBuffer);
			} else {
				//statusMessage = "malloc(3456) failed!";
			}
			free(grayDBuf);
		} else {
			//statusMessage = "malloc(GRAYDBUFFER_SIZE) failed!";
		}
		
		// turn status line back on
		SetIntVec(AUTO_INT_1, save_int_1);
		
		// reset user timer
		OSFreeTimer(USER_TIMER);
		
		// restore screen contents
		LCD_restore(screenBuffer);
		free(screenBuffer);
	} else {
		//statusMessage = "malloc(LCD_SIZE) failed!";
	}
	
	// be classy
	ST_helpMsg(statusMessage);
}
