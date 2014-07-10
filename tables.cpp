//----------------------------------------------------------------------------
//
// All game tables should go in this file.
//----------------------------------------------------------------------------

#include 	"game.h"

//----------------------------------------------------------------------------

struct	TbLoadFiles		game_load_files[]=
{
//	-------------------------------------------------------------------------------------------------------------
//	FILE NAME				ADDRESS					END ADDRESS					NUMBER OF BYTES		FLAGS
//	-------------------------------------------------------------------------------------------------------------
	{"pal.dat",				(VOID**)&palette,		0,							0,					0			},
//	{"data/font0-0.dat",	(VOID**)&font_data[0],	(VOID**)&end_font_data[0],	0,					0			},
//	{"data/font0-0.tab",	(VOID**)&font[0],		(VOID**)&end_fonts[0],		0,					0			},
//	{"data/point0-0.dat",	(VOID**)&pointer_data,	(VOID**)&end_pointer_data,	0,					0			},
//	{"data/point0-0.tab",	(VOID**)&pointer,		(VOID**)&end_pointers,		0,					0			},
	{"!",					0,						0,							0,					0			}
//	-------------------------------------------------------------------------------------------------------------
};

//----------------------------------------------------------------------------

struct	TbLoadFiles		mcga_load_files[]=
{
//	-------------------------------------------------------------------------------------------------------------
//	FILE NAME				ADDRESS						END ADDRESS						NUMBER OF BYTES		FLAGS
//	-------------------------------------------------------------------------------------------------------------
#ifdef	_DOSX
	{"*WS				",	(VOID**)&lbDisplay.WScreen,	0,								MCGA_SCREEN_MEM,	0	},
	{"*VesaData",			(VOID**)&lbVesaData,			0,								256,				LOW_MEM_MALLOC	},
#endif
//	{"data/mspr0-0.dat",	(VOID**)&game_sprite_data,	(VOID**)&end_game_sprite_data,	0,					0	},
//	{"data/mspr0-0.tab",	(VOID**)&game_sprite,		(VOID**)&end_game_sprites,		0,					0	},
	{"!",					0,							0,								0,					0	}
//	-------------------------------------------------------------------------------------------------------------
};

//----------------------------------------------------------------------------

struct	TbLoadFiles		vres256_load_files[]=
{
//	-------------------------------------------------------------------------------------------------------------
//	FILE NAME				ADDRESS						END ADDRESS						NUMBER OF BYTES		FLAGS
//	-------------------------------------------------------------------------------------------------------------
#ifdef	_DOSX
	{"*WS		",			(VOID**)&lbDisplay.WScreen,	0,								VRES256_SCREEN_MEM,	0				},
	{"*VesaData",			(VOID**)&lbVesaData,			0,								256,				LOW_MEM_MALLOC	},
#endif
//	{"data/hspr0-0.dat",	(VOID**)&game_sprite_data,	(VOID**)&end_game_sprite_data,	0,					0				},
//	{"data/hspr0-0.tab",	(VOID**)&game_sprite,		(VOID**)&end_game_sprites,		0,					0				},
	{"!",					0,							0,								0,					0				}
//	-------------------------------------------------------------------------------------------------------------
};


//***************************************************************************
//		Sprinte table
//***************************************************************************

struct	TbSetupSprite		setup_sprites[]=
{
//***************************************************************************
//	STRUCTURE START		STRUCTURE END		DATA ADDRESS
//***************************************************************************
	{&pointer,			&end_pointers,		&pointer_data		},
	{&font[0],			&end_fonts[0],		&font_data[0]		},
	{&game_sprite,		&end_game_sprites,	&game_sprite_data	},
	{0,					0,					0					},
//***************************************************************************
};




#if defined (_DEBUG) && defined(_WINDOWS)

//***************************************************************************
//		Menu Bar Config	(presented on the simulation windows menu bar)
//***************************************************************************
void ChangeToLowRes();
void UpdateLowRes(TbEdit_Command *pCmd);
TbEdit_DispatchTable cmds[] =
{
	{ID_MARK01_HELLO, ChangeToLowRes, UpdateLowRes},
	{0}
};
//***************************************************************************

#endif

