//----------------------------------------------------------------------------
//
// All keyboard and mouse input should be read in this file.
//----------------------------------------------------------------------------

#include 	"game.h"

//----------------------------------------------------------------------------
		    
SLONG	control_process()
{
	if (lbKeyOn[KB_LALT])
	{
		switch(lbInkey)
		{
			case	KB_ESC:
				flow_control_flags |= QUIT_TO_DOS;
				lbInkey = 0;
				break;
		}
	}
	return(0);
}

//----------------------------------------------------------------------------
