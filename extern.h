//----------------------------------------------------------------------------
//
// All function and data externs should go in this file.
//----------------------------------------------------------------------------

#ifndef	_EXTERN_H_
#define	_EXTERN_H_

//----------------------------------------------------------------------------
//>>>>	[DATA.C]

//mouse pointers 
extern	SBYTE*					pointer_data;
extern	SBYTE*					end_pointer_data;
extern	struct	TbSprite  		*pointer;
extern	struct	TbSprite  		*end_pointers;

//internal game sprites
extern	SBYTE*					game_sprite_data;
extern	SBYTE*					end_game_sprite_data;
extern	struct	TbSprite 		*game_sprite;
extern	struct	TbSprite 		*end_game_sprites;

//all fonts
extern	SBYTE*					font_data[8];
extern	SBYTE*					end_font_data[8];
extern	struct	TbSprite 		*font[8];
extern	struct	TbSprite 		*end_fonts[8];
extern	struct	TbSprite 		*userfont;
				
//game palette
extern	UBYTE					*palette;

// Global program control flags
extern	UWORD					flow_control_flags;

//Time structure used by 'BullfrogTime' - you may not need this.
extern	struct DosTime dos_time;

//You can get rid of these...
extern	SBYTE 					mem_string[];
extern	SBYTE 					flags_string[];
extern	SBYTE 					time_string[];
extern	SBYTE 					my_string[];
extern	SBYTE 					debug_string[];

// Action Function Stuff
extern	SBYTE					InkeyPressed;
extern	SLONG					ActionRC;

extern  class TActionTable 		act;

//----------------------------------------------------------------------------
//>>>>	[DRAW.C]
extern	SLONG					draw_game();

//----------------------------------------------------------------------------
//>>>>	[CONTROL.C]
extern	SLONG					control_process();

//----------------------------------------------------------------------------
//>>>>	[GAME.C]
extern	SLONG					game();
extern	SLONG					game_process();
extern	SLONG					game_setup();
extern	SLONG					game_reset();
extern	SLONG					game_setup_memory();
extern	SLONG					game_reset_memory();

//----------------------------------------------------------------------------
//>>>>	[HOST.C]
extern	SLONG					host_setup(void);
extern	SLONG					host_reset(void);
extern	SLONG					host_change_res(SLONG new_screen_mode);

#if defined (_DEBUG) && defined(_WINDOWS)
	extern TbEdit_DispatchTable cmds[];
#endif
//----------------------------------------------------------------------------
//>>>>	[TABLES.C]
extern	struct	TbLoadFiles		game_load_files[];
extern	struct	TbLoadFiles		mcga_load_files[];
extern	struct	TbLoadFiles		vres256_load_files[];
extern	struct	TbSetupSprite  	setup_sprites[];

//----------------------------------------------------------------------------
//>>>>	[VERSION.C]
extern	SLONG					display_copyright();

//----------------------------------------------------------------------------
#endif
