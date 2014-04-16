// functions for keypress detection

#ifndef KEYS_INCLUDED
#define KEYS_INCLUDED

// if any key is pressed
unsigned short isKeyPressed(void) {
	return (_rowread(0) & 0xff);
}

// hold until any key is pressed, and then hold while any key is pressed, until no keys are pressed
void waitForKeyPress(void) {
	while (!isKeyPressed());
	while (isKeyPressed());
}

#endif