// food.c

#include "game.h"

struct	Food	*foods;

UBYTE	food_colours[21] =
{
	0,
	17,18,19,20,
	21,22,23,24,
	25,26,27,28,
	29,30,31,32,
	33,34,35,36
};

void	init_foods(void)
{
	ULONG	i;

	foods = (struct Food *) MyAlloc(MAX_FOODS * sizeof(struct Food));
	memset(foods,0,sizeof(struct Food)*MAX_FOODS);
	for (i=0; i<MAX_FOODS; i++)
		foods[i].Head = -1;
}

void	free_foods(void)
{
	MyFree(foods);
}

UBYTE	count_bits(UWORD b)
{
	UBYTE	count = 0;

	while (b)
	{
		count += (b&1);
		b >>= 1;
	}
	return count;
}

UBYTE	choose_effect(void)
{
	ULONG	r;

	r = rand()%1000;

	if (r < 600)
		return GROW_EFFECT;
	else if (r < 650)
		return FAST_EFFECT;
	else if (r < 700)
		return SLOW_EFFECT;
	else if (r < 750)
		return SHRINK_EFFECT;
	else if (r < 780)
		return REVERSE_EFFECT;
	else if (r < 810)
		return KEYSWAP_EFFECT;
	else if (r < 840)
		return HEADSWAP_EFFECT;
	else if (r < 870)
		return SPECKLE_EFFECT;
	else if (r < 900)
		return TELEPORT_EFFECT;
	else if (r < 930)
		return SUPER_EFFECT;
	else if (r < 960)
		return INVINCIBLE_EFFECT;
	else if (r < 990)
		return STOP_EFFECT;
	else
		return PSYCHEDELIC_EFFECT;
}

void	create_food(ULONG f)
{
	ULONG	i;
	SLONG	temp_segment;
	UWORD	orig_x, x, y;
	UWORD	form;

	if (f < MAX_FOODS)
	{
		form = 0;
		while (!form)
			form = (UWORD) ((rand()&rand())&0xffff);
		foods[f].Form = form;
		foods[f].Size = count_bits(form);
		foods[f].Effect = choose_effect();
		foods[f].Colour = food_colours[foods[f].Effect];
		foods[f].Timer = 2000;

		temp_segment = get_a_segment();
		if (temp_segment == -1)
			return;
		if (assign_a_food_position(temp_segment,form))
		{
			put_a_segment(temp_segment);
			return;
		}
		orig_x = x = segs[temp_segment].X;
		y = segs[temp_segment].Y;
		put_a_segment(temp_segment);

		for (i=0; i<16; i++)
		{
			if (form & 1)
			{
				temp_segment = get_a_segment();
				if (temp_segment != -1)
				{
					foods[f].Size++;
					segs[temp_segment].Next = foods[f].Head;
					segs[temp_segment].Colour = foods[f].Colour;
					segs[temp_segment].X = x;
					segs[temp_segment].Y = y;
					foods[f].Head = temp_segment;
				}
				else
					return;
			}
			x += BLOB_SIZE;
			if (x - orig_x == BLOB_SIZE*4)
			{
				x = orig_x;
				y += BLOB_SIZE;
			}
			form >>= 1;
		}
	}
}

void	destroy_food(ULONG f)
{
	SLONG	temp_segment;

	if (f < MAX_FOODS)
	{
		foods[f].Size = 0;
		foods[f].Form = 0;
		foods[f].Colour = 0;
		foods[f].Effect = 0;
		foods[f].Timer = 0;
		while (foods[f].Head != -1)
		{
			temp_segment = segs[foods[f].Head].Next;
			put_a_segment(foods[f].Head);
			foods[f].Head = temp_segment;
		}
	}
}

void	draw_food(ULONG f)
{
	SLONG	n;

	n = foods[f].Head;
	while (n != -1)
	{
		DrawBox(segs[n].X-GRID_X_OFFSET,segs[n].Y-GRID_Y_OFFSET,BLOB_SIZE,BLOB_SIZE,segs[n].Colour);
		n = segs[n].Next;
	}
}

void	process_food(ULONG f)
{
	if (!--foods[f].Timer)
	{
		destroy_food(f);
		create_food(f);
	}
}

void	snake_eats_food(ULONG s, ULONG f)
{
	UWORD	beffect;
	ULONG	size;
	ULONG	other_s = s;
	ULONG	count;

	beffect = (UWORD) (1 << (foods[f].Effect-1));
	size = foods[f].Size;

	destroy_food(f);
	create_food(f);

	// clear any effects that use the same timer
	if (LENGTH_EFFECTS&beffect)
	{
		snakes[s].EffectsActive &= ~LENGTH_EFFECTS;
		snakes[s].GrowAmount = 0;
	}
	if (SPEED_EFFECTS&beffect)
	{
		snakes[s].EffectsActive &= ~SPEED_EFFECTS;
		snakes[s].EffectTimer2 = 0;
	}
	if (GENERAL_EFFECTS&beffect)
	{
		snakes[s].EffectsActive &= ~GENERAL_EFFECTS;
		snakes[s].EffectTimer = 0;
	}
	if (SUPER_EFFECT&beffect)
	{
		snakes[s].EffectsActive &= ~LENGTH_EFFECTS;
		snakes[s].EffectsActive &= ~SPEED_EFFECTS;
		snakes[s].GrowAmount = 0;
		snakes[s].EffectTimer = 0;
	}

	// apply effect

	switch (beffect)
	{
		case	BAPPEAR_EFFECT:
			break;
		case	BGROW_EFFECT:
		case	BSHRINK_EFFECT:
			snakes[s].EffectsActive |= beffect;
			snakes[s].GrowAmount = size*(2+rand()%3);
			// min snake length is 2
			if (beffect == BSHRINK_EFFECT && snakes[s].GrowAmount > snakes[s].Length-2)
			{
				snakes[s].GrowAmount = snakes[s].Length - 2;
				if (!snakes[s].GrowAmount)
					snakes[s].EffectsActive &= ~BSHRINK_EFFECT;
			}
			break;
		case	BINVINCIBLE_EFFECT:
			snakes[s].EffectsActive |= beffect;
			snakes[s].Invincibility += 4;
			break;
		case	BINVISIBLE_EFFECT:
			snakes[s].EffectsActive |= beffect;
			snakes[s].EffectTimer = size*(4+rand()%4);
			break;
		case	BPSYCHEDELIC_EFFECT:
			snakes[s].EffectsActive |= beffect;
			snakes[s].EffectTimer = size*(12+rand()%8);
			break;
		case	BSLOW_EFFECT:
		case	BFAST_EFFECT:
			snakes[s].EffectsActive |= beffect;
			snakes[s].EffectTimer2 = size*(12+rand()%8);
			break;
		case	BSTOP_EFFECT:
			snakes[s].EffectsActive |= beffect;
			snakes[s].EffectTimer2 = size*(6+rand()%4);
			break;

		case	BKEYSWAP_EFFECT:
			swap_keys(s);
			break;
		case	BHEADSWAP_EFFECT:
			if (number_of_players > 1)
			{
				count = 0;
				while ((other_s == s || (snakes[other_s].EffectsActive & BAPPEAR_EFFECT)) && count < 50)
				{
					other_s = rand()%number_of_players;
					count++;
				}
				if (other_s != s)
					swap_heads(s,other_s);
			}
			break;
		case	BREVERSE_EFFECT:
			reverse(s);
			break;
		case	BSPECKLE_EFFECT:
			speckle_tail(s);
			break;
		case	BTELEPORT_EFFECT:
			teleport(s);
			break;
		case	BDEAD_EFFECT:
			snakes[s].EffectsActive |= beffect;
			break;
		case	BSUPER_EFFECT:
			snakes[s].EffectsActive |= BFAST_EFFECT;
			snakes[s].EffectsActive |= BGROW_EFFECT;
			snakes[s].EffectTimer2 = -1;
			snakes[s].GrowAmount = -1;
			break;
		default:
			break;
	}
	
	snakes[s].Score += size*3;
}
