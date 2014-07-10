// segment.h

#ifndef	_SEGMENT_H_
#define	_SEGMENT_H_

#include "game.h"

struct	Segment
{
	UWORD	X;
	UWORD	Y;
	SLONG	Next;
	UBYTE	Colour;
};

void	  	init_segments(ULONG size);
SLONG	  	get_a_segment(void);
void	  	put_a_segment(SLONG	s);

extern	struct	Segment	*segs;

#endif
