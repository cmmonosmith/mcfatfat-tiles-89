// timer functions

volatile unsigned short counter;

// auto int 1 is main hardware timer, ~350Hz
DEFINE_INT_HANDLER (my_int_1_handler)
{
    counter++;
}

// a delay, in ticks, for the main hardware timer
void delay(unsigned short ticks) {
	counter = 0;
	while (counter < ticks);
}
