// game functions

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "draw.h"
#include "scroll.h"
#include "control.h"

// main loop
void game(unsigned short *scrollBufferLight, unsigned short *scrollBufferDark)
{
	// initialize some paramters
	short x = 1;
	short y = 1;

	// fill buffers
	short idx = GrayDBufGetHiddenIdx();
	drawBackground(testMap, testMapWidth, testMapHeight, x, y, scrollBufferLight, scrollBufferDark);
	copyScrollBuffer(scrollBufferLight, GrayDBufGetPlane(idx, LIGHT_PLANE));
	copyScrollBuffer(scrollBufferDark, GrayDBufGetPlane(idx, DARK_PLANE));
	drawCharacter(idx);
	GrayDBufToggle();

	// do stuff...
	//RR_ESC (PSEUDO_CONST_KBD (6, 8)), (PSEUDO_CONST_KBD (0, 6))
	//RR_UP  0, (PSEUDO_CONST_KBD (0, 5)) 
	while (1) {
		if (_keytest(RR_ESC))
		{
			// this is like, where a menu might go
			break;
		}
		if (_keytest(RR_LEFT) && !_keytest(RR_RIGHT))
		{
			x -= moveLeft(x, y, scrollBufferLight, scrollBufferDark);
		} 
		else if (_keytest(RR_RIGHT) && !_keytest(RR_LEFT))
		{
			x += moveRight(x, y, scrollBufferLight, scrollBufferDark);
		}
		if (_keytest(RR_UP) && !_keytest(RR_DOWN))
		{
			y -= moveUp(x, y, scrollBufferLight, scrollBufferDark);
		} 
		else if (_keytest(RR_DOWN) && !_keytest(RR_UP))
		{
			y += moveDown(x, y, scrollBufferLight, scrollBufferDark);
		}
	}
}

#endif