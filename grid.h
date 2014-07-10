// grid.h

#ifndef	_GRID_H_
#define	_GRID_H_

#include "game.h"

#define	BLOB_SIZE		4
#define	GRID_X_OFFSET	4
#define	GRID_Y_OFFSET	20
#define	MAX_X			158
#define	MAX_Y			114

#define	TO_GRID_X(x)	((x-GRID_X_OFFSET)/BLOB_SIZE)
#define	TO_GRID_Y(y)	((y-GRID_Y_OFFSET)/BLOB_SIZE)
#define	TO_REAL_X(x)	((x*BLOB_SIZE)+GRID_X_OFFSET)
#define	TO_REAL_Y(y)	((y*BLOB_SIZE)+GRID_Y_OFFSET)

SLONG	check_collision(UWORD x, UWORD y, SLONG s);
SLONG	assign_a_snake_position(ULONG s, UBYTE d);
SLONG	assign_a_food_position(ULONG s, UWORD form);

void	draw_grid(void);
void	draw_scores(void);

#endif
