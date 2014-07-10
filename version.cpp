//----------------------------------------------------------------------------
//
// This file is used for version control.
//----------------------------------------------------------------------------

#include 	"game.h"

//----------------------------------------------------------------------------

#define	PRODUCT_NAME		"Snakes!"
#define	VERSION_DATE		__DATE__
#define	VERSION_TIME		__TIME__
#define	SUPPLIED_TO			"BULLFROG PRODUCTIONS LTD." 
#define	VERSION_NUMBER		"BETA V1.0"
#define	PASSWORD			12345678

//----------------------------------------------------------------------------

SLONG	display_copyright()
{
	printf("Copyright (c) 1995 Bullfrog Productions Ltd.\n");
	printf("All rights reserved.\n");
	printf("%s (%s)\n", PRODUCT_NAME, VERSION_NUMBER);
	return(1);
}

//----------------------------------------------------------------------------
