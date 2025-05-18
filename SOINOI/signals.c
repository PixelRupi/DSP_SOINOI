#include "signals.h"
#include "LED.h"

volatile int last_error=0;

void signal_err(int err)
{
	last_error=err;
	if(last_error!=0)
		LED(last_error);
	else
		LED(0);
}
void set_err(int err)
{
	last_error|=err;
	if(last_error!=0)
		LED(last_error);
	else
		LED(0);
}

void clear_err(int err)
{
	last_error&=~err;
	if(last_error!=0)
		LED(last_error);
	else
		LED(0);
}
