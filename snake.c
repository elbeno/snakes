// snake.c

#include "game.h"

struct	Snake	*snakes;

SBYTE	x_move[7] = {0,  BLOB_SIZE/2, BLOB_SIZE, BLOB_SIZE/2, -BLOB_SIZE/2, -BLOB_SIZE, -BLOB_SIZE/2};
SBYTE	y_move[7] = {0, -BLOB_SIZE,   0,         BLOB_SIZE,    BLOB_SIZE,    0,         -BLOB_SIZE  };

UBYTE	snake_colours[MAX_SNAKES] =
{
	1,2,3,4,
	5,6,7,8,
	9,10,11,12,
	13,14,15,16
};

void	init_snakes(void)
{
	ULONG	i;

	snakes = (struct Snake *) MyAlloc(MAX_SNAKES * sizeof(struct Snake));
	memset(snakes,0,sizeof(struct Snake)*MAX_SNAKES);
	for (i=0; i<MAX_SNAKES; i++)
	{
		snakes[i].Head = -1;
		snakes[i].Lives = -1;
	}
}

void	free_snakes(void)
{
	MyFree(snakes);
}

void	create_snake(ULONG s)
{
	ULONG	i;
	SLONG	temp_segment;
	UWORD	x, y;

	if (s < MAX_SNAKES)
	{
		snakes[s].Length = 0;
		snakes[s].Colour = snake_colours[s];
		snakes[s].EffectTimer = 64;
		snakes[s].EffectTimer2 = 0;
		snakes[s].EffectsActive = BAPPEAR_EFFECT;
		snakes[s].Invincibility = 0;
		snakes[s].GrowAmount = 0;
		snakes[s].Direction = (UBYTE) (rand()%6 + 1);

		// snakes start with 5 segments
		for (i=0; i<5; i++)
		{
			temp_segment = get_a_segment();
			if (temp_segment != -1)
			{
				if (snakes[s].Length == 0)
				{
					if (assign_a_snake_position(temp_segment,snakes[s].Direction))
					{
						put_a_segment(temp_segment);
						return;
					}
					x = segs[temp_segment].X;
					y = segs[temp_segment].Y;
				}
				snakes[s].Length++;
				if (snakes[s].Length > snakes[s].MaxLength)
					snakes[s].MaxLength = snakes[s].Length;
				segs[temp_segment].Next = snakes[s].Head;
				segs[temp_segment].Colour = snakes[s].Colour;
				segs[temp_segment].X = x;
				segs[temp_segment].Y = y;
				snakes[s].Head = temp_segment;
				x += x_move[snakes[s].Direction];
				y += y_move[snakes[s].Direction];
			}
			else
				return;
		}
	}
}

void	destroy_snake(ULONG s)
{
	SLONG	temp_segment;

	if (s < MAX_SNAKES)
	{
		snakes[s].Length = 0;
		while (snakes[s].Head != -1)
		{
			temp_segment = segs[snakes[s].Head].Next;
			put_a_segment(snakes[s].Head);
			snakes[s].Head = temp_segment;
		}
		snakes[s].EffectTimer = 0;
		snakes[s].EffectTimer2 = 0;
		snakes[s].EffectsActive = 0;
		snakes[s].Invincibility = 0;
		snakes[s].GrowAmount = 0;
		snakes[s].Colour = 0;
		switch (snakes[s].Left)
		{
			case	-1:
				Display.LeftButton = 0;
			case	-2:
				Display.RightButton = 0;
			case	-3:
				Display.MiddleButton = 0;
			default:
				KeyOn[snakes[s].Left] = 0;
		}
		switch (snakes[s].Right)
		{
			case	-1:
				Display.LeftButton = 0;
			case	-2:
				Display.RightButton = 0;
			case	-3:
				Display.MiddleButton = 0;
			default:
				KeyOn[snakes[s].Right] = 0;
		}
	}
}

void	process_snake_effect(ULONG s)
{
	if (snakes[s].EffectsActive & BAPPEAR_EFFECT)
	{
		// fiddle colour
		
	}
	if (snakes[s].EffectsActive & BPSYCHEDELIC_EFFECT)
	{
		// fiddle colour
		
	}

	if (snakes[s].EffectsActive & SPEED_EFFECTS)
	{
		if (!--snakes[s].EffectTimer2)
			snakes[s].EffectsActive &= ~SPEED_EFFECTS;
	}
	if (snakes[s].EffectsActive & GENERAL_EFFECTS)
	{
		if (!--snakes[s].EffectTimer)
			snakes[s].EffectsActive &= ~GENERAL_EFFECTS;
	}
}

void	turn_left(ULONG s)
{
	if (--snakes[s].Direction < 1)
		snakes[s].Direction = 6;
}

void	turn_right(ULONG s)
{
	if (++snakes[s].Direction > 6)
		snakes[s].Direction = 1;
}

void	control_snake(ULONG s)
{
	// check for left turn
	if (snakes[s].Left < 0)
	{
		// using mouse buttons
		if (Display.LeftButton && snakes[s].Left == -1)
		{
			Display.LeftButton = 0;
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
				turn_right(s);
			else
				turn_left(s);
		}
		else if (Display.RightButton && snakes[s].Left == -2)
		{
			Display.RightButton = 0;
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
				turn_right(s);
			else
				turn_left(s);
		}
		else if (Display.MiddleButton && snakes[s].Left == -3)
		{
			Display.MiddleButton = 0;
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
				turn_right(s);
			else
				turn_left(s);
		}
	}
	else
	{
		// using keyboard
		if (KeyOn[snakes[s].Left])
		{
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
				turn_right(s);
			else
				turn_left(s);
			KeyOn[snakes[s].Left] = 0;
		}
	}

	// check for right turn
	if (snakes[s].Right < 0)
	{
		// using mouse buttons
		if (Display.LeftButton && snakes[s].Right == -1)
		{
			Display.LeftButton = 0;
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
				turn_left(s);
			else
				turn_right(s);
		}
		else if (Display.RightButton && snakes[s].Right == -2)
		{
			Display.RightButton = 0;
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
				turn_left(s);
			else
				turn_right(s);
		}
		else if (Display.MiddleButton && snakes[s].Right == -3)
		{
			Display.MiddleButton = 0;
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
				turn_left(s);
			else
				turn_right(s);
		}
	}
	else
	{
		// using keyboard
		if (KeyOn[snakes[s].Right])
		{
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
				turn_left(s);
			else
				turn_right(s);
			KeyOn[snakes[s].Right] = 0;
		}
	}
}

void	move_snake(ULONG s)
{
	SLONG	temp_segment;
	SLONG	n;

	if (snakes[s].EffectsActive & BAPPEAR_EFFECT)	// appearing snakes don't move
		return;

	if (snakes[s].EffectsActive & BDEAD_EFFECT)
	{
		// remove the tail
		n = snakes[s].Head;
		if (segs[n].Next == -1)
		{
			put_a_segment(n);
			snakes[s].Head = -1;
			destroy_snake(s);
			create_snake(s);
		}
		else
		{
			while (segs[segs[n].Next].Next != -1)
				n = segs[n].Next;
			temp_segment = segs[n].Next;
			segs[n].Next = -1;
			put_a_segment(temp_segment);
			snakes[s].Length--;
		}
		return;
	}

	// move the head on
	temp_segment = get_a_segment();
	if (temp_segment != -1)
	{
		segs[temp_segment].Next = snakes[s].Head;
		segs[temp_segment].X = (UWORD) (segs[snakes[s].Head].X + x_move[snakes[s].Direction]);
		segs[temp_segment].Y = (UWORD) (segs[snakes[s].Head].Y + y_move[snakes[s].Direction]);
		if (snakes[s].EffectsActive & BINVINCIBLE_EFFECT)
			segs[temp_segment].Colour = WHITE-2;
		else
			segs[temp_segment].Colour = snakes[s].Colour;
		snakes[s].Head = temp_segment;
	}

	if (snakes[s].EffectsActive & BGROW_EFFECT)
	{
		snakes[s].Length++;
		if (snakes[s].Length > snakes[s].MaxLength)
			snakes[s].MaxLength = snakes[s].Length;
		if (!--snakes[s].GrowAmount)
			snakes[s].EffectsActive &= ~BGROW_EFFECT;
	}
	else
	{
		// remove the tail
		n = snakes[s].Head;
		while (segs[segs[n].Next].Next != -1)
			n = segs[n].Next;
		temp_segment = segs[n].Next;
		segs[n].Next = -1;
		put_a_segment(temp_segment);
		if (snakes[s].EffectsActive & BSHRINK_EFFECT)
		{
			// remove the tail again
			n = snakes[s].Head;
			while (segs[segs[n].Next].Next != -1)
				n = segs[n].Next;
			temp_segment = segs[n].Next;
			segs[n].Next = -1;
			put_a_segment(temp_segment);
			snakes[s].Length--;
			if (!--snakes[s].GrowAmount)
				snakes[s].EffectsActive &= ~BSHRINK_EFFECT;
		}
	}
}

void	do_snake_collide(ULONG s)
{
	ULONG	col;
	UWORD	col_object;
	UWORD	coverage;

	col = check_collision(segs[snakes[s].Head].X,segs[snakes[s].Head].Y,s);
	col_object = (UWORD) (col&0xffff);
	coverage = (UWORD) (col>>16);

	if (col)
	{
		if (col_object == 255)		// hit a wall - fatal
		{
			snakes[s].EffectsActive |= BDEAD_EFFECT;
			if (snakes[s].Lives >= 0)
				snakes[s].Lives--;
		}
		else if (col_object < MAX_SNAKES)	// hit a snake
		{
			if (snakes[col_object].EffectsActive & BAPPEAR_EFFECT)
			{
				// snake was still appearing - eat it!
				destroy_snake(col_object);
				create_snake(col_object);
				snakes[s].Score += 50;
			}
			if (snakes[s].EffectsActive & BINVINCIBLE_EFFECT)	// am I invincible?
			{
				snakes[s].Invincibility -= coverage;
				if (snakes[s].Invincibility <= 0)
					snakes[s].EffectsActive &= ~BINVINCIBLE_EFFECT;
				if (snakes[s].Invincibility < 0)	// oops it ran out
				{
					snakes[s].Invincibility = 0;
					snakes[s].EffectsActive |= BDEAD_EFFECT;
					if (snakes[s].Lives >= 0)
						snakes[s].Lives--;
					if (s != col_object)
						snakes[col_object].Score += 75;
					else
						snakes[col_object].Score -= 25;
				}
			}
			else
			{
				snakes[s].EffectsActive |= BDEAD_EFFECT;
				if (snakes[s].Lives >= 0)
					snakes[s].Lives--;
				if (s != col_object)
					snakes[col_object].Score += 75;
				else
					snakes[col_object].Score -= 25;
			}
		}
		else
		{
			snake_eats_food(s,col_object-MAX_SNAKES);
		}
	}

}

void	process_snakes(void)
{
	ULONG	i;

	// control, process effects and move snakes
	for (i=0; i<MAX_SNAKES; i++)
	{
		if (snakes[i].Head != -1)
		{
			process_snake_effect(i);
			if (!(snakes[i].EffectsActive & BSLOW_EFFECT) || turn&1)
			{
				if (!(snakes[i].EffectsActive & BDEAD_EFFECT))
					control_snake(i);
				if (!(snakes[i].EffectsActive & BSTOP_EFFECT))
					move_snake(i);
			}
		}
	}

	// check for collisions
	for (i=0; i<MAX_SNAKES; i++)
	{
		if (!(snakes[i].EffectsActive & (BDEAD_EFFECT|BAPPEAR_EFFECT)))
			do_snake_collide(i);
	}


	// control and move fast snakes again
	for (i=0; i<MAX_SNAKES; i++)
	{
		if (snakes[i].EffectsActive & BFAST_EFFECT)
		{
			if (snakes[i].Head != -1)
			{
				if (!(snakes[i].EffectsActive & BDEAD_EFFECT))
					control_snake(i);
				move_snake(i);
			}
		}
	}

	// check for collisions again (fast snakes)
	for (i=0; i<MAX_SNAKES; i++)
	{
		if (snakes[i].EffectsActive & BFAST_EFFECT)
		{
			if (!(snakes[i].EffectsActive & (BDEAD_EFFECT|BAPPEAR_EFFECT)))
				do_snake_collide(i);
		}
	}
}

void	draw_snake(ULONG s)
{
	SLONG	n;

	n = snakes[s].Head;

	if (n != -1)
	{
		if (snakes[s].EffectsActive & BDEAD_EFFECT)
//			DrawBox(segs[n].X,segs[n].Y,BLOB_SIZE,BLOB_SIZE,segs[n].Colour);
			DrawBox(segs[n].X-GRID_X_OFFSET,segs[n].Y-GRID_Y_OFFSET,BLOB_SIZE,BLOB_SIZE,segs[n].Colour);
		else
		{
			if (snakes[s].EffectsActive & BKEYSWAP_EFFECT)
//				DrawBox(segs[n].X,segs[n].Y,BLOB_SIZE,BLOB_SIZE,WHITE-1);
				DrawBox(segs[n].X-GRID_X_OFFSET,segs[n].Y-GRID_Y_OFFSET,BLOB_SIZE,BLOB_SIZE,WHITE-1);
			else
//				DrawBox(segs[n].X,segs[n].Y,BLOB_SIZE,BLOB_SIZE,WHITE);
				DrawBox(segs[n].X-GRID_X_OFFSET,segs[n].Y-GRID_Y_OFFSET,BLOB_SIZE,BLOB_SIZE,WHITE);
		}
		n = segs[n].Next;
	}

	while (n != -1)
	{
		if (snakes[s].EffectsActive & BAPPEAR_EFFECT)
		{
//			DrawBox(segs[n].X,segs[n].Y,BLOB_SIZE,BLOB_SIZE,segs[n].Colour);
			if (turn&1)
				DrawBox(segs[n].X-GRID_X_OFFSET,segs[n].Y-GRID_Y_OFFSET,BLOB_SIZE,BLOB_SIZE,WHITE);
			else
				DrawBox(segs[n].X-GRID_X_OFFSET,segs[n].Y-GRID_Y_OFFSET,BLOB_SIZE,BLOB_SIZE,segs[n].Colour);
		}
		else
		{
//			DrawBox(segs[n].X,segs[n].Y,BLOB_SIZE,BLOB_SIZE,segs[n].Colour);
			DrawBox(segs[n].X-GRID_X_OFFSET,segs[n].Y-GRID_Y_OFFSET,BLOB_SIZE,BLOB_SIZE,segs[n].Colour);
		}

		n = segs[n].Next;
	}
}
