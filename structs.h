//----------------------------------------------------------------------------
//
// All structure declerations should go in this file.
//----------------------------------------------------------------------------

#ifndef	_STRUCTS_H_
#define	_STRUCTS_H_

//----------------------------------------------------------------------------


// These may be useful..

struct	Coord3D
{
	SWORD				Xpos;
	SWORD				Ypos;
	SWORD				Zpos;
};

struct	Coord2D
{
	SWORD				Xpos;
	SWORD				Ypos;
};

struct	TActionEntry
{
	SBYTE	Mode;
	SBYTE	Inkey;
	CBYTE	*KeyString;
	CBYTE	*Description;
	SLONG	(*Function)(VOID);
};

class TActionTable
{
	public:
	
	void			check_input( void);
	void			do_action( void);
	void			draw_table( void);
	void			msg( char *format, ...);
	
	private:
	
	TActionEntry	*CurrentAction;
	TActionEntry	*NextAction;
	TActionEntry	*OverAction;
	char			msg_text[512];
};

//----------------------------------------------------------------------------

#endif

//----------------------------------------------------------------------------
