// drawing functions

void Sprite16_208_AND(short x, short y, unsigned short *sprite, unsigned short *dest);
void Sprite16_208_OR(short x, short y, unsigned short *sprite, unsigned short *dest);
void Sprite16_240_AND(short x, short y, unsigned short *sprite, void *dest);
void Sprite16_240_OR(short x, short y, unsigned short *sprite, void *dest);

// clear a 208x144 buffer
void clearBuffer(void *dest)
{
	memset(dest, 0, 3744);
}

// fill the buffers with the background contents
void drawBackground(signed char *map, short width, short height, short x, short y, unsigned short *destLight, unsigned short *destDark)
{
	clearBuffer(destLight);
	clearBuffer(destDark);
	int i, j, mapx, mapy, mapvalue;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 9; j++)
		{
			mapx = x - 6 + i;
			mapy = y - 4 + j;
			if (mapx < 0 || mapy < 0 || mapx > width - 1 || mapy > height - 1)
			{
				Sprite16_208_OR(i<<4, j<<4, offMapSprite[0], destLight);
				Sprite16_208_OR(i<<4, j<<4, offMapSprite[1], destDark);
			}
			else
			{
				mapvalue = map[mapy * width + mapx];
				if (mapvalue >= 0)
				{
					Sprite16_208_OR(i<<4, j<<4, mapSprites[mapvalue][0], destLight);
					Sprite16_208_OR(i<<4, j<<4, mapSprites[mapvalue][1], destDark);
				}
			}
		}
	}
}

// draw the character sprite
void drawCharacter(short idx)
{
	Sprite16_240_OR(72, 42, charSprites[0], GrayDBufGetPlane(idx, LIGHT_PLANE));
	Sprite16_240_OR(72, 42, charSprites[1], GrayDBufGetPlane(idx, DARK_PLANE));
}

// ANDs a 16x16 sprite onto a 208x144 buffer, assuming the x value is a multiple of 16
void Sprite16_208_AND(short x, short y, unsigned short *sprite, unsigned short *dest)
{
    short h = 16;
    register short offset = (y<<3)+(y<<2)+y+(x>>4);
    register short *addr  = dest+offset;
    for (;h;h--,addr+=13) {
        *addr &= *sprite++;
    }
}

// ORs a 16x16 sprite onto a 208x144 buffer, assuming the x value is a multiple of 16
void Sprite16_208_OR(short x, short y, unsigned short *sprite, unsigned short *dest)
{
    short h = 16;
    register short offset = (y<<3)+(y<<2)+y+(x>>4);
    register short *addr  = dest+offset;
    for (;h;h--,addr+=13) {
        *addr |= *sprite++;
    }
}

// ripped from extgraph
// ANDs a 16x16 sprite onto a 240x128 buffer
void Sprite16_240_AND(short x, short y, unsigned short *sprite, void *dest)
{
    register long           addr = (long)dest+(y<<5)-(y<<1)+((x>>3)&0x1e);
    register unsigned short cnt  = 16-(x&15);
    short h = 16;
    for (;h;h--,addr+=30) *(long*)addr&=~((long)~((*sprite++) & 0xffff)<<cnt);
}

// ripped from extgraph
// ORs a 16x16 sprite onto a 240x128 buffer
void Sprite16_240_OR(short x, short y, unsigned short *sprite, void *dest)
{
    register long            addr = (long)dest+(y<<5)-(y<<1)+((x>>3)&0x1e);
    register unsigned short  cnt  = 16-(x&15);
    short h = 16;
    for (;h;h--,addr+=30) *(long*)addr|=(long)((*sprite++) & 0xffff)<<cnt;
}
