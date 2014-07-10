// segment.c

#include "game.h"

struct	Segment	*segs;
SLONG	free_head;

void	init_segments(ULONG size)
{
	ULONG	i;

	segs = (struct Segment *) MyAlloc(size * sizeof(struct Segment));
	for (i=0; i<size; i++)
	{
		segs[i].Next = i+1;
	}
	segs[i-1].Next = -1;
	free_head = 0;
}

SLONG	get_a_segment(void)
{
	SLONG	ret = -1;

	if (free_head != -1)
	{
		ret = free_head;
		free_head = segs[free_head].Next;
	}
	return ret;
}

void	put_a_segment(SLONG	s)
{
	segs[s].X = 0;
	segs[s].Y = 0;
	segs[s].Colour = 0;
	segs[s].Next = free_head;
	free_head = s;
}

