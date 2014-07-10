// player.c

#include "game.h"

ULONG	number_of_players;

CBYTE	namebuf[16][128];

CBYTE	*key_names[] =
{
	0,
	"ESCAPE",
	"1","2","3","4","5","6","7","8","9","0","-","=",
	"BACKSPACE",
	"TAB",
	"Q","W","E","R","T","Y","U","I","O","P","[","]",
	"RETURN",
	"LEFT CTRL",
	"A","S","D","F","G","H","J","K","L",";","\'","`",
	"LEFT SHIFT",
	"#","Z","X","C","V","B","N","M",",",".","/",
	"RIGHT SHIFT","KP *",
	"LEFT ALT",
	"SPACE",
	"CAPSLOCK",
	"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10",
#ifdef _WINDOWS			// windows weirdness
	"PAUSE",
#else
	"NUMLOCK",
#endif
	"SCRLOCK",
	"KP 7","KP 8","KP 9",
	"KP -","KP 4","KP 5","KP 6",
	"KP +","KP 1","KP 2","KP 3",
	"KP 0","KP .",
	0,0,			// unknown/unused
	"\\","F11","F12",
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,
	0,0,0,								// unknown/unused
	"ENTER",
	"RIGHT CTRL",
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0,
	0,0,0,0,0, 0,0,
	"KP /",
	0,
	"PRINT SCR",
	"RIGHT ALT",
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	"HOME",
	"UP",
	"PGUP",0,
	"LEFT",0,
	"RIGHT",0,
	"END",
	"DOWN",
	"PGDN",
	"INSERT",
	"DELETE"
};

void	init_players(void)
{
	ULONG	i;
	ULONG	len;
	CBYTE	str[128];
	UBYTE	asc;

	LbScreenClear(0);
	number_of_players = 0;
	while (!number_of_players)
	{
		sprintf(str,"How many players (1-8)?");
		DrawCheapText(4,4,str,WHITE);
		LbScreenSwap();
		if (Inkey >= KB_1 && Inkey <= KB_8)
		{
			number_of_players = Inkey-KB_1+1;
			sprintf(str,"How many players (1-8)? %d",number_of_players);
			DrawCheapText(4,4,str,WHITE);
			LbScreenSwap();
		}
		Inkey = 0;
	}

	for (i=0; i<number_of_players; i++)
	{		
		create_snake(i);
		snakes[i].Length = 5;
		snakes[i].Name = namebuf[i];
		namebuf[i][0] = 0;
		len = 0;
		sprintf(str,"Player %d name: %s",i+1,namebuf[i]);
		DrawCheapText(4,14+30*i,str,WHITE);
		LbScreenSwap();
		while (Inkey != KB_RETURN)
		{
			if(KeyOn[KB_BACKSPACE] && len>0)
			{
				KeyOn[KB_BACKSPACE] = 0;
				namebuf[i][--len]=0;
				DrawBox(4+56+(len+1)*4,14+30*i,4,5,0);
			}
			else
			{
				if (!(Inkey&0x80))
				{
					asc = InkeyToAsciiShift[Inkey];
					if (asc >= 32 && asc <= 127 && len < 128)
					{
						namebuf[i][len++] = asc;
						namebuf[i][len] = 0;
					}
				}
			}
			if (Inkey != KB_RETURN)
				Inkey = 0;
			sprintf(str,"Player %d name: %s ",i+1,namebuf[i]);
			DrawCheapText(4,14+30*i,str,WHITE);
			LbScreenSwap();
		}
		Inkey = 0;

		sprintf(str,"Player %d left: ",i+1);
		DrawCheapText(4,24+30*i,str,WHITE);
		LbScreenSwap();
		while (!snakes[i].Left)
		{
			while (!Inkey && !Display.LeftButton && !Display.RightButton && !Display.MiddleButton);
			if (Display.LeftButton)
			{
				Display.LeftButton = 0;
				snakes[i].Left = -1;
				sprintf(str,"Player %d left:  Left Button",i+1);
			}
			else if (Display.RightButton)
			{
				Display.RightButton = 0;
				snakes[i].Left = -2;
				sprintf(str,"Player %d left:  Right Button",i+1);
			}
			else if (Display.MiddleButton)
			{
				Display.MiddleButton = 0;
				snakes[i].Left = -3;
				sprintf(str,"Player %d left:  Middle Button",i+1);
			}
			else
			{
				if (!(Inkey&0x80))
				{
					if (lbExtendedKeyPress)
						Inkey |= 0x80;
					snakes[i].Left = Inkey;
					sprintf(str,"Player %d left:  %s",i+1,key_names[Inkey]);
				}
				Inkey = 0;
			}
		}
		DrawCheapText(4,24+30*i,str,WHITE);
		LbScreenSwap();		

		sprintf(str,"Player %d right: ",i+1);
		DrawCheapText(4,34+30*i,str,WHITE);
		LbScreenSwap();
		while (!snakes[i].Right)
		{
			while (!Inkey && !Display.LeftButton && !Display.RightButton && !Display.MiddleButton);
			if (Display.LeftButton)
			{
				Display.LeftButton = 0;
				snakes[i].Right = -1;
				sprintf(str,"Player %d right: Left Button",i+1);
			}
			else if (Display.RightButton)
			{
				Display.RightButton = 0;
				snakes[i].Right = -2;
				sprintf(str,"Player %d right: Right Button",i+1);
			}
			else if (Display.MiddleButton)
			{
				Display.MiddleButton = 0;
				snakes[i].Right = -3;
				sprintf(str,"Player %d right: Middle Button",i+1);
			}
			else
			{
				if (!(Inkey&0x80))
				{
					if (lbExtendedKeyPress)
						Inkey |= 0x80;
					snakes[i].Right = Inkey;
					sprintf(str,"Player %d right: %s",i+1,key_names[Inkey]);
				}
				Inkey = 0;
			}
		}
		DrawCheapText(4,34+30*i,str,WHITE);
		LbScreenSwap();
	 	KeyOn[snakes[i].Left] = KeyOn[snakes[i].Right] = 0;
	}
	LbScreenClear(0);
}
