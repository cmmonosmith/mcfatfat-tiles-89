// sprites

#define COLLISION_VALUE 1 // every sprite from this value onward is impassible

static unsigned short offMapSprite[2][16] = { //light/dark, value
	{0xCCCC, 0xCCCC, 0x3333, 0x3333, 0xCCCC, 0xCCCC, 0x3333, 0x3333, 0xCCCC, 0xCCCC, 0x3333, 0x3333, 0xCCCC, 0xCCCC, 0x3333, 0x3333},
	{0xCCCC, 0xCCCC, 0x3333, 0x3333, 0xCCCC, 0xCCCC, 0x3333, 0x3333, 0xCCCC, 0xCCCC, 0x3333, 0x3333, 0xCCCC, 0xCCCC, 0x3333, 0x3333}
};

static unsigned short mapSprites[2][2][16] = { //sprite number, light/dark, value
	{
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
		{0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}
	},
	{
		{0xFFFF, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0xFFFF},
		{0xFFFF, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0xFFFF}
	}
};

static unsigned short charSprites[2][16] = { // light/dark, value
	{0x03C0, 0x0C30, 0x300C, 0x2004, 0x4002, 0x4002, 0x8001, 0x8001, 0x8001, 0x8001, 0x4002, 0x4002, 0x2004, 0x300C, 0x0C30, 0x03C0},
	{0x03C0, 0x0C30, 0x300C, 0x2004, 0x4002, 0x4002, 0x8001, 0x8001, 0x8001, 0x8001, 0x4002, 0x4002, 0x2004, 0x300C, 0x0C30, 0x03C0}
};