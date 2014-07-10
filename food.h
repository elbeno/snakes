// food.h

#ifndef	_FOOD_H_
#define	_FOOD_H_

#include "game.h"

#define	MAX_FOODS	4

struct	Food
{
	SLONG	Head;
	ULONG	Size;
	ULONG	Timer;

	UBYTE	Colour;
	UBYTE	Effect;
	UWORD	Form;
};

void	init_foods(void);
void	free_foods(void);
void	create_food(ULONG f);
void	destroy_food(ULONG f);
void	draw_food(ULONG f);
void	process_food(ULONG f);
void	snake_eats_food(ULONG s, ULONG f);

extern	struct	Food	*foods;

#endif
