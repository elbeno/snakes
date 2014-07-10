//----------------------------------------------------------------------------
//
// All game include files should be grouped into this file.
//----------------------------------------------------------------------------

#ifndef	_GAME_H_
#define	_GAME_H_

// The Bullfrog library header.
#include 	<bullfrog.h>	

#ifdef _BULLFROG_WIN32_
	#define	sprintf wsprintf
#endif	

// Local headers.
#include 	"defines.h"
#include 	"structs.h"
#include 	"extern.h"
#include 	"macros.h"
#include 	"resource.h"

// game headers
#include	"segment.h"
#include 	"snake.h"
#include	"effect.h"
#include	"food.h"
#include	"grid.h"
#include	"player.h"

extern	ULONG	turn;

#endif

//----------------------------------------------------------------------------
