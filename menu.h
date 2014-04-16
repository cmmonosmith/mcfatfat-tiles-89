// functions for drawing menus and stuff

#ifndef MENU_INCLUDED
#define MENU_INCLUDED

short mainMenu()
{
	char PLAY[] = "PLAY";
	char QUIT[] = "QUIT";
	
	short idx = GrayDBufGetHiddenIdx();
	void *lightPlane = GrayDBufGetPlane(idx, LIGHT_PLANE);
	void *darkPlane = GrayDBufGetPlane(idx, DARK_PLANE);
	drawPicture(TITLE_IMAGE_LIGHT, lightPlane);
	drawPicture(TITLE_IMAGE_DARK, darkPlane);
	// draw other crap
	GrayDBufToggle();
	
	waitForKeyPress();
	return 1;
}

#endif