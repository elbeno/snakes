// effect.c

#include "game.h"

SLONG	nextbuf[1024];

void	swap_heads(ULONG s1, ULONG s2)
{
	UWORD	x, y;
	UBYTE	d;

	x = segs[snakes[s1].Head].X;
	y = segs[snakes[s1].Head].Y;
	segs[snakes[s1].Head].X = segs[snakes[s2].Head].X;
	segs[snakes[s1].Head].Y = segs[snakes[s2].Head].Y;
	segs[snakes[s2].Head].X = x;
	segs[snakes[s2].Head].Y = y;

	d = snakes[s1].Direction;
	snakes[s1].Direction = snakes[s2].Direction;
	snakes[s2].Direction = d;
}

void	swap_keys(ULONG s)
{
	ULONG	i;

	for (i=0; i<MAX_SNAKES; i++)
	{
		if (snakes[i].Head != -1)
		{
			if (i == s)
			{
				if (snakes[i].EffectsActive & BKEYSWAP_EFFECT)
					snakes[i].EffectsActive &= ~BKEYSWAP_EFFECT;
			}
			else
				snakes[i].EffectsActive ^= BKEYSWAP_EFFECT;
		}
	}
}

void	teleport(ULONG s)
{
	UWORD	x, y;
	ULONG	count = 0;

	do
	{
		x = (UWORD) TO_REAL_X(rand()%MAX_X);
		y = (UWORD) TO_REAL_Y(rand()%MAX_Y);
		count++;
	} while (check_collision(x,y,-1) && count < 100);

	if (count != 100)
	{
		segs[snakes[s].Head].X = x;
		segs[snakes[s].Head].Y = y;
	}
}


void	reverse(ULONG s)
{
	SLONG	n;
	ULONG	i;
	ULONG	r1, r2;
	SLONG	l;

	l = snakes[s].Length;
	if (l > 1024)
		return;
	
	// get the next fields
	n = snakes[s].Head;
	i = 0;
	while (n != -1)
	{
		nextbuf[i++] = n;
		n = segs[n].Next;
	}

	// reverse them
	for (i=0; i<l/2; i++)
	{
		r1 = i;
		r2 = l-i-1;
		n = nextbuf[r1];
		nextbuf[r1] = nextbuf[r2];
		nextbuf[r2] = n;
	}

	// put them back
	snakes[s].Head = nextbuf[0];
	for (i=0; i<l-1; i++)
	{
		segs[nextbuf[i]].Next = nextbuf[i+1];
	}
	segs[nextbuf[i]].Next = -1;

	// reverse direction
	snakes[s].Direction += 3;
	if (snakes[s].Direction > 6)
		snakes[s].Direction -= 6;
}

void	speckle_tail(ULONG s)
{
	SLONG	n;
	ULONG	i;
	ULONG	r1, r2;
	ULONG	l;

	l = snakes[s].Length;
	if (l > 1024)
		return;
	
	// get the next fields
	n = segs[snakes[s].Head].Next;
	i = 0;
	while (n != -1)
	{
		nextbuf[i++] = n;
		n = segs[n].Next;
	}

	// randomly permute them
	for (i=0; i<l-1; i++)
	{
		r1 = rand()%(l-1);
		r2 = rand()%(l-1);
		if (r1 != r2)
		{
			n = nextbuf[r1];
			nextbuf[r1] = nextbuf[r2];
			nextbuf[r2] = n;
		}
	}

	// put them back
	segs[snakes[s].Head].Next = nextbuf[0];
	for (i=0; i<l-2; i++)
	{
		segs[nextbuf[i]].Next = nextbuf[i+1];
	}
	segs[nextbuf[i]].Next = -1;
}