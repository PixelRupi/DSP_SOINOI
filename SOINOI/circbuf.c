#include <csl.h>
#include "circbuf.h"

void init_circular_buffer(CIRCBUFFER *b, Int16 *buf, int N)
{
	b->buf=buf;
	b->L=N;	b->w=0; b->r=0;
}
int circ_put(CIRCBUFFER* b, Int16 data)
{
	if(b->w==(b->r-1)&(b->L-1))
		return 1;
	b->buf[b->w]=data;
	b->w=(b->w+1)&(b->L-1);
	return 0;
}
int circ_get(CIRCBUFFER *b, Int16* data)
{
	if(b->w==b->r)
		return 1;
	*data=b->buf[b->r];
	b->r=(b->r+1)&(b->L-1);
	return 0;
}
int circ_len(CIRCBUFFER *b)
{
	return (b->w-b->r)&(b->L-1);
}
