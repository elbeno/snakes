//----------------------------------------------------------------------------
//
// All global variables should go in this file.
//----------------------------------------------------------------------------

#include 	"game.h"

//----------------------------------------------------------------------------

//mouse pointers 
SBYTE*					pointer_data;
SBYTE*					end_pointer_data;
struct	TbSprite		*pointer;
struct	TbSprite		*end_pointers;

//internal game sprites
SBYTE*					game_sprite_data;
SBYTE*					end_game_sprite_data;
struct	TbSprite		*game_sprite;
struct	TbSprite		*end_game_sprites;

//all fonts
SBYTE*					font_data[8];
SBYTE*					end_font_data[8];
struct	TbSprite		*font[8];
struct	TbSprite		*end_fonts[8];

//game palette
UBYTE					*palette;

// Global program control flags
UWORD					flow_control_flags = 0;

// Action Table
class	TActionTable  	act;

//----------------------------------------------------------------------------



