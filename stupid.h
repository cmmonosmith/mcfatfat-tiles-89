// stupid crap

#ifndef STUPID_INCLUDED
#define STUPID_INCLUDED

void fillBufferWithJunk(unsigned short *buffer) {
	char fillValue;
	int i;
	for (i = 0; i < 144; i++) {
		fillValue = (i % 2 == 0) ? 0xAA : 0x55;
		memset(buffer + (i * 13), fillValue, 26);
	}
}

#endif