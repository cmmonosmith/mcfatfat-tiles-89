// game functions

#define FRAME_DELAY 3

short moveLeft(short x, short y, unsigned short *scrollBufferLight, unsigned short *scrollBufferDark);
short moveRight(short x, short y, unsigned short *scrollBufferLight, unsigned short *scrollBufferDark);
short moveUp(short x, short y, unsigned short *scrollBufferLight, unsigned short *scrollBufferDark);
short moveDown(short x, short y, unsigned short *scrollBufferLight, unsigned short *scrollBufferDark);

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

short moveLeft(short x, short y, unsigned short *scrollBufferLight, unsigned short *scrollBufferDark)
{
	short moved = 0;
	if (testMap[y * testMapWidth + x - 1] < COLLISION_VALUE)
	{
		moved = 1;
		drawBackground(testMap, testMapWidth, testMapHeight, x, y, scrollBufferLight, scrollBufferDark);
		short idx;
		int i = 16;
		for (;i;i--)
		{
			scrollRight(scrollBufferLight);
			scrollRight(scrollBufferDark);
			idx = GrayDBufGetHiddenIdx();
			copyScrollBuffer(scrollBufferLight, GrayDBufGetPlane(idx, LIGHT_PLANE));
			copyScrollBuffer(scrollBufferDark, GrayDBufGetPlane(idx, DARK_PLANE));
			drawCharacter(idx);
			GrayDBufToggle();
			delay(FRAME_DELAY);
		}
	}
	return moved;
}

short moveRight(short x, short y, unsigned short *scrollBufferLight, unsigned short *scrollBufferDark)
{
	short moved = 0;
	if (testMap[y * testMapWidth + x + 1] < COLLISION_VALUE)
	{
		moved = 1;
		drawBackground(testMap, testMapWidth, testMapHeight, x, y, scrollBufferLight, scrollBufferDark);
		short idx;
		int i = 16;
		for (;i;i--)
		{
			scrollLeft(scrollBufferLight);
			scrollLeft(scrollBufferDark);
			idx = GrayDBufGetHiddenIdx();
			copyScrollBuffer(scrollBufferLight, GrayDBufGetPlane(idx, LIGHT_PLANE));
			copyScrollBuffer(scrollBufferDark, GrayDBufGetPlane(idx, DARK_PLANE));
			drawCharacter(idx);
			GrayDBufToggle();
			delay(FRAME_DELAY);
		}
	}
	return moved;
}

short moveUp(short x, short y, unsigned short *scrollBufferLight, unsigned short *scrollBufferDark)
{
	short moved = 0;
	if (testMap[(y - 1) * testMapWidth + x] < COLLISION_VALUE)
	{
		moved = 1;
		drawBackground(testMap, testMapWidth, testMapHeight, x, y, scrollBufferLight, scrollBufferDark);
		short idx;
		int i = 16;
		for (;i;i--)
		{
			scrollDown(scrollBufferLight);
			scrollDown(scrollBufferDark);
			idx = GrayDBufGetHiddenIdx();
			copyScrollBuffer(scrollBufferLight, GrayDBufGetPlane(idx, LIGHT_PLANE));
			copyScrollBuffer(scrollBufferDark, GrayDBufGetPlane(idx, DARK_PLANE));
			drawCharacter(idx);
			GrayDBufToggle();
			delay(FRAME_DELAY);
		}
	}
	return moved;
}

short moveDown(short x, short y, unsigned short *scrollBufferLight, unsigned short *scrollBufferDark)
{
	short moved = 0;
	if (testMap[(y + 1) * testMapWidth + x] < COLLISION_VALUE)
	{
		moved = 1;
		drawBackground(testMap, testMapWidth, testMapHeight, x, y, scrollBufferLight, scrollBufferDark);
		short idx;
		int i = 16;
		for (;i;i--)
		{
			scrollUp(scrollBufferLight);
			scrollUp(scrollBufferDark);
			idx = GrayDBufGetHiddenIdx();
			copyScrollBuffer(scrollBufferLight, GrayDBufGetPlane(idx, LIGHT_PLANE));
			copyScrollBuffer(scrollBufferDark, GrayDBufGetPlane(idx, DARK_PLANE));
			drawCharacter(idx);
			GrayDBufToggle();
			delay(FRAME_DELAY);
		}
	}
	return moved;
}
