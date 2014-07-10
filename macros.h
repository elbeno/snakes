//----------------------------------------------------------------------------
//
// All macros should go in this file.
//----------------------------------------------------------------------------

#ifndef	_MACROS_H_			
#define	_MACROS_H_

//----------------------------------------------------------------------------
// Here are some standard macros.
//----------------------------------------------------------------------------

// Sets the system colour 0. As the video card takes care of the process it can be used as a crude bench mark for your code.
// Call SET0 with different values at different points in your code and see how wide the colour bands are.
void SET0(UBYTE,UBYTE,UBYTE);
#pragma	aux	SET0 = \
		"mov	dx,03c8h	"\
		"xor	al,al		"\
		"out	dx,al		"\
		"mov	dl,0c9h		"\
		"mov	al,cl		"\
		"out	dx,al		"\
		"mov	al,ch		"\
		"out	dx,al		"\
		"mov	al,bl		"\
		"out	dx,al		"\
		parm [cl] [ch] [bl]\
		modify [ax dx];

//Byte and Word Manipulation little endian (PC) machines..
#define		HBYTE(number)				(*((UBYTE *)((ULONG)(&(number))+1)))	//__watcomc__ only
#define		HWORD(number)				(*((UWORD *)((ULONG)(&(number))+2)))	//__watcomc__ only
#define		LBYTE(number)				(*((UBYTE *)((ULONG)(&(number)))))		//__watcomc__ only
#define		LWORD(number)				(*((UWORD *)((ULONG)(&(number)))))		//__watcomc__ only

//Exceeding variables
#define		EXCEED(number,lex,hex)		if (number < lex) number=lex; if (number > hex) number=hex 
#define		EXCEED_WRAP(number,lex,hex)	if (number < lex) number=hex; if (number > hex) number=lex 

//average two numbers ..
#define		AVERAGE(dx,dy)				((dx+dy)/2)

//convert real degrees to game degrees..
#define		DEGREES(deg)				(((deg)*NUMBER_OF_ANGLES)/360)

//fractions 
#define		FRACTION(number,num1,num2)	(((number)*(num1))/(num2))

//percentage 0 -> 100
#define		PERCENTAGE(number,per)		FRACTION(number,per,100)

//random routines
#define		RANDOM(mod,seed)			(SLONG)(((seed)=((seed)*9377)+9439)%((ULONG)(mod)))
#define		RANDOM_SIGN(seed)			(SLONG)(((RANDOM(157,(seed))/79)*2)-1)				//-1,+1
#define		RANDOM_SIGN_OR_0(seed)		(SLONG)((RANDOM(157,(seed))/53)-1)					//-1,0,+1

//create coordinate structe
#define		SET_COORDINATES(c,x,y,z)	c.Xpos=(x); c.Ypos=(y); c.Zpos=(z)

//sign of a number
#define		SIGN(number)				(((number) == 0) ? 0 : (((number) > 0) ? 1 : -1))

//change the sign
#define		SWAP_SIGN(number)			((number) = -(number))

//number * number
#define		SQUARED(number)				((number)*(number))

//square root of number (number should be a ULONG)
#define		SQUARE_ROOT(number)			(SqrL(number))

//----------------------------------------------------------------------------
// Your macros...
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------

#endif

//----------------------------------------------------------------------------
