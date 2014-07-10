//----------------------------------------------------------------------------
//
// The main game loop should go in this file.
//----------------------------------------------------------------------------

#include 	"game.h"

static 	ULONG	frame = 0;
ULONG	frames;
ULONG	turn;

//----------------------------------------------------------------------------

// exaple of user defined menus on the sdk simulation window
#if  defined(_DEBUG) && defined(_WINDOWS)

	void ChangeToLowRes() 
	{
		flow_control_flags |= TOGGLE_RES;
	}

	void UpdateLowRes(TbEdit_Command *pCmd)
	{
		pCmd = pCmd;
		//LbEditSetCommandState(pCmd, TRUE, );
	}
#endif

//----------------------------------------------------------------------------

static	ULONG	currentTime=LbTimerClock();

SLONG	game()
{
	game_setup();
	turn = 0;
	
	for ( ;!(flow_control_flags & QUIT_TO_DOS) && LbWindowsControl(); frame++)
	{
		control_process();
		game_process();
		draw_game();
		
		LbScreenSwap();
		LbScreenClear(0);
	}

	game_reset();

	return(0);
}

//----------------------------------------------------------------------------

SLONG	game_process()
{
	ULONG	i;
/*
	if (flow_control_flags & TOGGLE_RES)
	{
		flow_control_flags ^= TOGGLE_RES;
		if (lbDisplay.ScreenMode == MODE_MCGA)
		{
			host_change_res(MODE_VRES256);
		}
		else if (lbDisplay.ScreenMode == MODE_VRES256)
		{
			host_change_res(MODE_MCGA);
		}
	}
*/	
	if ( (LbTimerClock() - currentTime) > 2 * 1000)
	{
		frames = frame / 2;
		currentTime = LbTimerClock();
		frame = 0;
	}

	for (i=0; i<MAX_FOODS; i++)
		process_food(i);
	process_snakes();

	turn++;

	return (0);
}

//----------------------------------------------------------------------------

SLONG	game_setup()
{
	time_t	t;

	t = time(NULL);
	srand(t);
	game_setup_memory();
	
//	LbSpriteSetupAll( setup_sprites);

	host_setup();

	init_players();

	LbTextSetWindow(0, 0, lbDisplay.PhysicalScreenWidth, lbDisplay.PhysicalScreenHeight);
	
//	LbTextSetFont(font[0]);

//	LbGhostTableGenerate(palette, 25, "data/ghost.dat");
//	LbFadeTableGenerate(palette, "data/fade.dat");

	return(1);
}

//----------------------------------------------------------------------------

SLONG	game_reset()
{
	game_reset_memory();
	host_reset();
	return(1);
}

//----------------------------------------------------------------------------

SLONG	game_setup_memory()
{
	ULONG	i;

	LbDataLoadAll( game_load_files);
	
	LbDataLoadAll( vres256_load_files);

	init_segments(8192);
	init_snakes();
	init_foods();

	for (i=0; i<MAX_FOODS; i++)
		create_food(i);
	
	return(0);
}

//----------------------------------------------------------------------------

SLONG	game_reset_memory()
{
	LbDataFreeAll( game_load_files);

	switch ( lbDisplay.ScreenMode)
	{
		case	MODE_MCGA:
//			LbDataFreeAll( mcga_load_files);
			break;

		case	MODE_VRES256:
			LbDataFreeAll( vres256_load_files);
			break;

	}

	free_snakes();
	free_foods();

	return(0);
}

//----------------------------------------------------------------------------

