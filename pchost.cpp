//----------------------------------------------------------------------------
//
// All code for setting the state of the host machine sholoud go in this file.
//----------------------------------------------------------------------------

#include 	"game.h"

//----------------------------------------------------------------------------

SLONG	host_setup(void)
{

#if defined (_DEBUG) && defined(_WINDOWS)
	LbEditSetMenu( NULL, NULL, cmds, IDR_MENU1);
	LbErrorLogSetup(NULL, NULL, Lb_ERROR_LOG_NEW);
#endif 

  	if ( !LbScreenSetup(MODE_VRES256, 640, 480, palette))
  	{
  		exit(0);
  	}
 
	LbMouseSetup(NULL, 1, 1);
 	LbIKeyboardOpen();

	return(1);
}

//----------------------------------------------------------------------------

SLONG	host_reset(void)
{
	LbMouseReset();
	LbIKeyboardClose();
	LbScreenReset();

	return(1);
}

//----------------------------------------------------------------------------

SLONG	host_change_res(SLONG new_screen_mode)
{
	if (new_screen_mode != lbDisplay.ScreenMode)
	{
		UWORD	flags_backup = lbDisplay.DrawFlags;

		switch (lbDisplay.ScreenMode)
		{
			case	MODE_MCGA:
//				LbDataFreeAll(mcga_load_files);
				break;

			case	MODE_VRES256:
//				LbDataFreeAll(vres256_load_files);
				break;

		}

 		switch (new_screen_mode)
		{
			case	MODE_MCGA:
				LbScreenReset();
//				LbDataLoadAll(mcga_load_files);
//				LbSpriteSetupAll(setup_sprites);
				if (!LbScreenSetup(MODE_MCGA, 320, 200, palette))
				{
					LbErrorLog("SetupScreen failed");
					exit(1);
				}
				LbMouseSetup(NULL, 1, 1);
				break;

			case	MODE_VRES256:
				LbScreenReset();
//				LbDataLoadAll(vres256_load_files);
//				LbSpriteSetupAll(setup_sprites);
				if (!LbScreenSetup(MODE_VRES256, 640, 480, palette))
				{
					LbErrorLog("SetupScreen failed");
					exit(1);
				}			
				LbMouseSetup(NULL, 1, 1);
				break;

		}
		
		lbDisplay.DrawFlags = flags_backup;
		return(1);
	}
	
	return(0);
}

//----------------------------------------------------------------------------
