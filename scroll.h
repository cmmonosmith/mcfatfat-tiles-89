// fast scroll functions copied from: tigcc.ticalc.org/tut/scroll_source.txt
// with minor modifications for personal usage

// instead of scrolling a screen buffer, it scrolls a larger graphics buffer
// i.e. 192x144

// note: pBuffer must start on an address that is a multiple of 4 (just make it a long)

// note to self: can probably remove clears, since the bottom/top lines are off-screen and would be drawn over

// copy scroll buffer to screen buffer
void copyScrollBuffer(unsigned short *scrollBuffer, unsigned short *screenBuffer) {
	register short *src = scrollBuffer;
	register short *dest = screenBuffer;
	register short lines = 99;
	
	src += 265;
	asm volatile (
	   "0:
		move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+
		move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+
		move.w (%0)+,(%1)+;move.w (%0)+,(%1)+
		lea (4,%0),%0
		lea (10,%1),%1
		dbra %2,0b"
		: "=a" (src), "=a" (dest), "=d" (lines)
		: "0"  (src), "1"  (dest), "2"  (lines)
	);
}

// scroll buffer one pixel left
void scrollLeft(unsigned short *pBuffer) {
	register short *buffer = pBuffer;
	register short lines = 143;
	
	buffer += 1728;
	
	asm volatile (
	   "0:
		and.b #0xee,%%ccr
		roxl.w -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0)
		roxl.w -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0)
		roxl.w -(%0);roxl.w -(%0);roxl.w -(%0);roxl.w -(%0)
		dbra %1,0b"
		: "=a" (buffer), "=d" (lines)
		: "0"  (buffer), "1"  (lines)
	);
}


// scroll buffer one pixel right
void scrollRight(unsigned short *pBuffer) {
	register short *buffer = pBuffer;
	register short lines = 143;
	
	asm volatile (
	   "0:
		and.b #0xee,%%ccr
		roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+
		roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+
		roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+;roxr.w (%0)+
		dbra %1,0b"
		: "=a" (buffer), "=d" (lines)
		: "0"  (buffer), "1"  (lines)
	);
}


// scroll buffer one pixel up
void scrollUp(unsigned short *pBuffer) {
	register short *dest = pBuffer;
	register short *src  = dest + 12;
	register short lines = 142;
	
	asm volatile (
	   "0:
		move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+
		move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+
		move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+;move.w (%0)+,(%1)+
		dbra %2,0b"
		: "=a" (src), "=a" (dest), "=d" (lines)
		: "0"  (src),  "1" (dest), "2"  (lines)
	);
}


// scroll buffer one pixel down
void scrollDown(unsigned short *pBuffer) {
	register short *dest = pBuffer;
	register short *src;
	register short lines = 142;

	dest += 1728;
	src = dest - 12;

	asm volatile (
	   "0:
		move.w -(%0),-(%1);move.w -(%0),-(%1);move.w -(%0),-(%1);move.w -(%0),-(%1)
		move.w -(%0),-(%1);move.w -(%0),-(%1);move.w -(%0),-(%1);move.w -(%0),-(%1)
		move.w -(%0),-(%1);move.w -(%0),-(%1);move.w -(%0),-(%1);move.w -(%0),-(%1)
		dbra %2,0b"
		: "=a" (src), "=a" (dest), "=d" (lines)
		: "0"  (src), "1"  (dest), "2"  (lines)
	);
}
