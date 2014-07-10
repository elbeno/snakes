//----------------------------------------------------------------------------
//
// This file should process command line arguments and call the main game function.
//----------------------------------------------------------------------------

#include 	"game.h"

//----------------------------------------------------------------------------

SLONG	main(UWORD argc, CBYTE **argv)
{
	SLONG	return_buffer;
	
	argc=argc;
	argv=argv;

	display_copyright();

	return_buffer = game();
	
	display_copyright();	 
	
	return (return_buffer);
}

//----------------------------------------------------------------------------



