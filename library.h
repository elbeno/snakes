#ifndef	_LIBRARY_H_
#define _LIBRARY_H_

//----------------------------------------------------------------------------
//
// This file contains all macros used for calling functions in a specialised way.
// In general this is done to allow transparent resolution changing.
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// LIBRARY.
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Virtual screen system.
//----------------------------------------------------------------------------

 

// These four macros are the tools needed to implementing a virtual draw screen of 64k by 64k.

#define VirtualWidthShift	16
#define VirtualHeightShift	16

#define ActualX(x)			(((x) * lbDisplay.GraphicsScreenWidth) >> VirtualWidthShift)
#define ActualY(y)			(((y) * lbDisplay.GraphicsScreenHeight) >> VirtualHeightShift)

#define VirtualX(x)			(((x) << VirtualWidthShift) / Display.GraphicsScreenWidth)
#define VirtualY(y)			(((y) << VirtualHeightShift) / Display.GraphicsScreenHeight)

// Not all of these virtual screen macros have been tested but the principle works...

#define	CharacterWidth64k(ch)						VirtualX( (font_ptr) ? font_ptr[(ch)-31].SWidth : 0 )
#define	CharacterHeight64k(ch)						VirtualY( (font_ptr) ? font_ptr[(ch)-31].SHeight : 0 )
#define CopyScreenBox64k(src,dest,x1,y1,x2,y2,w,h)	CopyScreenBox(src, dest, ActualX(x1), ActualY(y1), ActualX(x2), ActualY(y2), ActualX(w), ActualY(h))
#define	DrawBox64k(x, y, width, height, colour)		DrawBox(ActualX(x), ActualY(y), ActualX(width), ActualY(height), colour)
#define DrawCheapText64k(x, y, text, colour)		DrawCheapText(ActualX(x), ActualY(y), text, colour)
#define DrawCircle64k(x, y, radius, colour)			DrawCircle(ActualX(x), ActualY(y), ActualX(radius), colour)
#define DrawClipAgainstSprite64k(x,y,s,x2,y2,s2)	DrawClipAgainstSprite(ActualX(x), ActualY(y), s, ActualY(x2), ActualY(y2), s2)
#define DrawLine64k(x1, y1, x2, y2, colour)			DrawLine(ActualX(x1), ActualY(y1), ActualX(x2), ActualY(y2), colour)
#define DrawOneColourSprite64k(x,y,sprite,colour)	DrawOneColourSprite(ActualX(x), ActualY(y), sprite, colour)
#define DrawPixel64k(x, y, colour)					DrawPixel(ActualX(x), ActualY(y), colour)
#define DrawRegionOfSprite64k(x,y,sprite,reg_lim)	DrawRegionOfSprite(ActualX(x), ActualY(y), sprite, reg_lim)
#define DrawRemapSprite64k(x,y,sprite,remap_table)	DrawRemapSprite(ActualX(x), ActualY(y), sprite, remap_table)
#define DrawScaleSprite64k(x, y, sprite, scale)		DrawScaleSprite(ActualX(x), ActualY(y), sprite, scale)
#define DrawSprite64k(x, y, sprite)					DrawSprite(ActualX(x), ActualY(y), sprite)
#define	DrawText64k(x, y, string)					DrawText(ActualX(x), ActualY(y), string)
#define DrawTriangle64k(x1,y1,x2,y2,x3,y3,colour)	DrawTriangle(ActualX(x1), ActualY(y1), ActualX(x2), ActualY(y2), ActualX(x3), ActualY(y3), colour)
#define	SetGraphicsWindow64k(x, y, width, height)	LbScreenSetGraphicsWindow(ActualX(x), ActualY(y), ActualX(width), ActualY(height))
#define SetMousePosition64k(x, y)					LbMouseSetMousePosition(ActualX(x), ActualY(y))
#define	SetMouseWindow64k(x, y, width, height)		LbMouseSetWindow(ActualX(x), ActualY(y), ActualX(width), ActualY(height))
#define	SetTextClipWindow64k(x, y, width, height)	SetTextClipWindow(ActualX(x), ActualY(y), ActualX(width), ActualY(height))
#define	SetTextJustifyWindow64k(x, y, width)		SetTextJustifyWindow(ActualX(x), ActualY(y), ActualX(width))
#define	SetTextWindow64k(x, y, width, height)		LbTextSetWindow(ActualX(x), ActualY(y), ActualX(width), ActualY(height))
#define StringHeight64k(string)						VirtualY( StringHeight(string) )
#define StringWidth64k(string)						VirtualX( StringWidth(string) )
#define SwapScreensBox64k(src,x1,y1,x2,y2,w,h)		SwapScreensBox(src, ActualX(x1), ActualY(y1), ActualX(x2), ActualY(y2), ActualX(w), ActualY(h))
#define SwapScreensBoxClear64k(s,x1,y1,x2,y2,w,h,c)	SwapScreensBoxClear(src, ActualX(x1), ActualY(y1), ActualX(x2), ActualY(y2), ActualX(w), ActualY(h), c)
#define WordWidth64k(string)						VirtualX( WordWidth(string) )

//----------------------------------------------------------------------------
// Generay Library.
//----------------------------------------------------------------------------

//#define	ClearWorkScreen(colour)						ClearScreen(Display.WScreen, Display.GraphicsScreenHeight, colour)
#define	CopyFullScreen(source, dest)				CopyScreen(source, dest, Display.GraphicsScreenHeight)
#define	FadePaletteOut()							FadePalette(0, 16, FADE_CLOSED)
#define	FadePaletteIn(to_palette)					FadePalette(to_palette, 32, FADE_CLOSED)
#define SubmitAndClearWorkScreen(colour)			SwapScreens(Dipslay.WScreen, Display.GraphicsScreenHeight, colour)
//#define SubmitWorkScreen()							SwapScreens(Display.WScreen, Display.GraphicsScreenHeight)

//----------------------------------------------------------------------------
// LOCAL.
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

#endif
