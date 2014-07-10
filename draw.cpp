//----------------------------------------------------------------------------
//
// All functions that draw should go in this file.
//----------------------------------------------------------------------------

#include 	"game.h"

//----------------------------------------------------------------------------
extern ULONG	frames;

SLONG	draw_game()
{
//	CBYTE	text[100];
	ULONG	i;
	
	if (LbScreenLock() != Lb_ERROR)
	{
//		sprintf(text, "FPS %d", frames);
//		DrawCheapText(0, 180, text, 255);

		draw_grid();
		draw_scores();

		SetGraphicsWindow(GRID_X_OFFSET,GRID_Y_OFFSET,BLOB_SIZE*MAX_X,BLOB_SIZE*MAX_Y);

		for (i=0; i<MAX_FOODS; i++)
			draw_food(i);
	
		for (i=0; i<number_of_players; i++)
			draw_snake(i);

		SetGraphicsWindow(0,0,Display.PhysicalScreenWidth,Display.PhysicalScreenHeight);

		LbScreenUnlock();
	}
	
	return(1);
}

//----------------------------------------------------------------------------


