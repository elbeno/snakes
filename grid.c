// grid.c

#include "game.h"

void	draw_grid(void)
{
	Display.DrawFlags = OUTLINE_FLAG;
	DrawBox(GRID_X_OFFSET-1,GRID_Y_OFFSET-1,MAX_X*BLOB_SIZE+2,MAX_Y*BLOB_SIZE+2,WHITE);
	Display.DrawFlags = 0;
}

void	draw_scores(void)
{
	CBYTE	str[128];
	ULONG	i;
	UWORD	x = 0, y = 0;

	for (i=0; i<MAX_SNAKES; i++)
	{
		if (snakes[i].Head != -1)
		{
			sprintf(str,"%8s %d %d",snakes[i].Name,snakes[i].Score,snakes[i].MaxLength);
			DrawCheapText(x,y,str,snakes[i].Colour);
		}
		y += 10;
		if (y == 20)
		{
			x += 80;
			y = 0;
		}
	}
}

SLONG	check_collision(UWORD x, UWORD y, SLONG s)
{
	// returns:
	// 0 - no collision
	// low word contains collision object:
	// 255 - wall
	// 0 - MAX_SNAKES-1 - snake
	// MAX_SNAKES - ? - food
	// high word contains collision coverage (2, 4) for snake

	ULONG	i;
	SLONG	n;
	SLONG	ret = 0;

	// wall check
	if (x < GRID_X_OFFSET || x > (GRID_X_OFFSET+(MAX_X-1)*BLOB_SIZE))
		return 255;
	if (y < GRID_Y_OFFSET || y > (GRID_Y_OFFSET+(MAX_Y-1)*BLOB_SIZE))
		return 255;
	
	for (i=0; i<MAX_FOODS; i++)
	{
		n = foods[i].Head;
		while (n != -1)
		{
			if (y == segs[n].Y && abs(x-segs[n].X) <= 2)
			{
				return (i + MAX_SNAKES);
			}
			n = segs[n].Next;
		}
	}

	for (i=0; i<MAX_SNAKES; i++)
	{
		n = snakes[i].Head;
		if (s == i)		// don't collide with my own head!
			n = segs[n].Next;
		while (n != -1)
		{
			if (y == segs[n].Y && abs(x-segs[n].X) <= 2)
			{
				ret = i;
				if (x-segs[n].X)
					ret |= 2<<16;
				else
					ret |= 4<<16;
				return ret;
			}
			n = segs[n].Next;
		}
	}

	return 0;
}

SLONG	assign_a_snake_position(ULONG s, UBYTE d)
{
	UWORD	orig_x, orig_y;
	UWORD	x, y;
	ULONG	i;
	UBYTE	hit = 1;
	UBYTE	count = 0;

	while (hit == 1 && count < 100)
	{
		x = (UWORD) (rand()%(MAX_X-12) + 5);
		y = (UWORD) (rand()%(MAX_Y-12) + 5);
		orig_x = x = (UWORD) TO_REAL_X(x);
		orig_y = y = (UWORD) TO_REAL_Y(y);
		for (i=0; i<5; i++)
		{
			if (check_collision(x,y,-1))
			{
				count++;
				break;
			}
			x += x_move[d];
			y += y_move[d];
		}
		if (i == 5)
			hit = 0;
	}
	if (count == 100)
		return 1;
	segs[s].X = orig_x;
	segs[s].Y = orig_y;

	return 0;
}

SLONG	assign_a_food_position(ULONG s, UWORD form)
{
	UWORD	orig_x, orig_y;
	UWORD	x, y;
	ULONG	i;
	UBYTE	hit = 1;
	UBYTE	count = 0;

	while (hit == 1 && count < 100)
	{
		x = (UWORD) (rand()%MAX_X);
		y = (UWORD) (rand()%MAX_Y);
		orig_x = x = (UWORD) TO_REAL_X(x);
		orig_y = y = (UWORD) TO_REAL_Y(y);
		for (i=0; i<16; i++)
		{
			if (form & 1)
			{
				if (check_collision(x,y,-1))
				{
					count++;
					break;
				}
			}
			x += BLOB_SIZE;
			if (x - orig_x == BLOB_SIZE*4)
			{
				x = orig_x;
				y += BLOB_SIZE;
			}
			form >>= 1;
		}
		if (i == 16)
			hit = 0;
	}
	if (count == 100)
		return 1;
	segs[s].X = orig_x;
	segs[s].Y = orig_y;

	return 0;
}

