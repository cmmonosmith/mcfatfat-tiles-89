// functions for controlling the character in the game world

#ifndef CONTROL_INCLUDED
#define CONTROL_INCLUDED

#define FRAME_DELAY 3

//ADD THINGS THAT ARE GLOBALLY REFERENCED AS PARAMETERS

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

#endif