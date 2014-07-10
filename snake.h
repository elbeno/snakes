// snake.h

#ifndef	_SNAKE_H_
#define	_SNAKE_H_

#include "game.h"

#define	MAX_SNAKES	16
#define	WHITE		255

#define	NORTHEAST	1
#define	EAST		2
#define	SOUTHEAST	3
#define	SOUTHWEST	4
#define	WEST		5
#define	NORTHWEST	6

extern	SBYTE	x_move[7];
extern	SBYTE	y_move[7];

struct	Snake
{
	CBYTE	*Name;
	ULONG	Score;
	SLONG	Head;
	ULONG	Length;
	ULONG	MaxLength;

	SLONG	EffectTimer;
	SLONG	EffectTimer2;
	UWORD	EffectsActive;
	SWORD	Invincibility;
	SLONG	GrowAmount;

	SWORD	Left;
	SWORD	Right;

	UBYTE	Colour;
	UBYTE	Direction;
	SBYTE	Lives;
};

void	init_snakes(void);
void	free_snakes(void);
void	create_snake(ULONG s);
void	process_snakes(void);
void	draw_snake(ULONG s);

extern	struct	Snake	*snakes;

#endif
